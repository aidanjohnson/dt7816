/* 
 * This example shows the use of the output stream to output data continuously,
 * and how to configure the analog output and output stream. The example uses
 * Asynchronous IO (AIO) to generate a ramp waveform that is clocked at the
 * specified sampling rate
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

/*****************************************************************************
 * MACROS
 */

/* 
 * If _CONTINUOUS_OUTPUT_ is defined, this example operates as follows
 * 1) 2 (or more) buffers are each filled with one cycle of the ramp waveform
 * 2) Both buffers are queued
 * 3) Asynchronous IO (AIO) is started only once
 * 4) When a buffer completes, it is requeued, thereby generating a continuous
 *    ramp
 * 5) When the application is stopped, AIO is stopped
 * 
 * If _CONTINUOUS_OUTPUT_ is *not* defined, this example operates as follows
 * 1) 1 buffer is filled with one cycle of the ramp waveform
 * 2) A single buffer is queued
 * 3) Asynchronous IO (AIO) is started 
 * 4) The application waits for the entire buffer to be output from the output
 *    FIFO.
 * 5) When the output FIFO is empty, AIO is stopped
 * 6) Repeat from 2.
 * This illustrates how to repeatedly start and stop AIO and also ensure that
 * the DA is stopped only after the waveform has been played out.
 */
#define _CONTINUOUS_OUTPUT_      (1)

#define OUTPUT_RATE_HZ     (1000.0f)
#define MICRO_SEC          (1000000UL)

//Debug LED to show progress
#define PROGRESS_LED       (0)
/*
 * Maximum #of DA channels, DA resolution, DA dev file specific to board
 */
#ifdef DT7837
    #define OUT_STREAM_DEV          "/dev/dt7837-stream-out"
    #define DA_MAX_SAMPLE_RATE_HZ   (216000.0f)
    #define DA_FS_V                 (10.0f)
    typedef uint32_t                out_data_t;
#elif DT7816
    #define OUT_STREAM_DEV          "/dev/dt7816-stream-out"
    #define DA_MAX_SAMPLE_RATE_HZ   (400000.0f)
    #define DA_FS_V                 (10.0f)
    typedef int16_t                 out_data_t;
#else
    #error Undefined board type
#endif

#ifdef _CONTINUOUS_OUTPUT_
//Increase the number of queued buffers as the sample rate is increased.    
#define NUM_BUFFS          (8)
#else    
#define NUM_BUFFS          (1)
#endif
/*****************************************************************************
 * GLOBALS
 */

/*
 * Command line arguments
 */
static const char usage[]=
{
"%s\n"
#ifdef _CONTINUOUS_OUTPUT_
"Generate a continuous 1KHz ramp waveform from -10V to +10V\n"
#else  
"Generate a 1KHz ramp waveform from -10V to +10V every 1.5msec\n"
#endif
};

static int g_quit = 0;

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void ctrlC_handler(int i) 
{
    g_quit = 1;
}

#ifdef _CONTINUOUS_OUTPUT_
/******************************************************************************
 * AIO buffer done callback
 * @param buff : pointer to buffer with samples for enabled output channels
 * @param len  : length of buffer; this is an integral multiple of equal number
 *               of samples from all enabled channels
 * @return     : The return value determines whether this buffer will be 
 *               resubmitted for continued AIO operations 
 *               0 = do not resubmit, 1= resubmit 
 */
static int buffer_done_cb(void *buf, int len)
{
    //Your code here...
    return 1; //resubmit
}

/******************************************************************************
 * Output stream empty signal handler
 * @param i   : signal number SIGUSR2
 */
static void stream_empty_cb(int i) 
{
    //fprintf(stderr, "%s(%d)\n", __func__, i);
    //Your error code here ...
}
#endif

/******************************************************************************
 * Turn on/off the PROGRESS_LED
 * @param file : File handle of subsystem
 * @param on   : 0=off, 1=on
 */
