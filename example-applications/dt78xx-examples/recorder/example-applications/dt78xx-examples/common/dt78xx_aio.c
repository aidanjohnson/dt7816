/* 
 * APIs, data structures and macros used in DT78XX embedded application which
 * use the Linux Asynchronous IO file operations, or AIO for short.
 * 
 * Refer to the following for Linux AIO
 * https://code.google.com/p/kernel/wiki/AIOUserGuide
 * http://www.ibm.com/developerworks/library/l-async/
 * 
 * 
 * This code is based on the example documented in
 * http://www.fsl.cs.sunysb.edu/~vass/linux-aio.txt 
 * http://www.xmailserver.org/eventfd-aio-test.c
 *
 * Copyright (C) 2014 Data Translation Inc.
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

 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //memset
#include <linux/aio_abi.h>	/* for AIO types and constants */
#include <malloc.h>
#include <pthread.h>
#ifndef  __cplusplus
#define __USE_GNU   (1)
#endif
#include <signal.h>
#include <fcntl.h>

#include "dt78xx_aio.h"
#include "dt78xx_misc.h"
#include "aio_syscall.h"

#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"

/******************************************************************************
 * Macros
 */
#define AIO_SUBMIT    (0xA000000000000000ull)
#define AIO_DONE      (0x5000000000000000ull)
#define AIO_MASK      (0xF000000000000000ull)

// Minimum buffer size & buffer alignment dictated by DMA
#define MIN_BUFF_SIZE   (32)    
#define BUFF_ALIGNMENT  (32)

//Maximum number of events to wait for
#define NUM_EVENTS      (1)

