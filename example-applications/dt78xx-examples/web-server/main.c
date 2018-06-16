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
 * The embedded web application executes requests sent from a browser, controls
 * the board hardware, and responds to queries from the browser. 
 * 
 *   +------------------------------------------+       
 *   |    Embedded web  application             |     
 *   +------------------+-----------------------+
 *                      |
 *                      | ioctl/read/write/ file operations to 
 *                      | virtual device files for each board subsytem                    
 *                      |
 *   +------------------+-----------------------+
 *   |        dt78xx  device driver             |    
 *   +---+-----+--------+-------+-------+-------+
 *                      |                           
 *                      |                            
 *              board hardware    * 
 * PREREQUISITES :
 * 
 * (1) All static resources, such as html, png, jar files, must exist under
 * the DOCUMENT_ROOT directory defined in webdefs.h or specified as a command
 * line option; see usage[] below
 * 
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define __USE_GNU   (1)
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>


#include "webdefs.h"
#include "dt78xx_misc.h"
#include "dt78xx_aio.h"
/******************************************************************************
 * Macros
 */

//The device files associated with subsystems
#ifdef DT7837
#define BOARD_STR "dt7837"
#elif DT7816
#define BOARD_STR "dt7816"
#else
#define BOARD_STR 
#error BOARD_TYPE not defined!!
#endif
#define DIN_SUBSYSTEM       "/dev/"BOARD_STR"-din"
#define DOUT_SUBSYSTEM      "/dev/"BOARD_STR"-dout"
#define CTRTMR_SUBSYSTEM    "/dev/"BOARD_STR"-ctr-tmr"
#define AIN_SUBSYSTEM       "/dev/"BOARD_STR"-ain"
#define IN_STREAM           "/dev/"BOARD_STR"-stream-in"
#define TACH_SUBSYSTEM      "/dev/"BOARD_STR"-tach"
#define MCTR_SUBSYSTEM      "/dev/"BOARD_STR"-measure"

/******************************************************************************
 * Data types
 */

/******************************************************************************
 * Functions
 */
static int web_event_handler(struct mg_connection *conn, enum mg_event ev); 

//Prototypes for handler functions for specific URLs
#undef  __DELIM__
#define __DELIM__ ;
#undef  _
#define _( url, handler) \
extern enum mg_result  handler(struct mg_connection *conn);

      URL_HANDLERS
#undef _
#undef __DELIM__

/******************************************************************************
 * Globals
 */

//Table of handlers for for specific URLs
#undef  __DELIM__
#define __DELIM__ ,
#undef  _
#define _( url, handler)  {url,handler}
const struct urlHandler
{
    const char *pUrl;
    uri_handler pFunc;
} g_urlHandler[]=
{
      URL_HANDLERS
      {NULL, NULL}
};
#undef _
#undef __DELIM__

struct mg_server *g_server = NULL;

//Verbosity flag set by command line
int g_verbose = 0;

// Flag set by ctrl-C handler to force program termination gracefully
static int g_quit = 0;

//File handles for board subsystems
int fd_din = -1;
int fd_dout = -1;
int fd_ctrtmr = -1;
int fd_ain = -1;
int fd_in_stream = -1;
int fd_tach = -1;
int fd_mctr = -1;

//Asynchronous IO
struct aio_struct *g_aio_in;

//Begining part of HTML page displaying error
static const char error_page_begin[] =
"<!DOCTYPE html><html><head>"
"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"
"<link rel=\"stylesheet\" type=\"text/css\" href=\"stylesheet.css\" />"
"</head><body id=\"pagebody\">"
"<div id=\"contentarea\">"
"<h1>Device Error</h1>"
"<p>";

//Ending part of HTML page displaying error
static const char error_page_end[] =
"</p></div>"
"<a href=\"javascript:history.back()\">Go back</a>"
"</body></html>";

//Usage of this program
static const char usage[]=
{
"Web server application to control and acquire data in a DT78XX series board.\n"
"If this board's IP address is ip-addr, connect to this application from any\n"
"web browser using the URL http://ip-addr/8080\n\n"
"Usage : webserver [options]\n"
"Options :\n"
"-p|--port <number> : selects HTTP port number, default is 8080\n"
"-v|--verbose : enables printf messages\n"
"-r|--docroot <path> : path to directory with all resource files\n"
"-d|--daemon : runs this application as a daemon process\n"
};

/*****************************************************************************
 * Send an HTML page with the specified NULL-terminated error message in it
 * @param conn
 * @param msg
 * @return MG_TRUE
 */
enum mg_result printf_err_msg(struct mg_connection *conn, const char *msg)
{
   fprintf(stderr, "ERROR %s\n", msg);

    mg_send_data(conn, error_page_begin, sizeof(error_page_begin)-1);
    if (msg)
        mg_send_data(conn, msg, strlen(msg));
    mg_send_data(conn, error_page_end, sizeof(error_page_end)-1);
    return MG_TRUE;
}

