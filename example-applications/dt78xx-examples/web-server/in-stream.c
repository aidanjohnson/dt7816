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
  ****************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

#include "dt78xx_ioctl.h"
#include "webdefs.h"
#include "dt78xx_misc.h"
#include "dt78xx_aio.h"

/******************************************************************************
 * Macros
 */
#define BUFF_DONE_LED               (0)  //Debug led flashed on each buffer done                        
#define OVERRUN_LED                 (1)  //Debug led flashed on overrun                        
#define WAIT_TIMEOUT_MS             (100) //-1 for indefinite wait
#define DEFAULT_NUM_BUFFS           (3)
#define DEFAULT_SAMPLES_PER_CHAN    (1000)

/******************************************************************************
 * Data types
 */

//Status message sent via web socket
struct ws_acq_status
{
    int download;       //1=download data as CSV 
    int overrun;        //1=buffer overrun  
    uint32_t buff_done; //#of buffers completed since acquisition started
};
/******************************************************************************
 * Functions
 */

/******************************************************************************
 * Globals
 */


static int g_samples_per_chan = DEFAULT_SAMPLES_PER_CHAN;
static int g_num_buffs = DEFAULT_NUM_BUFFS;
static int g_queue_empty_stop = 1;  //Stop on buffer overrun
static int g_requeue = 0;      //requeue buffers after processing      
static chan_mask_t g_chan_mask; //cached on acquisition start
static int g_queue_empty = 0;       //#of times buffer overran while acquiring
static int g_buffs_done = 0;    //#of buffers done
void **g_buff_array;           //Array of pointers to input buffers
#ifdef DT7837       
static int g_chan_gain[AIN_MAX]; //channel gains cached on acquisition start
#endif
#include <linux/limits.h>

/******************************************************************************
 * Enhanced version of mg_send_file() that correctly prepends the "document_root"
 * to the file name
 * @param conn
 */
enum mg_result  mg_send_file_ex(struct mg_connection *conn)
{
    char path[PATH_MAX];
    snprintf(path, sizeof(path), 
#ifdef DT7837   
             "%sdt7837/in-stream.html",
#else
             "%sdt7816/in-stream.html",
#endif
             mg_get_option(g_server, "document_root"));
    mg_send_file(conn, path);
    return MG_MORE; // It is important to return MG_MORE after mg_send_file!
}

/******************************************************************************
 * Send the current status to a web socket connection opened to "/status.io"
 * @param conn : web socket connection
 */
static void ws_status_send(struct mg_connection *conn)
{
    struct ws_acq_status ws;
    ws.download = (g_buffs_done && g_queue_empty && !g_requeue);
    ws.overrun = g_queue_empty; 
    ws.buff_done = g_buffs_done;
    mg_websocket_write(conn, WEBSOCKET_OPCODE_BINARY, (void *)&ws, sizeof(ws));
}

/******************************************************************************
 * Send the current status to all web socket connections opened to "/status.io"
 */
static void ws_status_broadcast(void)
{
    struct mg_connection *conn;  
    //Iterate over all connections, and push data to websocket ones.
    for (conn = mg_next(g_server, NULL); conn != NULL; 
            conn = mg_next(g_server, conn)) 
    {
        if (conn->is_websocket && (conn->connection_param == (void*)ws_id_acq_status)) 
        {
            ws_status_send(conn);
        }
    }    
}

/******************************************************************************
 * Input stream empty signal handler
 * @param i   : signal number set by 
 */
void in_stream_empty_cb(int i) 
{
    PRINT("%s(%d) %s\n", __func__, i,g_queue_empty_stop?"STOP":"");
    ++g_queue_empty;
#if (defined OVERRUN_LED) && (OVERRUN_LED > -1) && (OVERRUN_LED < 8)
    dt78xx_led_t led;
    led.mask = (1<<OVERRUN_LED);    
    led.state = (1<<OVERRUN_LED);
    ioctl(fd_in_stream, IOCTL_LED_SET, &led);
#endif    
    if (g_queue_empty_stop && (g_buffs_done==g_num_buffs)) //Stop on queue empty
    {
        if (ioctl(fd_in_stream, IOCTL_STOP_SUBSYS, 0))
           perror("IOCTL_STOP_SUBSYS");
        aio_stop(g_aio_in);
    }
    ws_status_broadcast();
}

/******************************************************************************
 * AIO buffer done callback
 * @param buff : pointer to buffer with samples from enabled channels
 * @param len  : length of buffer; this is an integral multiple of equal number
 *               of samples from all enabled channels
 * @return     : The return value determines whether this buffer will be 
 *               resubmitted for continued AIO operations 
 *               0 = do not requeue, 1= requeue 
 */
