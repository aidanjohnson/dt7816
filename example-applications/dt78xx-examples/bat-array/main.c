/* 
* This is a custom application for DT7816 bat array asynchronous I/O sampling
* that configures the board's analog input 0. The sampled data is read 
* asynchronously from the input stream and written to a AIFF file. See:
* https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
* for additional details on (a)synchronous I/O.
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
#include <malloc.h>
#include <math.h>

#include "dt78xx_ioctl.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"

#define LIBAIFF_NOCOMPAT 1 // do not use LibAiff 2 API compatibility
#include "libaiff.h"

/*****************************************************************************
 * Macros
 */
#define DEFAULT_SAMPLE_RATE_HZ      (400000.0f)
#define DEFAULT_SAMPLES_PER_CHAN    (65536) // No more than 2^16 = 65536
#define DEFAULT_GAIN                (1) // gain 1 => +/- 10 V
#define DEFAULT_TRIG_LEVEL_V        (0.0f)

#ifdef DT7816
    #define DEV_STREAM_IN           "/dev/dt7816-stream-in"
    //AIN device file
    #define DEV_AIN                 "/dev/dt7816-ain"
    #define DOUT_DEV                "/dev/dt7816-dout"
#else
    #error Undefined board type
#endif
#define xstr(s) str(s)
#define str(s) #s

#define PATH_TO_STORAGE             "/usr/local/path/to/ssd/"
#define LEN                         255
#define NUM_CHANNELS                1 //8
#define NUM_BUFFS                   1 //
#define SAMPLE_RATE                 DEFAULT_SAMPLE_RATE_HZ
#define BLOCK_SIZE                  DEFAULT_SAMPLES_PER_CHAN

static int g_quit = 0;

/*****************************************************************************
 * Data types
 */

struct buffer
{
    int32_t num_samples;
    float values[1];  //variable sized array with num_samples
};

struct buffer_object
{
    float sample_rate;  
    int32_t num_samples;
    struct buffer *vbuf;  //buffer with raw values converted to voltage
};

/*
 * Command line arguments
 */
static const char g_usage[]=
{
"Samples AIN0 and writes data"
"to specified file in AIFF format;"
"AIFF files saved to path to storage\n"
"Usage : %s [options] <file or location identifier>\n"
"Options\n"
"-s|--samples : number of samples per buffer, default " xstr(DEFAULT_SAMPLES_PER_CHAN) "\n"
"-c|--clk : sampling rate in Hz, default " xstr(DEFAULT_SAMPLE_RATE_HZ) "\n"
"-d|--daemon : runs this application as a daemon process\n"
"-t|--trig : when the voltage on either AIN crosses 0V rising (threshold) acquisition "
"            is triggered. By default, acquisition is triggered when you start \n" 
"            the analog input operation using the ioct \n"    
};

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void sigint_handler(int i) 
{
    g_quit = -1;
}

static void led_indicators(uint8_t status, int streaming) 
{
    // standby := LED0, writing := LED1, recording := LED2, buffering := LED3,
    // := LED4, := LED5, := LED6, := LED7  
    //update debug leds (8 total): on = 1 = success
    dt78xx_led_t led;
    led.mask = 0xff;    // all bits are enabled (8 LEDs, L-R)
    led.state = (status & 0xff);
//    fprintf(stderr, "%d\n", status);
    ioctl(streaming, IOCTL_LED_SET, &led);    
}

