/*
 * KLM for Data Translation DT78xx data acquisition module.
 * 
 * This implements the file operations supported by the /dev/DT78xx
 * device
 *
 *  (C) Copyright (c) 2014 Data Translation Inc
 *                    www.datatranslation.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed WITHOUT ANY WARRANTY; without the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 * This software is based on "Linux Device Drivers, 3rd Edition" by Jonathan 
 * Corbet, Greg Kroah-Hartman, Alessandro Rubini. Refer to chapter 15-3;
 * http://www.makelinux.net/ldd3/chp-15-sect-3
 */
#include <linux/device.h>
#include <linux/spinlock.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/kref.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/page.h>
#include <linux/aio.h>

#include "dt78xx.h"

/**************************************************************************
 * Macros
 */
#ifdef _USE_MMAP_ //defined in Makefile
/*
 * Define this to fill the input DMA buffer with known strings at fixed
 * offsets. This is to test that the buffer can be mmap'd to user space and
 * the user application can read the strings
 */
#define _TEST_MMAP_ (1)

/*
 * Define this macro to use mmap vm_operations_struct
 */
#define _VM_MMAP_OPS_    (1)
#endif

/**************************************************************************
 * Data structures
 */
//Info used to manage AIO operation
struct aio_req_private 
{
    enum dma_data_direction dir;
    struct aio_request  req;
    struct dt78xx_device *dt_dev;
    struct kiocb        *iocb;  //iocb from user
    struct work_struct  work;
    struct iovec        iov;    //user buffer
    struct kref         kref;   //ref counting b/w DMA and AIO use of this request
    struct page         **usr_pg;  //page pointers returned by get_user_pages  
};

/**************************************************************************
 * Functions
 */
#if defined _USE_MMAP_ && defined _VM_MMAP_OPS_
static void mmap_open(struct vm_area_struct * area);
static void mmap_close(struct vm_area_struct * area);
static int mmap_fault(struct vm_area_struct *vma, struct vm_fault *vmf);
#endif
/**************************************************************************
 * Globals
 */

/*****************************************************************************
 * Unmap pages corresponding to user buffer. This is used to free/unmap pages
 * mapped by _aio_get_user_pages()
 * @param pages : Pointer to array of struct page*, from _aio_get_user_pages()
 * @param num_pages : number of pages in pages[] array
 * @param dirty : 1= pages dirty
 */
static void _aio_free_user_pages(struct page *pages[], unsigned long num_pages,
                                 int dirty)
{
    size_t i;

    if (!pages)
    {
        return;
    }
    for (i = 0; i < num_pages; i++) 
    {
        if (pages[i])
        {
            if (dirty)
            {
                set_page_dirty_lock(pages[i]);
            }
            put_page(pages[i]);
        }
    }
    kfree(pages);
}

/*****************************************************************************
 * Maps and pins down user buffer.
 * @param dev   : struct device*
 * @param reqx  : pointer to aio_request_in with the iov member initialized
 * @parm write  : whether pages will be written to by the caller
 * @return      : 0= success, aio_request_in  members  req.num_sgs,reqx->usr_pg
 *                will be initialized
 *                <0 = error
 */
static int _aio_get_user_pages(struct device *dev, struct aio_req_private *reqx,
                               int write)
{
    int ret;
    unsigned long first_page, last_page, base, len;
    base = (unsigned long)reqx->iov.iov_base;
    len = (unsigned long)reqx->iov.iov_len;
    first_page = (base & PAGE_MASK) >> PAGE_SHIFT;
    last_page = ((base + len-1) & PAGE_MASK) >> PAGE_SHIFT;
    reqx->req.num_sgs = last_page - first_page + 1;
    
    //allocate array of page pointers
    reqx->usr_pg = kzalloc(reqx->req.num_sgs * sizeof(struct page *), GFP_KERNEL);
    if (unlikely(!reqx->usr_pg)) 
    {
        dev_err(dev, "[%s] ERROR kzalloc page\n", __func__);
        reqx->req.num_sgs = 0;
        reqx->usr_pg = NULL;
        return (-ENOMEM);
    }
    
    //map the user pages
    down_write(&current->mm->mmap_sem);
    ret = get_user_pages(current,  current->mm, base, reqx->req.num_sgs, 
                       write,// int write, 
                       1, //int force, 
                       reqx->usr_pg,// struct page **pages, 
                       NULL);// struct vm_area_struct **vmas);
    up_write(&current->mm->mmap_sem);  
    if (ret <= 0)
    {
        dev_err(dev, "[%s] ERROR %d get_user_pages\n", __func__, ret);
        kfree(reqx->usr_pg);
        reqx->req.num_sgs = 0;
        reqx->usr_pg = NULL;
        return (-ENOMEM);
    }
    
    return (0);
}

