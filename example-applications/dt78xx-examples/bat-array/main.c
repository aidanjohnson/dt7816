/* 
* This is a custom application for DT7816 bat array asynchronous I/O sampling
* that configures the board's analog inputs. The sampled data is read 
* asynchronously from the input stream and written to a AIFF file. See:
* https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
* for additional details on (a)synchronous I/O.
 * 
 * (c) Aidan Johnson (johnsj96@uw.edu)
 * 29 June 2018
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

//Analog inputs enabled/active/on (1) or disabled/inactive/off (0)
#define AIN0                1
#define AIN1                0
#define AIN2                0
#define AIN3                0
#define AIN4                0
#define AIN5                0
#define AIN6                0
#define AIN7                0
#define PATH_TO_STORAGE     "/usr/local/path/to/ssd/"
#define SAMPLE_RATE_HZ      400000.0
 //!! SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS <= 65536 samples = 2^(16 bits) !!
#define SAMPLES_PER_FILE    65536 // SAMPLES_PER_CHAN = SAMPLES_PER_FILE / NUM_CHANNELS
#define NUM_BUFFS           1 //Number of buffers per file initialised

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

/*
 * Command line arguments
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
"-s|--samples : number of samples per file, default " xstr(SAMPLES_PER_FILE) ".\n"
"               Note that you are limited to 2^(16-bits) = 65536 samples combined\n"
"               for all channels >= (samples/channel)(channels/buffer)(buffers)\n"
"-c|--clk     : sampling rate in Hz, default " xstr(SAMPLE_RATE_HZ) ".\n"
"-b|--buffers : number of buffers per file written, default " xstr(NUM_BUFFS) ".\n"
"-d|--daemon  : runs this application as a daemon process.\n"
"-t|--trig    : when the voltage on either AIN crosses " xstr(TRIG_LEVEL_V) "V rising (threshold)\n"
"               acquisition is triggered. By default, acquisition is triggered\n"
"               when you start the analog input operation using the ioct.\n"   
"\n"
};

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void sigint_handler(int i) {
    g_quit = -1;
}

static void led_indicators(uint8_t status, int streaming) {
    // Updates debug LEDs (8 in total), LED ON = 1 = READING/WRITING
    // Viewing the board such that the debug pin row is above the user LEDs:
    //
    // | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN6 | PIN7 | PIN8 | PIN9 | PIN10 |
    // ***** LED7 ** LED6 ** LED5 ** LED4 ** LED3 ** LED2 ** LED1 ** LED0 *****
    //
    // LED0 := AIN0, LED1 := AIN1, LED2 := AIN2, LED3 := AIN3,
    // LED4 := AIN4, LED5 := AIN5, LED6 := AIN6, LED7 := AIN7
    
    dt78xx_led_t led;
    led.mask = 0xff;    // all bits are enabled (8 LEDs allowed)
    led.state = (status & 0xff);
    ioctl(streaming, IOCTL_LED_SET, &led);    
}

static void timestamp(char* filePath, char** argv) {
    struct timeval tv;
    gettimeofday(&tv, NULL); //Gets current time
    
     //Time corresponding to first sample (see start of while loop)
    const char *outputPath = PATH_TO_STORAGE; //A set path to local storage
    const char *ID; //Identification prefix
    ID = argv[optind]; //Physical location/identity: identifier
    struct tm *t_iso = gmtime(&tv.tv_sec); // UTC aka GMT in ISO 8601: Zulu
    char fileTime[LEN];

    //YYYY-MM-DD HH:mm:ss:uuuuuu (u=microseconds)
    sprintf(fileTime, "_%04d%02d%02dT%02d%02d%02d%liZ.aiff", 
            t_iso->tm_year+1900, t_iso->tm_mon, t_iso->tm_mday, 
            t_iso->tm_hour, t_iso->tm_min, t_iso->tm_sec, (long) tv.tv_usec); 
    char fileName[LEN];
    strcpy(fileName, ID); //Identify
    strcat(fileName, fileTime); //Timestamped
    strcpy(filePath, outputPath); //Directory path
    strcat(filePath, fileName); //Full file path: concatenates filename
}

/******************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv) {
    
    uint8_t sysStatus = 0x00;
    int ret = EXIT_SUCCESS;
    int daemonise = 0;
    int auto_trig = 1;
    int samples_per_file = SAMPLES_PER_FILE;
    int num_buffers = NUM_BUFFS;
    int num_channels = NUM_CHANNELS;
    
    struct circ_buffer buffer_object = {.sample_rate = SAMPLE_RATE, .vbuf = NULL};
    
    dt78xx_clk_config_t clk = {.ext_clk=0, //Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    struct aio_struct *aio = NULL;
    int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
    int ch_code;//8 bit binary; channel on := 1, channel off := 0
    int opt = 0;
    while ((opt = getopt(argc, argv, "s:c:d:t:i:b:")) != -1) {
        switch (opt) {
            case 's':
                samples_per_file = strtoul(optarg, NULL, 10);
                if (samples_per_file <= 0)
                {
                    printf(g_usage, argv[0]);
                    return (EXIT_FAILURE);
                }
                break;
            case 'c':
                clk.clk_freq = atof(optarg);
                buffer_object.sample_rate = clk.clk_freq;
                break;
            case 'd' :
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
            default :
                printf(g_usage, argv[0]);
                return EXIT_FAILURE;
        }
    }
    
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
    
    int samples_per_chan = samples_per_file / channels_per_file;
    int gross_samples = samples_per_file * num_buffers;
    if(gross_samples > 65536) {
        fprintf(stderr, "Fatal Error: exceeded 16-bits!\n");
        fprintf(stderr, "SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS = %.0f > 65536\n", 
                gross_samples);
        return (EXIT_FAILURE);
    }
    
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
        fprintf(stderr, "Daemonising...\n");
        if (daemon(1,0) < 0)
            perror("daemon");
    }
    
    //Open input stream
    fprintf(stderr, "Opening stream...\n");
    int fd_stream = open(DEV_STREAM_IN, O_RDONLY);
    if (fd_stream < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    }
    
    //Open analog input
    fprintf(stderr, "Opening analog input...\n");
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
    
    //Redundant, but shows how to get sample rate
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_GET, &clk)) {
        perror("IOCTL_SAMPLE_CLK_GET");    
        goto _exit;
    }
    
    //Configure for software trigger
    fprintf(stderr, "Configuring trigger...\n");
    int i;
    for (i = 0; i < channels_per_file; i++) {
        dt78xx_trig_config_t trig_cfg = trig_cfg_ai[ch_on[i]];
        trig_cfg.src_cfg.threshold.ain = ch_on[i]; //AIN(ch on)
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
    
    //Write channel mask
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
    fprintf(stderr, "Initialising...\n");
    aio = aio_create(fd_stream, 0, NULL, NULL);
    if (!aio) {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //Size/allocate a buffer to hold the specified samples for each channel
    //buflen = 16*samples_per_chan*channels_per_file/8 
    //(in bytes; assuming samples_per_chan multiple of 32)
    int buflen = aio_buff_size(samples_per_chan, chan_mask, 
                                &buffer_object.num_samples);
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples for %d channels...\n", 
                    clk.clk_freq, buffer_object.num_samples, channels_per_file);
    void **buf_array = aio_buff_alloc(aio, num_buffers, buflen);
    if (!buf_array) {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    
    //Allocate a buffer to hold the raw values converted to Volts
    const int vbuf_len = samples_per_chan * channels_per_file;
    buffer_object.vbuf = RingBuf_new(sizeof(float), vbuf_len);
    if (!buffer_object.vbuf) {
        fprintf(stderr, "ERROR buffer_object.vbuf\n");
        goto _exit;
    }
    
    //Wait for user input to start or abort
    fprintf(stdout,"Press s to start, any other key to quit\n");
    while (1) {
        int c = getchar();
        if (c == 's')
        {
            break;
        }
        goto _exit;
    }
    
    ret = 0;
    int fileNum = 0; //Diagnostic/debugging file counter
    
    //Infinite loop until aborted by ctrl-C
    while (!g_quit) {
  
        char filePath[LEN];
        timestamp(filePath, argv);
               
        //Submit the buffers
        fprintf(stderr, "\nCommencing buffer...\n");
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

        /* Issue a software start; this is redundant if trigger source is 
         * threshold trigger or external trigger */ 
        if ((ioctl(fd_stream, IOCTL_START_SUBSYS, 0))) {
            fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        }

        //Wait for all buffers to complete
        fprintf(stderr, "Buffering in progress...\n");
        int buff_done = 0;
        while (!g_quit && (buff_done < num_buffers)) {
            int ret = aio_wait(aio, 0);
            if (ret < 0) //error
                break;
            buff_done += ret;
        }
        
        //Gets current active channels, indicating status on LEDs
        //AIN0 = 0x01, AIN1 = 0x02, AIN2 = 0x04, AIN3 = 0x08
        //AIN4 = 0x10, AIN5 = 0x20, AIN6 = 0x40, AIN7 = 0x80
        chan_mask_t activeCH;
        if (ioctl(fd_stream, IOCTL_CHAN_MASK_GET, &activeCH)) {
            perror("IOCTL_CHAN_MASK_GET");    
            goto _exit;
        }
        sysStatus = activeCH;
        led_indicators(sysStatus, fd_stream);

        //Stop streaming after buffer completion
        fprintf(stderr, "Completing...\n");
        ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);  
        aio_stop(aio);
        
         //Write acquired data to the specified .aiff output file
        AIFF_Ref file;
        file = AIFF_OpenFile(filePath, F_WRONLY);
        if (file) {
            fileNum += 1;
            fprintf(stderr, "Opened .aiff file...\n");
            
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
            fprintf(stderr, "Reading buffer and writing file...\n");
            
            //The order of the data in the input (AIN) buffer is as follows,
            //assuming that all channels are enabled in the input stream:
            //Analog input channels 0 through 7. Each analog input sample is a
            //16-bit, two’s complement value.
            int16_t *raw = buf_array[buff_done];
            
            int queue, ch;
            //Read pointer lags write pointer by channels_per_file
            for (queue = 0; queue < buffer_object.num_samples + 1; queue++) {  
                for (ch = 0; ch < channels_per_file; ch++, ++raw) {
                    int ain_i = ch_on[ch];
                    if (queue < buffer_object.num_samples) {
                        float sample_volt = raw2volts(*raw, ain_cfg[ain_i].gain);
                        float* wptr = &sample_volt; //write pointer
                        buffer_object.vbuf->add(buffer_object.vbuf, wptr);
                    }
                    if (queue > 0) {
                        float* rptr = NULL; //read pointer for writing to file
                        buffer_object.vbuf->pull(buffer_object.vbuf, &rptr);
                        
                        //Simultaneously analog input (channel) samples put inline 
                        //and sequentially like so:
                        // ___________ ___________ ___________ ___________
                        //|           |           |           |           |
                        //| Channel 1 | Channel 2 | Channel 1 | Channel 2 |
                        //|___________|___________|___________|___________|
                        // <---------> <---------> <---------> <--------->
                        //   Segment     Segment     Segment     Segment
                        // <---------------------> <--------------------->
                        //     Sample frame 1          Sample frame 2  
                        
                        writ = AIFF_WriteSamples32Bit(file, (int32_t*) &rptr, 1);
                    }
                }
            }
        }
        end = AIFF_EndWritingSamples(file);
        if (start && writ && end) {
            fprintf(stderr, "%do .aiff file written\n", fileNum);
        }

        //Stops writing
        if (AIFF_CloseFile(file)) {
            fprintf(stderr, "Closed file...\n");
            sysStatus = 0x00; //All off
            led_indicators(sysStatus, fd_stream);
            fprintf(stderr, "File at %s\n", filePath);
        } else {
            fprintf(stderr, "ERROR audio_file_close");
            goto _exit;
        }
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

