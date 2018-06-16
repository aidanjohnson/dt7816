/*****************************************************************************
 * DT78XX embedded web application definitions
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
 */
#ifndef __WEBDEFS_H_
#define __WEBDEFS_H_

#include <stdint.h>
#include "mongoose.h"

/******************************************************************************
 * Macros
 */

/*
 * Default port can be overridden by command line arguments
 */
#define DEFAULT_LISTENING_PORT  "8080"
    
#define DEFAULT_DOCUMENT_ROOT   "res/"

/* All static resources, such as html, png, jar files, must exist under
 * the DOCUMENT_ROOT directory relative to the server executable
 */
#ifdef DT7837
#define AIN_MAX     (4)    //Maximum number of AIN channels
#define AOUT_MAX    (1)    // Maximum number of AOUT channels
#elif DT7816
#define AIN_MAX     (8)    //Maximum number of AIN channels
#else
#define AIN_MAX     (0)    
#endif

#define PRINT(fmt, ...) \
    ({if (g_verbose) printf(fmt, ##__VA_ARGS__);})

/******************************************************************************
 * Data types
 */

/******************************************************************************
 * Globals
 */
 
//Device file handles for subsystems
int fd_din;          //digital input 
int fd_dout;         //digital output         
int fd_ctrtmr;       //counter timer    
int fd_ain;          //analog input
int fd_in_stream;    //input stream
int fd_tach;         //tachometer
int fd_mctr;         //measure counter

//Enable/disable printf messages. Set by command line
int g_verbose;

struct mg_server *g_server;
struct aio_struct *g_aio_in;

enum web_socket_id {ws_id_acq_status=0x1234};

/******************************************************************************
 * Correctly send the HTTP 204 "No Content" status
 * @param conn
 * @return MG_TRUE
 */
static inline enum mg_result status_no_content(struct mg_connection *conn)
{
    mg_send_status(conn, 204);
    mg_printf(conn, "\r\n"); //Mandatory; won't work without this !!
    return MG_TRUE;
}

/******************************************************************************
 * Send an HTML page with the specified NULL terminated error message in it
 * @param conn
 * @param msg
 * @return MG_TRUE
 */
enum mg_result printf_err_msg(struct mg_connection *conn, const char *msg);

/*****************************************************************************
 * Send an HTML page with the formatted errno code and error message
 * @param conn
 * @param err
 * @param fmt
 * @param ... : varargs
 * @return MG_TRUE
 */
enum mg_result printf_errno_html(struct mg_connection *conn, int err, 
                                 const char *fmt, ...);

/*****************************************************************************
 * Send a plain text formatted errno code and error message
 * @param conn
 * @param err
 * @param fmt
 * @param ... : varargs
 * @return MG_TRUE
 */
enum mg_result printf_errno(struct mg_connection *conn, int err, 
                                 const char *fmt, ...);

/******************************************************************************
 Callback function that handles a specific URL to generate a dhtml page
 Params :
    Passed from main event handler
 Return :
    MG_xx value
 **/
typedef enum mg_result (*uri_handler)(struct mg_connection *conn);   

/******************************************************************************
 * Input stream empty callback
 * @param i   : signal number SIGUSR1
 */
void in_stream_empty_cb(int i);

/******************************************************************************
 * Input/Output buffer done callbacks.
 * @param buff : See definition of buffer_done_cb_t
 * @param len  : See definition of buffer_done_cb_t
 * @return     : The return value determines whether this buffer will be 
 *               resubmitted for continued AIO operations 
 *               0 = do not resubmit, 1= resubmit 
 */
int in_buffer_done_cb(void *buff, int len);
int out_buffer_done_cb(void *buff, int len);

/******************************************************************************
 * Output stream empty callback
 * @param i   : signal number SIGUSR2
 */
void out_stream_empty_cb(int i);

/******************************************************************************
 * This macro implements the XMacro paradigm. To learn about XMacros see
 * http://www.embedded.com/design/programming-languages-and-tools/
 * 4403953/C-language-coding-errors-with-X-macros-Part-1
 
 * Table of URL to handler functions, each row has two arguments
     1      : is string that is the URL.
     2      : pointer to handler function

 *****************************************************************************/
#define URL_HANDLERS \
_("/digin.io",          ev_handler_digin)           __DELIM__ \
_("/digout.io",         ev_handler_digout)          __DELIM__ \
_("/ctrtmr_get.io",     ev_handler_ctrtmr_get)      __DELIM__ \
_("/ctrtmr_post.io",    ev_handler_ctrtmr_post)     __DELIM__ \
_("/ctrtmr.io",         ev_handler_ctrtmr_ctrl)     __DELIM__ \
_("/ain-cfg.io",        ev_handler_ain_cfg)         __DELIM__ \
_("/trig-cfg.io",       ev_handler_trig_cfg)        __DELIM__ \
_("/clk-cfg.io",        ev_handler_clk_cfg)         __DELIM__ \
_("/buff-cfg.io",       ev_handler_buffer_cfg)      __DELIM__ \
_("/acq_control.io",    ev_handler_acq_ctrl)        __DELIM__ \
_("/download.io",       ev_handler_download)        __DELIM__ \
_("/din-cfg.io",        ev_handler_din_cfg)         __DELIM__ \
_("/tach-cfg.io",       ev_handler_tach_cfg)        __DELIM__ \
_("/mctr-cfg.io",       ev_handler_mctr_cfg)        __DELIM__ \
_("/status.io",         ev_handler_status)          __DELIM__ \
_("/connector.png",     send_connector_png)         __DELIM__ \
_("/in-stream.html",    send_in_stream_page)        __DELIM__ \
_("/board-name.txt",    send_board_name)            __DELIM__ 
#endif