/*****************************************************************************
 * Send an HTML page with the formatted errno code and error message
 * @param conn
 * @param err
 * @param fmt
 * @param ... : varargs
 * @return MG_TRUE
 */
enum mg_result printf_errno_html(struct mg_connection *conn, int err, 
                                 const char *fmt, ...)
{
    char str[128];
    int len = 0;
    va_list    args;

    if (fmt)
    {
        va_start(args, fmt);
        len = vsnprintf(str, sizeof(str), fmt, args);
        va_end(args);  
        if (len+1 < sizeof(str))
        {
            str[len]=' '; //overwrite term null
            len += 1;
        }
    }
    len += snprintf(&str[len], sizeof(str)-len, "error %d", err);
    if (len+1 < sizeof(str))
    {
        str[len]=' '; //overwrite term null
        len += 1;
    }
    strerror_r(err, &str[len], sizeof(str)-len);
    len = strlen(str);
    
    fprintf(stderr, "%s\n", str);
    
    mg_send_data(conn, error_page_begin, sizeof(error_page_begin)-1);
    mg_send_data(conn, str, len);
    mg_send_data(conn, error_page_end, sizeof(error_page_end)-1);
    return MG_TRUE;
}

/*****************************************************************************
 * Print and optionally Send a plain text formatted errno code and error message
 * @param conn : browser connection to send to; may be NULL
 * @param err
 * @param fmt
 * @param ... : varargs
 * @return MG_TRUE
 */
enum mg_result printf_errno(struct mg_connection *conn, int err, 
                                 const char *fmt, ...)
{
    char str[128];
    int len = 0;
    va_list    args;

    if (fmt)
    {
        va_start(args, fmt);
        len = vsnprintf(str, sizeof(str), fmt, args);
        va_end(args);  
        if (len+1 < sizeof(str))
        {
            str[len]=' '; //overwrite term null
            len += 1;
        }
    }
    len += snprintf(&str[len], sizeof(str)-len, "error %d", err);
    if (len+1 < sizeof(str))
    {
        str[len]=' '; //overwrite term null
        len += 1;
    }
    strerror_r(err, &str[len], sizeof(str)-len);
    len = strlen(str);
    
    fprintf(stderr, "%s\n", str);
    if (conn)
        mg_send_data(conn, str, len);
    return MG_TRUE;
}

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void ctrlC_handler(int i) 
{
    g_quit = 1;
    PRINT("%s Signal %d\n", __func__,i);
}

/******************************************************************************
 * Create and configure the libmongoose server
 * @param argc : usual param to main()
 * @param argv : usual param to main()
 * @return 0=success
 */
int main(int argc, char *argv[]) 
{
    int err = EXIT_SUCCESS;
    int opt =0;
    char *port = DEFAULT_LISTENING_PORT;
    char *doc_root = DEFAULT_DOCUMENT_ROOT;
    int demon = 0;
    
    //Specifying the expected options
    static struct option long_options[] = 
    {
        {"verbose",     no_argument,        0,  'v' },
        {"port",        required_argument,  0,  'p' },
        {"docroot",     required_argument,  0,  'r' },
        {"daemon",      no_argument,        0,  'd' },
        {0,             0,                  0,  0   }
    };
    //parse the command line options
    opterr=0;
    while ((opt = getopt_long(argc, argv,"vdp:r:", long_options, NULL)) != -1) 
    {
        switch (opt) 
        {
            case 'v' : 
                g_verbose = 1;
                break;
            case 'p' : 
                 port = optarg;
                 break;
            case 'r' : 
                 doc_root = optarg;
                 break;
            case 'd' :
                demon = 1;
                break;
            default: 
                printf(usage); 
                exit(EXIT_FAILURE);
        }
    }
    
    //Run as a daemon if specified in command line. MUST preceed any file I/O
    if (demon)
    {
        if (daemon(1,g_verbose))
            perror("daemon");
    }
        
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, ctrlC_handler);
      
    //open the digital input subsystem
    if ((fd_din = open(DIN_SUBSYSTEM, O_RDWR)) < 0)
    {
        perror("open din");
        err = EXIT_FAILURE;
        goto _exit;
    }
    //open digital output subsystem
    if ((fd_dout = open(DOUT_SUBSYSTEM, O_RDWR)) < 0)
    {
        perror("open dout");
        err = EXIT_FAILURE;
        goto _exit;
    }
    //open counter timer subsystem
    if ((fd_ctrtmr = open(CTRTMR_SUBSYSTEM, O_RDWR)) < 0)
    {
        perror("open counter/timer");
        err = EXIT_FAILURE;
        goto _exit;
    }
    //open ain dev file
    if ((fd_ain = open(AIN_SUBSYSTEM, O_RDWR)) < 0)
    {
        perror("open ain");
        err = EXIT_FAILURE;
        goto _exit;
    }
    //open tachometer dev file
    if ((fd_tach = open(TACH_SUBSYSTEM, O_RDWR)) < 0)
    {
        perror("open tach");
        err = EXIT_FAILURE;
        goto _exit;
    }
    //open measure counter dev file
    if ((fd_mctr = open(MCTR_SUBSYSTEM, O_RDWR)) < 0)
    {
        perror("open measure ctr");
        err = EXIT_FAILURE;
        goto _exit;
    }
    //open input stream dev file
    if ((fd_in_stream = open(IN_STREAM, O_RDWR)) < 0)
    {
        perror("open input stream");
        err = EXIT_FAILURE;
        goto _exit;
    }  
    /* initialize AIO for input. Set this process to receive signals from input
     * streams when it over runs i.e queue is empty of buffers */ 
    g_aio_in = aio_create(fd_in_stream, 0, in_buffer_done_cb, in_stream_empty_cb);
    if (!g_aio_in)
    {
        err = EXIT_FAILURE;
        goto _exit;
    }    

    // Create and configure the server
    g_server = mg_create_server(NULL, web_event_handler);
    mg_set_option(g_server, "listening_port", port);
    mg_set_option(g_server, "document_root", doc_root);

    PRINT("listening_port %s\n", mg_get_option(g_server, "listening_port"));
    PRINT("document_root %s\n", mg_get_option(g_server, "document_root"));

    /* 
     * Infinite Loop processing web server, Asynchronous I/O for input and
     * output streams
     * Hit Ctrl-C to terminate the program
     */
    while (!g_quit) 
    {
        mg_poll_server(g_server, 10); //wait for 10ms
        aio_wait(g_aio_in, 0);        //service input stream events, if any
    }

    // Cleanup, 