int in_buffer_done_cb(void *buff, int len)
{
    ++g_buffs_done;
    
    PRINT("%s %s\n", __func__, g_queue_empty && g_queue_empty_stop?"STOP":"");
    //If operation was stopped on queue empty, clean up after all buffers have
    //been dequeued and processed
    if (g_queue_empty_stop && g_queue_empty && (g_buffs_done==g_num_buffs)) 
    {
        if (ioctl(fd_in_stream, IOCTL_STOP_SUBSYS, 0))
           perror("IOCTL_STOP_SUBSYS");
        aio_stop(g_aio_in);
    }
    
    // Buffer processing here
#if (defined BUFF_DONE_LED) && (BUFF_DONE_LED > -1) && (BUFF_DONE_LED < 8)
    dt78xx_led_t led;
    led.mask = (1<<BUFF_DONE_LED);    
    led.state = (1<<BUFF_DONE_LED);
    ioctl(fd_in_stream, IOCTL_LED_SET, &led);
#endif    
    
    //Process completed buffers here  
    
    ws_status_broadcast();
    
#if (defined BUFF_DONE_LED) && (BUFF_DONE_LED > -1) && (BUFF_DONE_LED < 8)
    led.state = 0;
    ioctl(fd_in_stream, IOCTL_LED_SET, &led);
#endif  
    return g_requeue;
}

/******************************************************************************
 * Handler for HTTP GET and POST on URL "/din-cfg.io". 
 * When the static page "in-stream.html" is displayed and the user clicks on the 
 * digital input configuration menu, the "dialog box" (i.e form) identified by 
 * #din-cfg is displayed. The GET and POST from that form are described below
 *  
 * GET : When the form is displayed it performs a GET on url "/din-cfg.io".
 * This handler then reads enabled channels from the board and sends the 
 * configuration as a list of id=value pairs separated by &. The id is the id
 * of the HTML element in the page and the value is that element's value
 * 
 * POST : When the form is submitted, this handler parses the CGI encoded
 * name=value pairs enables/disables digital inputs in the stream configuration
 * in the board
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_din_cfg(struct mg_connection *conn)
{
    char value[32];
    //Get all enabled channels 
    uint32_t mask;
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_GET, (chan_mask_t*)&mask))
       return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_GET"));
    
    /* ------------------------------------------
     * handle GET 
     * ------------------------------------------*/
    if (!strcmp(conn->request_method, "GET"))
    {
        mg_send_header(conn, "Content-Type", "text/plain");
        mg_printf_data(conn, "#din_enable=%d", mask&chan_mask_din?1:0);
        return MG_TRUE;
    }
    
    /* ------------------------------------------
     * handle POST 
     * ------------------------------------------*/
    mask &= ~chan_mask_din;
    //Digital input enable <checkbox> and will be absent if unchecked
    if ((mg_get_var(conn, "din_enable", value, sizeof(value))) > 0)
        mask |= chan_mask_din;
    //Update the channel mask
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_SET, &mask))
       return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_SET"));

    return (mg_send_file_ex(conn));
}

/******************************************************************************
 * Handler for HTTP GET and POST on URL "/ain-cfg.io". 
 * When the static page "in-stream.html" is displayed and the user clicks on the 
 * Analog Input configuration menu, the "dialog box" (i.e form) identified by 
 * #ain-cfg is displayed. The GET and POST from that form are described below
 *  
 * GET : When the form is displayed it performs a GET on url "/ain-cfg.io".
 * This handler then reads from the board and sends the configuration as a list 
 * of id=value pairs separated by &. The id is the id of the HTML 
 * element in the page and the value is that element's value
 * 
 * POST : When the form is submitted, this handler parses the CGI encoded
 * name=value pairs and writes the resultant configuration to the board
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_ain_cfg(struct mg_connection *conn)
{
    int i;
    char name[32], value[32];
    chan_mask_t mask; 
#ifdef DT7837       
    dt78xx_ain_config_t cfg;
#endif
    /* ------------------------------------------
     * handle POST 
     * ------------------------------------------*/
    if (!strcmp(conn->request_method, "POST"))
    {
        mask = 0;
        //get config of each AIN channel
        for (i=0; i < AIN_MAX; ++i)
        {
#ifdef DT7837       
            memset(&cfg, 0, sizeof(cfg));
            cfg.ain = i;
            //gain is from <select>
            sprintf(name, "%d_gain", i);
            mg_get_var(conn, name, value, sizeof(value));
            cfg.gain = (value[0]=='1')?1:0; //0=x1, 1=x10 gain
            //coupling from <select>
            sprintf(name, "%d_coupling", i);
            mg_get_var(conn, name, value, sizeof(value));
            cfg.ac_coupling = (value[0]=='1')?1:0; //0=DC, 1=AC
            //current source is <checkbox> and will be absent if unchecked
            sprintf(name, "%d_current", i);
            if (mg_get_var(conn, name, value, sizeof(value)) > 0)
                cfg.current_on = 1;
            
            //set the channel conguration
            if (ioctl(fd_ain, IOCTL_AIN_CFG_SET, &cfg))
                return (printf_errno_html(conn, errno, "IOCTL_AIN_CFG_SET"));
#endif            
            //channel enable is <checkbox> and will be absent if unchecked
            sprintf(name, "%d_enable", i);
            if (mg_get_var(conn, name, value, sizeof(value)) > 0)
                mask |= (i==0)?chan_mask_ain0:(i==1)?chan_mask_ain1:
                        (i==2)?chan_mask_ain2:(i==3)?chan_mask_ain3:
                        (i==4)?chan_mask_ain4:(i==5)?chan_mask_ain5:
                        (i==6)?chan_mask_ain6:(i==7)?chan_mask_ain7:0;
        }
        //Get all enabled channels and update the channel mask
        chan_mask_t tmp;
        if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_GET, &tmp))
           return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_GET"));

        tmp &= (chan_mask_din|chan_mask_meas_ctr|chan_mask_tach);
        mask |= tmp;
        if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_SET, &mask))
           return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_SET"));

        return (mg_send_file_ex(conn));
    }
    
     /* ------------------------------------------
     * handle GET
     * ------------------------------------------*/
    //get the mask of AIN channels enabled in input stream 
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_GET, &mask))
       return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_GET"));
       
    mg_send_header(conn, "Content-Type", "text/plain");
    //enabled ??
    mg_printf_data(conn, "&#0_enable=%d", (mask & chan_mask_ain0)?1:0);
    mg_printf_data(conn, "&#1_enable=%d", (mask & chan_mask_ain1)?1:0);
    mg_printf_data(conn, "&#2_enable=%d", (mask & chan_mask_ain2)?1:0);
    mg_printf_data(conn, "&#3_enable=%d", (mask & chan_mask_ain3)?1:0);
