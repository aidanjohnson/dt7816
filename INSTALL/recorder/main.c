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

float sampleRate = SAMPLE_RATE; // Audio file sampling rate in Hz
int autoTrigger = AUTO_TRIG;
int fileSeconds = FILE_TIME_S;
int fileSamples = SAMPLES_PER_FILE;
int chanSamples = SAMPLES_PER_CHAN;
int fileBuffers = BUFFERS_PER_FILE;
int bufferSamples = SAMPLES_PER_BUFFER;
int numChannels = NUM_CHANNELS;
int durationDays = DURATION_DAYS; // Number of days for sampling/recording
int nightCycle = NIGHT_CYCLE; // On = 1, sampling only after dusk and before dawn
double lat = DEFAULT_LATITUDE; // Latitude coordinate
double lon = DEFAULT_LONGITUDE; // Longitude coordinate
long safetyMargin = SAFETY_MARGIN; // Increases sampling duration by 2*safetyMargin (in s)

chan_mask_t chanMask; // Channel mask cached on acquisition start
int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
char filePath[LEN]; // String for output file path
const char *ID;

int inStream = -1; // Device file handle for input stream
int aInput = -1; // Device file handle for analog input channels
int outStream = -1; // Device file handle for output stream

long sunset;
long sunrise;

int fileBuffer; // Cumulative number of buffers completed so far per cycle
int fileNum;; // Diagnostic/debugging file counter
void **inBuffer; // Pointer to input asynchronous buffers

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
    int exitStatus = EXIT_SUCCESS; // Exit flag
    
    ID = argv[optind]; // Identifier
    
    /* Sampling rate clock configuration initialisation */
    dt78xx_clk_config_t clk = {.ext_clk=0, // Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    /* Enabled analog input channels */
    int tempChan; // 8 bit binary; channel on := 1, channel off := 0
    
    /* Specifying the expected command line options */
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
    
    /* Command line options */
    while ((opt = getopt_long(argc, argv, "s:c:d:t:i:m:n:p:l:", long_options, NULL)) != -1) {
        switch (opt) {
            case 's':
                fileSeconds = strtoul(optarg, NULL, 10);
                if (fileSeconds <= 0) {
                    printf(usage, argv[0]);
                    exit(EXIT_FAILURE);
                }
                fileSamples = clk.clk_freq * fileSeconds;  
                break;
            case 'c':
                clk.clk_freq = atof(optarg);
                if ((clk.clk_freq < CLK_MIN_HZ) || (clk.clk_freq > CLK_MAX_HZ)) {
                    fprintf(stderr, "Sample must be %.3f - %.3f\n", 
                            CLK_MIN_HZ, CLK_MAX_HZ);
                    exit(EXIT_FAILURE);
                }
                fileSamples = clk.clk_freq * fileSeconds;  
                fileBuffers = fileSamples / bufferSamples;
                break;
            case 'd' :
                durationDays = atoi(optarg);
                break; 
            case 't' :
                autoTrigger = 0;
                break;
            case 'i' :
                tempChan = atoi(optarg);
                int d;
                numChannels = 0;
                for (d = 0; d < 8; d++) {
                    int digit = tempChan % 10;
                    ain[7-d] = digit;
                    if (digit) numChannels++;
                    tempChan /= 10;
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
    
    /* Setup input AIO stream */
    exitStatus = setupAIO(clk, argc);
    if (!exitStatus) {
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
    
    /* 
     * Calculates sunset (sunsclipse) and sunrise (sunsight) times based on: 
     * 1) Date and (2) Latitude and Longitude coordinates
     */
    long *sunsets = malloc(sizeof(long)*durationDays);
    long *sunrises = malloc(sizeof(long)*durationDays);
    calcSunUpDown(sunsets, sunrises);
    
    int elapsedDays = 0; // Resets day counter
        
    /* Infinite loop until aborted by ctrl-C */
    fprintf(stdout, "Press ctrl-C to exit\n"); 
    while (!forceQuit && durationDays > elapsedDays) {
        long present = getPresentTime();
        // TODO: sleep for <blank> s so not calculating present time so frequently?
        sunset = sunsets[elapsedDays];
        sunrise = sunrises[elapsedDays];
        int night = 0;

        /* If after dusk and before dawn (entering night) */
        while (!forceQuit && (present < sunrise && present >= sunset)) {                                            
            
            /* Start of night: only done once it begins */
            if (!night) {
                fileNum = 0;
                fileBuffer = 0;
                night = 1; // night has begun (only once a day)
                if (!armStartStream()) {
                    goto _exit; // Arm and start input stream
                }
            }
            /* Continuous sampling of input stream begins. */
            aio_wait(inAIO, 0);

            present = getPresentTime(); // Updates time for while loop check
        }
        if (night) {
            elapsedDays++; // If after dawn (leaving the end of night), 1 day elapsed
        }
        if (!stopStream()) { 
            goto _exit;
        }
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

