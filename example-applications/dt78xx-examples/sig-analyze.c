/*****************************************************************************
 * DT78XX embedded web application
 *
 * Copyright (C) 2014 Data Translation Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * You are free to use this source code under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * This code uses libmongoose. Refer to the documentation in mongoose.h for
 * licensing requirements, and vendors contact information. API documetation
 * can be browsed at http://cesanta.com/docs/API.shtml
 * 
 ***************************************************************************** 
 * The embedded web application controls the board hardware, acquires data from
 * an analog input channel, performs FFT and "publishes" the results using an
 * embedded web server.  Any web browser can connect to the board when this
 * application is running, and display the acquired waveform and spectrum.
 * 
 * PREREQUISITES :
 * 
 * (1) All static resources, such as html, png, jar files, must exist under
 * the DOCUMENT_ROOT directory or specified as a command
 * line option; see usage[] below
 * 
 ****************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <fftw3.h>
#include <math.h>
#include "mongoose.h"

#include "dt78xx_ioctl.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"

/*****************************************************************************
 * Macros
 */
#define NUM_SAMPLES             (1024)
#define NUM_BUFS                (1)
#define DEFAULT_TRIG_LEVEL_V    (0.0f)
#define DEFAULT_GAIN            (1)      // gain 1 => +/-10V
#define DEFAULT_FS_V            (10.0f)  // for gain of 1

//web server parameters
#define DEFAULT_LISTENING_PORT  "8080"
#define DEFAULT_DOCUMENT_ROOT   "res/"

#ifdef DT7837
    #define SAMPLE_RATE_HZ          (100000.0f)
    #define DEV_STREAM_IN   "/dev/dt7837-stream-in"
    #define DEV_AIN         "/dev/dt7837-ain"
#elif DT7816
    #define SAMPLE_RATE_HZ          (400000.0f)
    #define DEV_STREAM_IN   "/dev/dt7816-stream-in"
    #define DEV_AIN         "/dev/dt7816-ain"
#else
    #error Undefined board type
#endif

//Make sure that FFTW data types are correctly defined
_Static_assert ((sizeof(fftwf_complex) == 8), "fftwf_complex size bad"); 
_Static_assert ((sizeof(fftw_complex) == 16), "fftw_complex size bad"); 

/*****************************************************************************
 * Data types
 */
//web socket types (hypercaffeinated)
enum ws_type_t {ws_type_spectrum=0xC0FFEE01, ws_type_waveform=0xC0FFEE02};

//header appended to data sent via web sockets for displaying data
struct ws_buffer
{
    enum ws_type_t type;
    int32_t num_samples;
    float values[1];  //variable sized array with num_samples
};

//Overall parameters available in struct mg_connection's server_param member
struct server_param
{
    float sample_rate;  
    int32_t num_samples;
    struct ws_buffer *vbuf;  //buffer with raw values converted to voltage
    struct ws_buffer *sbuf;  //buffer with FFT spectrum
};

//Window applied to sampled data
struct fft_window
{
    float coherent_gain;    //coherent gain
    float w[1];             //sized for number of samples
};

/*****************************************************************************
 * Functions
 */
static int web_evt_handler(struct mg_connection *conn, enum mg_event ev); 
static enum mg_result cb_board_name(struct mg_connection *conn);
static enum mg_result cb_fft_spectrum(struct mg_connection *conn);
static enum mg_result cb_waveform(struct mg_connection *conn);
static enum mg_result cb_sample_rate(struct mg_connection *conn);
static struct fft_window *blackman_harris_window(struct fft_window *, float *, int);
/*****************************************************************************
 * Globals
 */
static int g_quit = 0;

//Command line arguments
static const char g_usage[]=
{
"This application samples analog input AIN0 at the maximum rate, computes \n"
"spectrum and displays waveforms in a web browser. If this board's IP address\n"
"is ip-addr, connect to this application from any web browser using the URL\n"
"http://ip-addr:8080\n\n"    
"Usage : %s [options]\n"
"Options\n"
"-r|--docroot <path> : path to directory with all resource files\n"
"-d|--daemon : runs this application as a daemon process\n"
"-n|--nowindow : do not window sampled data before FFT. By default, a 4-term\n"
"                Blackman Harris window is used\n"  
"-a|--auto : auto trigger acquisition. By default, acquisition is triggered \n" 
"            when the voltage on AIN0 crosses 0V rising\n"    
};

