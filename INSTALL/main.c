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

#include "dt78xx_ioctl.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"

#include "tinywav.h"

#define _WAIT_STREAM_EMPTY_         (1)
#define DEFAULT_SAMPLE_RATE_HZ      (400000.0f)
#define DEFAULT_SAMPLES_PER_CHAN    (1024)
#define DEFAULT_NUM_BUFF            (2)
#ifdef DT7816
    #define DEV_STREAM_IN "/dev/dt7816-stream-in"
    //AIN device file
    #define DEV_AIN "/dev/dt7816-ain"
#else
    #error Undefined board type
#endif
#define xstr(s) str(s)
#define str(s) #s
static int g_quit = 0;

/*
 * Command line arguments
 */
static const char usage[]=
{
"Samples AIN0 and writes data"
"to specified file in WAV format\n"
"Usage : %s [options] <file>\n"
"Options\n"
"-b buffers : number of buffers queued, default " xstr(DEFAULT_NUM_BUFF) "\n"
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

/******************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    int ret = EXIT_SUCCESS;
    int fd_stream = 0;  
    int fd_ain = 0;
    int opt;
    int samples_per_chan = DEFAULT_SAMPLES_PER_CHAN;
    int numbuf = DEFAULT_NUM_BUFF;
    chan_mask_t chan_mask = chan_mask_ain0;
    dt78xx_clk_config_t clk = {.ext_clk=0, 
                               .ext_clk_din=0, 
                               .clk_freq=DEFAULT_SAMPLE_RATE_HZ};
    dt78xx_ain_config_t ain_cfg ={.ain=0,.gain=1,.ac_coupling=0,.current_on=0,
                                  .differential=0};
    
    struct aio_struct *aio = NULL;
    
    while ((opt = getopt(argc, argv, "tms:b:w:c:g:")) != -1) 
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
            
            case 'b':
                numbuf = strtoul(optarg, NULL, 10);
                if (numbuf <=0)
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
    fd_stream = open(DEV_STREAM_IN, O_RDONLY);
    if (fd_stream < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    }
    
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

    //configure sampling rate. The actual rate is returned on success
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
    
    //configure for software trigger
    dt78xx_trig_config_t trig_cfg;
    trig_cfg.src = trig_src_sw;
    if (ioctl(fd_stream, IOCTL_START_TRIG_CFG_SET, &trig_cfg))
    {
        perror("IOCTL_START_TRIG_CFG_SET");    
        goto _exit;
    }
    
    //write channel mask
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
    
    //size each buffer to hold the specified samples for each channel
    int buflen = aio_buff_size(samples_per_chan, chan_mask, &samples_per_chan);
    void **buf_array = aio_buff_alloc(aio, numbuf, buflen);
    if (!buf_array)
    {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    //submit the buffers
    if (aio_start(aio))
    {
        fprintf(stderr, "ERROR aio_start\n");
        goto _exit;
    }
    
    fprintf(stdout,"Sampling at %f Hz gain %hu queued %d buffers each of %d samples\n", 
                    clk.clk_freq, ain_cfg.gain, numbuf, samples_per_chan);
    
    //Wait for user input to start or abort
    fprintf(stdout,"Press s to start, any other key to quit\n");
    ret = 0;
    while (1)
    {
        int c = getchar();
        if (c == 's')
        {
            if ((ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0)))   
            {
                fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                        errno, strerror(errno));
                goto _exit;
            }
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
    
    //wait for all buffers to complete
#ifdef _WAIT_STREAM_EMPTY_
    while (!g_quit)
    {
        if (aio_wait(aio, -1) < 0)
            break;
    }
#else
    int buff_done = 0;
    while (!g_quit && (buff_done != numbuf))
    {
        if (aio_wait(aio, -1) > 0)
        {
            ++buff_done;
            fprintf(stdout, "%d buffers done\n", buff_done);
        }
        else
            break; //error
    }
#endif        
    
    //After completion ...
    ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);    
    //Write acquired data to the specified file
    FILE * fd_data = fopen(argv[optind], "w");
    if (!fd_data)
    {
        fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    //Header row in csv file
    fprintf(fd_data,"Sample#,AIN0 (V), AIN0 (count)");
    int i;
    for (i=0; i < numbuf; ++i)
    {
        int j;
        float volt;
        void *raw = buf_array[i];
        for (j=1; j <= samples_per_chan ;++j)
        {
#ifdef DT7816
            //AIN channels are 16-bits  and always come first
            volt = raw2volts(*(int16_t *)raw, ain_cfg.gain); 
            fprintf(fd_data,"%6d, %.5f,%hd", 
                    j+(i*samples_per_chan),volt,*(int16_t *)raw);
            raw += sizeof(int16_t);
#endif               
            fprintf(fd_data,"\n");
        }
    }
    fclose(fd_data);
    fprintf(stdout, "Total %d samples written to %s\n", 
            samples_per_chan*numbuf, argv[optind]);

_exit : 
    aio_stop(aio);
    aio_destroy(aio);
    if (fd_ain > 0)
        close(fd_ain);
    if (fd_stream > 0)
        close(fd_stream);
    return (ret);
}

