/* 
* This is a custom application for DT7816 autonomous asynchronous I/O sampling
* that configures the board's analog inputs. The sampled data is read 
* asynchronously from the input stream and written to a AIFF file. See:
* https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
* for additional details on (a)synchronous I/O.
 * 
 * (c) Aidan Johnson (johnsj96@uw.edu)
 * 05 July 2018
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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <malloc.h>
#include <math.h>
#include <omp.h>

#include "dt78xx_ioctl.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"

#define LIBAIFF_NOCOMPAT 1 // do not use LibAiff 2 API compatibility
#include "libaiff.h"

#include "RingBuf.h"

/*****************************************************************************
 * Customisable Macros
 */

// The sample rate, active channels, number of buffers, and samples per channel  
// can be set with command line flags in a terminal shell used to run this program.

//Default analog inputs (AINx) enabled/active/on (1) or disabled/inactive/off (0)
#define AIN0                1
#define AIN1                0
#define AIN2                0
#define AIN3                0
#define AIN4                0
#define AIN5                0
#define AIN6                0
#define AIN7                0
#define PATH_TO_STORAGE     "/usr/local/path/to/ssd/" //Predefined write path
#define PATH_TO_SUN_CYCLE   "/usr/local/sunup_sundown.txt"
#define SAMPLE_RATE_HZ      400000.0
 //Constraint: SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS <= 65536 samples = 2^(16 bits)
#define SAMPLES_PER_FILE    65536 // SAMPLES_PER_CHAN = SAMPLES_PER_FILE / NUM_CHANNELS
#define NUM_BUFFS           1 //Number of buffers per file initialised
#define DURATION_DAYS       21 //Default number of days of sampling
#define SAFETY_MARGIN       3600l //Buffers in seconds before sunset and after sunrise
#define NIGHT_CYCLE         1 //Cycles recording on at night and off at day

/*****************************************************************************
 * Do Not Touch These Macros
 */

#ifdef DT7816
    #define DEV_STREAM_IN   "/dev/dt7816-stream-in"
    //AIN device file
    #define DEV_AIN         "/dev/dt7816-ain"
    #define DOUT_DEV        "/dev/dt7816-dout"
#else
    #error Undefined board type
#endif

#define xstr(s) str(s)
#define str(s) #s

#define TRIG_LEVEL_V        0.0
#define DEFAULT_GAIN        1 // gain 1 => +/- 10 V; must be 1 for DT7816
#define LEN                 512 //Default character array size
#define NUM_CHANNELS        AIN0+AIN1+AIN2+AIN3+AIN4+AIN5+AIN6+AIN7 //max ch: 8
#define SAMPLE_RATE         SAMPLE_RATE_HZ

static int g_quit = 0;

/*****************************************************************************
 * Data types
 */

struct circ_buffer {
    float sample_rate;  
    int32_t num_samples;
    RingBuf *vbuf;  //buffer with raw values converted to voltage
};

/*****************************************************************************
 * Command line arguments with help
 */