static const struct url_handler
{
    const char *url;
    enum mg_result (*handler)(struct mg_connection *conn);
} g_url_handler[]=
{
    {"/boardname.get",      cb_board_name},
    {"/spectrum.get",       cb_fft_spectrum},             
    {"/waveform.get",       cb_waveform},             
    {"/samplerate.get",     cb_sample_rate},
    {NULL, NULL}
};
/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void sigint_handler(int i) 
{
    g_quit = -1;
}

/******************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    int ret = EXIT_SUCCESS;
    int opt;
    int no_window = 0;
    int demonize = 0;
    int auto_trig = 0;
    const char *doc_root = DEFAULT_DOCUMENT_ROOT;
    struct server_param server_param =
    {
        .sample_rate = SAMPLE_RATE_HZ,
        .vbuf = NULL,
        .sbuf = NULL,
    };
    //Specifying the expected options
    const struct option long_options[] = 
    {
        {"nowindow",    no_argument,        0,  'n' },
        {"daemon",      no_argument,        0,  'd' },
        {"auto",        no_argument,        0,  'a' },
        {"docroot",     required_argument,  0,  'r' },
        {0,             0,                  0,  0   }
    };
    
    opterr=0;
    while ((opt = getopt_long(argc, argv,"adnr:", long_options, NULL)) != -1) 
    {
        switch (opt) 
        {
           case 'n':
                no_window = 1;
                break;
            case 'd' :
                demonize = 1;
                break;
            case 'a' :
                auto_trig = 1;
                break;
            case 'r' : 
                 doc_root = optarg;
                 break;
            default :
                printf(g_usage, argv[0]);
                return EXIT_FAILURE;
        }
    }  
    
    if (server_param.sample_rate <= 0.0f) 
    {
        printf(g_usage, argv[0]);
        return (EXIT_FAILURE);
    }
    
    //Run as a daemon if specified in command line. MUST preceed any file I/O
    if (demonize)
    {
        if (daemon(1,0) < 0)
            perror("daemon");
    }
     
    //create and initialize the web server
    struct mg_server *websvr;
    if (!(websvr = mg_create_server((void *)&server_param, web_evt_handler)))
    {
        fprintf(stderr, "ERROR mg_create_server\n");
        return (EXIT_FAILURE);
    }
    //set web server configuration
    mg_set_option(websvr, "listening_port", DEFAULT_LISTENING_PORT);
    mg_set_option(websvr, "document_root", doc_root);
    
    //Open input stream
    int fd_stream = open(DEV_STREAM_IN, O_RDONLY);
    if (fd_stream < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        mg_destroy_server(&websvr);
        return (EXIT_FAILURE);
    }
    
    //open analog input
    int fd_ain = open(DEV_AIN, O_RDONLY);
    if (fd_ain < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(fd_stream);
        mg_destroy_server(&websvr);
        return (EXIT_FAILURE);
    }
    
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, sigint_handler);

    //configure sampling rate. The actual rate is returned on success
    dt78xx_clk_config_t cfg;
    cfg.clk_freq = server_param.sample_rate;
    cfg.ext_clk = 0; //internal clock
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_SET, &cfg))
    {
        perror("IOCTL_SAMPLE_CLK_SET");    
        goto _exit;
    }
    server_param.sample_rate = cfg.clk_freq; //actual rate
    
    //write channel mask
    chan_mask_t chan_mask = chan_mask_ain0;
    if (ioctl(fd_stream, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //Channel gain, coupling and current source
    dt78xx_ain_config_t ain_cfg;
    ain_cfg.gain = DEFAULT_GAIN; 
    ain_cfg.ac_coupling = 0; //dc coupling
    ain_cfg.current_on = 0; //current source off
    ain_cfg.ain = 0; //AIN0
    if (ioctl(fd_ain, IOCTL_AIN_CFG_SET, &ain_cfg))
    {
        fprintf(stderr, "IOCTL_AIN_CFG_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //configure trigger on AIN0
    dt78xx_trig_config_t trig_cfg;
    trig_cfg.src_cfg.threshold.ain = 0; //AIN0
    if (auto_trig) //auto == software trigger
        trig_cfg.src = trig_src_sw;
    else           //default trigger == threshold trigger
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

    //Create and initialize AIO structures
    struct aio_struct *aio = aio_create(fd_stream, 0, NULL, NULL);
    if (!aio)
    {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //size each buffer to hold the specified samples for each channel
    int buflen = aio_buff_size(NUM_SAMPLES, chan_mask, 
                                &server_param.num_samples);
    void **buf_array = aio_buff_alloc(aio, NUM_BUFS, buflen);
    if (!buf_array)
    {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    //allocate a buffer to hold the raw values converted to volts
    server_param.vbuf = fftwf_malloc(sizeof(struct ws_buffer)+
                                sizeof(float)*server_param.num_samples*NUM_BUFS);
    if (!server_param.vbuf)
    {
        fprintf(stderr, "ERROR server_param.vbuf\n");
        goto _exit;
    }
    
    //allocate a buffer to hold the FFT spectral amplitudes
    server_param.sbuf = fftwf_malloc(sizeof(struct ws_buffer)+
                                     sizeof(float)*((server_param.num_samples/2)+1)*NUM_BUFS);
    if (!server_param.sbuf)
    {
        fprintf(stderr, "ERROR server_param.sbuf\n");
        goto _exit;
    }
    
    //complex output of FFTW
    fftwf_complex *fft_cmplx = fftwf_malloc (sizeof(fftwf_complex)*
                                            ((server_param.num_samples/2)+1)*NUM_BUFS);
    if (!fft_cmplx)
    {
        fprintf(stderr, "ERROR fft_cmplx\n");
        goto _exit;
    }
    
    //FFTW plan
    fftwf_plan fft_plan = fftwf_plan_dft_r2c_1d (server_param.num_samples, 
                                                 server_param.vbuf->values, 
                                                 fft_cmplx, 
                                                 FFTW_ESTIMATE);
    if (!fft_plan)
    {
        fprintf(stderr, "ERROR fft_plan\n");
        goto _exit;
    }
   
    struct fft_window *bh_win=NULL;
    //Infinite loop until aborted by ctrl-C
    while (!g_quit)
    {
        //submit the buffers for Asynchronous IO
        if (aio_start(aio))
        {
            fprintf(stderr, "ERROR aio_start\n");
            break;
        }
        
        //arm 
        if ((ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0)))   
        {
            fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            break;
        }
        
        /* issue a software start; this is redundant if trigger source is 
         * threshold trigger or external trigger */ 
        if ((ioctl(fd_stream, IOCTL_START_SUBSYS, 0)))   
        {
            fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            break;
        }
        
        //wait for all buffers to complete and poll the web server
        int buf_done = 0;
        while (!g_quit && (buf_done < NUM_BUFS))
        {
            mg_poll_server(websvr, 100);
            int ret = aio_wait(aio, 0);
            if (ret < 0) //error
                break;
            buf_done += ret;
        }
        
        //Stop streaming after buffer completion
        ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);  
        aio_stop(aio);

        //convert the raw values to voltage
        float *out = server_param.vbuf->values;
        for (buf_done=0; buf_done < NUM_BUFS; ++buf_done)
        {
#ifdef DT7837
            //AIN channels are 32-bits
            int32_t *raw = buf_array[buf_done];
#elif DT7816    
            //AIN channels are 16-bits
            int16_t *raw = buf_array[buf_done];
#endif
            for (int sample=0; sample < server_param.num_samples; 
                 ++sample, ++raw, ++out)
            {
                *out = raw2volts(*raw, DEFAULT_GAIN); 
            }
        }
        
        //Iterate over all web connections, and push volt data to websocket clients
        for (struct mg_connection *conn = mg_next(websvr, NULL); conn != NULL; 
             conn = mg_next(websvr, conn)) 
        {
            if (conn->is_websocket)
            {
                if (conn->connection_param == (void*)ws_type_waveform)
                    cb_waveform(conn);
            }
        }  
        
        if (!no_window)
        {
            //Apply window funtion to acquired data,
            bh_win = blackman_harris_window(bh_win, server_param.vbuf->values, 
                                            server_param.num_samples);
            if (!bh_win)
            {
                fprintf(stderr, "ERROR malloc window\n");
                break;
            }
        }
        
        //Compute FFT 
        fftwf_execute(fft_plan);
        
        //Compute spectral magnitudes; see figure 12 in the following
        //http://www.staff.vu.edu.au/msek/frequency%20analysis%20-%20fft.pdf
        out = server_param.sbuf->values;
        float fmax = log10f(DEFAULT_FS_V); //full scale 10V
        for (int j=0; j < (server_param.num_samples/2)+1; ++j, ++out)
        {
            float mag = (fft_cmplx[j][0])*(fft_cmplx[j][0]) + 
                        (fft_cmplx[j][1])*(fft_cmplx[j][1]);
            mag = 2.0f*sqrtf(mag)/server_param.num_samples;
            if (j==0) //DC correction
                mag /= 2.0f;
            *out = 20.0 *(log10f(mag) - fmax);
        }
         
        //Iterate over all web connections, and push spectrum to websocket clients
        for (struct mg_connection *conn = mg_next(websvr, NULL); conn != NULL; 
             conn = mg_next(websvr, conn)) 
        {
            if (conn->is_websocket)
            {
                if (conn->connection_param == (void*)ws_type_spectrum)
                    cb_fft_spectrum(conn);
            }
        }
        //delay to prevent web browsers to be swamped with data
        usleep(50*1000);
    }
      
