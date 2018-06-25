/* 
* This is a custom application for DT7816 bat array asynchronous I/O sampling
* that configures the board's analog input 0. The sampled data is read 
* asynchronously from the input stream and written to a WAV file. See:
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

#include "dt78xx_ioctl.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"

#include "tinywav.h"

#define _WAIT_STREAM_EMPTY_         (1)
#define DEFAULT_SAMPLE_RATE_HZ      (400000.0f)
#define DEFAULT_SAMPLES_PER_CHAN    (16384) // More causes an error?

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
#define NUM_CHANNELS                1
#define NUM_BUFF                    1
#define SAMPLE_RATE                 DEFAULT_SAMPLE_RATE_HZ
#define BLOCK_SIZE                  DEFAULT_SAMPLES_PER_CHAN

static int g_quit = 0;

/*
 * Command line arguments
 */
static const char usage[]=
{
"Samples AIN0 and writes data"
"to specified file in WAV format;"
"WAV files saved to path to storage\n"
"Usage : %s [options] <file or location identifier>\n"
"Options\n"
"-s samples : number of samples per buffer, default " xstr(DEFAULT_SAMPLES_PER_CHAN) "\n"
"-c clk     : sampling rate in Hz, default " xstr(DEFAULT_SAMPLE_RATE_HZ) "\n"

};

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void sigint_handler(int i) 
{
    g_quit = -1;
}

#ifdef _WAIT_STREAM_EMPTY_
/******************************************************************************
 * Output stream empty signal handler
 * @param i   : signal number SIGUSR2
 */
static void stream_empty_cb(int i) 
{
    fprintf(stdout, "%s\n", __func__);
    //process queue empty indication; in this case quit the foreground loop
    g_quit = 1;
}
#endif

static void led_indicators(char *system, int streaming) 
{
    // standby := LED0, writing := LED1, recording := LED2, buffering := LED3,
    // := LED4, := LED5, := LED6, := LED7  
    //update debug leds (8 total): on = 1 = success
    dt78xx_led_t led;
    uint16_t status = strtoul(system, NULL, 2);
    led.mask = 0xff;    // all bits are enabled (8 LEDs, L-R)
    led.state = (unsigned char) (status & 0xff);
    ioctl(streaming, IOCTL_LED_SET, &led);    
}