static const char g_usage[] = {
"\n--------------------Autonomous Microphone Array for the DT7816 DAQ------------------\n"
"Samples channels AINx (at most 8 simultaneous channels) and writes data to\n"
"a timestamped file in AIFF format, saving it following a predefined path to\n"
"storage. The files are saved to <path>/<prefix>_<YYYY-DD-MMTHHmmssuuuuuuZ>.aiff\n"
"Usage        : %s <identifier prefix> [options] \n"
"Required     : a file or location identifier prefix, such as NORTH or 1.\n" 
"Options\n"
"-i|--inputs  : 8-bit binary string to enable and disable analog input channels.\n"
"               A channel is on if its bit is 1 and off if its bit is 0. Bit \n"
"               positions 0/1/2/3/4/5/6/7 correspond to channels AIN0/1/2/3/4/5/6/7.\n"
"               For example, 10101001 enables AIN0/2/4/7 and disables AIN1/3/5/6.\n"
"               By default, on channels AIN0 is enabled (i.e., 10000000).\n"        
"-s|--samples : number of samples per file, defaults " xstr(SAMPLES_PER_FILE) ".\n"
"               Note that you are limited to 2^(16-bits) = 65536 samples combined\n"
"               for all channels >= (samples/channel)(channels/buffer)(buffers)\n"
"-c|--clk     : sampling rate in Hz, defaults " xstr(SAMPLE_RATE_HZ) ".\n"
"-b|--buffers : number of buffers per file written, defaults " xstr(NUM_BUFFS) ".\n"
"-d|--dur     : fixed duration of sampling period in days at night as determined "
"               by sunset and sunrise times, defaults " xstr(DURATION_DAYS) " days.\n"
"-r|--run     : runs this application as a daemon process, defaults off.\n"
"-t|--trig    : when the voltage on either AIN crosses " xstr(TRIG_LEVEL_V) " V rising (threshold)\n"
"               acquisition is triggered. By default, acquisition is triggered\n"
"               when you start the analog input operation using the ioct.\n"
"-m|--margin  : margin of safety before the time of sunset and after the time of "
"               sunrise in seconds (hours*3600), defaults " xstr(SAFETY_MARGIN) " s."
"\n"
};

/*****************************************************************************
 * Helper functions
 */

static void sigint_handler(int i) {
    //Signal handler for ctrl-c prevents the abrupt termination of processes
    g_quit = -1;
}

static void led_indicators(uint8_t status, int streaming) {
    // Updates debug LEDs (8 in total), LED ON (1) := CHANNEL is READING/WRITING
    // Viewing the DT7816 such that the debug pin row is above the user LEDs:
    //  ______ ______ ______ ______ ______ ______ ______ ______ ______ _______
    // | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN6 | PIN7 | PIN8 | PIN9 | PIN10 |
    // ***** LED7 ** LED6 ** LED5 ** LED4 ** LED3 ** LED2 ** LED1 ** LED0 *****
    //
    // LED0 := AIN0, LED1 := AIN1, LED2 := AIN2, LED3 := AIN3,
    // LED4 := AIN4, LED5 := AIN5, LED6 := AIN6, LED7 := AIN7
    //
    // where the analog input channels have the following coding returned by
    // IOCTL_CHAN_MASK_GET:
    //
    // AIN0 = 0x01, AIN1 = 0x02, AIN2 = 0x04, AIN3 = 0x08
    // AIN4 = 0x10, AIN5 = 0x20, AIN6 = 0x40, AIN7 = 0x80
    //
    // and for input header pins (J16):
    //  ___________________________________________________
    // ||  2 |  4 |  6 |  8 | 10 | 12 | 14 | 16 | 18 | 20 ||
    // ||  1 |  3 |  5 |  7 |  9 | 11 | 13 | 15 | 17 | 19 ||7; //Defaults to 7 days
    // 
    // Analog Inputs (AINs):
    //
    // PIN5 := AIN0, PIN7 := AIN1, PIN9 := AIN2, PIN11 := AIN3 
    // PIN13 := AIN4, PIN15 := AIN5, PIN17 := AIN6, PIN19 := AIN7
    //
    // Analog Grounds (AGRDs):
    //
    // PIN6 := AGRD0, PIN8 := AGRD1, PIN10 := AGRD2, PIN12 := AGRD3 
    // PIN14 := AGRD4, PIN16 := AGRD5, PIN18 := AGRD6, PIN20 := AGRD7
    
    dt78xx_led_t led;
    led.mask = 0xff;    // all bits are enabled (8 LEDs capable of being lit)
    led.state = (status & 0xff);
    ioctl(streaming, IOCTL_LED_SET, &led);    
}