//#define DEBUG (1)
#ifdef DEBUG
#define dbg_printf(fmt, ...) \
        fprintf(stdout, fmt, ##__VA_ARGS__)
#else
#define dbg_printf(fmt, ...)
#endif

/******************************************************************************
 * Data types
 */
struct aio_struct
{
    aio_context_t ctx;          //Asynchronous I/O context
    int fd;                     //device file to perform AIO with
    int write;                  //Write or read from fd
    struct io_event events[NUM_EVENTS];  //for io_getevents()
    struct iocb **iocbs;        //array of iocbs
    uint32_t **buf_array;       //array of buffers each embedded in an iocb
    int num_buf;                //#of buffers (==iocbs) queued
    int buflen;                 //length of buffer in each iocb
    int count;                  //running count of buffers submitted
    buffer_done_cb_t cb;        //buffer done callback
    int started;                //1 after aio_start() called, 0 while idle
};

int aio_wait(struct aio_struct *aio, int millisec)
{
    int ret, i;
    struct iocb *done[1];
    if (millisec >= 0)
    {
        struct timespec tmo;
        tmo.tv_sec = millisec/1000;
        tmo.tv_nsec = (millisec - tmo.tv_sec*1000)*1000;
        ret = io_getevents(aio->ctx, 1, NUM_EVENTS, aio->events, &tmo);
    }
    else
        ret = io_getevents(aio->ctx, 1, NUM_EVENTS, aio->events, NULL);
    if (ret != 0)
        dbg_printf("[%s] io_getevents %d\n", __func__, ret);        
    if (ret <= 0) //if  the wait interrupted
        return ret;
    
    for (i=0; i < ret; ++i)
    {
        struct iocb *cb = (struct iocb *)aio->events[i].obj;
        if (aio->events[i].res2) //Non-zero ==error
        {
#if 1            
            fprintf(stderr, "aio_data %llx evt_data %llx %llx err %llx\n", 
                cb->aio_data,  aio->events[i].data, aio->events[i].res, 
                    aio->events[i].res2);
#endif            
            errno = aio->events[i].res2;
            perror("iocb");
            continue;
        }
#if 0            
        if ((cb->aio_data != aio->events[i].data) || 
            ((aio->events[i].data & AIO_MASK) != AIO_SUBMIT))
        {
            fprintf(stderr, "ERROR aio_data %llx evt_data %llx\n", 
                cb->aio_data,  aio->events[i].data);
        }
#endif            
        cb->aio_data &= ~AIO_MASK; //iocb done
        cb->aio_data |= AIO_DONE;        
        void *buf = (void *)((__u32)cb->aio_buf);
        if (aio->cb &&  aio->cb(buf, aio->buflen))
        {
            cb->aio_data = (AIO_SUBMIT | (aio->count & ~AIO_MASK)); 
            ++aio->count;
            done[0] = cb;
            dbg_printf("[%s] resubmit\n", __func__);        
            if (io_submit(aio->ctx, 1, done) < 1)
            {
                fprintf(stderr, "ERROR io_submit\n");
                ret = -EIO;
                break;
            }
        }                          
    }
    return ret;
}

int aio_start(struct aio_struct *aio)
{
    int ret,i;
    if (!aio || aio->started)
        return (-EIO); //error
    
    aio->count = 0;
    for (i=0; i < aio->num_buf; ++i, ++aio->count)
    {
        struct iocb *cb = (struct iocb *)aio->iocbs[i];
        cb->aio_data = (AIO_SUBMIT | aio->count);
    }
    ret = io_submit(aio->ctx, aio->num_buf, aio->iocbs);
    if (ret == aio->num_buf)
    {
        aio->started = 1;
        return 0;
    }
    return ret; //error
}

void aio_stop(struct aio_struct *aio)
{
    int i;
    if (!aio || !aio->started)
        return;
    for (i=0; i < aio->num_buf; ++i)
    {
        struct iocb *cb = aio->iocbs[i];
        //Cancel iocb's that were aborted
        if (cb && ((cb->aio_data & AIO_MASK) == AIO_SUBMIT))
        {
            io_cancel(aio->ctx, cb, aio->events);
            cb->aio_data &= ~AIO_MASK;
        }
    }
    aio->started = 0;
    //FIX to allow repeated io_submit
    io_destroy(aio->ctx);
    aio->ctx = 0;
    io_setup(MAX_AIO, &aio->ctx);
}

static void _free_iocb(struct aio_struct *aio)
{
    int i;
    
    if (aio->iocbs)
    {
        for (i=0; i < aio->num_buf; ++i)
        {
            struct iocb *cb = aio->iocbs[i];
            if (cb) 
            {
                if (cb->aio_buf)
                    free((void *)(cb->aio_buf));
                free(cb);
            }
        }
        free(aio->iocbs);
        aio->iocbs = NULL;
    }
    if (aio->buf_array)
    {
        free(aio->buf_array);
        aio->buf_array = NULL;
    }
    aio->num_buf = 0;
    aio->buflen = 0;
    aio->count = 0;
}


void aio_buff_free(struct aio_struct *aio)
{
    _free_iocb(aio);    
}

void **aio_buff_alloc(struct aio_struct *aio, int buffs, int len)
{
    int err = 0;
    int i;
    int alignment = BUFF_ALIGNMENT; 
    
    if (buffs > MAX_AIO)
    {
        fprintf(stderr, "[%s(%d)] ERROR Buffs > %d\n", 
                __func__, __LINE__, MAX_AIO);
        return NULL;
    }
    //if nothing has changed..
    if ((aio->num_buf == buffs) && (aio->buflen == len))
    {
        aio->count = 0;
        return (void **)aio->buf_array;
    }
    //free existing iocbs and buffers if either have changed & alloc again
    _free_iocb(aio);

    do
    {
        aio->iocbs = (struct iocb **)malloc(sizeof(struct iocb *) * buffs);
        if (!aio->iocbs)
        {
           fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
           err = -ENOMEM;
           break;
        }
        memset(aio->iocbs, 0, (sizeof(struct iocb *) * buffs));
        
        aio->buf_array = (uint32_t **)malloc(sizeof(uint32_t *) * buffs);
        if (!aio->buf_array)
        {
           fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
           err = -ENOMEM;
           break;
        }
        memset(aio->buf_array, 0, (sizeof(uint32_t *) * buffs));
        
        for (i=0; i < buffs; ++i)
        {
            struct iocb *cb = (struct iocb *)malloc(sizeof(struct iocb));
            if (!cb)
            {
                fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
                err = -ENOMEM;
                break;
            }
            memset(cb, 0, sizeof(struct iocb));
            aio->iocbs[i] = cb;
            aio->buf_array[i] = (uint32_t *)memalign(alignment,len);
            if (!aio->buf_array[i])
            {
                fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
                err = -ENOMEM;
                break;
            }
            cb->aio_fildes = aio->fd;
            cb->aio_lio_opcode = aio->write?IOCB_CMD_PWRITE:IOCB_CMD_PREAD;
            cb->aio_buf = (__u64)(void *)aio->buf_array[i];
            cb->aio_nbytes = len;
        }
        
        aio->num_buf = buffs;
        aio->buflen = len;
        aio->count = 0;
    } while (0);
    
    if (err)
    {
        _free_iocb(aio);
        return NULL;
    }
    
    return (void **)aio->buf_array;
}

struct aio_struct *aio_create(int fd, int write, buffer_done_cb_t cb, 
                              void (* sighandler)(int))
{
    struct aio_struct *aio;
    aio = (struct aio_struct *)malloc(sizeof(*aio));
    memset(aio, 0, sizeof(*aio));
    if ((io_setup(MAX_AIO, &aio->ctx)))
    {
        free(aio);
        perror("io_setup");
        return NULL;
    }

    aio->fd = fd;
    aio->write = write;
    aio->cb = cb;    
    if (sighandler)
    {
        int signum = write ? SIGUSR2 : SIGUSR1;
        if (file_sigaction_register(fd, signum, sighandler))
        {
            free(aio);
            return NULL;
        }
    }
    return aio;
}

void aio_destroy(struct aio_struct *aio)
{
    if (aio)
    {
        _free_iocb(aio);
        io_destroy(aio->ctx);
        free(aio);
    }
}

/* Standard C Function: Greatest Common Divisor */
static int _gcd (int a, int b)
{
    int c;
    while ( a != 0 ) 
    {
       c = a; 
       a = b%a;  
       b = c;
    }
    return b;
}

/*****************************************************************************
 * Compute the total length of the buffer to hold *at least* the number of 
 * samples per channel for the specified number of channels. 
 * THIS API COMPUTES THE LENGTH SO THAT 
 * (1) AN INTEGRAL NUMBER OF SAMPLES PER CHANNEL FITS IN THE  BUFFER AND ALSO 
 * (2) THE BUFFER IS AN INTEGRAL MULTIPLE OF 32, mandated by the ARM DMA engine.
 * @param samples_chan : desired #of samples per channel
 * @param mask         : mask identifying channels to be sampled
 * @param actual       : actual number of samples per channel returned here,
 *                       !null
 * @return  : size of buffer in bytes.
 */
int aio_buff_size(int samples_chan, chan_mask_t mask, int *actual)
{
    int gcd, lcm, sample_len, buf_len;
    if (!samples_chan)
        return 0;
    if (!mask)
        return 0;
    /* sample_len = #of bytes needed to hold one sample of all channels
     * enabled in the mask. There are differences in data sizes between
     * boards for different types of channels.
     */
#ifdef DT7837
    //All channels are 32-bits in this board; count bits set in channel mask
    uint32_t _mask = (uint32_t)mask;
    for (sample_len=0; _mask; sample_len += sizeof(int32_t))
        _mask &= (_mask -1);
#elif DT7816
    /* AIN and DIN channels 16-bits
     * Tach, Measure counter, counter/timer are 32-bits
     */
    sample_len = 0;
    if (mask & chan_mask_ain0) sample_len += sizeof(int16_t);
    if (mask & chan_mask_ain1) sample_len += sizeof(int16_t);
    if (mask & chan_mask_ain2) sample_len += sizeof(int16_t);
    if (mask & chan_mask_ain3) sample_len += sizeof(int16_t);
    if (mask & chan_mask_ain4) sample_len += sizeof(int16_t);
    if (mask & chan_mask_ain5) sample_len += sizeof(int16_t);
    if (mask & chan_mask_ain6) sample_len += sizeof(int16_t);
    if (mask & chan_mask_ain7) sample_len += sizeof(int16_t);
    if (mask & chan_mask_tach) sample_len += sizeof(uint32_t);   
    if (mask & chan_mask_meas_ctr) sample_len += sizeof(uint32_t);
    if (mask & chan_mask_din) sample_len += sizeof(int16_t);
    if (mask & chan_mask_aout0) sample_len += sizeof(int16_t);
    if (mask & chan_mask_aout1) sample_len += sizeof(int16_t);
    if ((mask & chan_mask_dout0)||(mask & chan_mask_dout1)||
        (mask & chan_mask_dout2)||(mask & chan_mask_dout3)||
        (mask & chan_mask_dout4)||(mask & chan_mask_dout5)||
        (mask & chan_mask_dout6)||(mask & chan_mask_dout7))
        sample_len += sizeof(int16_t);
#else
#error 
#endif     
    buf_len = samples_chan * sample_len;
    gcd = _gcd(sample_len, MIN_BUFF_SIZE);
    lcm = (sample_len/gcd) * MIN_BUFF_SIZE;
    buf_len = ((buf_len + lcm -1) / lcm) * lcm; //round up
    if (actual)
        *actual = buf_len/sample_len;
    return buf_len;
}