_exit :  
    aio_destroy(g_aio_in);
    if (fd_in_stream > 0)
        close(fd_in_stream);
    if (fd_mctr > 0)
        close(fd_mctr);
    if (fd_tach > 0)
        close(fd_tach);
    if (fd_ain > 0)
        close(fd_ain);
    if (fd_ctrtmr > 0)
        close(fd_ctrtmr);
    if (fd_dout > 0)
        close(fd_dout);
    if (fd_din > 0)
        close(fd_din);
    if (g_server)
        mg_destroy_server(&g_server);
    PRINT("%s EXIT\n", argv[0]);
    return err;
}

/******************************************************************************
 * Request handler. The default page served is index.html. All dynamic pages
 * identified with an extension of .dhtml are generated by the server. All other
 * static files are located under DOCUMENT_ROOT and served by default by
 * libmongoose
 * @param conn : see http://cesanta.com/docs/API.shtml
 * @param ev   : see http://cesanta.com/docs/API.shtml
 * @return : MG_TRUE, MG_FALSE, MG_MORE
 */
static int web_event_handler(struct mg_connection *conn, enum mg_event ev) 
{
    switch (ev) 
    {
        case MG_WS_CONNECT: // New websocket connection
        case MG_REQUEST:
        {
            PRINT("%s %s %s\n", (ev==MG_REQUEST)?"MG_REQUEST":"MG_WS_CONNECT", 
                conn->uri, conn->request_method);
            //Check if the URL must be handled by a specific handler
            const struct urlHandler *p = g_urlHandler;
            while (p->pUrl && strcmp(conn->uri, p->pUrl)) 
                ++p;
            if (p && p->pFunc)
                return (p->pFunc(conn));
            //let libmongoose handle all other requests
            return MG_FALSE;
        }
        case MG_CLOSE:
            PRINT("MG_CLOSE %s\n", conn->uri);
            return MG_FALSE;
        case MG_AUTH: 
            return MG_TRUE;
        case MG_HTTP_ERROR :
            return MG_FALSE;
        default: 
            return MG_FALSE;
    }
}

/******************************************************************************
 * Handler for URL "/connector.png". This sends the board specific connector
 * png file or web page with connector information
 * @param conn
 * @return 
 */
enum mg_result send_connector_png(struct mg_connection *conn)
{
#ifdef DT7837  
    //DT7837 connector is one single png file
    conn->uri = "dt7837/connector.png";
#elif DT7816
    //DT7816 connector has tables for each connector in an html page
    conn->uri = "dt7816/connector.html";
#endif    
    return MG_FALSE;
}

/******************************************************************************
 * Handler for URL "/in-stream.html". This sends the board specific html file
 * to configure and control the input stream
 * @param conn
 * @return 
 */
enum mg_result send_in_stream_page(struct mg_connection *conn)
{
#ifdef DT7837   
    conn->uri = "dt7837/in-stream.html";
#elif DT7816
    conn->uri = "dt7816/in-stream.html";
#endif    
    return MG_FALSE;
}

/******************************************************************************
 * Handler for URL /board-name.txt". This sends the string identifying the
 * specific board
 * @param conn
 * @return 
 */
enum mg_result send_board_name(struct mg_connection *conn)
{
    mg_send_header(conn, "Content-Type", "text/plain");
#ifdef DT7837   
    mg_printf_data(conn, "DT7837");
#elif DT7816
    mg_printf_data(conn, "DT7816");
#endif    
    return MG_TRUE;
}