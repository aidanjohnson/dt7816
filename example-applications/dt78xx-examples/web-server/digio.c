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

#include "webdefs.h"
#include "dt78xx_ioctl.h"

/******************************************************************************
 * Macros
 */

/******************************************************************************
 * Data types
 */

/******************************************************************************
 * Functions
 */

/******************************************************************************
 * Globals
 */

/**
 * Handler for HTTP GET on URL "digio.in". Reads the digital inputs and returns
 * it formatted as decimal and hex number
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_digin(struct mg_connection *conn)
{
    uint8_t val;
    mg_send_header(conn, "Content-Type", "text/plain");
    if (read(fd_din, (void *)&val, sizeof(val)) < 0)
    {
        perror("read din\n");
        mg_printf_data(conn, "error");
    }
    else
        mg_printf_data(conn, "%#x (%d)", val, val);
    return MG_TRUE;
}

/**
 * Handler for HTTP GET and POST on URL "digout.in". For POST, Writes the 
 * digital out, for GET Reads it back and returns it formatted as decimal and
 *  hex number
 * @param conn
 * @return : MG_TRUE
 */
enum mg_result ev_handler_digout(struct mg_connection *conn)
{
    uint8_t val;
    char buff[32];
    mg_send_header(conn, "Content-Type", "text/plain");
    if (strcmp(conn->request_method, "POST") == 0)
    {
        mg_get_var(conn, "dout", buff, sizeof(buff));
        val = strtoul(buff, NULL, 16);
        if (write(fd_dout, (void *)&val, sizeof(val)) < 0)
        {
            perror("write dout\n");
            mg_printf_data(conn, "error");
        }
    }
    if (read(fd_dout, (void *)&val, sizeof(val)) < 0)
    {
        perror("read dout\n");
        mg_printf_data(conn, "error");
    }
    else
        mg_printf_data(conn, "%#x (%d)", val, val);
    return MG_TRUE;
}

