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

/* Contains helper functions, global variables, macros, and required libraries */
#include "recorder_helpers.h" 

struct aio_struct *inAIO; // Asynchronous I/O  
         
int autoTrigger = AUTO_TRIG;
int fileSamples = SAMPLES_PER_FILE;
int chanSamples = SAMPLES_PER_CHAN;
int numBuffers = NUM_BUFFS;
int numChannels = NUM_CHANNELS;
int durationDays = DURATION_DAYS; // Number of days for sampling/recording
int nightCycle = NIGHT_CYCLE; // On = 1, sampling only after dusk and before dawn
double lat = DEFAULT_LATITUDE; // Latitude coordinate
double lon = DEFAULT_LONGITUDE; // Longitude coordinate
long safetyMargin = SAFETY_MARGIN; // Increases sampling duration by 2*safetyMargin (in s)

chan_mask_t chanMask; // Channel mask cached on acquisition start

int inStream = -1; // Device file handle for input stream
int aInput = -1; // Device file handle for analog input channels
int outStream = -1; // Device file handle for output stream

void **inBuffer;

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
    int opt = 0;
    int exitStatus = EXIT_SUCCESS;
    
//    struct circular_queue ping = {.sample_rate = SAMPLE_RATE, 
//                                  .buffer = NULL};
//    struct circular_queue pong = {.sample_rate = SAMPLE_RATE, 
//                                  .buffer = NULL};
        
    dt78xx_clk_config_t clk = {.ext_clk=0, // Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
    int ch_code; // 8 bit binary; channel on := 1, channel off := 0
    
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
    while ((opt = getopt_long(argc, argv, "s:c:d:b:t:i:m:n:p:l:", long_options, NULL)) != -1) {
        switch (opt) {
            case 's':
                fileSamples = strtoul(optarg, NULL, 10);
                if (fileSamples <= 0) {
                    printf(usage, argv[0]);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'c':
                clk.clk_freq = atof(optarg);
//                ping.sample_rate = clk.clk_freq;
//                pong.sample_rate = clk.clk_freq;
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
    
    /* Sets up force quit handler to terminate process gracefully */
    sigaction_register(SIGINT, forceQuitHandler);
    
    /* Creates mask for enabled channels, which has a bitwise format. */
    int *chOn = malloc(sizeof(int)*numChannels); // Array of enabled channel indices
    createChanMask(ain, chOn);
   
    /* First fatal error check: bit restriction */
    exitStatus = checkFatal(fileSamples, numBuffers); // See recorder_helpers.h
    
    /* Channel configuration */
    dt78xx_ain_config_t ainConfig[8] = {}; // Analog input configuration array
    configChan(ainConfig);
    
    /* Second fatal error check: channel identity and sampling rate */
    exitStatus = checkID(argc, argv);
//    exitStatus = checkRate(ping, argv);
//    exitStatus = checkRate(pong, argv);
    
    /* Third fatal error check: opening the input stream */
    exitStatus = openStream();
    
    /* Fourth fatal error check: opening analog input */
    exitStatus = openAIN();
    
    /* Passes all fatal error checks; proceeds to setup.
     * Graduates to graceful exit protocol. 
     */

    /* Opens asynchronous I/O (AIO) context */
    inAIO = aio_create(inStream, 0, isInAIODone, isInStreamEmpty);

    /* Configures sampling rate; actual rate is returned on success */
    if (ioctl(inStream, IOCTL_SAMPLE_CLK_SET, &clk)) {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
//    ping.sample_rate = clk.clk_freq; // Actual sampling frequency
//    pong.sample_rate = clk.clk_freq;
       
    dt78xx_trig_config_t ainTrigConfig[8] = {}; // Array of analog input configurations
    initTrig(ainTrigConfig); // Initialises trigger
    
    /* Configures for software trigger for all enabled channels */
    fprintf(stdout, "Configuring trigger...\n");
    int i;
    for (i = 0; i < numChannels; i++) {
        int chan = chOn[i];
        if (configTrig(ainTrigConfig[chan])) {
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
    for (i = 0; i < numChannels; i++) {
        int ainIndex = chOn[i];
        if (ioctl(aInput, IOCTL_AIN_CFG_SET, &ainConfig[ainIndex])) {
            fprintf(stderr, "IOCTL_AIN%d_CFG_SET ERROR %d \"%s\"\n", 
                    ainIndex, errno, strerror(errno));
            goto _exit;
        }
    }
    
    /* Size/allocate a buffer to hold the specified samples for each channel
     * where: bufLen = 16*chanSamples*numChannels/8 (in bytes, assuming 
     * chanSamples multiple of 32)
     */
    int actualSamples;
    int buffSize = aio_buff_size(chanSamples, chanMask, &actualSamples);
//    ping.num_samples = actualSamples;
//    pong.num_samples = actualSamples;
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples for %d channels...\n", 
                    clk.clk_freq, actualSamples, numChannels);
    
    /* Creates and initialises AIO stream buffers/structures */
    fprintf(stdout, "Initialising...\n");
    if ((inBuffer = aio_buff_alloc(inAIO, numBuffers, buffSize)) == NULL) {
        fprintf(stderr, "alloc_queue_buffers ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
   /* Submits AIO buffers*/ 
    if ((exitStatus = aio_start(inAIO))) {
        fprintf(stderr, "AIO start failure error");
        goto _exit;
    }

//    /* Allocates a circular/ring buffer/queue to hold the recorded values in Volts */
//    getCircularQueue(ping.buffer);
//    getCircularQueue(pong.buffer);
//    if (!ping.buffer) {
//        fprintf(stderr, "ERROR ping circular_queue buffer\n");
//        goto _exit;
//    }
//    if (!pong.buffer) {
//        fprintf(stderr, "ERROR pong circular_queue buffer\n");
//        goto _exit;
//    }
    
    /* Waits for user input to start or abort */
    fprintf(stdout,"Press s to start, any other key to quit\n");
    while (1) {
        int c = getchar();
        if (c == 's') {
            break;
        }
        goto _exit;
    }
    
//    /* Calculates timeout wait in ms */
//    const int wait = 1000 / (SAMPLE_RATE * chanSamples * numChannels);
    
    /* Calculates sunset (sunsclipse) and sunrise (sunsight) times based on: */
    /* (1) Date and (2) Latitude and Longitude coordinates */
    long *sunsets = malloc(sizeof(long)*durationDays);
    long *sunrises = malloc(sizeof(long)*durationDays);
    calcSunUpDown(sunsets, sunrises);
    
    int elapsedDays = 0; // Resets day counter
    int fileNum = 0; // Diagnostic/debugging file counter
    char filePath[LEN]; // String for output file path
    
    const int fileBuffers = 10;
    
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
            
            /* If key pressed */
            if(kbhit()) {
                char c = fgetc(stdin);        
                if ((c=='q')||(c=='Q')) /* Quits */
                    break;
                fflush(stdin);
            }

            int bufferCount = 0;

            if (bufferCount == 0) {
                /* Arms the input stream */
                if ((ioctl(inStream, IOCTL_ARM_SUBSYS, 0))) {
                    fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                          errno, strerror(errno));
                    goto _exit;
                }   
                       
                /* 
                 * Issues a software start for continuous input operation; this is 
                 * redundant if trigger source is threshold or externally triggered 
                 */
                if ((ioctl(inStream, IOCTL_START_SUBSYS, 0))) {
                    fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                            errno, strerror(errno));
                    goto _exit;
                }
                
                /* Gets time of first sample recording for timestamp */
                timestamp(filePath, argv, PATH_TO_STORAGE);
            }            

            while (!forceQuit & bufferCount < fileBuffers) {
                /* Continuous sampling of input stream begins */
    //            aio_wait(inAIO, wait); // Waits for time to fill buffer in ms
                if (aio_wait(inAIO, -1) > 0) { // Timeout when one buffer completely filled
                    ++bufferCount;
                } else {
                    break; // error
                }
            }
            
            /* Write acquired data to the specified .aiff output file */
            AIFF_Ref file = malloc(sizeof(AIFF_Ref));

            /* Sets AIFF file metadata */
            setMetadata(file, sunset, sunrise);

            file = AIFF_OpenFile(filePath, F_WRONLY);
            if (file) {
                fileNum += 1;
                fprintf(stdout, "Opened .aiff file...\n");

                /* Sets formatting */
                if (!AIFF_SetAudioFormat(file, numChannels, 
                                        (double) clk.clk_freq, 
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
                    
/******************************************************************************
 * AIO API flow diagram. API marked with * must be called only once.
 * 
 *      aio_create*
 *          |
 *          v
 *          +--<--------------------------------+
 *      aio_buff_alloc()                        |
 *          |                                   |
 *          |                                   |
 *      aio_start()                             |
 *          |                                   |
 *      aio_wait ()<-------->buffer_done_cb_t   |
 *          :                                   |
 *          :                                   |
 *      aio_wait ()<-------->buffer_done_cb_t   |
 *          :                                   |loop
 *          :                                   |
 *          |                                   |
 *      aio_stop()                              |
 *          |                                   |
 *          +-------------------------------->--+
 *          |            +----<-----+
 *          :            |          |
 *       aio_get_completed_buff     |
 *          :            |          |
 *          |            +---->-----+
 *          |
 *          |
 *          |
 *          v
 *      aio_destroy*
 */
                    
            int nBuffer;
            for (nBuffer = 0; nBuffer < numBuffers; ++nBuffer) {
                void *raw = inBuffer[nBuffer];
                int sample;
                for (sample = 0; sample < chanSamples; ++sample) {
                    if (chanMask & chan_mask_ain0) {
                        raw2volts(*(int16_t *)raw, ainConfig[0].gain);
                        raw += sizeof(int16_t);
                    }
                    if (chanMask & chan_mask_ain1) {
                        raw2volts(*(int16_t *)raw, ainConfig[1].gain);
                        raw += sizeof(int16_t);   
                    }
                    if (chanMask & chan_mask_ain2) {
                        raw2volts(*(int16_t *)raw, ainConfig[2].gain);
                        raw += sizeof(int16_t);   
                    }
                    if (chanMask & chan_mask_ain3) {
                        raw2volts(*(int16_t *)raw, ainConfig[3].gain);
                        raw += sizeof(int16_t);   
                    }
                    if (chanMask & chan_mask_ain4) {
                        raw2volts(*(int16_t *)raw, ainConfig[4].gain);
                        raw += sizeof(int16_t);   
                    }
                    if (chanMask & chan_mask_ain5) {
                        raw2volts(*(int16_t *)raw, ainConfig[5].gain);
                        raw += sizeof(int16_t);   
                    }
                    if (chanMask & chan_mask_ain6) {
                        raw2volts(*(int16_t *)raw, ainConfig[6].gain);
                        raw += sizeof(int16_t);   
                    }                    
                    if (chanMask & chan_mask_ain7) {
                        raw2volts(*(int16_t *)raw, ainConfig[7].gain);
                        raw += sizeof(int16_t);   
                    }                    
                }
            }
            
            /* Stops writing */            
            if (!AIFF_EndWritingSamples(file)) {
                fprintf(stderr, "ERROR ending writing .aiff file");
                goto _exit;
            } else {
                fprintf(stdout, "%do .aiff file written\n", fileNum);
            }

            /* Closes file */
            if (AIFF_CloseFile(file)) {
                fprintf(stdout, "Closed file...\n");
                fprintf(stdout, "File at %s\n", filePath);
            } else {
                fprintf(stderr, "ERROR audio_file_close");
                goto _exit;
            }
            
            present = getPresentTime(); /* Updates time for while loop check */
        }
        if (night) elapsedDays++; /* If after dawn (leaving night), 1 day elapsed */
        
        // Stop stream 
        ioctl(inStream, IOCTL_STOP_SUBSYS, 0); 
    }

/* Exit protocol and procedure */
_exit :
    fprintf(stdout,"\n");
    aio_destroy(inAIO);
    if (aInput > 0)
        close(aInput);
    if (outStream > 0)
        ioctl(outStream, IOCTL_STOP_SUBSYS, 0); 
    if (inStream > 0)
        ioctl(inStream, IOCTL_STOP_SUBSYS, 0); 
    if (inStream > 0)
        close(inStream);
    kbfini(); // see dt78xx_misc.h
    return (exitStatus);
}

