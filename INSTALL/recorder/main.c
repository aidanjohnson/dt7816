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
         
int autoTrigger; // AUTO_TRIG
int fileSeconds; // FILE_TIME_S
int fileSamples; // SAMPLES_PER_FILE
int chanSamples; // SAMPLES_PER_CHAN
int fileBuffers; // BUFFERS_PER_FILE
int bufferSamples; // SAMPLES_PER_BUFFER
int numChannels; // NUM_CHANNELS
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
        
    dt78xx_clk_config_t clk = {.ext_clk=0, // Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
    int ch_code; // 8 bit binary; channel on := 1, channel off := 0
    
    /* Specifying the expected options */
    static struct option long_options[] = {
        {"seconds",     required_argument,  0,  's' },
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
    while ((opt = getopt_long(argc, argv, "s:c:d:t:i:m:n:p:l:", long_options, NULL)) != -1) {
        switch (opt) {
            case 's':
                fileSeconds = strtoul(optarg, NULL, 10);
                if (fileSeconds <= 0) {
                    printf(usage, argv[0]);
                    exit(EXIT_FAILURE);
                }
                fileSamples = clk.clk_freq / fileSeconds;  
                break;
            case 'c':
                clk.clk_freq = atof(optarg);
                if ((clk.clk_freq < CLK_MIN_HZ) || (clk.clk_freq > CLK_MAX_HZ)) {
                    fprintf(stderr, "Sample must be %.3f - %.3f\n", 
                            CLK_MIN_HZ, CLK_MAX_HZ);
                    exit(EXIT_FAILURE);
                }
                fileSamples = clk.clk_freq / fileSeconds;  
                fileBuffers = fileSamples / bufferSamples;
                break;
            case 'd' :
                durationDays = atoi(optarg);
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
                chanSamples = bufferSamples / numChannels;
                fileBuffers = fileSamples / bufferSamples;
                if (fileBuffers % 2 == 1) {
                    fprintf(stderr, "Number of buffers must even; using one fewer\n");
                    fileBuffers--;
                }
                if (fileBuffers <= 0) {
                    fprintf(stderr, "Number of buffers must be positive and non-zero\n");
                    exit(EXIT_FAILURE);
                }
                if (fileBuffers > MAX_AIO_EVENTS) {
                    fprintf(stderr, "Max number of buffers is %d\n", MAX_AIO_EVENTS);
                    exit(EXIT_FAILURE);
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
                exit(EXIT_FAILURE);
        }
    }
             
    /* Sets up force quit handler to terminate process gracefully */
    sigaction_register(SIGINT, forceQuitHandler);
    
    /* Creates mask for enabled channels, which has a bitwise format. */
    int *chOn = malloc(sizeof(int)*numChannels); // Array of enabled channel indices
    createChanMask(ain, chOn);
   
    /* First fatal error check: bit restriction */
    checkFatal(fileSamples, 2); // See recorder_helpers.h
    
    /* Channel configuration */
    dt78xx_ain_config_t ainConfig[8] = {}; // Analog input configuration array
    configChan(ainConfig);
    
    /* Second fatal error check: channel identity and sampling rate */
    checkID(argc, argv);
    
    /* Third fatal error check: opening the input stream */
    openStream();
    
    /* Fourth fatal error check: opening analog input */
    openAIN();
    
    /* 
     * Passes all fatal error checks; proceeds to setup.
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
    
    /* 
     * Size/allocate a buffer to hold the specified samples for each channel
     * where: bufLen = 16*chanSamples*numChannels/8 (in bytes, assuming 
     * chanSamples multiple of 32)
     */
    int actualSamples;
    chanSamples = fileSamples / numChannels;
    int buffSize = aio_buff_size(chanSamples, chanMask, &actualSamples);
    fprintf(stdout,"Sampling at %f Hz to 2 buffers of %d samples for %d channels...\n", 
                    clk.clk_freq, actualSamples, numChannels);
    chanSamples = actualSamples;
         
    /* Creates and initialises AIO stream buffers/structures */
    fprintf(stdout, "Initialising...\n");
    if ((inBuffer = aio_buff_alloc(inAIO, 2, buffSize)) == NULL) {
        fprintf(stderr, "alloc_queue_buffers ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
   /* Submits AIO buffers*/ 
    if ((exitStatus = aio_start(inAIO))) {
        fprintf(stderr, "AIO start failure error");
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
    calcSunUpDown(sunsets, sunrises);
    
    int elapsedDays = 0; // Resets day counter
    int fileNum = 0; // Diagnostic/debugging file counter
    char filePath[LEN]; // String for output file path
    const int fileCycles = fileBuffers / 2; // Number of cycles of double buffering per file
    const int fileSize = chanSamples * numChannels * fileBuffers; // Size of file write queue
        
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
                if ((c=='q')||(c=='Q')) // Quits
                    break;
                fflush(stdin);
            }

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

            /* 
             * Continuous sampling of input stream begins. 
             * Writes acquired data to the specified .aiff output file.
             */
            while (!forceQuit && (present < sunrise && present >= sunset)) {   
                
                /* Gets time of first sample recording for timestamp */
                timestamp(filePath, argv, PATH_TO_STORAGE);
                
                struct circular_queue fileQueue = getFileQueue(ainConfig, clk, fileSize);
                AIFF_Ref file = malloc(sizeof(AIFF_Ref));
                setMetadata(file, sunset, sunrise);

                file = AIFF_OpenFile(filePath, F_WRONLY);
                if (file) {
                    fileNum += 1;
                    fprintf(stdout, "Opened the %d th .aiff file...\n", fileNum);

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
                
                int buffersDone = 0; // Cumulative number of buffers completed so far per cycle
                int cycles = 0; // Cycle counter
                int numDone = 0; // Number of buffers completed in timeout/wait period
                
                /* Cycle 0: fills ping */
                while (numDone < 1) {
                    numDone = aio_wait(inAIO, -1); // Timeout when one buffer completely filled
                    if (numDone < 0) break; // error
                    buffersDone += numDone;
                }
                /* exit from while loop signals ping is full */

                /* 
                 * Last half of Cycle 0 (fills pong, reads ping); entirety of
                 * Cycle 1, 2, ... fileCycles - 1 (alternates fill/read ping/pong).
                 * The double buffering sink: producer is inBuffer, consumer is fileQueue
                 */
                while (cycles < fileCycles) {
                    numDone = 0;
                    if (buffersDone % 2 == 0) {
                        // Read and write from pong
                        exitStatus = AIFF_WriteSamples32Bit(file, (int32_t*) &(inBuffer[PONG]), buffSize)
                        while (numDone < 1) { // Sink, until ping full
                           numDone = aio_wait(inAIO, -1);
                           if (numDone < 0) break; // error
                           buffersDone += numDone;
                        }
                    } else {
                        // Read and write from ping
                        exitStatus = AIFF_WriteSamples32Bit(file, (int32_t*) &(inBuffer[PING]), buffSize)
                        while (numDone < 1) { // Sink, until pong full
                           numDone = aio_wait(inAIO, -1);
                           if (numDone < 0) break; // error
                           buffersDone += numDone;
                        }
                    }
                    cycles++;
                }
                /* exit from while loop signals to write single file */
                
                if (exitStatus) {
                    fprintf(stderr, "ERROR writing .aiff file");
                    goto _exit;
                }                         
                if (!AIFF_EndWritingSamples(file)) {
                    fprintf(stderr, "ERROR ending writing .aiff file");
                    goto _exit;
                } else {
                    fprintf(stdout, "%do .aiff file written\n", fileNum);
                }
                if (AIFF_CloseFile(file)) {
                    fprintf(stdout, "Closed file...\n");
                    fprintf(stdout, "File at %s\n", filePath);
                } else {
                    fprintf(stderr, "ERROR audio_file_close");
                    goto _exit;
                }
                
                present = getPresentTime(); // Updates time for while loop check
            }
        }
        if (night) elapsedDays++; // If after dawn (leaving night), 1 day elapsed
        
        ioctl(inStream, IOCTL_STOP_SUBSYS, 0); // Stop stream
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