static void getSunTime(struct tm* time, char* date_time) {
    //Assumes UTC time given
    char year[4];
    char month[2];
    char day[2];
    char hour[2];
    char minute[2];
    char second[2];
    int k;
    for (k = 0; k < 4; k++) {
        year[k] = date_time[k];
        if (k < 2) {
            month[k] = date_time[k + 5];
            day[k] = date_time[k + 8];
            hour[k] = date_time[k + 11];
            minute[k] = date_time[k + 14];
            second[k] = date_time[k + 17];
        }
    }
    time->tm_year = atol(year) - 1900;
    time->tm_mon = atoi(month) - 1;
    time->tm_mday = atoi(day);
    time->tm_hour = atoi(hour);
    time->tm_min = atoi(minute);
    time->tm_sec = atoi(second);
}

static void getTime(struct tm** curTime, struct timeval* clockTime) {
    gettimeofday(&(*clockTime), NULL); //Gets current time
    *curTime = gmtime(&(*clockTime).tv_sec); // UTC aka GMT in ISO 8601: Zulu
}

static long getTimeEpoch(struct tm* readableTime) {
    return (long) mktime(&(*readableTime));
}

static void timestamp(char* filePath, char** argv) {
    struct timeval tv;
    struct tm *t_iso; //Time in accordance to ISO 8601
    getTime(&t_iso, &tv); //Gets current time in UTC (aka GMT or Zulu) 
     //Time corresponding to first sample (see start of while loop)
    const char *outputPath = PATH_TO_STORAGE; //A set path to local storage
    const char *ID; //Identification prefix
    ID = argv[optind]; //Physical location/identity: identifier
    char fileTime[LEN];

    //YYYY-MM-DD HH:mm:ss:uuuuuu (u=microseconds)
    sprintf(fileTime, "_%04d%02d%02dT%02d%02d%02d%liZ.aiff", 
            t_iso->tm_year+1900, t_iso->tm_mon + 1, t_iso->tm_mday, 
            t_iso->tm_hour, t_iso->tm_min, t_iso->tm_sec, (long) tv.tv_usec); 
    char fileName[LEN];
    strcpy(fileName, ID); //Identify
    strcat(fileName, fileTime); //Timestamped
    strcpy(filePath, outputPath); //Directory path
    strcat(filePath, fileName); //Full file path: concatenates filename
}

static int findElapsedDays(struct tm** sunsets, struct tm** sunrises, int totalDays) {
    int elapsedDays = 0;
    struct timeval sysTime;
    struct tm* sysDate;
    getTime(&sysDate, &sysTime);
    long sysEpoch = (long) sysTime.tv_sec;

    if (sysEpoch <= getTimeEpoch(&(*sunsets)[0])) { //First sunset in epoch time
        elapsedDays = 0;
    } else if (sysEpoch >= getTimeEpoch(&(*sunrises)[totalDays - 1])) { //Last sunrise in epoch time
        elapsedDays = totalDays;
    } else {
        //Find where current system time is (relative to) sun up/down cycle
        while (sysEpoch > getTimeEpoch(&(*sunrises)[elapsedDays])) {
            elapsedDays++;
        }
    }
    return elapsedDays;
}

static long getPresentTime() {
    struct tm* isoTime;
    struct timeval epochTime;
    getTime(&isoTime, &epochTime);
    return (long) epochTime.tv_sec;
}

/******************************************************************************
 * Simultaneous 8-channel analog input signal AIFF recorder
 */