/******************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char **argv)
{
    char sysStatus[8] = {0};
    int ret = EXIT_SUCCESS;
    int fd_stream = 0;  
    int fd_ain = 0;
    int opt;
    int samples_per_chan = BLOCK_SIZE;
    int numbuf = NUM_BUFF;
    chan_mask_t chan_mask = chan_mask_ain0;
    dt78xx_clk_config_t clk = {.ext_clk=0, //Internal clock
                               .ext_clk_din=0, 
                               .clk_freq=DEFAULT_SAMPLE_RATE_HZ
                              };
    dt78xx_ain_config_t ain_cfg ={.ain=0, //AIN0
                                  .gain=1, //Default gain
                                  .ac_coupling=0, //DC coupling
                                  .current_on=0, //Current source off
                                  .differential=0
                                 }; 
    
    struct aio_struct *aio = NULL;
    
    opt = 0;
    while ((opt = getopt(argc, argv, "s:c:")) != -1) 
    {

        switch (opt) 
        {
            case 's':
                samples_per_chan = strtoul(optarg, NULL, 10);
                if (samples_per_chan <= 0)
                {
                    printf(usage, argv[0]);
                    return (EXIT_FAILURE);
                }
                break;
                        
            case 'c':
                clk.clk_freq = atof(optarg);
                break;
                
            default :
                printf(usage, argv[0]);
                return EXIT_FAILURE;
        }
    }  
    
    if (optind >= argc) //missing WAV file name
    {
        printf(usage, argv[0]);
        return (EXIT_FAILURE);
    }
    
    //Open input stream
    fd_stream = open(DEV_STREAM_IN, O_RDONLY);
    if (fd_stream < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    }
    
    //Open analog input
    fd_ain = open(DEV_AIN, O_RDONLY);
    if (fd_ain < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(fd_stream);
        return (EXIT_FAILURE);
    }
    
            
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, sigint_handler);

    //Configure sampling rate. The actual rate is returned on success
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_SET, &clk))
    {
        perror("IOCTL_SAMPLE_CLK_SET");    
        goto _exit;
    }
    
    //Redundant, but shows how to get sample rate
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_GET, &clk))
    {
        perror("IOCTL_SAMPLE_CLK_GET");    
        goto _exit;
    }
    
    //Configure for software trigger
    dt78xx_trig_config_t trig_cfg;
    trig_cfg.src = trig_src_sw;
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
    if (ioctl(fd_ain, IOCTL_AIN_CFG_SET, &ain_cfg))
    {
        fprintf(stderr, "IOCTL_AIN_CFG_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //Create and initialize AIO structures
#ifdef _WAIT_STREAM_EMPTY_
    aio = aio_create(fd_stream, 0, NULL, stream_empty_cb);
#else
    aio = aio_create(fd_stream, 0, NULL, NULL);
#endif
    if (!aio)
    {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //Size/allocate a buffer to hold the specified samples for each channel
    int buflen = aio_buff_size(samples_per_chan, chan_mask, &samples_per_chan);
    void **buf_array = aio_buff_alloc(aio, numbuf, buflen);
    if (!buf_array)
    {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples\n", 
                    clk.clk_freq, samples_per_chan);
    
    //Wait for user input to start or abort
    fprintf(stdout,"Press s to start, any other key to quit\n");
    ret = 0;
    while (1)
    {
        sysStatus[0] = 1; //LED1 on
        led_indicators(sysStatus, fd_stream);
        int c = getchar();
        if (c == 's')
        {
            //ARM
            if ((ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0)))   
            {
                fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                        errno, strerror(errno));
                goto _exit;
            }
            //Issue a software start
            if ((ioctl(fd_stream, IOCTL_START_SUBSYS, 0)))
            {
                fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                        errno, strerror(errno));
                goto _exit;
            }
            break;
        }
        goto _exit;
    }
    sysStatus[0] = 0; //LED1 off
    led_indicators(sysStatus, fd_stream);
        
    int fileNum = 0; //Diagnostic/debugging file counter
    while (!g_quit)
    {
        sysStatus[2] = 1; //LED2 on
        led_indicators(sysStatus, fd_stream);
            
        //Submit the buffers for asynchronous I/O
        if (aio_start(aio))
        {
            fprintf(stderr, "ERROR aio_start\n");
            goto _exit;
        }

        //Wait for all buffers to complete
        int buff_done = 0;
        while (!g_quit && (buff_done < numbuf))
        {
            sysStatus[3] = 1; //LED3 on
            led_indicators(sysStatus, fd_stream);
            int ret = aio_wait(aio, 0);
            if (ret < 0) //error
                break;
            buff_done += ret;
        }
    
        //Stop streaming after buffer completion
        ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);  
        aio_stop(aio);
        sysStatus[3] = 0; //LED3 off
        led_indicators(sysStatus, fd_stream);

        //Write acquired data to the specified file
        const char *outputPath = PATH_TO_STORAGE; //A set path to local storage
        const char *ID = argv[1]; //Physical location/identity: identifier
        time_t curTime;
        curTime = time(NULL);
        struct tm *locTime = localtime(&curTime);
        char fileTime[LEN];
        strftime(fileTime, LEN, "_%Y%m%d_%H%M%S.wav", locTime); //YYYYMMDD_HHmmss
        char fileName[LEN];
        strcpy(fileName, ID); //Identify
        strcat(fileName, fileTime); //Timestamped
        char filePath[LEN];
        strcpy(filePath, outputPath); //Directory path
        strcat(filePath, fileName); //Full file path: concatenates filename

        TinyWav tw;
        tinywav_open_write(&tw, 
                NUM_CHANNELS, 
                SAMPLE_RATE, 
                TW_FLOAT32, //Output samples: 32-bit floats. TW_INT16: 16-bit
                TW_INLINE, //Samples in-line in a single buffer.
                           //Other options include TW_INTERLEAVED and TW_SPLIT
                filePath
        );

        //Writes
        sysStatus[1] = 1; //LED0 on
        led_indicators(sysStatus, fd_stream);
        fileNum += 1;
        tinywav_write_f(&tw, buf_array, buflen); //Writes to .wav output file
        
        //Stops writing
        tinywav_close_write(&tw);
        sysStatus[1] = 0; //LED0 off
        led_indicators(sysStatus, fd_stream);
        
        //Delay: Not sure why it helps prevent errors?
        usleep(50*1000);
    }
    sysStatus[2] = 0; //LED2 off
    led_indicators(sysStatus, fd_stream);

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