_exit : 
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    aio_stop(aio);
    aio_destroy(aio);
    if (fd_ain > 0)
        close(fd_ain);
    if (fd_stream > 0)
        close(fd_stream);
    mg_destroy_server(&websvr);
    if (server_param.vbuf)
        fftwf_free(server_param.vbuf);
    if (server_param.sbuf)
        fftwf_free(server_param.sbuf);
    if (fft_cmplx)
        fftwf_free (fft_cmplx);
    if (fft_plan)
        fftwf_destroy_plan(fft_plan);
    if (bh_win)
        free(bh_win);
    return (ret);
}

/******************************************************************************
 * Callback to process HTTP requests invoked by mg_poll_server 
 * @param conn  : web connection
 * @param ev
 * @return      : MG_TRUE if callback handled request, MG_FALSE if default
 *                handler is to be invoked 
 */
static int web_evt_handler(struct mg_connection *conn, enum mg_event ev) 
{
    const struct url_handler *p;
    switch (ev) 
    {
        case MG_AUTH: 
            return MG_TRUE;
            
        case MG_REQUEST: 
            //printf("MG_REQUEST %s\n", conn->uri);
            //Check if the URL must be handled by a specific handler
            p = g_url_handler;
            while (p->url && strcmp(conn->uri, p->url)) 
                ++p;
            if (p && p->handler)
                return (p->handler(conn));
             //let libmongoose handle all other requests
            return MG_FALSE;
            
        case MG_CLOSE:
            //printf("MG_CLOSE %s\n", conn->uri);
            return MG_FALSE;
          
        case MG_WS_CONNECT:  // New websocket connection established
        {
            //printf("MG_WS_CONNECT %s\n", conn->uri);
            p = g_url_handler;
            while (p->url && strcmp(conn->uri, p->url)) 
                ++p;
            if (p && p->handler)
                return (p->handler(conn));
            return MG_FALSE;
        }
        default:
            return MG_FALSE;
    }
}