#ifdef DT7816   
    //Four additional AIN channels
    mg_printf_data(conn, "&#4_enable=%d", (mask & chan_mask_ain4)?1:0);
    mg_printf_data(conn, "&#5_enable=%d", (mask & chan_mask_ain5)?1:0);
    mg_printf_data(conn, "&#6_enable=%d", (mask & chan_mask_ain6)?1:0);
    mg_printf_data(conn, "&#7_enable=%d", (mask & chan_mask_ain7)?1:0);
#endif    
#ifdef DT7837       
    //get config of each AIN channel, 
    for (i=0; i < AIN_MAX; ++i, mask >>= 1)
    {
       memset(&cfg, 0, sizeof(cfg));
       cfg.ain = i;
       if (ioctl(fd_ain, IOCTL_AIN_CFG_GET, &cfg))
           return (printf_errno_html(conn, errno, "IOCTL_AIN_CFG_GET"));
       //gain
       mg_printf_data(conn, "&#%d_gain=%d", i, cfg.gain);
       //coupling
       mg_printf_data(conn, "&#%d_coupling=%d", i, cfg.ac_coupling);
       //current source
       mg_printf_data(conn, "&#%d_current=%d", i, cfg.current_on);
    }
#endif       
    return MG_TRUE;
}

/******************************************************************************
 * Handler for HTTP GET and POST on URL "/trig-cfg.io". 
 * When the static page "in-stream.html" is displayed and the user clicks on the 
 * Trigger configuration menu, the "dialog box" (i.e form) identified by 
 * #trig-cfg is displayed. The GET and POST from that form are described below
 *  
 * GET : When the form is displayed it performs a GET on url "/trig-cfg.io".
 * This handler then reads from the board and sends the configuration as a list 
 * of id=value pairs separated by &. The id is the id of the HTML 
 * element in the page and the value is that element's value
 * 
 * POST : When the form is submitted, this handler parses the CGI encoded
 * name=value pairs and writes the resultant trigger configuration to the board
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_trig_cfg(struct mg_connection *conn)
{
    char value[32];
    dt78xx_trig_config_t cfg;
    
    memset(&cfg, 0, sizeof(cfg));
    /* ------------------------------------------
     * handle POST 
     * ------------------------------------------*/
    if (!strcmp(conn->request_method, "POST"))
    {
        if (mg_get_var(conn, "trig-src", value, sizeof(value)) < 0)
            return (printf_err_msg(conn, "Missing trig-src"));
        
        cfg.src = value[0]-'0';
        if (cfg.src == trig_src_ext)
        {
            //din is a single decimal digit
            if (mg_get_var(conn, "din", value, sizeof(value)) > 0)
                cfg.src_cfg.ext.din = value[0]-'0';
            //edge is single decimal digit
            if (mg_get_var(conn, "din-edge", value, sizeof(value)) > 0)
                cfg.src_cfg.ext.edge_rising = value[0]-'0';
        }
        else if (cfg.src == trig_src_threshold)
        {
            //ain is a single decimal digit
            if (mg_get_var(conn, "ain", value, sizeof(value)) > 0)
                cfg.src_cfg.threshold.ain = value[0]-'0';
            //edge is single decimal digit
            if (mg_get_var(conn, "ain-edge", value, sizeof(value)) > 0)
                cfg.src_cfg.threshold.edge_rising = value[0]-'0';
            //threshold is a float; it has to be multiplied by specified channel's
            //full scale
            if (mg_get_var(conn, "ain-threshold", value, sizeof(value)) > 0)
            {
                float f;
                f = strtof(value, NULL);
#ifdef DT7837
                dt78xx_ain_config_t ain_cfg;
                memset(&ain_cfg, 0, sizeof(ain_cfg));
                ain_cfg.ain = cfg.src_cfg.threshold.ain;
                if (ioctl(fd_ain, IOCTL_AIN_CFG_GET, &ain_cfg))
                     return (printf_errno_html(conn, errno, "IOCTL_AIN_CFG_GET"));
                
                cfg.src_cfg.threshold.level = 
                                    volts2raw(f, ain_cfg.gain);
#elif DT7816
                cfg.src_cfg.threshold.level = volts2raw(f, 1);
#endif
            }
        }
        //set the trigger configuration for the input stream 
        if (ioctl(fd_in_stream, IOCTL_START_TRIG_CFG_SET, &cfg))
            return (printf_errno_html(conn, errno, "IOCTL_START_TRIG_CFG_SET"));

        return (mg_send_file_ex(conn));
    }
    
     /* ------------------------------------------
     * handle GET
     * ------------------------------------------*/
    //get the trigger configuration for the input stream 
    if (ioctl(fd_in_stream, IOCTL_START_TRIG_CFG_GET, &cfg))
       return (printf_errno_html(conn, errno, "IOCTL_START_TRIG_CFG_GET"));
     
    mg_send_header(conn, "Content-Type", "text/plain");
    //source
    mg_printf_data(conn, "#trig-src=%d", cfg.src);
    if (cfg.src == trig_src_ext)
    {
        //Digital input
        mg_printf_data(conn, "&#din=%d", cfg.src_cfg.ext.din);
        //Digital input edge
        mg_printf_data(conn, "&#din-edge=%d", cfg.src_cfg.ext.edge_rising);
    }
    else if (cfg.src == trig_src_threshold)
    {
        float f;
        //Analogl input
        mg_printf_data(conn, "&#ain=%d", cfg.src_cfg.threshold.ain);
        //Analog input edge
        mg_printf_data(conn, "&#ain-edge=%d", cfg.src_cfg.threshold.edge_rising);
#ifdef DT7837
        //convert the threshold to voltage corresponding to the selected 
        //channel's gain
        dt78xx_ain_config_t ain_cfg;
        memset(&ain_cfg, 0, sizeof(ain_cfg));
        ain_cfg.ain = cfg.src_cfg.threshold.ain;
        if (ioctl(fd_ain, IOCTL_AIN_CFG_GET, &ain_cfg))
            return (printf_errno_html(conn, errno, "IOCTL_AIN_CFG_GET"));
            
        f = raw2volts(cfg.src_cfg.threshold.level, ain_cfg.gain);
#elif DT7816
        f = raw2volts(cfg.src_cfg.threshold.level, 1);
#endif        
        mg_printf_data(conn, "&#ain-threshold=%.3f", f);
    }
    return MG_TRUE;
}

