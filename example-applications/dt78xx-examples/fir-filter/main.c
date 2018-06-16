/* 
 * This example shows the use of the output stream and input stream used
 * simultaneously and continuously. AIN0 is configured and sampled at the
 * specified clock rate, the sampled buffers are FIR filtered using either
 * coefficients from a user specified file or defaults for a low-pass filter,
 * and the resultant output to AOUT0 at the specified clock rate.
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
 * Usage :
 *	See usage() below
 *****************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <linux/aio_abi.h>	/* for AIO types and constants */
#include <malloc.h>

#include "dt78xx_ioctl.h"
#include "aio_syscall.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"
#include "fir.h"

#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

/*****************************************************************************
 * MACROS
 */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif

#define MAX_AIO_EVENTS      (64)
#define MAX_FIFO_ENTRIES    (16)
#define WAIT_MS             (5)
/*
 * Debug led turned on/off at entry/exit of FIR filter function to measure its
 * timing. Statistics collected for more than 100K invocations of this function
 * using 1024 samples per buffer and 69 tap filter are,
 *                     Mean      Min       Max         Std-dev
 * FIR_USES_FLOAT      694.27us  671us     1.53ms      32.0485us
 * FIR_USES_INT        551.64us  545us     1.2ms       12.85us
 * 
 * Note that the release build use GCC's "auto vectorization" feature for the
 * NEON and hence the significant decrease in processing time. For more details,
 * see 
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dht0004a/CHDBAIDJ.html
 * 
 */
#define BUFF_DONE_LED               (0)     

//Debug led turned on at entry to buffer underrun callback
//#define OVERRUN_LED                 (1) 

//Debug led blinks to indicate collecion status
#define STATUS_LED                  (7)

#if (defined STATUS_LED) && ((STATUS_LED < 0) || (STATUS_LED > 7))
    #error STATUS_LED
#endif
#if (defined OVERRUN_LED) && ((OVERRUN_LED < 0) || (OVERRUN_LED > 7))
    #error OVERRUN_LED
#endif
#if (defined BUFF_DONE_LED) && ((BUFF_DONE_LED < 0) || (BUFF_DONE_LED > 7))
    #error BUFF_DONE_LED
#endif

/*
 * Board specific macros. Note that the maximum clock rate is 100KHz because
 * the FIR filter coefficients are designed with that sampling frequency
 */
#ifdef DT7837
    #define OUT_STREAM_DEV  "/dev/dt7837-stream-out"
    #define IN_STREAM_DEV   "/dev/dt7837-stream-in"
    #define AIN_DEV         "/dev/dt7837-ain"
    #define CLK_MAX_HZ      (100000.0f)
    #define CLK_MIN_HZ      (30000.0f) //Minimum for DA
#elif DT7816
    #define OUT_STREAM_DEV  "/dev/dt7816-stream-out"
    #define IN_STREAM_DEV   "/dev/dt7816-stream-in"
    #define AIN_DEV         "/dev/dt7816-ain"
    #define CLK_MAX_HZ      (100000.0f)
    #define CLK_MIN_HZ      (100.0f) //Minimum for AD
#else
    #error Undefined board type
#endif

/*****************************************************************************
 * GLOBALS
 */

/*
 * Command line arguments
 */
static const char usage[]=
{
"%s [options] [coeff-file]\n"
"Sample AIN0, filter acquired buffers and output to AOUT0. FIR filter \n" 
"coefficients read from optional coeff-file or default to 6KHz low-pass filter\n"
"If coeff-file is specified, each line must have a single coefficient in \n"
#ifdef FIR_USES_FLOAT
"single precision floating point format\n"
#elif  DT7837
"32-bit integer format\n"
#elif DT7816    
"16-bit integer format\n"
#endif
"Options : \n"
"-c|--clk    : Sampling rate in Hz, default 100000\n"
"-n|--numbuf : Number of buffers queued, default 8\n"
"-s|--samples: Number of *samples* per buffer, default 1024\n"
};

static int g_quit = 0;

#if (defined STATUS_LED) 
//turn on/off indicator led after this count based on sampling rate & buffer
uint32_t g_led_count;
#endif

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void ctrlC_handler(int i) 
{
    g_quit = 1;
}

#if (defined STATUS_LED) 
/*****************************************************************************
 * Blink status LED approximately once a second
 */
