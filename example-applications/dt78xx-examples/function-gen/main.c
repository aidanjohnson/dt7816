/* 
 * This example shows the use of the output stream to output data continuously,
 * and how to configure the analog output and output stream. The example uses
 * Asynchronous IO (AIO) to generate sine/triangle/sawtooth waveform with 
 * programmable frequency and amplitude using Direct Digital Synthesis (DDS).
 * Digital output 0 generates a pulse waveform with 50% duty cycle, outputs 
 * 1,2,3,4 each generate phase shifted pulse waveforms with 25% duty cycle.
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

#include "dt78xx_ioctl.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"
#include "dds.h"

/*****************************************************************************
 * MACROS
 */

//Debug led turned on/off at entry/exit of buffer completion callback
#define BUFF_DONE_LED               (0)                          
//Debug led turned on/off at entry/exit of buffer underrun callback
#define OVERRUN_LED                 (1) 
//write DDS buffer to file for debug
//#define FILE_DUMP                 (1)  
//Number of channels; 1==AOUT0 only, 2==AOUT0+DOUT
#define NUM_OUT_CHANS               (2)  

#if (NUM_OUT_CHANS == 2)
#define DOUT_MASK \
(chan_mask_dout4 | chan_mask_dout3 | chan_mask_dout2 | chan_mask_dout1 \
 | chan_mask_dout0)
#endif
/*
 * Maximum #of DA channels, DA resolution, DA dev file specific to board
 */
#ifdef DT7837
    #define OUT_STREAM_DEV  "/dev/dt7837-stream-out"
    #define CLK_MAX_HZ      (216000.0f)
    #define DA_P2P_FS       (20.0f)
    typedef uint32_t        data_t;
#elif DT7816
    #define OUT_STREAM_DEV  "/dev/dt7816-stream-out"
    #define CLK_MAX_HZ      (400000.0f)
    #define DA_P2P_FS       (20.0f)
    typedef int16_t         data_t;
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
"%s [options] {sin|tri|saw|square}\n"
"Generate sine/triangle/sawtooth/square waveform with programmable frequency\n"
"and amplitude using Direct Digital Synthesis (DDS).\n"
#if (NUM_OUT_CHANS == 2)
"Digital output 0 generates a pulse waveform with 50%% duty cycle, "
"outputs 1,2,3,4 generate phase shifted pulse waveforms with 25%% duty cycle.\n"
#endif
"Options : \n"
"-c|--clk    : Frequency of generated waveform, default 1KHz\n"
"-n|--numbuf : Number of buffers queued, default 8\n"
"-s|--samples: Number of *samples* per channel, default 1024\n"
"-v|--volt   : Peak-to-peak output voltage, default 1V\n"
};

static const char change_verbiage[]=
{
"Enter one of more of the following, terminated by carriage return\n"
"-c <number> to change frequency of waveform to <number> Hz\n"
"-v <number> to change amplitude of waveform to <number> V\n"
"sine|saw|square|triangle to change waveform type\n"
"control C to quit\n\n"
};
static int g_quit = 0;
int g_out_strm = -EINVAL;

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void ctrlC_handler(int i) 
{
    g_quit = 1;
}

/******************************************************************************
 * AIO buffer done callback
 * @param buff : pointer to buffer with samples from enabled channels
 * @param len  : length of buffer; this is an integral multiple of equal number
 *               of samples from all enabled channels
 * @return     : The return value determines whether this buffer will be 
 *               resubmitted for continued AIO operations 
 *               0 = do not resubmit, 1= resubmit 
 */
static int buffer_done_cb(void *buf, int len)
{
#if (defined BUFF_DONE_LED) && (BUFF_DONE_LED > -1) && (BUFF_DONE_LED < 8)
    dt78xx_led_t led;
    led.mask = (1<<BUFF_DONE_LED);    
    led.state = (1<<BUFF_DONE_LED);
    ioctl(g_out_strm, IOCTL_LED_SET, &led);
#endif 
    
    dds_buff_fill(buf, len, NUM_OUT_CHANS);
    //Your code here...
    
#if (defined BUFF_DONE_LED) && (BUFF_DONE_LED > -1) && (BUFF_DONE_LED < 8)
    led.state = 0;
    ioctl(g_out_strm, IOCTL_LED_SET, &led);
#endif    
    return 1;
}

/******************************************************************************
 * Output stream empty signal handler
 * @param i   : signal number SIGUSR2
 */
static void stream_empty_cb(int i) 
{
#if (defined OVERRUN_LED) && (OVERRUN_LED > -1) && (OVERRUN_LED < 8)
    dt78xx_led_t led;
    led.mask = (1<<OVERRUN_LED);    
    led.state = (1<<OVERRUN_LED);
    ioctl(g_out_strm, IOCTL_LED_SET, &led);
#endif 
    
    fprintf(stderr, "%s(%d)\n", __func__, i);
    //Your error code here ...
    
#if (defined OVERRUN_LED) && (OVERRUN_LED > -1) && (OVERRUN_LED < 8)
    led.state = 0;
    ioctl(g_out_strm, IOCTL_LED_SET, &led);
#endif
}