/******************************************************************************
 * Handler for HTTP GET and POST on URL "/clk-cfg.io". 
 * When the static page "in-stream.html" is displayed and the user clicks on the 
 * Clock configuration menu, the "dialog box" (i.e form) identified by 
 * #clk-cfg is displayed. The GET and POST from that form are described below
 *  
 * GET : When the form is displayed it performs a GET on url "/clk-cfg.io".
 * This handler then reads the sampling rate from the board and sends the 
 * configuration as a list of id=value pairs separated by &. The id is the id
 * of the HTML element in the page and the value is that element's value
 * 
 * POST : When the form is submitted, this handler parses the CGI encoded
 * name=value pairs and writes the resultant clock rate to the board
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_clk_cfg(struct mg_connection *conn)
{
    char value[32];
    dt78xx_clk_config_t cfg;
    /* ------------------------------------------
     * handle POST 
     * ------------------------------------------*/
    if (!strcmp(conn->request_method, "POST"))
    {
        memset(&cfg, 0, sizeof(cfg));
#ifdef DT7816
        if (mg_get_var(conn, "clk_din", value, sizeof(value)))
            cfg.ext_clk_din = atoi(value);    
        if (mg_get_var(conn, "clk_src", value, sizeof(value)))
        {
            if (atoi(value)!=0) //external
            {
                if (mg_get_var(conn, "clk_bar", value, sizeof(value))>0)
                    cfg.ext_clk=2;
                else
                    cfg.ext_clk=1;
            }
        }
#endif
        if (mg_get_var(conn, "clk_freq", value, sizeof(value)))
            cfg.clk_freq = strtof(value, NULL);    
        if (ioctl(fd_in_stream, IOCTL_SAMPLE_CLK_SET, &cfg))
            return (printf_errno_html(conn, errno, "IOCTL_SAMPLE_CLK_SET"));

        return (mg_send_file_ex(conn));
    }  
    
    /* ------------------------------------------
     * handle GET
     * ------------------------------------------*/
    if (ioctl(fd_in_stream, IOCTL_SAMPLE_CLK_GET, &cfg))
        return (printf_errno_html(conn, errno, "IOCTL_SAMPLE_CLK_GET"));
    mg_send_header(conn, "Content-Type", "text/plain");