/******************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    uint8_t sysStatus = 0x00;
    int ret = EXIT_SUCCESS;
    int daemonise = 0;
    int auto_trig = 1;
    int opt;
    int samples_per_chan = BLOCK_SIZE;
    
    chan_mask_t chan_mask = chan_mask_ain0;
//    chan_mask_t chan_mask = {chan_mask_ain0, chan_mask_ain1, chan_mask_ain2,
//                             chan_mask_ain3, chan_mask_ain4, chan_mask_ain5,
//                             chan_mask_ain6, chan_mask_ain7};

    struct buffer_object buffer_object =
    {
        .sample_rate = SAMPLE_RATE,
        .vbuf = NULL,
    };
    dt78xx_clk_config_t clk = {.ext_clk=0, //Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
    dt78xx_ain_config_t ain0_cfg ={.ain=0, //AIN0
                                  .gain=1, //Default gain
                                  .ac_coupling=0, //DC coupling
                                  .current_on=0, //Current source off
                                  .differential=0
                                 }; 
//    dt78xx_ain_config_t ain1_cfg ={.ain=1, //AIN1
//                                   .gain=1, //Default gain
//                                   .ac_coupling=0, //DC coupling
//                                   .current_on=0, //Current source off
//                                   .differential=0
//                                  }; 
//    dt78xx_ain_config_t ain2_cfg ={.ain=2, //AIN2
//                                   .gain=1, //Default gain
//                                   .ac_coupling=0, //DC coupling
//                                   .current_on=0, //Current source off
//                                   .differential=0
//                                  }; 
//    dt78xx_ain_config_t ain3_cfg ={.ain=3, //AIN3
//                                   .gain=1, //Default gain
//                                   .ac_coupling=0, //DC coupling
//                                   .current_on=0, //Current source off
//                                   .differential=0
//                                  }; 
//    dt78xx_ain_config_t ain4_cfg ={.ain=4, //AIN4
//                                   .gain=1, //Default gain
//                                   .ac_coupling=0, //DC coupling
//                                   .current_on=0, //Current source off
//                                   .differential=0
//                                  }; 
//    dt78xx_ain_config_t ain5_cfg ={.ain=5, //AIN5
//                                   .gain=1, //Default gain
//                                   .ac_coupling=0, //DC coupling
//                                   .current_on=0, //Current source off
//                                   .differential=0
//                                  }; 
//    dt78xx_ain_config_t ain6_cfg ={.ain=6, //AIN6
//                                   .gain=1, //Default gain
//                                   .ac_coupling=0, //DC coupling
//                                   .current_on=0, //Current source off
//                                   .differential=0
//                                  }; 
//    dt78xx_ain_config_t ain7_cfg ={.ain=7, //AIN7
//                                   .gain=1, //Default gain
//                                   .ac_coupling=0, //DC coupling
//                                   .current_on=0, //Current source off
//                                   .differential=0
//                                  }; 
    dt78xx_ain_config_t ain_cfg[NUM_CHANNELS] = {ain0_cfg};
//    dt78xx_ain_config_t ain_cfg[NUM_CHANNELS] = {ain0_cfg, ain1_cfg, ain2_cfg,
//                                                 ain3_cfg, ain4_cfg, ain5_cfg,
//                                                 ain6_cfg, ain7_cfg};

    opt = 0;
    while ((opt = getopt(argc, argv, "s:c:d:t:")) != -1) 
    {

        switch (opt) 
        {
            case 's':
                samples_per_chan = strtoul(optarg, NULL, 10);
                if (samples_per_chan <= 0)
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
            
            case 't' :
                auto_trig = 0;
                break;
                
            default :
                printf(g_usage, argv[0]);
                return EXIT_FAILURE;
        }
    }  
    
    if (optind >= argc) //missing AIFF file identifier
    {
        printf(g_usage, argv[0]);
        return (EXIT_FAILURE);
    }
    
    if (buffer_object.sample_rate <= 0.0f)
    {
        printf(g_usage, argv[0]);
        return (EXIT_FAILURE);
    }
    
    //Run as a daemon if specified in command line. MUST preceed any file I/O
    fprintf(stderr, "Daemonising...\n");
    if (daemonise)
    {
        if (daemon(1,0) < 0)
            perror("daemon");
    }
    
    //Open input stream
    fprintf(stderr, "Opening stream...\n");
    int fd_stream = open(DEV_STREAM_IN, O_RDONLY);
    if (fd_stream < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    }
    
    //Open analog input
    fprintf(stderr, "Opening analog input...\n");
    int fd_ain = open(DEV_AIN, O_RDONLY);
    if (fd_ain < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(fd_stream);
        return (EXIT_FAILURE);
    }
            
    //Set up ctrl-c handler to terminate process gracefully
    sigaction_register(SIGINT, sigint_handler);

    //Configure sampling rate. The actual rate is returned on success
    clk.clk_freq = buffer_object.sample_rate;
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_SET, &clk))
    {
        perror("IOCTL_SAMPLE_CLK_SET");    
        goto _exit;
    }
    buffer_object.sample_rate = clk.clk_freq; //Actual rate
    
    //Redundant, but shows how to get sample rate
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_GET, &clk))
    {
        perror("IOCTL_SAMPLE_CLK_GET");    
        goto _exit;
    }
    
    //Configure for software trigger
    fprintf(stderr, "Configuring trigger...\n");
    dt78xx_trig_config_t trig_cfg;
    trig_cfg.src_cfg.threshold.ain = 0; //AIN0
    if (auto_trig) //default trigger == auto or software trigger
        trig_cfg.src = trig_src_sw;
    else           //threshold trigger
    {
        trig_cfg.src = trig_src_threshold;
        trig_cfg.src_cfg.threshold.edge_rising = 1;
        trig_cfg.src_cfg.threshold.level = volts2raw(DEFAULT_TRIG_LEVEL_V,DEFAULT_GAIN);
    }
    if (ioctl(fd_stream, IOCTL_START_TRIG_CFG_SET, &trig_cfg))
    {
        perror("IOCTL_START_TRIG_CFG_SET");    
        goto _exit;
    }
    
    //Write channel mask
    if (ioctl(fd_stream, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //Channel gain, coupling and current source
    int ain;
    for (ain = 0; ain < NUM_CHANNELS; ain++) {
            if (ioctl(fd_ain, IOCTL_AIN_CFG_SET, &ain_cfg[ain]))
            {
                fprintf(stderr, "IOCTL_AIN%d_CFG_SET ERROR %d \"%s\"\n", 
                        ain, errno, strerror(errno));
                goto _exit;
            }
    }
    
    //Create and initialise AIO structures
    fprintf(stderr, "Initialising...\n");
    struct aio_struct *aio = aio_create(fd_stream, 0, NULL, NULL);
    if (!aio)
    {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //Size/allocate a buffer to hold the specified samples for each channel
    fprintf(stderr, "Allocating buffer...\n");
    int buflen = aio_buff_size(samples_per_chan, chan_mask, 
                                &buffer_object.num_samples);
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples...\n", 
                    clk.clk_freq, buffer_object.num_samples);
    void **buf_array = aio_buff_alloc(aio, NUM_BUFFS, buflen);
    if (!buf_array)
    {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    //Allocate a buffer to hold the raw values converted to Volts
    buffer_object.vbuf = malloc(sizeof(struct buffer) + sizeof(float) *
                                buffer_object.num_samples * NUM_BUFFS);
    if (!buffer_object.vbuf)
    {
        fprintf(stderr, "ERROR buffer_object.vbuf\n");
        goto _exit;
    }
    

    //Wait for user input to start or abort
    fprintf(stdout,"Press s to start, any other key to quit\n");
    while (1)
    {
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
    while (!g_quit)
    {
        sysStatus += 0x04; //LED2 on
        led_indicators(sysStatus, fd_stream);

        //submit the buffers
        fprintf(stderr, "Starting... bufffer ");
        if (aio_start(aio))
        {
            fprintf(stderr, "ERROR aio_start\n");
            goto _exit;
        }

        //ARM
        fprintf(stderr, "... ARM ");
        if ((ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0)))   
        {
            fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        }

        /* Issue a software start; this is redundant if trigger source is 
         * threshold trigger or external trigger */ 
        fprintf(stderr, "... software\n");
        if ((ioctl(fd_stream, IOCTL_START_SUBSYS, 0)))
        {
            fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        }

        //Wait for all buffers to complete
        fprintf(stderr, "Waiting...\n");
        int buff_done = 0;
        while (!g_quit && (buff_done < NUM_BUFFS))
        {
            int ret = aio_wait(aio, 0);
            if (ret < 0) //error
                break;
            buff_done += ret;
        }

        //Stop streaming after buffer completion
        fprintf(stderr, "Buffer Complete...\n");
        ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);  
        aio_stop(aio);
        
        //convert the raw values to voltage
        fprintf(stderr, "Converting to voltage...\n");
        float *out = buffer_object.vbuf->values;
        const int v_length = buffer_object.num_samples * NUM_BUFFS * NUM_CHANNELS;
        float volts[v_length];
        for (buff_done=0; buff_done < NUM_BUFFS; ++buff_done)
        { 
            //AIN channels are 16-bits
            int16_t *raw = buf_array[buff_done];
            int sample;
            for (sample=0; sample < buffer_object.num_samples; 
                    ++sample, ++raw, ++out)
            {
                for (ain = 0; ain < NUM_CHANNELS; ain++)
                {
//                    fprintf(stderr, "Sample %d of channel %d\n", sample, ain);
                    *out = raw2volts(*raw, ain_cfg[ain].gain);
                    int sample_ain = sample + buffer_object.num_samples * (buff_done + ain);
                    volts[sample_ain] = *out;
                }
            }
        }

        //Write acquired data to the specified file
        fprintf(stderr, "Making .aiff...\n");
        fprintf(stderr, "Getting path... ");
        const char *outputPath = PATH_TO_STORAGE; //A set path to local storage
        fprintf(stderr, "%s\n", outputPath);
        fprintf(stderr, "Getting identifier... ");
        fprintf(stderr, "%s\n", argv[optind]);
        const char *ID;
        ID = argv[optind]; //Physical location/identity: identifier
        time_t curTime;
        curTime = time(NULL);
        struct tm *locTime = localtime(&curTime);
        int64_t millis;
        time_t secs = millis / 1000;
        tm *ptm = gmtime(&secs);
        uint32_t ms = millis % 1000;
        fprintf(stderr, "Creating timestamp... ");
        char fileTime[LEN];
        strftime(fileTime, LEN, "_%Y%m%d_%H%M%S.aiff", locTime); //YYYYMMDD_HHmmss
        fprintf(stderr, "%s\n", fileTime);
        fprintf(stderr, "Creating file name... ");
        char fileName[LEN];
        strcpy(fileName, ID); //Identify
        strcat(fileName, fileTime); //Timestamped
        fprintf(stderr, "%s\n", fileName);
        fprintf(stderr, "Creating file path... ");
        char filePath[LEN];
        strcpy(filePath, outputPath); //Directory path
        strcat(filePath, fileName); //Full file path: concatenates filename
        fprintf(stderr, "%s\n", filePath);

        AIFF_Ref file;
        file = AIFF_OpenFile(filePath, F_WRONLY);
        if (file) {
            sysStatus += 0x01; //LED0 on
            led_indicators(sysStatus, fd_stream);
            fileNum += 1;
            fprintf(stderr, "Opened .aiff file...\n");
            
            //Writes to .aiff output file
            if (AIFF_SetAudioFormat(file, NUM_CHANNELS, 
                                    (double) buffer_object.sample_rate, sizeof(float))) {
                fprintf(stderr, ".aiff format set...\n");
            } else {
                AIFF_CloseFile(file);
                fprintf(stderr, "ERROR audio_format_set");
                goto _exit;
            }
            int start = AIFF_StartWritingSamples(file);
            int writ = AIFF_WriteSamples32Bit(file, (int32_t*) volts, (int) buffer_object.num_samples);
            int end = AIFF_EndWritingSamples(file);
            if (start && writ && end) fprintf(stderr, "%do .aiff file written\n", fileNum);

            //Stops writing
            fprintf(stderr, "Closing file... ");
            if (AIFF_CloseFile(file)) {
                fprintf(stderr, "Closed\n");
                sysStatus -= 0x05; //LED0 and LED2 off
                led_indicators(sysStatus, fd_stream);
            }
        }
    }

//Exit protocol and procedure    
_exit :
    aio_stop(aio);
    aio_destroy(aio);
    if (fd_ain > 0)
        close(fd_ain);
    if (fd_stream > 0)
        close(fd_stream);
    return (ret);
}