int main (int argc, char** argv) {
    
    uint8_t sysStatus = 0x00;
    int ret = EXIT_SUCCESS;
    int daemonise = 0;
    int auto_trig = 1;
    int samples_per_file = SAMPLES_PER_FILE;
    int num_buffers = NUM_BUFFS;
    int num_channels = NUM_CHANNELS;
    int duration_days = DURATION_DAYS;
    
#if NIGHT_CYCLE
    long safety_margin = SAFETY_MARGIN;
#endif
    
    struct circ_buffer buffer_object = {.sample_rate = SAMPLE_RATE, .vbuf = NULL};
    
    dt78xx_clk_config_t clk = {.ext_clk=0, //Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    struct aio_struct *aio = NULL;
    int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
    int ch_code;//8 bit binary; channel on := 1, channel off := 0
    int opt = 0;
    while ((opt = getopt(argc, argv, "s:c:d:r:b:t:i:m:")) != -1) {
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
                break;
            case 'd' :
                duration_days = atoi(optarg);
                break; 
            case 'r' :
                daemonise = 1;
                break;
            case 'b' :
                num_buffers = atoi(optarg);
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
            default :
                printf(g_usage, argv[0]);
                return EXIT_FAILURE;
        }
    }
    
    //Creates mask for enabled channels
    const int channels_per_file = num_channels; //aka Block Size
    chan_mask_t chan_mask = 0x0;
    int *ch_on = malloc(sizeof(int)*channels_per_file);
    int ch_index = 0;
    if (ain[0]) {
        chan_mask |= chan_mask_ain0;
        ch_on[ch_index++] = 0;
    }
    if (ain[1]) {
        chan_mask |= chan_mask_ain1;
        ch_on[ch_index++] = 1;    
    }
    if (ain[2]) {
        chan_mask |= chan_mask_ain2;
        ch_on[ch_index++] = 2;
    }
    if (ain[3]) {
        chan_mask |= chan_mask_ain3;
        ch_on[ch_index++] = 3;
    }
    if (ain[4]) {
        chan_mask |= chan_mask_ain4;
        ch_on[ch_index++] = 4;
    }
    if (ain[5]) {
        chan_mask |= chan_mask_ain5;
        ch_on[ch_index++] = 5;
    }
    if (ain[6]) {
        chan_mask |= chan_mask_ain6;
        ch_on[ch_index++] = 6;
    }
    if (ain[7]) {
        chan_mask |= chan_mask_ain7;
        ch_on[ch_index++] = 7;
    }
    
    //SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS <= 65536 samples = 2^(16 bits)
    int samples_per_chan = samples_per_file / channels_per_file;
    int gross_samples = samples_per_file * num_buffers;
    if(gross_samples > 65536) {
        fprintf(stderr, "Fatal Error: exceeded 16-bits!\n");
        fprintf(stderr, "SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS = %d > 65536\n", 
                gross_samples);
        return (EXIT_FAILURE);
    }
    
    //Configures all channels even if not enabled and used
    dt78xx_trig_config_t trig0_cfg;
    dt78xx_ain_config_t ain0_cfg ={.ain=0, //AIN0
                                  .gain=1, //Default gain
                                  .ac_coupling=0, //DC coupling
                                  .current_on=0, //Current source off
                                  .differential=0
                                  }; 
    dt78xx_trig_config_t trig1_cfg;
    dt78xx_ain_config_t ain1_cfg ={.ain=1, //AIN1
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    dt78xx_trig_config_t trig2_cfg;
    dt78xx_ain_config_t ain2_cfg ={.ain=2, //AIN2
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    dt78xx_trig_config_t trig3_cfg;
    dt78xx_ain_config_t ain3_cfg ={.ain=3, //AIN3
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    dt78xx_trig_config_t trig4_cfg;
    dt78xx_ain_config_t ain4_cfg ={.ain=4, //AIN4
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    dt78xx_trig_config_t trig5_cfg;
    dt78xx_ain_config_t ain5_cfg ={.ain=5, //AIN5
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    dt78xx_trig_config_t trig6_cfg;
    dt78xx_ain_config_t ain6_cfg ={.ain=6, //AIN6
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    dt78xx_trig_config_t trig7_cfg;
    dt78xx_ain_config_t ain7_cfg ={.ain=7, //AIN7
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    dt78xx_ain_config_t ain_cfg[8] = {ain0_cfg, ain1_cfg, 
                                      ain2_cfg, ain3_cfg, 
                                      ain4_cfg, ain5_cfg,
                                      ain6_cfg, ain7_cfg};
    dt78xx_trig_config_t trig_cfg_ai[8] = {trig0_cfg, trig1_cfg, 
                                           trig2_cfg, trig3_cfg, 
                                           trig4_cfg, trig5_cfg,
                                           trig6_cfg, trig7_cfg};
    
    //Missing AIFF file identifier
    if (optind >= argc) {
        printf(g_usage, argv[0]);
        return (EXIT_FAILURE);
    }
    
    if (buffer_object.sample_rate <= 0.0f) {
        printf(g_usage, argv[0]);
        return (EXIT_FAILURE);
    }
    
    //Run as a daemon if specified in command line. MUST preceed any file I/O
    if (daemonise) {
        fprintf(stdout, "Daemonising...\n");
        if (daemon(1,0) < 0)
            perror("daemon");
    }
    
    //Open input stream
    fprintf(stdout, "Opening stream...\n");
    int fd_stream = open(DEV_STREAM_IN, O_RDONLY);
    if (fd_stream < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    }
    
    //Open analog input
    fprintf(stdout, "Opening analog input...\n");
    int fd_ain = open(DEV_AIN, O_RDONLY);
    if (fd_ain < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(fd_stream);
        return (EXIT_FAILURE);
    }
            
    //Set up ctrl-c handler to terminate process gracefully
    sigaction_register(SIGINT, sigint_handler);

    //Configure sampling rate. The actual rate is returned on success
    clk.clk_freq = buffer_object.sample_rate;
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_SET, &clk)) {
        perror("IOCTL_SAMPLE_CLK_SET");    
        goto _exit;
    }
    buffer_object.sample_rate = clk.clk_freq; //Actual rate
       
    //Configure for software trigger for all enabled channels
    fprintf(stdout, "Configuring trigger...\n");
    int i;
    for (i = 0; i < channels_per_file; i++) {
        dt78xx_trig_config_t trig_cfg = trig_cfg_ai[ch_on[i]];
        trig_cfg.src_cfg.threshold.ain = ch_on[i]; //AINx(ch on)
        if (auto_trig) //default trigger == auto or software trigger
            trig_cfg.src = trig_src_sw;
        else { //threshold trigger
            trig_cfg.src = trig_src_threshold;
            trig_cfg.src_cfg.threshold.edge_rising = 1;
            trig_cfg.src_cfg.threshold.level = volts2raw(TRIG_LEVEL_V,DEFAULT_GAIN);
        }
        if (ioctl(fd_stream, IOCTL_START_TRIG_CFG_SET, &trig_cfg)) {
            perror("IOCTL_START_TRIG_CFG_SET");    
            goto _exit;
        }
    }
    
    //Write channel mask for selected/enabled channels
    if (ioctl(fd_stream, IOCTL_CHAN_MASK_SET, &chan_mask)) {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //Channel gain, coupling and current source 
    for (i = 0; i < channels_per_file; i++) {
        int ain_i = ch_on[i];
        if (ioctl(fd_ain, IOCTL_AIN_CFG_SET, &ain_cfg[ain_i])) {
            fprintf(stderr, "IOCTL_AIN%d_CFG_SET ERROR %d \"%s\"\n", 
                    ain_i, errno, strerror(errno));
            goto _exit;
        }
    }
    
    //Create and initialise AIO structures
    fprintf(stdout, "Initialising...\n");
    aio = aio_create(fd_stream, 0, NULL, NULL);
    if (!aio) {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //Size/allocate a buffer to hold the specified samples for each channel
    //where: buflen = 16*samples_per_chan*channels_per_file/8 
    //(in bytes, assuming samples_per_chan multiple of 32)
    int buflen = aio_buff_size(samples_per_chan, chan_mask, 
                                &buffer_object.num_samples);
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples for %d channels...\n", 
                    clk.clk_freq, buffer_object.num_samples, channels_per_file);
    void **buf_array = aio_buff_alloc(aio, num_buffers, buflen);
    if (!buf_array) {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    //Allocate a circular/ring buffer/queue to hold the recorded values in Volts
    const int vbuf_len = samples_per_chan * channels_per_file;
    buffer_object.vbuf = RingBuf_new(sizeof(float), vbuf_len);
    if (!buffer_object.vbuf) {
        fprintf(stderr, "ERROR buffer_object.vbuf\n");
        goto _exit;
    }

#if NIGHT_CYCLE    
    FILE *sunUpDown;
    sunUpDown = fopen(PATH_TO_SUN_CYCLE, "r");
    if (sunUpDown == NULL) {
        fprintf(stderr, "ERROR cannot open sun up and down cycle .txt file\n");
        goto _exit;
    }
    
    int elapsed_days = 0;
    struct tm *sunsets = malloc(sizeof(struct tm)*duration_days);
    struct tm *sunrises = malloc(sizeof(struct tm)*duration_days);
    char line_sunset[26];
    char line_sunrise[26];
    for (elapsed_days = 0; elapsed_days < duration_days; elapsed_days++) {
        if (fscanf(sunUpDown, "%s", line_sunset) != 1) { // sunset 
            if (elapsed_days == 0) {
                fprintf(stderr, "ERROR insufficient number of sunsets\n");
                goto _exit;
            }
            fprintf(stderr, "ERROR insufficient number of sunsets (< %d); "
                    "using last day's sunset time\n", duration_days);
            sunsets[elapsed_days] = sunsets[elapsed_days - 1];
        } else {
            getSunTime(&(sunsets[elapsed_days]), line_sunset);   
        }
        if (fscanf(sunUpDown, "%s", line_sunrise) != 1) { // sunrise 
            if (elapsed_days == 0) {
                fprintf(stderr, "ERROR insufficient number of sunrises\n");
                goto _exit;
            }            
            fprintf(stderr, "ERROR insufficient number of sunrises (< %d); "
                    "using last day's sunrise time\n", duration_days);
            sunrises[elapsed_days] = sunrises[elapsed_days - 1];
        } else {
            getSunTime(&(sunrises[elapsed_days]), line_sunrise); 
        }
    }
    elapsed_days = findElapsedDays(&sunsets, &sunrises, duration_days);
#endif
    
    //Wait for user input to start or abort
    fprintf(stdout,"Press s to start, any other key to quit\n");
    while (1) {
        int c = getchar();
        if (c == 's') {
            break;
        }
        goto _exit;
    }
    
    ret = 0;
    int fileNum = 0; //Diagnostic/debugging file counter
    
    //Infinite loop until aborted by ctrl-C
    while (!g_quit) {
#if NIGHT_CYCLE
        long present = getPresentTime();
        long sunset = getTimeEpoch(&sunsets[elapsed_days]) - safety_margin;
        long sunrise = getTimeEpoch(&sunrises[elapsed_days]) + safety_margin;
        int night = 0;

        //If after dusk and before dawn (entering night)
        while (present < sunrise && present >= sunset && !g_quit) {
            night = 1;
#endif            
            //Gets time of first sample recording for timestamp
            char filePath[LEN];
            timestamp(filePath, argv);

            //Submit the buffers
            fprintf(stdout, "\nCommencing buffer...\n");
            if (aio_start(aio)) {
                fprintf(stderr, "ERROR aio_start\n");
                goto _exit;
            }

            //ARM
            if ((ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0))) {
                fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                        errno, strerror(errno));
                goto _exit;
            }

            //Issue a software start; this is redundant if trigger source is 
            //threshold trigger or external trigger 
            if ((ioctl(fd_stream, IOCTL_START_SUBSYS, 0))) {
                fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                        errno, strerror(errno));
                goto _exit;
            }

            //Wait for all buffers to complete
            fprintf(stdout, "Buffering in progress...\n");
            int buff_done = 0;
            while (!g_quit && (buff_done < num_buffers)) {
                int ret = aio_wait(aio, 0);
                if (ret < 0) //error
                    break;
                buff_done += ret;
            }

            //Gets current active channels, indicating status on LEDs
            chan_mask_t activeCH;
            if (ioctl(fd_stream, IOCTL_CHAN_MASK_GET, &activeCH)) {
                perror("IOCTL_CHAN_MASK_GET");    
                goto _exit;
            }
            sysStatus = activeCH;
            led_indicators(sysStatus, fd_stream);

            //Stop streaming after buffer completion
            fprintf(stdout, "Completing...\n");
            ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);  
            aio_stop(aio);

             //Write acquired data to the specified .aiff output file
            AIFF_Ref file;
            file = AIFF_OpenFile(filePath, F_WRONLY);
            if (file) {
                fileNum += 1;
                fprintf(stdout, "Opened .aiff file...\n");

                //Sets formatting
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

            int start, writ, end;
            start = AIFF_StartWritingSamples(file);

            //Convert the raw values to voltage
            for (buff_done=0; buff_done < num_buffers; ++buff_done) { 
                fprintf(stdout, "Reading buffer and writing file...\n");

                //The order of the data in the input (AIN) buffer is as follows,
                //assuming that all channels are enabled in the input stream:
                //Analog input channels 0 through 7. Each analog input sample is a
                //16-bit, two’s complement value.
                int16_t *raw = buf_array[buff_done];

                int queue, ch;
                //Circular buffer write and read pointers lead and follow
                for (queue = 0; queue < buffer_object.num_samples + 1; queue++) {  
                    for (ch = 0; ch < channels_per_file; ch++, ++raw) {
                        //Decouples input from output with circular buffer
                        int ain_i = ch_on[ch];
                        //Write pointer leads read pointer by channels_per_file
                        if (queue < buffer_object.num_samples) { 
                            float sample_volt = raw2volts(*raw, ain_cfg[ain_i].gain);
                            float* wptr = &sample_volt; //write pointer for input
                            buffer_object.vbuf->add(buffer_object.vbuf, wptr);
                        }
                        //Read pointer lags write pointer by channels_per_file
                        if (queue > 0) {
                            float* rptr = NULL; //read pointer for writing to file
                            buffer_object.vbuf->pull(buffer_object.vbuf, &rptr);

                            //Simultaneously analog input (channel) samples put 
                            //inline and sequentially for AIFF recording like so:
                            // ___________ ___________ ___________ ___________
                            //|           |           |           |           |
                            //| Channel 1 | Channel 2 | Channel 1 | Channel 2 | ...
                            //|___________|___________|___________|___________|
                            // <---------> <---------> <---------> <--------->  ...
                            //   Segment     Segment     Segment     Segment
                            // <---------------------> <--------------------->  ...
                            //     Sample frame 1          Sample frame 2  

                            writ = AIFF_WriteSamples32Bit(file, (int32_t*) &rptr, 1);
                        }
                    }
                }
            }
            end = AIFF_EndWritingSamples(file);

            //Checks for successful file writing
            if (start && writ && end) {
                fprintf(stderr, "%do .aiff file written\n", fileNum);
            }

            //Stops writing
            if (AIFF_CloseFile(file)) {
                fprintf(stdout, "Closed file...\n");
                sysStatus = 0x00; //All off
                led_indicators(sysStatus, fd_stream);
                fprintf(stdout, "File at %s\n", filePath);
            } else {
                fprintf(stderr, "ERROR audio_file_close");
                goto _exit;
            }
            
#if NIGHT_CYCLE            
            present = getPresentTime(); //Updates time for while loop check
        }
        
        if (night) elapsed_days++; //If after dawn (leaving night), 1 day elapsed
#endif
    }

//Exit protocol and procedure    
_exit :
    sysStatus = 0x00;
    led_indicators(sysStatus, fd_stream);
    aio_stop(aio);
    aio_destroy(aio);
    if (fd_ain > 0)
        close(fd_ain);
    if (fd_stream > 0)
        close(fd_stream);
    return (ret);
}