/*****************************************************************************
 * Create an array of scatterlist for the array of mapped pages corresponding
 * to user buffer
 */
static int _aio_map_sg(struct device *dev, struct aio_req_private *reqx)
{
    unsigned long num_page, offset, base, len;
    int i, mapped;
     
    base = (unsigned long)reqx->iov.iov_base;
    len = (unsigned long)reqx->iov.iov_len;
    offset = base - (base & PAGE_MASK);
    num_page = reqx->req.num_sgs;
    
    //allocate the scatter gather list corresponding to the array of pages
    reqx->req.sg = kzalloc(num_page * sizeof(struct scatterlist), GFP_KERNEL);
    if (unlikely(!reqx->req.sg)) 
    {
        dev_err(dev, "[%s] ERROR kzalloc sg\n", __func__);
        return (-ENOMEM);
    }
    // Map a scatter-gather list to point at the userspace pages
    sg_init_table(reqx->req.sg, num_page);
    
    //first
    if (num_page > 1) 
    {
        sg_set_page(&reqx->req.sg[0], reqx->usr_pg[0], PAGE_SIZE - offset, offset);
    }
    else
    {
        sg_set_page(&reqx->req.sg[0], reqx->usr_pg[0], len, offset);
    }

    /*middle*/
    for(i=1; i < num_page-1; i++)
    {
        sg_set_page(&reqx->req.sg[i], reqx->usr_pg[i], PAGE_SIZE, 0);
    }

    /*last*/
    if (num_page > 1) 
    {
        sg_set_page(&reqx->req.sg[num_page-1], reqx->usr_pg[num_page-1],
            len - (PAGE_SIZE - offset) - ((num_page-2)*PAGE_SIZE), 0);
    }   
    
    mapped = dma_map_sg(dev, reqx->req.sg, num_page, reqx->dir);
    if (mapped != num_page)
    {
        dev_err(dev, "[%s] ERROR %d dma_map_sg\n", __func__, mapped);
        kfree(reqx->req.sg);
        return (-ENOMEM);
    }
    
    return 0;
}

/*****************************************************************************
 */
static void _aio_request_free(struct kref *kref)
{
    struct aio_req_private *reqx;
    
    reqx = container_of(kref, struct aio_req_private, kref);
    if (reqx->req.sg)
    {
        dma_unmap_sg(&reqx->dt_dev->pdev->dev, reqx->req.sg, reqx->req.num_sgs,
                     reqx->dir);
        kfree(reqx->req.sg);
    }

    _aio_free_user_pages(reqx->usr_pg, reqx->req.num_sgs, 1);
#if 0    
    DEV_DBG(&reqx->dt_dev->pdev->dev, "[%s] user_data %llx user_buf %p len %d\n", 
              __func__, reqx->iocb->ki_user_data, reqx->iov.iov_base, 
              reqx->iov.iov_len);
#endif    
    kfree(reqx);    
}
static void _aio_complete_worker(struct work_struct *work)
{
    struct aio_req_private *reqx;
    struct kiocb *iocb;
    int    status;
    unsigned long actual;    
    reqx = container_of(work, struct aio_req_private, work);
    
    iocb = reqx->iocb;
    iocb->private = NULL;
	status = reqx->req.status;
	actual = reqx->req.actual;
#if 0    
    DEV_DBG(&reqx->dt_dev->pdev->dev, 
        "[%s] user_data %llx user_buf %p len %d actual %lu status %d}\n", 
        __func__, iocb->ki_user_data, reqx->iov.iov_base, reqx->iov.iov_len,
        reqx->req.actual, reqx->req.status);
#endif    
    
    //Free this request
    kref_put(&reqx->kref, _aio_request_free);
	
    //error code is io_event's res2
    aio_complete(iocb, actual, status); 
}
/*****************************************************************************
 * Called to cancel all outstanding reuests. Note that this is called at
 * interrupt context
 * @param iocb
 * @return 0
 */
