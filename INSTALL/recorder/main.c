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

static int g_quit = 0; /* Force exit or quit (ctrl+c) */

static void forceQuit_handler(int i) {
    g_quit = -1;
}

/*
 * ==== Simultaneous 8-channel analog input signal AIFF recorder ====
 */

int main (int argc, char** argv) {
    
    int ret = EXIT_SUCCESS;
    int auto_trig = AUTO_TRIG;
    int samples_per_file = SAMPLES_PER_FILE;
    int num_buffers = NUM_BUFFS;
    int num_channels = NUM_CHANNELS;
    int duration_days = DURATION_DAYS;
    int night_cycle = NIGHT_CYCLE;
    double lat = DEFAULT_LATITUDE;
    double lon = DEFAULT_LONGITUDE;
    long safety_margin = SAFETY_MARGIN;
    
    struct circ_buffer buffer_object = {.sample_rate = SAMPLE_RATE, 
                                        .vbuf = NULL};
    
    dt78xx_clk_config_t clk = {.ext_clk=0, /* Internal clock */
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
    int ch_code; /* 8 bit binary; channel on := 1, channel off := 0 */

    aio_context_t ioctx = 0;
    struct iocb **in_iocb = NULL;
    
    //Specifying the expected options
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
                samples_per_file = strtoul(optarg, NULL, 10);
                if (samples_per_file <= 0) {
                    printf(g_usage, argv[0]);
                    return (EXIT_FAILURE);
                }
                break;
            case 'c':
                clk.clk_freq = atof(optarg);
                buffer_object.sample_rate = clk.clk_freq;
                if ((clk.clk_freq < CLK_MIN_HZ) || (clk.clk_freq > CLK_MAX_HZ)) {
                    fprintf(stderr, "Sample must be %.3f - %.3f\n", 
                            CLK_MIN_HZ, CLK_MAX_HZ);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'd' :
                duration_days = atoi(optarg);
                break; 
            case 'b' :
                num_buffers = atoi(optarg);
                if (num_buffers <= 0) {
                    fprintf(stderr, "Number of buffers must be positive and non-zero\n");
                    exit(EXIT_FAILURE);
                }
                if (num_buffers > MAX_AIO_EVENTS) {
                    fprintf(stderr, "Max number of buffers is %d\n", MAX_AIO_EVENTS);
                    exit(EXIT_FAILURE);
                }
                break;
           case 't' :
                auto_trig = 0;
                break;
            case 'i' :
                ch_code = atoi(optarg);
                int d;
                num_channels = 0;
                for (d = 0; d < 8; d++) {
                    int digit = ch_code % 10;
                    ain[7-d] = digit;
                    if (digit) num_channels++;
                    ch_code /= 10;
                }
                break;
            case 'm' :
                safety_margin = atol(optarg);
                break;
            case 'n' :
                night_cycle = atoi(optarg);
                break;
            case 'p' :
                lat = atof(optarg);
                break;
            case 'l' :
                lon = atof(optarg);
                break;
            default :
                printf(g_usage, argv[0]);
                return EXIT_FAILURE;
        }
    }
         
#if (defined STATUS_LED) 
    g_led_count = (uint32_t)(clk.clk_freq / samples_per_file);
    g_led_count /= 2;
#endif   
    
    /* Creates mask for enabled channels */
    const int channels_per_file = num_channels; /* aka Block Size */
    chan_mask_t chan_mask = 0x0;
    int *ch_on = malloc(sizeof(int)*channels_per_file);
    createChanMask(ain, ch_on, &chan_mask);
   
    int samples_per_chan = SAMPLES_PER_CHAN;
    checkFatal(SAMPLES_PER_FILE * NUM_BUFFS);
    
    dt78xx_ain_config_t ain_cfg[8] = {};
    configChan(ain_cfg);
    
    checkID(argc, argv);
    checkRate(buffer_object, argv);
    
    int in_strm;
    openStream(&in_strm);
    int a_in;
    openAIN(&in_strm, &a_in);
            
    //Set up AIO context
    if (io_setup(MAX_AIO_EVENTS, &ioctx))
    {
        fprintf(stderr, "io_setup ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }

    /* Set up ctrl-c handler to terminate process gracefully */
    sigaction_register(SIGINT, forceQuit_handler);

    /* Configure sampling rate. The actual rate is returned on success */
    clk.clk_freq = buffer_object.sample_rate;
    if (ioctl(in_strm, IOCTL_SAMPLE_CLK_SET, &clk)) {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    buffer_object.sample_rate = clk.clk_freq; /* Actual rate */
       
    dt78xx_trig_config_t trig_cfg_ai[8] = {};
    initTrig(trig_cfg_ai);
    
    /* Configure for software trigger for all enabled channels */
    fprintf(stdout, "Configuring trigger...\n");
    int i;
    for (i = 0; i < channels_per_file; i++) {
        int chan = ch_on[i];
        if (configTrig(&in_strm, trig_cfg_ai[chan], auto_trig)) {
            fprintf(stderr, "IOCTL_START_TRIG_CFG_SET ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        }
    }
    
    /* Write channel mask for selected/enabled channels */
    if (ioctl(in_strm, IOCTL_CHAN_MASK_SET, &chan_mask)) {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    /* Channel gain, coupling and current source */
    for (i = 0; i < channels_per_file; i++) {
        int ain_i = ch_on[i];
        if (ioctl(a_in, IOCTL_AIN_CFG_SET, &ain_cfg[ain_i])) {
            fprintf(stderr, "IOCTL_AIN%d_CFG_SET ERROR %d \"%s\"\n", 
                    ain_i, errno, strerror(errno));
            goto _exit;
        }
    }
    
    /* Size/allocate a buffer to hold the specified samples for each channel */
    /* where: buflen = 16*samples_per_chan*channels_per_file/8 */ 
    /* (in bytes, assuming samples_per_chan multiple of 32) */
    int buflen = aio_buff_size(samples_per_chan, chan_mask, 
                                &buffer_object.num_samples);
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples for %d channels...\n", 
                    clk.clk_freq, buffer_object.num_samples, channels_per_file);
    
    /* Create and initialise AIO stream buffers/structures */
    fprintf(stdout, "Initialising...\n");
    in_iocb = alloc_iocb_buffers(in_strm, 0, num_buffers, buflen);
    if (!in_iocb) {
        fprintf(stderr, "alloc_queue_buffers ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }

    /* Submit the buffers */
    fprintf(stdout, "\nCommencing buffer...\n");
    if (io_submit(ioctx, num_buffers, in_iocb) != num_buffers)
    {
        fprintf(stderr, "ERROR aio_start\n");
        goto _exit;
    }
    fprintf(stdout, "Clock %.3f Queued %d buffers each %d samples (%d bytes)\n", 
                        clk.clk_freq, num_buffers, samples_per_file, buflen);

    /* ARM */
    if ((ioctl(in_strm, IOCTL_ARM_SUBSYS, 0))) {
        fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }

    /* Issue a software start; this is redundant if trigger source is */
    /* threshold trigger or external trigger */
    if ((ioctl(in_strm, IOCTL_START_SUBSYS, 0))) {
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
    
    /* Allocate a circular/ring buffer/queue to hold the recorded values in Volts */
    const int vbuf_len = samples_per_chan * channels_per_file;
    buffer_object.vbuf = RingBuf_new(sizeof(float), vbuf_len);
    if (!buffer_object.vbuf) {
        fprintf(stderr, "ERROR buffer_object.vbuf\n");
        goto _exit;
    }
    
    /* Wait for user input to start or abort */
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
    long *sunsets = malloc(sizeof(long)*duration_days);
    long *sunrises = malloc(sizeof(long)*duration_days);
    calcSunUpDown(sunsets, sunrises, duration_days, safety_margin, lon, lat, night_cycle);
    
    int elapsed_days = 0; /* Resets counter */
    ret = 0;
    int file_num = 0; /* Diagnostic/debugging file counter */
    
    /* Infinite loop until aborted by ctrl-C or q/Q enetered */
    fprintf(stdout, "Press q or Q or ctrl-C to exit\n"); 
    while (!g_quit && duration_days > elapsed_days) {
        long present = getPresentTime();
        long sunset = sunsets[elapsed_days];
        long sunrise = sunrises[elapsed_days];
        int night = 0;

        /* If after dusk and before dawn (entering night) */
        while (!g_quit && (present < sunrise && present >= sunset)) {           
            if (g_quit) {
                goto _exit;
            } else {
                night = 1;
            }

            struct iocb *done[1];
            struct io_event events[1];  /* For io_getevents() */
            
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
            char file_path[LEN];
            timestamp(file_path, argv, PATH_TO_STORAGE);

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
                } else if (cb->aio_fildes == in_strm) {
#ifdef BUFF_DONE_LED
                    dt78xx_led_t led;
                    led.mask = (1<<BUFF_DONE_LED);    
                    led.state = (1<<BUFF_DONE_LED);
                    ioctl(in_strm, IOCTL_LED_SET, &led);
#endif 
                    void *buf = (void *)((__u32)cb->aio_buf);


                    /* Write acquired data to the specified .aiff output file */
                    AIFF_Ref file = malloc(sizeof(AIFF_Ref));

                    /* Sets AIFF file metadata */
                    setMetadata(file, lon, lat, sunset, sunrise);

                    file = AIFF_OpenFile(file_path, F_WRONLY);
                    if (file) {
                        file_num += 1;
                        fprintf(stdout, "Opened .aiff file...\n");

                        /* Sets formatting */
                        if (!AIFF_SetAudioFormat(file, channels_per_file, 
                                                (double) buffer_object.sample_rate, 
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
                    if (!writeBuffer(file, buffer_object, channels_per_file, 
                                    num_buffers, ch_on, buf, ain_cfg)) {
                        fprintf(stderr, "ERROR writing .aiff file");
                        goto _exit;
                    }

                    if (!AIFF_EndWritingSamples(file)) {
                        fprintf(stderr, "ERROR ending writing .aiff file");
                        goto _exit;
                    } else {
                        fprintf(stdout, "%do .aiff file written\n", file_num);
                    }
                    
                    /* Stops writing */
                    if (AIFF_CloseFile(file)) {
                        fprintf(stdout, "Closed file...\n");
                        fprintf(stdout, "File at %s\n", file_path);
                    } else {
                        fprintf(stderr, "ERROR audio_file_close");
                        goto _exit;
                    }


                    /* Queues the buffer to input stream */
                    cb->aio_fildes = in_strm;
                    cb->aio_lio_opcode = IOCB_CMD_PWRITE;
                    
#ifdef BUFF_DONE_LED
                    led.state = 0;
                    ioctl(in_strm, IOCTL_LED_SET, &led);
#endif    
                } else {
                    /* Queues the buffer back to input stream */
                    cb->aio_fildes = in_strm;
                    cb->aio_lio_opcode = IOCB_CMD_PREAD;
                }
#ifdef STATUS_LED
                updateStatusLed(in_strm, 0);
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
        if (night) elapsed_days++; /* If after dawn (leaving night), 1 day elapsed */
    }

/* Exit protocol and procedure */
_exit :
    fprintf(stdout,"\n");
    if (a_in > 0)
        close(a_in);
    if (in_strm > 0)
        ioctl(in_strm, IOCTL_STOP_SUBSYS, 0); 
    updateStatusLed(in_strm, num_buffers);
    if (ioctx)
       io_destroy(ioctx);
    if (in_strm > 0)
        close(in_strm);
    kbfini(); /* see dt78xx_misc.h */
    return (ret);
}