/******************************************************************************
 * Handler for URL /boardname.get. This sends the string identifying the
 * specific board
 * @param conn
 * @return 
 */
static enum mg_result cb_board_name(struct mg_connection *conn)
{
#ifdef DT7837   
    mg_printf_data(conn, "DT7837");
#elif DT7816
    mg_printf_data(conn, "DT7816");
#endif    
    return MG_TRUE;    
}

/******************************************************************************
 * Handler for URL /samplerate.get. This sends the sampling rate
 * @param conn
 * @return 
 */
static enum mg_result cb_sample_rate(struct mg_connection *conn)
{
    mg_send_data(conn, 
                &((struct server_param *)(conn->server_param))->sample_rate,
                sizeof(float));
    return MG_TRUE;    
}
/******************************************************************************
 * Handler for URL /spectrum.get. This sends the FFT data
 * @param conn
 * @return 
 */
static enum mg_result cb_fft_spectrum(struct mg_connection *conn)
{
    if (!conn->connection_param)
    {
        conn->connection_param = (void *)ws_type_spectrum;
        return MG_FALSE;
    }
        
    struct ws_buffer *sbuf = ((struct server_param *)(conn->server_param))->sbuf;
    sbuf->type = ws_type_spectrum;
    sbuf->num_samples = ((struct server_param *)(conn->server_param))->num_samples/2+1;
    mg_websocket_write(conn, WEBSOCKET_OPCODE_BINARY, (void *)sbuf, 
                       (sizeof(struct ws_buffer)+
                        sizeof(float)*
                        (((struct server_param *)(conn->server_param))->num_samples/2+1)*
                        NUM_BUFS));
    return MG_TRUE;    
}