static void update_status_led(int fd, int reset)
{
    static uint32_t count = 0; //msb has status led on/off state
    dt78xx_led_t led;
    led.mask = (1<<STATUS_LED);  
    if (reset)
    {
        count = 0;
        led.state = 0;
        ioctl(fd, IOCTL_LED_SET, &led);
        return;
    }
    
    ++count;
    if ((count & INT32_MAX) < g_led_count)
        return;
    
    if (count & ~INT32_MAX)
    {
        led.state = 0;
        count = 0;
    }
    else
    {
        led.state = 0xff;
        count = ~INT32_MAX;
    }
    ioctl(fd, IOCTL_LED_SET, &led);
}
#endif

/******************************************************************************
 * Output stream empty/underrun signal handler
 * @param i   : signal number SIGUSR2
 */
static void out_underrun_cb(int i) 
{
#if (defined OVERRUN_LED) 
    dt78xx_led_t led;
    led.mask = (1<<OVERRUN_LED);    
    led.state = (1<<OVERRUN_LED);
    ioctl(g_out_strm, IOCTL_LED_SET, &led);
#endif 
    
    fprintf(stderr, "%s(%d)\n", __func__, i);
    //Your error code here ...
    
#if (defined OVERRUN_LED) 
    led.state = 0;
    ioctl(g_out_strm, IOCTL_LED_SET, &led);
#endif
}

/******************************************************************************
 * Input stream fill/overrun signal handler
 * @param i   : signal number SIGUSR1
 */
static void in_overrun_cb(int i) 
{
    
    fprintf(stderr, "%s(%d)\n", __func__, i);
    //Your error code here ...
}

/******************************************************************************
 * Free allocated iocbs
 * @param iocbs
 * @param num
 */
static void free_iocb_buffers(struct iocb **iocbs, int num)
{
    if (!iocbs)
        return;
    while (--num >= 0)
    {
        if (iocbs[num])
        {
            if (iocbs[num]->aio_buf)
                free ((void *)(uint32_t)iocbs[num]->aio_buf);
            free (iocbs[num]);
        }
    }
    free (iocbs);
}

/******************************************************************************
 * Allocate array of iocbs and buffers in each. BUFFERS MUST BE MULTIPLE OF
 * 32-BYTES AND ALIGNED AT 32-BYTE BOUNDARY
 * @param fd        : stream
 * @param write     : 1=output stream, 0=input stream
 * @param numbuf    : Number of buffers
 * @param buflen    : Length of each buffer in bytes
 * @return          : NULL=error, >0=pointer to array of icob pointers 
 */
static struct iocb **alloc_iocb_buffers(int fd, int write, int numbuf, int buflen)
{
    struct iocb **iocbs; //array of iocb pointers
    int i;
    int alignment = 32; //REQUIRED  
    
    //allocate array of pointers to iocb's
    iocbs = (struct iocb **)malloc(sizeof(struct iocb *) * numbuf);
    if (!iocbs)
    {
       fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
       return NULL;
    }
    memset(iocbs, 0, (sizeof(struct iocb *) * numbuf));
    
    //allocate iocb for each buffer
    for (i=0; i < numbuf; ++i)
    {
        struct iocb *cb = (struct iocb *)malloc(sizeof(struct iocb));
        if (!cb)
        {
            fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
            break;
        }
        memset(cb, 0, sizeof(struct iocb));
        iocbs[i] = cb;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
        cb->aio_buf = (__u64)memalign(alignment, buflen);
#pragma GCC diagnostic pop        
        if (!cb->aio_buf)
        {
            fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
            break;
        }
        cb->aio_fildes = fd;
        cb->aio_lio_opcode = write?IOCB_CMD_PWRITE:IOCB_CMD_PREAD;
        cb->aio_nbytes = buflen;
        cb->aio_data = write;
    }
    
    if (i == numbuf) //no errors
        return iocbs;
    
    //malloc failed
    free_iocb_buffers(iocbs, numbuf);

    return NULL;
}

/******************************************************************************
 * Configure output stream to include AOUT0, sampling clock and software
 * trigger
 * @param sample_rate
 * @return <0=error. >0 handle of output stream file
 */
