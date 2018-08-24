/* 
 * @file main.c
 * @brief This is a custom application for DT7816 autonomous asynchronous I/O sampling
 * that configures the board's analog inputs. The sampled data is read 
 * asynchronously from the input stream and written to a AIFF file. See:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
 * for additional details on (a)synchronous I/O.
 * 
 * (c) Aidan Johnson (johnsj96@uw.edu)
 * 12 July 2018
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * 
 * ============================================================================
 * Usage :
 *	See usage() below
 */

/* Contains helper functions, global constants (macros), and required libraries */
#include "recorder_helpers.h" 

/*
 * ==== Signal handler for ctrl-c prevents the abrupt termination of processes ====
 */

static int forceQuit = 0; // Force exit or quit (ctrl+c)

static void forceQuitHandler(int i) {
    forceQuit = -1;
}

/*
 * ==== Simultaneous 8-channel analog input signal AIFF recorder ====
 */

int main (int argc, char** argv) {
    
    int ret = EXIT_SUCCESS;
    int autoTrigger = AUTO_TRIG;
    int fileSamples = SAMPLES_PER_FILE;
    int chanSamples = SAMPLES_PER_CHAN;
    int numBuffers = NUM_BUFFS;
    int numChannels = NUM_CHANNELS;
    int durationDays = DURATION_DAYS;
    int nightCycle = NIGHT_CYCLE;
    double lat = DEFAULT_LATITUDE;
    double lon = DEFAULT_LONGITUDE;
    long safetyMargin = SAFETY_MARGIN;
    
    struct circ_buffer ringBuffer = {.sample_rate = SAMPLE_RATE, 
                                        .vbuf = NULL};
    
    dt78xx_clk_config_t clk = {.ext_clk=0, // Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
    int ch_code; // 8 bit binary; channel on := 1, channel off := 0

    aio_context_t ioctx = 0; // Input/Output (I/O) context 
    struct iocb **iocbs = NULL; // I/O control blocks pointers
    
    /* Specifying the expected options */
    static struct option long_options[] = {
        {"buffers",     required_argument,  0,  'b' },
        {"samples",     required_argument,  0,  's' },
        {"clk",         required_argument,  0,  'c' },
        {"trig",        required_argument,  0,  't' },
        {"dur",         required_argument,  0,  'd' },
        {"inputs",      required_argument,  0,  'i' },
        {"margin",      required_argument,  0,  'm' },
        {"night",       required_argument,  0,  'n' },
        {"phi",         required_argument,  0,  'p' },
        {"lambda",      required_argument,  0,  'l' },
        {0,             0,                  0,   0  }
    };
    int opt = 0;
    while ((opt = getopt_long(argc, argv, "s:c:d:b:t:i:m:n:p:l:", long_options, NULL)) != -1) {
        switch (opt) {
            case 's':
                fileSamples = strtoul(optarg, NULL, 10);
                if (fileSamples <= 0) {
                    printf(usage, argv[0]);
                    return (EXIT_FAILURE);
                }
                break;
            case 'c':
                clk.clk_freq = atof(optarg);
                ringBuffer.sample_rate = clk.clk_freq;
                if ((clk.clk_freq < CLK_MIN_HZ) || (clk.clk_freq > CLK_MAX_HZ)) {
                    fprintf(stderr, "Sample must be %.3f - %.3f\n", 
                            CLK_MIN_HZ, CLK_MAX_HZ);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'd' :
                durationDays = atoi(optarg);
                break; 
            case 'b' :
                numBuffers = atoi(optarg);
                if (numBuffers <= 0) {
                    fprintf(stderr, "Number of buffers must be positive and non-zero\n");
                    exit(EXIT_FAILURE);
                }
                if (numBuffers > MAX_AIO_EVENTS) {
                    fprintf(stderr, "Max number of buffers is %d\n", MAX_AIO_EVENTS);
                    exit(EXIT_FAILURE);
                }
                break;
           case 't' :
                autoTrigger = 0;
                break;
            case 'i' :
                ch_code = atoi(optarg);
                int d;
                numChannels = 0;
                for (d = 0; d < 8; d++) {
                    int digit = ch_code % 10;
                    ain[7-d] = digit;
                    if (digit) numChannels++;
                    ch_code /= 10;
                }
                break;
            case 'm' :
                safetyMargin = atol(optarg);
                break;
            case 'n' :
                nightCycle = atoi(optarg);
                break;
            case 'p' :
                lat = atof(optarg);
                break;
            case 'l' :
                lon = atof(optarg);
                break;
            default :
                printf(usage, argv[0]);
                return EXIT_FAILURE;
        }
    }
         
#ifdef STATUS_LED
    g_led_count = (uint32_t)(clk.clk_freq / fileSamples);
    g_led_count /= 2;
#endif   
    
    /* Creates mask for enabled channels */
    const int fileChannels = numChannels; // Block size
    chan_mask_t chanMask = 0x0;
    int *chOn = malloc(sizeof(int)*fileChannels);
    createChanMask(ain, chOn, &chanMask);
   
    /* First fatal error check: bit restriction */
    checkFatal(fileSamples, numBuffers); // See recorder_helpers.h
    
    /* Channel configuration */
    dt78xx_ain_config_t ainConfig[8] = {}; // Analog input configuration array
    configChan(ainConfig);
    
    /* Second fatal error check: channel identity and sampling rate */
    checkID(argc, argv);
    checkRate(ringBuffer, argv);
    
    /* Third fatal error check: opening the input stream */
    int inStream;
    openStream(&inStream);
    
    /* Fourth fatal error check: opening analog input */
    int aInput;
    openAIN(&inStream, &aInput);
    
    /* Passes all fatal error checks; proceeds to setup.
     * Graduates to graceful exit protocol. 
     */

    /* Opens asynchronous I/O (AIO) context */
    if (io_setup(MAX_AIO_EVENTS, &ioctx)) {
        fprintf(stderr, "io_setup ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }

    /* Sets up force quit handler to terminate process gracefully */
    sigaction_register(SIGINT, forceQuitHandler);

    /* Configures sampling rate; actual rate is returned on success */
    clk.clk_freq = ringBuffer.sample_rate;
    if (ioctl(inStream, IOCTL_SAMPLE_CLK_SET, &clk)) {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    ringBuffer.sample_rate = clk.clk_freq; // Actual sampling frequency
       
    dt78xx_trig_config_t ainTrigConfig[8] = {}; // Array of analog input configurations
    initTrig(ainTrigConfig); // Initialises trigger
    
    /* Configures for software trigger for all enabled channels */
    fprintf(stdout, "Configuring trigger...\n");
    int i;
    for (i = 0; i < fileChannels; i++) {
        int chan = chOn[i];
        if (configTrig(&inStream, ainTrigConfig[chan], autoTrigger)) {
            fprintf(stderr, "IOCTL_START_TRIG_CFG_SET ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        }
    }
    
    /* Writes channel mask for selected/enabled channels */
    if (ioctl(inStream, IOCTL_CHAN_MASK_SET, &chanMask)) {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    /* Sets channel gain, coupling and current source */
    for (i = 0; i < fileChannels; i++) {
        int ainIndex = chOn[i];
        if (ioctl(aInput, IOCTL_AIN_CFG_SET, &ainConfig[ainIndex])) {
            fprintf(stderr, "IOCTL_AIN%d_CFG_SET ERROR %d \"%s\"\n", 
                    ainIndex, errno, strerror(errno));
            goto _exit;
        }
    }
    
    /* Size/allocate a buffer to hold the specified samples for each channel
     * where: bufLen = 16*chanSamples*fileChannels/8 (in bytes, assuming 
     * chanSamples multiple of 32)
     */
    int bufLen = aio_buff_size(chanSamples, chanMask, 
                                &ringBuffer.num_samples);
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples for %d channels...\n", 
                    clk.clk_freq, ringBuffer.num_samples, fileChannels);
    
    /* Creates and initialises AIO stream buffers/structures (i.e., control blocks) */
    fprintf(stdout, "Initialising...\n");
    iocbs = alloc_iocb_buffers(inStream, 0, numBuffers, bufLen); // control block
    if (!iocbs) {
        fprintf(stderr, "alloc_queue_buffers ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }

    /* Submits I/O requests to the AIO context */
    fprintf(stdout, "\nCommencing buffer...\n");
    if (io_submit(ioctx, numBuffers, iocbs) != numBuffers)
    {
        fprintf(stderr, "ERROR aio_start\n");
        goto _exit;
    }
    fprintf(stdout, "Clock %.3f Queued %d buffers each %d samples (%d bytes)\n", 
                        clk.clk_freq, numBuffers, fileSamples, bufLen);

    /* Arms the input stream */
    if ((ioctl(inStream, IOCTL_ARM_SUBSYS, 0))) {
        fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }

    /* Issues a software start for continuous input operation; this is 
     * redundant if trigger source is threshold or externally triggered 
     */
    if ((ioctl(inStream, IOCTL_START_SUBSYS, 0))) {
        fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }

#ifdef FILE_DUMP    
    int buff_write = 0;
#endif   
    struct timespec tmo;
    tmo.tv_sec = WAIT_MS/1000;
    tmo.tv_nsec = (WAIT_MS - tmo.tv_sec*1000)*1000;
    
    /* Allocates a circular/ring buffer/queue to hold the recorded values in Volts */
    const int vBufferLen = chanSamples * fileChannels;
    ringBuffer.vbuf = RingBuf_new(sizeof(float), vBufferLen);
    if (!ringBuffer.vbuf) {
        fprintf(stderr, "ERROR ringBuffer.vbuf\n");
        goto _exit;
    }
    
    /* Waits for user input to start or abort */
    fprintf(stdout,"Press s to start, any other key to quit\n");
    while (1) {
        int c = getchar();
        if (c == 's') {
            break;
        }
        goto _exit;
    }
    
    /* Calculates sunset (sunsclipse) and sunrise (sunsight) times based on: */
    /* (1) Date and (2) Latitude and Longitude coordinates */
    long *sunsets = malloc(sizeof(long)*durationDays);
    long *sunrises = malloc(sizeof(long)*durationDays);
    calcSunUpDown(sunsets, sunrises, durationDays, safetyMargin, lon, lat, nightCycle);
    
    int elapsedDays = 0; // Resets day counter
    ret = 0;
    int fileNum = 0; // Diagnostic/debugging file counter
    
    /* Infinite loop until aborted by ctrl-C or q/Q entered */
    fprintf(stdout, "Press q or Q or ctrl-C to exit\n"); 
    while (!forceQuit && durationDays > elapsedDays) {
        long present = getPresentTime();
        long sunset = sunsets[elapsedDays];
        long sunrise = sunrises[elapsedDays];
        int night = 0;

        /* If after dusk and before dawn (entering night) */
        while (!forceQuit && (present < sunrise && present >= sunset)) {           
            if (forceQuit) {
                goto _exit;
            } else {
                night = 1;
            }

            struct iocb *done[1];
            struct io_event events[1];  // For io_getevents()
            
            /* If key pressed */
            if(kbhit()) {
                char c = fgetc(stdin);
#ifdef FILE_DUMP    
                if (c=='w')
                    buff_write = 1;
#endif            
                if ((c=='q')||(c=='Q')) /* Quits */
                    break;
                fflush(stdin);
            }
        
            /* Gets time of first sample recording for timestamp */
            char filePath[LEN];
            timestamp(filePath, argv, PATH_TO_STORAGE);

            /* Waits for buffer completion */
            int ret = io_getevents(ioctx, 1, ARRAY_SIZE(events), events, &tmo);
            for (i=0; i < ret; ++i) {
                struct iocb *cb = (struct iocb *)events[i].obj;
                if (events[i].res2) {
                    fprintf(stdout, "aio_data %llx evt_data %llx %llx %llx\n", 
                        cb->aio_data,  events[i].data, events[i].res, 
                            events[i].res2);
                    errno = events[i].res2;
                    perror("iocb");
                    break;
                } else if (cb->aio_fildes == inStream) {
#ifdef BUFF_DONE_LED
                    dt78xx_led_t led;
                    led.mask = (1<<BUFF_DONE_LED);    
                    led.state = (1<<BUFF_DONE_LED);
                    ioctl(inStream, IOCTL_LED_SET, &led);
#endif 
                    void *buf = (void *)((__u32)cb->aio_buf);


                    /* Write acquired data to the specified .aiff output file */
                    AIFF_Ref file = malloc(sizeof(AIFF_Ref));

                    /* Sets AIFF file metadata */
                    setMetadata(file, lon, lat, sunset, sunrise);

                    file = AIFF_OpenFile(filePath, F_WRONLY);
                    if (file) {
                        fileNum += 1;
                        fprintf(stdout, "Opened .aiff file...\n");

                        /* Sets formatting */
                        if (!AIFF_SetAudioFormat(file, fileChannels, 
                                                (double) ringBuffer.sample_rate, 
                                                sizeof(float))) {
                            AIFF_CloseFile(file);
                            fprintf(stderr, "ERROR audio_format_set");
                            goto _exit;
                        }
                    } else {
                        fprintf(stderr, "ERROR audio_file_open");
                        goto _exit; 
                    }

                    if (!AIFF_StartWritingSamples(file)) {
                        fprintf(stderr, "ERROR starting writing .aiff file");
                        goto _exit;
                    }
                    
                    /* Writes buffer to intermediate circular buffer to be written to file */
                    if (!writeBuffer(file, ringBuffer, fileChannels, 
                                    numBuffers, chOn, buf, ainConfig)) {
                        fprintf(stderr, "ERROR writing .aiff file");
                        goto _exit;
                    }

                    if (!AIFF_EndWritingSamples(file)) {
                        fprintf(stderr, "ERROR ending writing .aiff file");
                        goto _exit;
                    } else {
                        fprintf(stdout, "%do .aiff file written\n", fileNum);
                    }
                    
                    /* Stops writing */
                    if (AIFF_CloseFile(file)) {
                        fprintf(stdout, "Closed file...\n");
                        fprintf(stdout, "File at %s\n", filePath);
                    } else {
                        fprintf(stderr, "ERROR audio_file_close");
                        goto _exit;
                    }


                    /* Queues the buffer to input stream */
                    cb->aio_fildes = inStream;
                    cb->aio_lio_opcode = IOCB_CMD_PWRITE;
                    
#ifdef BUFF_DONE_LED
                    led.state = 0;
                    ioctl(inStream, IOCTL_LED_SET, &led);
#endif    
                } else {
                    /* Queues the buffer back to input stream */
                    cb->aio_fildes = inStream;
                    cb->aio_lio_opcode = IOCB_CMD_PREAD;
                }
#ifdef STATUS_LED
                updateStatusLed(inStream, 0);
#endif    
                /* Re-submits the buffer */
                done[0] = cb;
                if (io_submit(ioctx, 1, done) < 1)
                {
                    fprintf(stderr, "ERROR io_submit\n");
                    ret = -EIO;
                    break;
                }
            }   
            
            present = getPresentTime(); /* Updates time for while loop check */
        }
        if (night) elapsedDays++; /* If after dawn (leaving night), 1 day elapsed */
    }

/* Exit protocol and procedure */
_exit :
    fprintf(stdout,"\n");
    if (aInput > 0)
        close(aInput);
    if (inStream > 0)
        ioctl(inStream, IOCTL_STOP_SUBSYS, 0); 
    updateStatusLed(inStream, numBuffers);
    if (ioctx)
       io_destroy(ioctx);
    if (inStream > 0)
        close(inStream);
    kbfini(); // see dt78xx_misc.h
    return (ret);
}