#ifdef DT7816
    mg_printf_data(conn, "#clk_src=%d", (cfg.ext_clk!=0)?1:0);
    mg_printf_data(conn, "&#clk_din=%d", cfg.ext_clk_din);
    mg_printf_data(conn, "&#clk_bar=%d", (cfg.ext_clk==2)?1:0);
#endif    
    
    mg_printf_data(conn, "&#clk_freq=%.3f", cfg.clk_freq);
    return MG_TRUE;
}

/******************************************************************************
 * Handler for HTTP GET and POST on URL "/buff-cfg.io". 
 * When the static page "in-stream.html" is displayed and the user clicks on the 
 * buffer configuration menu, the "dialog box" (i.e form) identified by 
 * #buff-cfg is displayed. The GET and POST from that form are described below
 *  
 * GET : When the form is displayed it performs a GET on url "/buff-cfg.io".
 * This handler sends the buffer configuration as a list of id=value pairs 
 * separated by &. The id is the id of the HTML element in the page and the 
 * value is that element's value
 * 
 * POST : When the form is submitted, this handler parses the CGI encoded
 * name=value pairs and saves the buffer configuration parameters to local
 * variables
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_buffer_cfg(struct mg_connection *conn)
{
    char value[32];
    chan_mask_t mask;
    //Get all enabled channels and update the channel mask
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_GET, &mask))
       return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_GET"));
    /* ------------------------------------------
     * handle POST 
     * ------------------------------------------*/
    if (!strcmp(conn->request_method, "POST"))
    {
        acq_status_t stat;
        //buffer config can't be changed if armed
        if (ioctl(fd_in_stream, IOCTL_ACQ_STATUS_GET, &stat))
            return (printf_errno_html(conn, errno, "IOCTL_ACQ_STATUS_GET"));
        if (stat & acq_status_armed)
            return (printf_errno_html(conn, EBUSY, NULL));
        
        if (mg_get_var(conn, "sample_chan", value, sizeof(value)))
            g_samples_per_chan = strtof(value, NULL);    
        if (mg_get_var(conn, "num_buffs", value, sizeof(value)))
            g_num_buffs = strtof(value, NULL);    
        //Stop on buffer overrun <checkbox> and will be absent if unchecked
        if ((mg_get_var(conn, "overrun_stop", value, sizeof(value))) > 0)
            g_queue_empty_stop = 1;
        else
            g_queue_empty_stop = 0;
        if ((mg_get_var(conn, "resubmit", value, sizeof(value))) > 0)
            g_requeue = 1;
        else
            g_requeue = 0;
        aio_buff_size(g_samples_per_chan, mask, &g_samples_per_chan);
         
        return (mg_send_file_ex(conn));
    }  
    
    /* ------------------------------------------
     * handle GET 
     * ------------------------------------------*/
    chan_mask_t tmp;
    int chans;
    tmp = mask;
    //#of channels enabled
    for (chans = 0; tmp; chans++)
      tmp &= tmp - 1; 
    mg_send_header(conn, "Content-Type", "text/plain");
    mg_printf_data(conn, "#chan=%d", chans);
    aio_buff_size(g_samples_per_chan, mask, &g_samples_per_chan);
    mg_printf_data(conn, "&#sample_chan=%d", g_samples_per_chan);
    mg_printf_data(conn, "&#num_buffs=%d", g_num_buffs);
    mg_printf_data(conn, "&#overrun_stop=%d", g_queue_empty_stop);
    mg_printf_data(conn, "&#resubmit=%d", g_requeue);
    return MG_TRUE;
}