/******************************************************************************
 * Poll the keyboard, parse user input and update waveform parameters
 * @param clk
 * @param p2pvolt
 * @param wave
 * @return : 1=wavform parameters changed, 0=no keyboard entry/no changes
 */
static int waveform_changed(float *clk, float *p2pvolt, enum wave_type *wave)
{
    static char line[80];
    static int cnum = 0;
    int changed=0;
    
    if(!kbhit()) //see dt78xx_misc.h
        return 0;
    
    //read characters entered and store into buffer until a CR
    int c = fgetc(stdin);
    line[cnum++] = c;
    printf("%c",c);
    fflush(stdin);
    fflush(stdout);
    if (c != '\n')
        return 0;
    
    //process buffer when CR entered
    line[cnum] = '\0';
    char *pch = strtok(line, " -");
    float tmp;
    while (pch != NULL)
    {
        if (*pch == 'c') //change output clock
        {
            pch = strtok (NULL, " ,-");
            tmp = strtof(pch, NULL);
            if ((tmp > 0.0f) && (tmp < CLK_MAX_HZ))
            {
                *clk = tmp;
                changed=1;
            }
        }
        else if (*pch == 'v') //change output voltage
        {
            pch = strtok (NULL, " ,-");
            tmp = strtof(pch, NULL);
            if ((tmp > 0.0f) && (tmp <= DA_P2P_FS))
            {
                *p2pvolt = tmp;
                changed=1;
            }            
        }
        else if (!strncasecmp(pch,"sin", 3)) //change wave to sine
        {
            *wave = wave_sine; 
            changed=1;
        }
        else if (!strncasecmp(pch,"tri", 3)) //change wave to triangle
        {
            *wave = wave_triangle; 
            changed=1;
        }
        else if (!strncasecmp(pch,"saw", 3)) //change wave to sawtooth
        {
            *wave = wave_sawtooth; 
            changed=1;
        }
        else if (!strncasecmp(pch,"squ", 3)) //change wave to square
        {
            *wave = wave_square; 
            changed=1;
        }
        pch = strtok (NULL, " ,.-");
    }
    cnum = 0;
    return changed;
}
/*****************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    int opt;
    int err = EXIT_SUCCESS;
    float wave_freq_hz = 1000.0f;
    int numbuf = 8;
    int samples_per_chan = 1024;
    float p2pvolt = 1.0f;
     
    //Specifying the expected options
    static struct option long_options[] = 
    {
        {"clk",         required_argument,  0,  'c' },
        {"numbuf",      required_argument,  0,  'n' },
        {"samples",     required_argument,  0,  's' },
        {"volt",        required_argument,  0,  'v' },
        {0,             0,                  0,  0   }
    };
    
    opterr=0;
    while ((opt = getopt_long(argc, argv,"c:n:s:v:", long_options, NULL)) != -1) 
    {
        switch (opt) 
        {
            case 'c' : 
                wave_freq_hz = strtof(optarg, NULL);
                if (wave_freq_hz <= 0.0f)
                {
                    printf(usage, argv[0]); 
                    exit(EXIT_FAILURE);
                }
                break;
            case 'v' :
                p2pvolt = strtof(optarg, NULL);
                if ((p2pvolt <= 0.0f) || (p2pvolt > DA_P2P_FS))
                {
                    printf(usage, argv[0]); 
                    exit(EXIT_FAILURE);
                }
                break;
            case 'n' : 
                numbuf = atoi(optarg);
                if (numbuf <= 0)
                {
                    printf(usage, argv[0]); 
                    exit(EXIT_FAILURE);
                }
                break;
            case 's' : 
                samples_per_chan = atoi(optarg);
                if (samples_per_chan <= 0)
                {
                    printf(usage, argv[0]); 
                    exit(EXIT_FAILURE);
                }
                break;
            default: 
                printf(usage, argv[0]); 
                exit(EXIT_FAILURE);
        }
    }
    
    enum wave_type wave = -1;
    //Check what type of waveform to generate
    if (optind < argc)
    {
        wave = !strncasecmp(argv[optind],"saw", 3) ? wave_sawtooth :
               !strncasecmp(argv[optind],"tri", 3) ? wave_triangle :
               !strncasecmp(argv[optind],"sin", 3) ? wave_sine : 
               !strncasecmp(argv[optind],"squ", 3) ? wave_square : -1;
    }
    if (wave == -1)
    {
        printf(usage, argv[0]); 
        exit(EXIT_FAILURE);
    }
    g_out_strm = open(OUT_STREAM_DEV, O_RDWR);
    if (g_out_strm < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    //configure sampling rate. The actual rate is returned on success
    dt78xx_clk_config_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.clk_freq = CLK_MAX_HZ;
    if (ioctl(g_out_strm, IOCTL_SAMPLE_CLK_SET, &cfg))
    {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
            
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, ctrlC_handler);
    
    //Initialize DDS 
    if ((err=dds_init(CLK_MAX_HZ, &wave_freq_hz, p2pvolt/2.0f, wave)))
    {
        fprintf(stderr, "dds_init ERROR %d \"%s\"\n", 
                err, strerror(err));
        goto _exit;
    }
    
    //write channel mask to enable AOUT0
    chan_mask_t chan_mask = chan_mask_aout0;
#if (NUM_OUT_CHANS == 2)
    //write channel mask to enable DOUT3:0
    chan_mask |= DOUT_MASK;
#endif    
    if (ioctl(g_out_strm, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
    //configure trigger to s/w
    dt78xx_trig_config_t trig;
    trig.src = trig_src_sw;
    if (ioctl(g_out_strm, IOCTL_START_TRIG_CFG_SET, &trig))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
    
    //Create and initialize AIO structures
    struct aio_struct *aio = aio_create(g_out_strm, 1, buffer_done_cb, 
                                        stream_empty_cb);
    if (!aio)
    {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //Allocate buffers, each sized to hold the specified #of samples
    int buflen = aio_buff_size(samples_per_chan, chan_mask, NULL);
    void **buf_array = aio_buff_alloc(aio, numbuf, buflen);
    if (!buf_array)
    {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    //Fill each buffer with a segment of the generated waveform
    int i;
    for (i=0; i< numbuf; ++i)
    {        
        dds_buff_fill(buf_array[i], buflen, NUM_OUT_CHANS);
    }
#ifdef FILE_DUMP
    //write all queued buffers to file for debugging
    FILE *dump = fopen("buffer.csv", "w");
    if (dump)
    {
        int j;
        for (j=0; j < buflen/sizeof(data_t); j+=NUM_OUT_CHANS)
        {
            if (j==0)
            {
                fprintf(dump,",");
                for (i=0; i< numbuf; ++i)
                {
                   fprintf(dump,"buff%d,", i); 
#if (NUM_OUT_CHANS == 2)
                   fprintf(dump,"buff%d dout,", i); 
#endif
                }
                fprintf(dump,"\n");
            }
            fprintf(dump,"%d,", j);
            for (i=0; i< numbuf; ++i)
            {
                fprintf(dump, "%d,", ((data_t *)buf_array[i])[j]);
#if (NUM_OUT_CHANS == 2)
                fprintf(dump, "%d,", ((data_t *)buf_array[i])[j]);
#endif
            }
            fprintf(dump,"\n");
        }
        fclose(dump);
    }
#endif    
    
    //submit the buffers
    if (aio_start(aio))
    {
        fprintf(stderr, "ERROR aio_start\n");
        goto _exit;
    }
    fprintf(stdout, "Queued %d buffers each %d samples (%d bytes)\n", 
                        numbuf, buflen/NUM_OUT_CHANS, buflen);
    fprintf(stdout, change_verbiage);
    fprintf(stdout, "-v %.6f -c %.4f %s\n", p2pvolt, wave_freq_hz,
            (wave==wave_sine)?"sine":(wave==wave_triangle)?"triangle":
                     (wave==wave_square)?"square":"sawtooth");
    fprintf(stdout, "Output %s p2p %.6fV at %.4fHz, sample rate %.4fHz\n", 
                     (wave==wave_sine)?"sine":(wave==wave_triangle)?"triangle":
                     (wave==wave_square)?"square":"sawtooth", 
                    p2pvolt, wave_freq_hz, CLK_MAX_HZ);
    
    //arm and start output stream
    if (ioctl(g_out_strm, IOCTL_ARM_SUBSYS, 0))
    {
        fprintf(stderr, "ERROR IOCTL_ARM_SUBSYS %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
    if (ioctl(g_out_strm, IOCTL_START_SUBSYS, 0))
    {
        fprintf(stderr, "ERROR IOCTL_START_SUBSYS %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    } 
    
    //Infinite loop until ctrl-C entered
    while (!g_quit)
    {
        //Poll for buffer completion; this will call buffer_done_cb
        aio_wait(aio, 20);
        //Poll keyboard to update waveform 
        if (waveform_changed(&wave_freq_hz, &p2pvolt, &wave))
        {
            dds_init(CLK_MAX_HZ, &wave_freq_hz, p2pvolt/2.0f, wave);
            fprintf(stdout, "Output %s p2p %.6fV at %.4fHz, sample rate %.4fHz\n", 
                         (wave==wave_sine)?"sine":(wave==wave_triangle)?"triangle":
                         (wave==wave_square)?"square":"sawtooth", 
                        p2pvolt, wave_freq_hz, CLK_MAX_HZ);
        }
    }
    
    dds_free();
        
_exit:   
    ioctl(g_out_strm, IOCTL_STOP_SUBSYS, 0); 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    aio_stop(aio);
    aio_destroy(aio);
#pragma GCC diagnostic pop    
    close(g_out_strm);
    kbfini(); //see dt78xx_misc.h
    return (err);
}

