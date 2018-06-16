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

/******************************************************************************
 * Handler for HTTP GET on URL ctrtmr_get.io. 
 * Details :  
 * The  static web form ctrtmr.html is loaded in response to a HTTP GET
 * when the user clicks on the corresponding menu item in menu.html.
 * That page has the elements for configuring and controling the counter/timer.
 * The onLoad() event in ctrtmr.html executes an AJAX function to GET 
 * ctrtmr_get.io. This handler then sends the current configuration of the 
 * counter/timer. The web page's onLoad() handler parses the configuration info
 * and alters the web page dynamically to reflect the current configuration.
 * 
 * This is one of several alternatives to generate a dynamic web page.
 * 
 * @param conn
 * @return : MG_TRUE. MG_FALSE for error
 */
enum mg_result ev_handler_ctrtmr_get(struct mg_connection *conn)
{
    dt78xx_ct_config_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    //handle GET only
    if (strcmp(conn->request_method, "GET"))
        return MG_FALSE;
         
    if (ioctl(fd_ctrtmr, IOCTL_CT_CFG_GET, &cfg))
    {
        perror("ctr tmr get config\n");
        return MG_FALSE;
    }
    /*
     * Response is a list of id=value pairs separated by semi-colons. The id
     * is the id of the HTML element in the page and the value is that element's
     * value
     */
    
    //Mode
    if (cfg.mode == ct_mode_idle)
        mg_printf_data(conn, "#ctr_mode=idle;");
    else if (cfg.mode == ct_mode_1shot)
        mg_printf_data(conn, "#ctr_mode=oneshot;");
    else if (cfg.mode == ct_mode_divider)
        mg_printf_data(conn, "#ctr_mode=divider;");
    else if (cfg.mode == ct_mode_counter)
        mg_printf_data(conn, "#ctr_mode=counter;");
    else 
    {
        mg_printf_data(conn, "#ctr_mode=unknown;");
        PRINT("[%s] Unknown mode\n", __func__);
    }
    
    //Gate
    if (cfg.gate == ct_gate_none)
        mg_printf_data(conn, "#gate=none;");
    else if (cfg.gate == ct_gate_ext_hi)
        mg_printf_data(conn, "#gate=exthi;");
    else if (cfg.gate == ct_gate_ext_lo)
        mg_printf_data(conn, "#gate=extlo;");
    
    //External gate digital input; redundant if gate is "none"
    mg_printf_data(conn, "#gate_din=%d;", cfg.ext_gate_din);
    
    //Clock source
    mg_printf_data(conn, "#clock=%s;", cfg.ext_clk?"ext":"int");
    
    //External clock digital input; redundant if clock is "int"
    mg_printf_data(conn, "#clock_din=%d;", cfg.ext_clk_din);
    
    //period and pulse and output pin for modes clock divider and 1 shot
    if (cfg.mode == ct_mode_divider)
    {
        mg_printf_data(conn, "#cfg_divider_divisor=%d;", cfg.divider.period);
        mg_printf_data(conn, "#cfg_divider_pulse=%.2f;", 
                       (100.0f * cfg.divider.pulse)/cfg.divider.period);
        mg_printf_data(conn, "#cfg_divider_dout=%d;", cfg.divider.out);
        mg_printf_data(conn, "#cfg_divider_polarity=%d;", cfg.divider.out_hi);
    }
    else if (cfg.mode == ct_mode_1shot)
    {
        mg_printf_data(conn, "#cfg_1shot_divisor=%d;", cfg.one_shot.period);
        mg_printf_data(conn, "#cfg_1shot_pulse=%.2f;", 
                       (100.0f * cfg.one_shot.pulse)/cfg.one_shot.period);
        mg_printf_data(conn, "#cfg_1shot_dout=%d;", cfg.one_shot.out);
        mg_printf_data(conn, "#cfg_1shot_polarity=%d;", cfg.one_shot.out_hi);
    }
    return MG_TRUE;
}

/******************************************************************************
 * Handles POST to /ctrtmr_post.io. This is invoked when the user submits the
 * form ctrtmr.html
 * @param conn
 * @return MG_TRUE
 */
enum mg_result ev_handler_ctrtmr_post(struct mg_connection *conn)
{
    char buff[64];
    int err;
    dt78xx_ct_config_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    
    //Mode must always be there
    if (mg_get_var(conn, "mode", buff, sizeof(buff)) < 0)
    {
        PRINT("[%s] missing mode\n", __func__);
        return MG_FALSE;
    }
    if (!strcmp(buff, "divider"))
        cfg.mode = ct_mode_divider;
    else if (!strcmp(buff, "counter"))
        cfg.mode = ct_mode_counter;
    else if (!strcmp(buff, "oneshot"))
        cfg.mode = ct_mode_1shot;
    else
        cfg.mode = ct_mode_idle;
    