static int configure_output(float sample_rate)
{
    int fd;
    
    if ((fd = open(OUT_STREAM_DEV, O_RDWR)) < 0)
    {
        perror("open");
        return -ENODEV;
    }    
    //configure sampling rate. The actual rate is returned on success
    dt78xx_clk_config_t clk;
    memset(&clk, 0, sizeof(clk));
    clk.clk_freq = sample_rate;
    if (ioctl(fd, IOCTL_SAMPLE_CLK_SET, &clk))
    {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return -errno;
    }
    
    //write channel mask to enable AOUT0
    chan_mask_t chan_mask = chan_mask_aout0;
    if (ioctl(fd, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return -errno;
    } 
    //configure s/w trigger 
    dt78xx_trig_config_t trig;
    memset(&trig, 0, sizeof(trig));
    trig.src = trig_src_sw;
    if (ioctl(fd, IOCTL_START_TRIG_CFG_SET, &trig))
    {
        fprintf(stderr, "IOCTL_START_TRIG_CFG_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return -errno;
    } 
    return fd;
}

/******************************************************************************
 * Configure input stream to include AIN0, sampling rate, s/w trigger and 
 * AIN0 configures for DC coupling, gain 1, IEPE disabled
 * @param sample_rate
 * @return <0=error. >0 handle of input stream file
 */
static int configure_input(float sample_rate)
{
    int fd, fd_ain;
    
    if ((fd = open(IN_STREAM_DEV, O_RDWR)) < 0)
    {
        perror("open");
        return -ENODEV;
    }    
    //configure sampling rate. The actual rate is returned on success
    dt78xx_clk_config_t clk;
    memset(&clk, 0, sizeof(clk));
    clk.clk_freq = sample_rate;
    if (ioctl(fd, IOCTL_SAMPLE_CLK_SET, &clk))
    {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return -errno;
    }
    
    //write channel mask to enable AIN0
    chan_mask_t chan_mask = chan_mask_ain0;
    if (ioctl(fd, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return -errno;
    } 
    //configure s/w trigger 
    dt78xx_trig_config_t trig;
    memset(&trig, 0, sizeof(trig));
    trig.src = trig_src_sw;
    if (ioctl(fd, IOCTL_START_TRIG_CFG_SET, &trig))
    {
        fprintf(stderr, "IOCTL_START_TRIG_CFG_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return -errno;
    } 
    
    //open the AIN subsystem to configure AIN0
    if ((fd_ain = open(AIN_DEV, O_RDONLY)) < 0)
    {
        close(fd);
        return -ENODEV;
    }    
    //Channel gain, coupling and current source
    dt78xx_ain_config_t ain_cfg;
    ain_cfg.ain = 0;
    ain_cfg.gain = 1; //x1 gain
    ain_cfg.ac_coupling = 0; //dc coupling
    ain_cfg.current_on = 0; //current source off
    if (ioctl(fd_ain, IOCTL_AIN_CFG_SET, &ain_cfg))
    {
        fprintf(stderr, "IOCTL_AIN_CFG_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        close(fd);
        close(fd_ain);
        return -errno;
    }
    
    close(fd_ain);
    return fd;
}

/*****************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    int opt, i;
    int err = EXIT_SUCCESS;
    float sample_clk = CLK_MAX_HZ; //default sampling rate
    int numbuf = 8;     //default #of buffers in AIO
    int samples = 1024; //default #of samples per buffer
    int buflen;
    int in_strm = -EINVAL;
    int out_strm = -EINVAL;
    const char *coeff_file = NULL; //Use internal FIR coeffs by default
    
    aio_context_t ioctx = 0;
    struct iocb **out_iocb = NULL;
    struct iocb **in_iocb = NULL;
     
    //Specifying the expected options
    static struct option long_options[] = 
    {
        {"numbuf",      required_argument,  0,  'n' },
        {"samples",     required_argument,  0,  's' },
        {"clock",       required_argument,  0,  'c' },
        {0,             0,                  0,  0   }
    };
    
    opterr=0;
    while ((opt = getopt_long(argc, argv,"n:s:c:", long_options, NULL)) != -1) 
    {
        switch (opt) 
        {
            case 'n' : 
                numbuf = atoi(optarg);
                if (numbuf <= 0)
                {
                    printf(usage, argv[0]); 
                    exit(EXIT_FAILURE);
                }
                if (numbuf > MAX_AIO_EVENTS)
                {
                    fprintf(stderr, "Max number of buffers is %d\n", MAX_AIO_EVENTS);
                    exit(EXIT_FAILURE);
                }
                break;
            case 's' : 
                samples = atoi(optarg);
                if (samples <= 0)
                {
                    printf(usage, argv[0]); 
                    exit(EXIT_FAILURE);
                }
                break;
            case 'c' : 
                sample_clk = strtof(optarg, NULL);
                if ((sample_clk < CLK_MIN_HZ) || (sample_clk > CLK_MAX_HZ))
                {
                    fprintf(stderr, "Sample must be %.3f - %.3f\n", 
                            CLK_MIN_HZ, CLK_MAX_HZ);
                    exit(EXIT_FAILURE);
                }
                break;
            default: 
                printf(usage, argv[0]); 
                exit(EXIT_FAILURE);
        }
    }
    
    //If an optional FIR filter coeff file is specified....
    if (optind < argc)
    {
        struct stat _stat;
        if (stat(argv[optind], &_stat))
        {
            fprintf(stderr, "%s \"%s\"\n", argv[optind], strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (!S_ISREG(_stat.st_mode))
        {
            fprintf(stderr, "%s isn't a regular file\n", argv[optind]);
            exit(EXIT_FAILURE);
        }
        coeff_file = argv[optind]; //user specified coeff file
    }
    //Initialize FIR filter 
    if (fir_filter_alloc(coeff_file) <= 0)
    {
        fprintf(stderr, "Cannot read filter coeffs from %s\n", argv[optind]);
        exit(EXIT_FAILURE);
    }
        
#if (defined STATUS_LED) 
    g_led_count = (uint32_t)(sample_clk/samples);
    g_led_count /= 2;
#endif    
    
    //Set up AIO context
    if ((err = io_setup(MAX_AIO_EVENTS, &ioctx)))
    {
        fprintf(stderr, "io_setup ERROR %d \"%s\"\n", 
                err, strerror(err));
        goto _exit;
    }
            
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, ctrlC_handler);
    
    /* Allocate buffers, each sized to hold the specified #of samples. Since both
     * AD or DA samples are identical in size, the buffer length to hold a 
     * specific number of samples will be the same for either chan_mask_ain0 or
     * chan_mask_aout0.
     */
    buflen = aio_buff_size(samples, chan_mask_ain0, NULL);
    
    /*----------------  output stream    --------------------------------*/
    //open and configure the output stream
    out_strm = configure_output(sample_clk);
    if (out_strm < 0)
    {
        err = -out_strm;
        fprintf(stderr, "configure_output ERROR %d \"%s\"\n", 
                err, strerror(err));
        goto _exit;
    }
    //allocate buffers for output stream 
    if (!(out_iocb = alloc_iocb_buffers(out_strm, 1, numbuf, buflen)))
    {
        fprintf(stderr, "alloc_iocb_buffers ERROR %d \"%s\"\n", 
                err, strerror(err));
        err = EXIT_FAILURE;
        goto _exit;
    }
    //register signal SIGUSR2 for output stream buffer underrun
    file_sigaction_register(out_strm, SIGUSR2, out_underrun_cb);
    
    /*----------------  input stream    --------------------------------*/
    //open the input stream
    in_strm = configure_input(sample_clk);
    if (in_strm < 0)
    {
        err = -in_strm;
        fprintf(stderr, "configure_input ERROR %d \"%s\"\n", 
                err, strerror(err));
        goto _exit;
    }
    //allocate buffers for input stream
    if (!(in_iocb = alloc_iocb_buffers(in_strm, 0, numbuf, buflen)))
    {
        fprintf(stderr, "alloc_queue_buffers ERROR %d \"%s\"\n", 
                err, strerror(err));
        goto _exit;
    }
    //register signal SIGUSR1 for input stream buffer overrun
    file_sigaction_register(in_strm, SIGUSR1, in_overrun_cb);
         
    //submit the output buffers
    if (io_submit(ioctx, numbuf, out_iocb) != numbuf)
    {
        fprintf(stderr, "ERROR aio_start\n");
        goto _exit;
    }
    //submit the input buffers
    if (io_submit(ioctx, numbuf, in_iocb) != numbuf)
    {
        fprintf(stderr, "ERROR aio_start\n");
        goto _exit;
    }
    fprintf(stdout, "Clock %.3f Queued %d buffers each %d samples (%d bytes)\n", 
                        sample_clk, numbuf, samples, buflen);
  
    //arm output stream
    if (ioctl(out_strm, IOCTL_ARM_SUBSYS, 0))
    {
        fprintf(stderr, "ERROR IOCTL_ARM_SUBSYS %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
    //arm input stream
    if (ioctl(in_strm, IOCTL_ARM_SUBSYS, 0))
    {
        fprintf(stderr, "ERROR IOCTL_ARM_SUBSYS %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    //start both input and output simultaneously
    uint32_t simultaneous = 1;
    if (ioctl(out_strm, IOCTL_START_SUBSYS, &simultaneous))
    {
        fprintf(stderr, "ERROR IOCTL_START_SUBSYS %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
#ifdef FILE_DUMP    
    int buff_write = 0;
#endif    
    struct timespec tmo;
    tmo.tv_sec = WAIT_MS/1000;
    tmo.tv_nsec = (WAIT_MS - tmo.tv_sec*1000)*1000;
    
    //Infinite loop until ctrl-C or q/Q enetered
    fprintf(stdout, "Press q or Q or ctrl-C to exit\n"); 
    while (!g_quit)
    {
        struct iocb *done[1];
        struct io_event events[1];  //for io_getevents()
        
        //if key pressed
        if(kbhit())
        {
            char c = fgetc(stdin);
#ifdef FILE_DUMP    
            if (c=='w')
                buff_write = 1;
#endif            
            if ((c=='q')||(c=='Q'))//quit
                break;
            fflush(stdin);
        }
        
        //check buffer completion
        int ret = io_getevents(ioctx, 1, ARRAY_SIZE(events), events, &tmo);
        for (i=0; i < ret; ++i)
        {
            struct iocb *cb = (struct iocb *)events[i].obj;
            if (events[i].res2) //Non-zero ==error
            {
#if 1            
                fprintf(stdout, "aio_data %llx evt_data %llx %llx %llx\n", 
                    cb->aio_data,  events[i].data, events[i].res, 
                        events[i].res2);
#endif            
                errno = events[i].res2;
                perror("iocb");
                break;
            }
            if (cb->aio_fildes == in_strm) //input
            {
#if (defined BUFF_DONE_LED) 
                dt78xx_led_t led;
                led.mask = (1<<BUFF_DONE_LED);    
                led.state = (1<<BUFF_DONE_LED);
                ioctl(out_strm, IOCTL_LED_SET, &led);
#endif 
                void *buf = (void *)((__u32)cb->aio_buf);
                fir_filter(buf, samples);
                //queue the filtered buffer to output stream
                cb->aio_fildes = out_strm;
                cb->aio_lio_opcode = IOCB_CMD_PWRITE;
                
#if (defined BUFF_DONE_LED) 
                led.state = 0;
                ioctl(out_strm, IOCTL_LED_SET, &led);
#endif    
            }
            else
            {
                //queue the buffer back to input stream
                cb->aio_fildes = in_strm;
                cb->aio_lio_opcode = IOCB_CMD_PREAD;
            }
#if (defined STATUS_LED) 
            update_status_led(out_strm, 0);
#endif    
            //re-submit the buffer
            done[0] = cb;
            if (io_submit(ioctx, 1, done) < 1)
            {
                fprintf(stderr, "ERROR io_submit\n");
                ret = -EIO;
                break;
            }
        }
    }
    
_exit: 
    fprintf(stdout,"\n");
    //stop the streams
    if (out_strm > 0)
        ioctl(out_strm, IOCTL_STOP_SUBSYS, 0); 
    if (in_strm > 0)
        ioctl(in_strm, IOCTL_STOP_SUBSYS, 0); 

    //free the iocb and buffers 
    free_iocb_buffers(out_iocb, numbuf);
    free_iocb_buffers(in_iocb, numbuf);
    
    if (ioctx)
       io_destroy(ioctx);
    if (in_strm > 0)
        close(in_strm);
    if (out_strm > 0)
    {
#if (defined STATUS_LED) 
        update_status_led(out_strm, 1);
#endif    
        close(out_strm);
    }
    fir_filter_free();
    kbfini(); //see dt78xx_misc.h
    return (err);
}
