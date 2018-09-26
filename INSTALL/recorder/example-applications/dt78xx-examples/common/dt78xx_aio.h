#ifndef _AIO_H_
#define	_AIO_H_
/*****************************************************************************
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
#include <stdint.h>
#include "dt78xx_ioctl.h"
#define MAX_AIO         (128)

/******************************************************************************
 * AIO API flow diagram. API marked with * must be called only once.
 * 
 *      aio_create*
 *          |
 *          v
 *          +--<--------------------------------+
 *      aio_buff_alloc()                        |
 *          |                                   |
 *          |                                   |
 *      aio_start()                             |
 *          |                                   |
 *      aio_wait ()<-------->buffer_done_cb_t   |
 *          :                                   |
 *          :                                   |
 *      aio_wait ()<-------->buffer_done_cb_t   |
 *          :                                   |loop
 *          :                                   |
 *      aio_wait ()<-------->buffer_done_cb_t   |
 *          :                                   |
 *          :                                   |
 *          |                                   |
 *      aio_stop()                              |
 *          |                                   |
 *          +-------------------------------->--+
 *          |            +----<-----+
 *          :            |          |
 *       aio_get_completed_buff     |
 *          :            |          |
 *          |            +---->-----+
 *          |
 *          |
 *          |
 *          v
 *      aio_destroy*
 */
struct aio_struct;

/******************************************************************************
 * AIO buffer done callback
 * @param buff : pointer to buffer with samples from enabled channels
 * @param len  : length of buffer; this is an integral multiple of equal number
 *               of samples from all enabled channels
 * @return     : The return value determines whether this buffer will be 
 *               resubmitted for continued AIO operations 
 *               0 = do not resubmit, 1= resubmit 
 */
typedef int (* buffer_done_cb_t)(void *buff, int len);

/*****************************************************************************
 * Initialize AIO only once when application starts
 * @param fd : device file used for AIO operations
 * @parma write : 0 for reading from file, 1 to write to file
 * @param cb : Optional callback to handle buffer completions; NULL for no
 *              callback 
 * @param sighandler : Optional signal handler for buffer overrun/underrun. 
 *              NULL to ignore buffer overrun/underrun.
 * @return On success returns pointer to aio_struct, NULL = error
 */
struct aio_struct *aio_create(int fd, int write, buffer_done_cb_t cb,
                              void (* sighandler)(int));

/*****************************************************************************
 * Free AIO only once when application terminates
 * @param aio : structure returned from aio_init()
 */
void aio_destroy(struct aio_struct *aio);

/*****************************************************************************
 * Buffer allocation prior to performing AIO operations. 
 * @param aio       : structure returned from aio_init()
 * @param numbuf    : Number of buffers each of buflen to be queued
 * @param buflen    : Length of each buffer in bytes, returned by aio_buff_size()
 * @return : non-NULL=pointer to array of allocated buffers; the array has
 *           numbuf pointers each of buflen bytes, NULL=failure
 * @note : If this API is invoked more than once with the same 'numbuf' and
 *          'buflen', no new allocation occurs and the return pointer is the
 *           same as that returned by the first call to this API
 *          Memory allocated by this API must be free'd either by aio_buff_free()
 *          or aio_destroy()
 */
void **aio_buff_alloc(struct aio_struct *aio, int numbuf, int buflen);

/*****************************************************************************
 * Deallocate memory allocated for buffers by aio_buff_alloc() 
 * @param aio       : structure returned from aio_init()
 */
void aio_buff_free(struct aio_struct *aio);

/*****************************************************************************
 * Initiate AIO read operation after aio_configure()
 * @param aio       : structure returned from aio_init()
 * @return : 0=success, <0=failure
 */
int aio_start(struct aio_struct *aio);

/*****************************************************************************
 * Stop AIO read operation initiated by aio_start()
 * @param aio       : structure returned from aio_init()
 */
void aio_stop(struct aio_struct *aio);

/*****************************************************************************
 * Block waiting for at least one buffer to be completed in the specified time. 
 * Buffers completed during this timeout will invoke the callback registered
 * in aio_create().
 * @param aio       : structure returned from aio_init()
 * @param millisec  : miliseconds to block, -1 to block for ever
 * @return : <0 = timeout/error, >0 = #of buffers completed
 */
int aio_wait(struct aio_struct *aio, int millisec);

/*****************************************************************************
 * Compute the total length of the buffer to hold *at least* the number of 
 * samples per channel for the specified number of channels. 
 * THIS API COMPUTES THE LENGTH SO THAT 
 * (1) AN INTEGRAL NUMBER OF SAMPLES PER CHANNEL FITS IN THE  BUFFER AND ALSO 
 * (2) THE BUFFER IS AN INTEGRAL MULTIPLE OF 32, mandated by the ARM DMA engine.
 * @param samples_chan : desired #of samples per channel
 * @param mask         : mask identifying channels to be sampled
 * @param actual       : actual number of samples per channel returned here,
 *                       if the pointer is not null
 * @return  : size of buffer in bytes.
 */
int aio_buff_size(int samples_chan, chan_mask_t mask, int *actual);

int aioWriteQueue(struct aio_struct *aio, int ms);

#endif	/* _AIO_H_ */