/******************************************************************************
 * Handler for URL /waveform.get. This sends the raw waveform data
 * @param conn
 * @return MG_FALSE when connected, MG_TRUE for other web events
 */
static enum mg_result cb_waveform(struct mg_connection *conn)
{
    if (!conn->connection_param)
    {
        conn->connection_param = (void *)ws_type_waveform;
        return MG_FALSE;
    }
        
    struct ws_buffer *vbuf = ((struct server_param *)(conn->server_param))->vbuf;
    vbuf->type = ws_type_waveform;
    vbuf->num_samples = ((struct server_param *)(conn->server_param))->num_samples;
    mg_websocket_write(conn, WEBSOCKET_OPCODE_BINARY, (void *)vbuf, 
                       (sizeof(struct ws_buffer)+
                        sizeof(float)*
                        ((struct server_param *)(conn->server_param))->num_samples*
                        NUM_BUFS));
    return MG_TRUE;    
}

/******************************************************************************
 * 4 term Blackman Harris Window. 
 * See https://en.wikipedia.org/wiki/Window_function
 * @param bh            : pointer to struct fft_window w/t Blackman Harris window
 * @param buf           : pointer to buffer with samples
 * @param num_samples   : number of samples in buffer
 * @return              : pointer to array with Blackman Harris window
 */
static struct fft_window *blackman_harris_window(struct fft_window *bh, 
                                                float *buf, int num_samples)
{
    if (!bh)
    {
        bh = malloc(sizeof(struct fft_window)+ sizeof(float)*(num_samples-1));
        if (!bh)
            return NULL;
        //Generate 4-term Blackman Harris window
        float z = (2.0f * M_PI)/(num_samples-1);
        bh->coherent_gain = 0.0f;
        //calculate coherent gain = Sum(w]j])/(#samples)
        for (int j=0; bh && (j < num_samples); ++j)
        {
            bh->w[j] = 0.35875f - (0.48829f*cos(j*z)) + (0.14128f*cos(2*j*z))
                        -(0.01168f * cos(3*j*z) );
            bh->coherent_gain += bh->w[j];
        }
        bh->coherent_gain /= num_samples;
    }
    
    //Apply the BH window and scale with the coherent gain
    if (bh && buf)
    {
        for (int j=0; j < num_samples; ++j)
            buf[j] *= (bh->w[j]/bh->coherent_gain);
    }
    return (bh);
}