/******************************************************************************
 * Handler for HTTP GET and POST on url "/acq_control.io" to control acquisition. 
 * In the static page "in-stream.html" when the  user clicks on the "stop" 
 * button a GET is performed to this url. A POST is performed when the user
 * clicks the "start" button.
 * GET : Unconditionally stops acqusition; no parameters read from GET and no
 * response returned
 * POST : Attempts to start acqusition and returns a response to indicate
 * error, and no response on success
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_acq_ctrl(struct mg_connection *conn)
{
    int tmp = 0;
    int err;
    acq_status_t status;
    
    if (ioctl(fd_in_stream, IOCTL_ACQ_STATUS_GET, &status))
       return (printf_errno(conn, errno, "IOCTL_ACQ_STATUS_GET"));
    
    //GET ==> stop
    if (!strcmp(conn->request_method, "GET"))
    {
        if (ioctl(fd_in_stream, IOCTL_STOP_SUBSYS, &tmp))
           return (printf_errno(conn, errno, "IOCTL_STOP_SUBSYS"));
        aio_stop(g_aio_in);
        ws_status_broadcast();
        return (status_no_content(conn));
    }
    
    //POST ==> start
    if (ioctl(fd_in_stream, IOCTL_ACQ_STATUS_GET, &status))
       return (printf_errno(conn, errno, "IOCTL_ACQ_STATUS_GET"));
    if (status & acq_status_armed)
       return (printf_errno(conn, EBUSY, "Subsystem armed"));
    
    //Clear these so that errors in starting don't retain buffers from last acq
    g_queue_empty = 0; //clear #of overruns detected
    g_buffs_done = 0; //clear #of buffers done
    
    //Get all enabled channels; if none then error 
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_GET, (chan_mask_t*)&g_chan_mask))
       return (printf_errno(conn, errno, "IOCTL_CHAN_MASK_GET"));
    if (!g_chan_mask)
        return (printf_errno(conn, EINVAL, "No channels enabled"));
    
#ifdef DT7837
    //Get the gains for the AIN channels that are enabled
    int chan;
    chan_mask_t mask = g_chan_mask;
    mask &= (chan_mask_ain0 | chan_mask_ain1 |chan_mask_ain2 | chan_mask_ain3);
    for (chan = 0; mask; mask >>= 1, ++chan)
    {
        dt78xx_ain_config_t cfg;
        if (!(mask & 1))
            continue;
        cfg.ain = chan;
        if (ioctl(fd_ain, IOCTL_AIN_CFG_GET, &cfg))
            return (printf_errno(conn, errno, "IOCTL_AIN_CFG_GET"));
        g_chan_gain[chan] = cfg.gain;
     }
#endif    
    //size up the new buffers  
    int size;
    size = aio_buff_size(g_samples_per_chan, g_chan_mask, &g_samples_per_chan);
    
    //allocate and  initialize buffers for asynchronous IO  
    if ((g_buff_array = aio_buff_alloc(g_aio_in, g_num_buffs, size))==NULL)
        return (printf_errno(conn, ENOMEM, "No memory"));
    
    //submit the AIO buffers
    if ((err = aio_start(g_aio_in)))
        return (printf_errno(conn, err, "Failed AIO start"));
    
    //Finally, arm and start the h/w
    tmp = 0; //unused
    if (ioctl(fd_in_stream, IOCTL_ARM_SUBSYS, &tmp))
    {
        err = errno;
        return (printf_errno(conn, err, "IOCTL_ARM_SUBSYS"));
    }
    if (ioctl(fd_in_stream, IOCTL_START_SUBSYS, &tmp))
    {
        err = errno;
         return (printf_errno(conn, err, "IOCTL_START_SUBSYS"));
    }
    return (status_no_content(conn));
}

/******************************************************************************
 * Handler for HTTP GET on url "/download.io" to download acquisition data as
 * a CSV file. This is from the static page "in-stream.html" when the  user 
 * clicks on the <a href="download.io" download> tag
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_download(struct mg_connection *conn)
{
    acq_status_t status;
    int i;
    
    ioctl(fd_in_stream, IOCTL_ACQ_STATUS_GET, &status);
    //acquiring data OR no data => can't send file
    if ((status & acq_status_armed) || !g_buffs_done) 
    {
        mg_send_status(conn, 204); //No Content
        mg_send_data(conn, "", 0); //Last chunk: mark the end of reply
        return MG_TRUE;
    }
    mg_send_header(conn, "Content-Type", "text/plain");
    
    //Print out the column headers
    if (g_chan_mask & chan_mask_ain0)
        mg_printf_data(conn, "Ain0 (V),");
    if (g_chan_mask & chan_mask_ain1)
        mg_printf_data(conn, "Ain1 (V),");
    if (g_chan_mask & chan_mask_ain2)
        mg_printf_data(conn, "Ain2 (V),");
    if (g_chan_mask & chan_mask_ain3)
        mg_printf_data(conn, "Ain3 (V),");
#ifdef DT7816 
    //four additional AIN channels in DT7816
    if (g_chan_mask & chan_mask_ain4)
        mg_printf_data(conn, "Ain4 (V),");
    if (g_chan_mask & chan_mask_ain5)
        mg_printf_data(conn, "Ain5 (V),");
    if (g_chan_mask & chan_mask_ain6)
        mg_printf_data(conn, "Ain6 (V),");
    if (g_chan_mask & chan_mask_ain7)
        mg_printf_data(conn, "Ain7 (V),");
#endif    
    if (g_chan_mask & chan_mask_tach)
        mg_printf_data(conn, "Tach (Hz),");
    if (g_chan_mask & chan_mask_meas_ctr)
        mg_printf_data(conn, "Measure Ctr (counts),");
    if (g_chan_mask & chan_mask_din)
        mg_printf_data(conn, "DIN (bits)");
    mg_printf_data(conn, "\n");
    //Format the values from each buffer
    for (i=0; i<g_num_buffs; ++i)
    {
        int j;
        void *raw = g_buff_array[i];
        /* format each the value of each enabled channel. The buffer has data
         * organized according to the enumerations in chan_mask_t, i.e 
         * AIN0,AIN1,...,AIN3,...,Tachometer,Measure Counter,DIN
         */
        for (j=0; j < g_samples_per_chan ;++j)
        {
#ifdef DT7837
            int chan;
            chan_mask_t mask = g_chan_mask;
            mask &= (chan_mask_ain0 | chan_mask_ain1 |chan_mask_ain2 | chan_mask_ain3);
            for (chan = 0; mask; mask >>= 1, ++chan)
            {
                if (!(mask & 1))
                    continue;
                mg_printf_data(conn, "%.6f,", raw2volts(*(int32_t *)raw, 
                               g_chan_gain[chan]));
                raw += sizeof(int32_t);
            }
#elif DT7816
            if (g_chan_mask & chan_mask_ain0)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
            if (g_chan_mask & chan_mask_ain1)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
            if (g_chan_mask & chan_mask_ain2)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
            if (g_chan_mask & chan_mask_ain3)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
            if (g_chan_mask & chan_mask_ain4)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
            if (g_chan_mask & chan_mask_ain5)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
            if (g_chan_mask & chan_mask_ain6)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
            if (g_chan_mask & chan_mask_ain7)
            {
                mg_printf_data(conn, "%.6f,", raw2volts(*(int16_t *)raw, 1));
                raw += sizeof(int16_t);
            }
#endif
            //Tach channel, if enabled, is 32-bits and comes after AIN channels
            if (g_chan_mask & chan_mask_tach) //tach
            {
                // frequency measured is 12,000,000 / (count - 1)
                // stale readings have ms bit set
                int stale = (*(uint32_t*)raw & ~(UINT32_MAX>>1));
                if (stale)
                {
                    *(uint32_t*)raw &= (UINT32_MAX>>1);
                }
                mg_printf_data(conn,"%f %s,", 
                    (*(uint32_t*)raw!=0)?12000000.0f/(*(uint32_t*)raw - 1):0.0f,
                    stale?"(stale)":"");
                raw += sizeof(uint32_t);
            }
            //Measure counter, if enabled, is 32-bits and comes after tach
            if (g_chan_mask & chan_mask_meas_ctr) 
            {
                // stale readings have ms bit set
                if (*(uint32_t*)raw & ~(UINT32_MAX>>1))
                {
                    *(uint32_t*)raw &= (UINT32_MAX>>1);
                    mg_printf_data(conn,"%d (stale),", *(uint32_t*)raw);
                }
                else
                    mg_printf_data(conn,"%d,", *(uint32_t*)raw);
                raw += sizeof(uint32_t);
            }
            //DIN, if enabled, is either 32-bits or 16-bits and comes last
            if (g_chan_mask & chan_mask_din) 
            {
#ifdef DT7837
                mg_printf_data(conn, "%d,", *(uint32_t *)raw & 0xff);
                raw += sizeof(uint32_t);
#elif DT7816
                mg_printf_data(conn, "%d,", *(uint16_t *)raw & 0xff);
                raw += sizeof(uint16_t);
#endif                
            }
            mg_printf_data(conn, "\n");
        }
    }
    return MG_TRUE;
}