static void update_led(int file, int on)
{
    dt78xx_led_t led;
    led.mask = (1<<PROGRESS_LED); 
    if (on)
        led.state = (1<<PROGRESS_LED);
    else
        led.state = 0;
    ioctl(file, IOCTL_LED_SET, &led);
}
/*****************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    int err = EXIT_SUCCESS;
    int fd_stream = -EINVAL;
    int num_samples = (int)(DA_MAX_SAMPLE_RATE_HZ/OUTPUT_RATE_HZ);
    struct aio_struct *aio = NULL;
    
    //print usage if there are any command line arguments
    if (argc > 1)
    {
        printf(usage, argv[0]);
        exit(EXIT_FAILURE);
    }
            
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, ctrlC_handler);
    
    //open the output stream
    fd_stream = open(OUT_STREAM_DEV, O_RDWR);
    if (fd_stream < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    //configure sampling rate. The actual rate is returned on success
    dt78xx_clk_config_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.clk_freq = DA_MAX_SAMPLE_RATE_HZ;
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_SET, &cfg))
    {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //write channel mask to enable AOUT0
    chan_mask_t chan_mask = chan_mask_aout0;
    if (ioctl(fd_stream, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
    
    //configure trigger to s/w
    dt78xx_trig_config_t trig;
    trig.src = trig_src_sw;
    if (ioctl(fd_stream, IOCTL_START_TRIG_CFG_SET, &trig))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
    
    //Create and initialize AIO structures, note 1 below is for output
#ifdef _CONTINUOUS_OUTPUT_
    aio = aio_create(fd_stream, 1, buffer_done_cb, stream_empty_cb);
#else
    aio = aio_create(fd_stream, 1, NULL, NULL);
#endif
    if (!aio)
    {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //Allocate buffers, each sized to hold the specified #of samples
    int buflen = aio_buff_size(num_samples, chan_mask, &num_samples);
    void **buf_array = aio_buff_alloc(aio, NUM_BUFFS, buflen);
    if (!buf_array)
    {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    //Fill each buffer with a -10V to +10V ramp
    int i, buf_index;
    for (buf_index=0; buf_index < NUM_BUFFS; ++buf_index)
    {
        out_data_t *buf_ptr= buf_array[buf_index];
        for (i=0; i< num_samples; ++i, ++buf_ptr)
        {        
            float f = -DA_FS_V + (2*DA_FS_V*i)/(float)num_samples;
            *buf_ptr = volts2raw(f, 1);
        }
    }

#ifdef _CONTINUOUS_OUTPUT_
        //queue the buffers and start AIO
        if ((err=aio_start(aio)) !=0)
        {
            fprintf(stderr, "ERROR aio_start %d\n", err);
            goto _exit;
        }
        //arm output stream
        if (ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0))
        {
            fprintf(stderr, "ERROR IOCTL_ARM_SUBSYS %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        } 
        //start output stream
        if (ioctl(fd_stream, IOCTL_START_SUBSYS, 0))
        {
            fprintf(stderr, "ERROR IOCTL_START_SUBSYS %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        } 
        //Buffers are completed at this rate
        uint32_t buff_done_us = (num_samples*MICRO_SEC)/DA_MAX_SAMPLE_RATE_HZ;
         //Infinite loop until ctrl-C is pressed
        while (!g_quit)
        {   
            /*---------------------------------------------------------------
             * Buffers will be completed every
             * num_samples/DA_SAMPLE_RATE_HZ micro seconds and must be requeued.
             * Therefore, aio_wait() must be called repeatedly at this 
             * interval; otherwise the queue will become empty. The usleep()
             * allows you to see what happens if aio_wait() is not called
             * often enough. Debug LED 0 is '1' for this duration
             *--------------------------------------------------------------*/
            update_led(fd_stream, 1);
            usleep(buff_done_us/2);  //Place holder for some useful work
            update_led(fd_stream, 0);
            
            aio_wait(aio, 0);
        }
        //check the output FIFO status
        acq_status_t status = 0;
        ioctl(fd_stream, IOCTL_ACQ_STATUS_GET, &status);
        fprintf(stdout, "FIFO is %s empty\n", 
                        (status&acq_status_fifo_empty?"":"not"));
#else
    //Time in us it will take to output the entire waveform
    uint32_t stream_empty_us = (num_samples*NUM_BUFFS*MICRO_SEC)/DA_MAX_SAMPLE_RATE_HZ;
    //fprintf(stdout,"empty in %u us\n", stream_empty_us);
    
    //Infinite loop until ctrl-C is pressed
    while (!g_quit)
    {   
        //submit the buffer
        if ((err=aio_start(aio)) !=0)
        {
            fprintf(stderr, "ERROR aio_start %d\n", err);
            goto _exit;
        }
        //arm output stream
        if (ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0))
        {
            fprintf(stderr, "ERROR IOCTL_ARM_SUBSYS %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        } 
        
        //Update LED, 
        update_led(fd_stream, 1);

        //start output stream
        if (ioctl(fd_stream, IOCTL_START_SUBSYS, 0))
        {
            fprintf(stderr, "ERROR IOCTL_START_SUBSYS %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        } 
    
        //Wait until output FIFO is empty before stopping
        acq_status_t status = 0;
        ioctl(fd_stream, IOCTL_ACQ_STATUS_GET, &status);
        while (!(status & acq_status_fifo_empty))
        {
            update_led(fd_stream, 1);
            
            //---------------------------------------
            usleep(stream_empty_us);  //Place holder for some useful work
            //---------------------------------------
            
            update_led(fd_stream, 0);
            ioctl(fd_stream, IOCTL_ACQ_STATUS_GET, &status);
        }
        
        //---------------------------------------
        //some more useful work here
        //---------------------------------------
        
        //stop output stream
        ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0); 
        aio_stop(aio);

        //---------------------------------------
        //some more useful work here
        //---------------------------------------
    }
#endif    
    //stop output stream
    ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0); 
    aio_stop(aio);
        
_exit: 
    //clean up
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    aio_destroy(aio);
#pragma GCC diagnostic pop    
    close(fd_stream);
    return (err);
}