static int _aio_cancel(struct kiocb *iocb)
{
    int err;
    struct aio_req_private *reqx = iocb->private;
    
    if ((err = dt78xx_request_dequeue(iocb->ki_filp, &reqx->req)) < 0)
        return err;
    
    //Must clean up request outside interrupt context
    reqx->req.status = ECANCELED;
    INIT_WORK(&reqx->work, _aio_complete_worker); 
    schedule_work(&reqx->work);
    
    return 0;
}
/****************************************************************************
 * Callback invoked from edma completion hander for a completed request
 * @param req
 */
static void _aio_complete(struct aio_request *req)
{
    struct aio_req_private *reqx;    
    
    reqx =  container_of(req, struct aio_req_private, req);
    INIT_WORK(&reqx->work, _aio_complete_worker); 
    schedule_work(&reqx->work);
}
/*****************************************************************************
 * Asynchronous read or write
 * This is invoked by user code io_submit() for each struct iocb submitted.
 * 
 * @param iocb
 * @param iov       : User buffer parameters corresponding to struct iocb
 * @param nr_segs   : Always 1. See aio_setup_single_vector() in fs/aio.c
 * @param dir       : DMA_TO_DEVICE or DMA_FROM_DEVICE
 * @return -EIOCBQUEUED : request queued successfully without errors 
 *         Any other -ve value is error
 */
ssize_t dt78xx_aio(struct kiocb *iocb, const struct iovec *iov,
                   unsigned long nr_segs, enum dma_data_direction dir)
{
    int ret = 0;
    struct aio_req_private *reqx = NULL;
    struct dt78xx_device *dt_dev;
    struct device *dev;
    
    dt_dev = file_to_dt78xx(iocb->ki_filp);
    dev = &dt_dev->pdev->dev;
    //sanity check
    if (WARN_ON((nr_segs != 1)|| (!iocb) || (!iov) || 
                ((dir!=DMA_TO_DEVICE) && (dir!=DMA_FROM_DEVICE))))
    {
        return (-EINVAL);
    }
    //prevent cat/echo operations that are synchronous and cause panic in
    //kiocb_set_cancel_fn() later
    if (!iocb->ki_ctx)
    {
        return -EPERM;
    }
    
    dev_lock(dt_dev);

    //allocate the private data structure to manage this AIO request 
    reqx = kzalloc(sizeof(struct aio_req_private), GFP_KERNEL);
    if (unlikely(!reqx)) 
    {
        dev_err(dev, "[%s] ERROR kzalloc aio_request_in\n", __func__);
        ret = -ENOMEM;
        goto aiorfinish;
    }
    //initialize all members
    reqx->dir = dir;
    reqx->dt_dev = dt_dev;
    kref_init(&reqx->kref);
    reqx->iocb = iocb;
    reqx->iov.iov_base = iov[0].iov_base;
    reqx->iov.iov_len = iov[0].iov_len; //same as iocb->ki_nbytes
    reqx->req.complete_cb = _aio_complete;
    kiocb_set_cancel_fn(iocb, _aio_cancel);
    iocb->private = reqx;

    //Map user pages
    ret = _aio_get_user_pages(dev, reqx, 1);
    if (unlikely(ret)) 
    {
        goto aiorfinish;
    }
    //map scatter buffers corresponding to user pages
    ret = _aio_map_sg(dev, reqx);
    if (unlikely(ret)) 
    {
        dev_err(dev, "[%s] ERROR kzalloc sg array\n", __func__);
        goto aiorfinish;
    }
    //Finally queue this request 
    ret = dt78xx_request_queue(iocb->ki_filp, &reqx->req);
    if (unlikely(ret)) 
    {
        goto aiorfinish;
    }
    
aiorfinish :
    dev_unlock(dt_dev);

    if (ret) //error
    {
        iocb->private = NULL;
        if (reqx)
        {
            if (reqx->req.sg)
            {
                dma_unmap_sg(dev, reqx->req.sg, reqx->req.num_sgs, reqx->dir);
                kfree(reqx->req.sg);
            }
            if (reqx->usr_pg)
            {
                _aio_free_user_pages(reqx->usr_pg, reqx->req.num_sgs, 0);
            }
            kfree(reqx);    
        }
    }
    else
    {
        ret = -EIOCBQUEUED; //NOTE that success is not 0
    }
    return (ret);
}
EXPORT_SYMBOL_GPL(dt78xx_aio);