/******************************************************************************
 * Handler for HTTP GET and POST on URL "/tach-cfg.io". 
 * 
 * GET reads the current configuration of the tachometer from the board and 
 * returns it as a list of id=value pairs separated by &. The id is the id of 
 * the HTML element in the page and the value is that element's value.
 * 
 * POST writes the tach configuration to the board
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_tach_cfg(struct mg_connection *conn)
{
    chan_mask_t mask;
    char value[32];
    dt78xx_tach_config_t cfg;
    //Get all enabled channels 
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_GET, &mask))
       return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_GET"));
    
    /* ------------------------------------------
     * handle GET 
     * ------------------------------------------*/
    if (!strcmp(conn->request_method, "GET"))
    {
        mg_send_header(conn, "Content-Type", "text/plain");
        mg_printf_data(conn, "#tach_enable=%d", (mask&chan_mask_tach)?1:0);
        //Get the tach config
        if (ioctl(fd_tach, IOCTL_TACH_CFG_GET, (chan_mask_t*)&cfg))
           return (printf_errno(NULL, errno, "IOCTL_TACH_CFG_GET"));
        mg_printf_data(conn, "&#tach_edge=%d", cfg.edge_rising);
        mg_printf_data(conn, "&#tach_stale=%d", cfg.stale_flag);
        return MG_TRUE;
    }
    
    /* ------------------------------------------
     * handle POST 
     * ------------------------------------------*/
    
    //enable <checkbox> and will be absent if unchecked, including all disabled
    //tags
    if ((mg_get_var(conn, "tach_enable", value, sizeof(value))) > 0)
        mask |= chan_mask_tach;
    else
        mask &= ~chan_mask_tach;
    //Update the channel mask
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_SET, &mask))
       return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_SET"));
    
    if (mask & chan_mask_tach)
    {
        //update the tach config
        memset(&cfg, 0, sizeof(cfg));
        if (mg_get_var(conn, "tach_edge", value, sizeof(value)) > 0)
            cfg.edge_rising = value[0]-'0';
        if (mg_get_var(conn, "tach_stale", value, sizeof(value)) > 0)
            cfg.stale_flag = 1;
        if (ioctl(fd_tach, IOCTL_TACH_CFG_SET, (chan_mask_t*)&cfg))
           return (printf_errno_html(conn, errno, "IOCTL_TACH_CFG_SET"));
    }
    return (mg_send_file_ex(conn));
}