    //Gate type if POSTED
    if (mg_get_var(conn, "gate", buff, sizeof(buff)) > 0)
    {
        if (!strcmp(buff, "exthi"))
            cfg.gate = ct_gate_ext_hi;
        else if (!strcmp(buff, "extlo"))
            cfg.gate = ct_gate_ext_lo;
        else 
            cfg.gate = ct_gate_none;
    }
    //Gate DIN if POSTED
    if (mg_get_var(conn, "gate_din", buff, sizeof(buff)) > 0)
        cfg.ext_gate_din = (uint8_t)strtoul(buff, NULL, 10);
    
    //Clock source if POSTED
    if (mg_get_var(conn, "clock", buff, sizeof(buff)) > 0)
    {
        if (!strcmp(buff, "ext"))
            cfg.ext_clk = 1;
    }
    
    //Clock DIN if POSTED
    if (mg_get_var(conn, "clock_din", buff, sizeof(buff)) > 0)
        cfg.ext_clk_din = (uint8_t)strtoul(buff, NULL, 10);
    
    //Divider config
    if (cfg.mode == ct_mode_divider)
    {
        //#of input clock pulse in divided clock output
        if (mg_get_var(conn, "cfg_divider_divisor", buff, sizeof(buff)) > 0)
            cfg.divider.period = strtoul(buff, NULL, 10);
        //duty cycle to #of input clock pulse in active pulse output
        if (mg_get_var(conn, "cfg_divider_pulse", buff, sizeof(buff)) > 0)
        {
            float f = strtof(buff, NULL); //Percent between 1 and 99
            f *= cfg.divider.period;
            f /= 100.0f;
            cfg.divider.pulse = (uint32_t)f;
        }
        //Clock DOUT pin
        if (mg_get_var(conn, "cfg_divider_dout", buff, sizeof(buff)) > 0)
            cfg.divider.out = (uint8_t)strtoul(buff, NULL, 10);
        //Clock DOUT polarity
        if (mg_get_var(conn, "cfg_divider_polarity", buff, sizeof(buff)) > 0)
            cfg.divider.out_hi = (uint8_t)strtoul(buff, NULL, 10);
    }
    else if (cfg.mode == ct_mode_1shot)
    {
        //#of input clock pulse in one-shot output
        if (mg_get_var(conn, "cfg_1shot_divisor", buff, sizeof(buff)) > 0)
            cfg.one_shot.period = strtoul(buff, NULL, 10);
        //duty cycle to #of input clock pulse in active pulse output
        if (mg_get_var(conn, "cfg_1shot_pulse", buff, sizeof(buff)) > 0)
        {
            float f = strtof(buff, NULL); //Percent between 1 and 99
            f *= cfg.one_shot.period;
            f /= 100.0f;
            cfg.one_shot.pulse = (uint32_t)f;
        }
        //1-shot DOUT pin
        if (mg_get_var(conn, "cfg_1shot_dout", buff, sizeof(buff)) > 0)
            cfg.one_shot.out = (uint8_t)strtoul(buff, NULL, 10);
        //1-shot DOUT pin
        if (mg_get_var(conn, "cfg_1shot_polarity", buff, sizeof(buff)) > 0)
            cfg.one_shot.out_hi = (uint8_t)strtoul(buff, NULL, 10);
    }
    
    if ((err = ioctl(fd_ctrtmr, IOCTL_CT_CFG_SET, &cfg))) //error
    {
        char msg[128];
        perror("IOCTL_CT_CFG_SET ");  
        snprintf(msg, sizeof(msg)-1, 
                 "Failed to save counter/timer configuration<br />Error %d \"%s\"",
                 errno, strerror(errno));
        return printf_err_msg(conn, msg);
    }
   
    return status_no_content(conn);
}

/******************************************************************************
 * Handles GET/POST to /ctrtmr.io. 
 * POST is invoked when the user clicks either Start or Stop button in the 
 * ctrtmr.html form. GET is invoked when the Read button is clicked 
 * @param conn
 * @return MG_TRUE
 */
enum mg_result ev_handler_ctrtmr_ctrl(struct mg_connection *conn)
{
    int err = 0;
    if (!strcmp(conn->request_method, "POST"))
    {
        char tmp[4];
        if (mg_get_var(conn, "start", tmp, sizeof(tmp)) > 0) //Start
            err = ioctl(fd_ctrtmr, IOCTL_START_SUBSYS, NULL);
        else
            ioctl(fd_ctrtmr, IOCTL_STOP_SUBSYS, NULL);

        if (!err)
        {
            mg_send_status(conn, 304);
            return MG_TRUE;
        }

        perror("start ");  
        mg_printf_data(conn, "Errno %d \"%s\"", errno, strerror(errno));
        return MG_TRUE;
    }
    
    uint32_t count;
    err = read(fd_ctrtmr, &count, sizeof(count));
    if (err < 0)
        perror("read"); 
    else if (err == sizeof(count)) //#of bytes read
        mg_printf_data(conn,"%u (%#08x)\n", count,count);
    else
        PRINT("Got only %d bytes\n", err);
    return MG_TRUE;
}