/******************************************************************************
 * Handler for HTTP GET and POST on URL "/ctr-cfg.io". 
 * 
 * GET reads the current configuration of the measure counter from the board and 
 * returns it as a list of id=value pairs separated by &. The id is the id of 
 * the HTML element in the page and the value is that element's value.
 * 
 * POST writes the tach configuration to the board
 * 
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_mctr_cfg(struct mg_connection *conn)
{
    uint32_t mask;
    char value[32];
    dt78xx_mctr_config_t cfg;
    //Get all enabled channels 
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_GET, (chan_mask_t*)&mask))
       return (printf_errno(NULL, errno, "IOCTL_CHAN_MASK_GET"));
    
    /* ------------------------------------------
     * handle GET 
     * ------------------------------------------*/
    if (!strcmp(conn->request_method, "GET"))
    {
        mg_send_header(conn, "Content-Type", "text/plain");
        //measure counter enabled/disabled
        mg_printf_data(conn, "&#mctr_enable=%d", mask & chan_mask_meas_ctr);
        //measure counter config
        if (ioctl(fd_mctr, IOCTL_MCTR_CFG_GET, &cfg))
            return (printf_errno(NULL, errno, "IOCTL_MCTR_CFG_GET"));
        mg_printf_data(conn, "&#mctr_start=%d", cfg.start_sel);
        mg_printf_data(conn, "&#mctr_stop=%d", cfg.stop_sel);
        mg_printf_data(conn, "&#mctr_stale=%d", cfg.stale_flag);
        return MG_TRUE;
    }
    
    /* ------------------------------------------
     * handle POST 
     * ------------------------------------------*/
    
    //enable <checkbox> and will be absent if unchecked, including all disabled
    //tags
    if ((mg_get_var(conn, "mctr_enable", value, sizeof(value))) > 0)
        mask |= chan_mask_meas_ctr;
    else
        mask &= ~chan_mask_meas_ctr;
    //Update the channel mask
    if (ioctl(fd_in_stream, IOCTL_CHAN_MASK_SET, &mask))
       return (printf_errno_html(conn, errno, "IOCTL_CHAN_MASK_SET"));
    
    if (mask & chan_mask_meas_ctr)
    {
        //update the measure counter config
        memset(&cfg, 0, sizeof(cfg));
        if (mg_get_var(conn, "mctr_start", value, sizeof(value)) > 0)
            cfg.start_sel = atoi(value);
        if (mg_get_var(conn, "mctr_stop", value, sizeof(value)) > 0)
            cfg.stop_sel = atoi(value);
        if (mg_get_var(conn, "mctr_stale", value, sizeof(value)) > 0)
            cfg.stale_flag = 1;
        if (ioctl(fd_mctr, IOCTL_MCTR_CFG_SET, (chan_mask_t*)&cfg))
           return (printf_errno_html(conn, errno, "IOCTL_MCTR_CFG_SET"));
    }
    
    return (mg_send_file_ex(conn));
}

/******************************************************************************
 * Handler for web socket connection to "/status.io"
 * @param conn
 * @return MG_TRUE
 */
enum mg_result ev_handler_status(struct mg_connection *conn)
{
    //add identifier for this specified connection
    conn->connection_param = (void *)ws_id_acq_status;     
    ws_status_send(conn);
    return MG_TRUE;
}
