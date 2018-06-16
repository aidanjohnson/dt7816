/*****************************************************************************
 * DT78xx USB gadget driver
 *
 * Copyright (C) 2014 Data Translation Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 ***************************************************************************** 
 * This kernel module is a simplified version of gadgetfs and has the same
 * kind of functionality. When loaded, it enumerates as a USB gadget, creates
 * a specified number of bulk USB endpoints and exposes each end point as a
 * virtual file in /dev. A user mode application
 * can perform file operations on each file to send data to the USB host through
 * an IN endpoint and receive data from the USB host via an OUT endpoint. The
 * module merely serves as a conduit for data and does not care about the data
 * itself.
 * Unlike gadgetfs, this module does not require the user to initialize it with
 * USB descriptors and to handle ep0 setup requests. All initialization is
 * performed, based on either defaults or modparms, when the module is loaded.
 * 
 * MODULE PARAMETERS :
 * ------------------
 * The following module parameters can be used in modprobe and will be listed
 * under /sys/module/g_dt78xx/parameters/. Default values are used if no 
 * modparms are specified in modprobe. 
 * 
 * module param         Description                          Default
   idVendor         USB Vendor ID (ushort)                   0x0867
   idProduct        USB Product ID (ushort)                  0x7855
   bcdDevice        USB Device version (BCD) (ushort)        0x0000           
   iSerialNumber    SerialNumber string (charp)              "0123456789"
   iManufacturer    USB Manufacturer string (charp)          "Data Translation"             
   iProduct         USB Product string (charp)               "DT78xx"
   inPipes          Number of bulk USB input pipes (ushort)   1
   outPipes         Number of bulk USB output pipes (ushort)  1
 
 * Example to override specific parameters,
 * modprobe g_dt78xx iManufacturer="ABCDefgh" idVendor=100
 * 
 * Each endpoint corresponds to a virtual file under /dev named as follows,
 * /dev/dtxxxx_ep1in    corresponds to EP1 IN address 0x81
 * /dev/dtxxxx_ep1out   corresponds to EP1 OUT address 0x01
 * as so on. The xxxx correspopnds to the idProduct
 * 
 * Note that the directions are relative to the USB host. Hence, to send data
 * to a USB host write to an IN endpoint. To receive data from a USB host read 
 * from an OUT endpoint. File operations on each virtual file are,
 * open       : both IN and OUT endpoints. A file can be opened by only one
 *              reader/writer at a time. Different files can be opened 
 *              simultaneously. Once a file is closed it can be re-opened. 
 * close      : both IN and OUT endpoints.  
 * read       : blocking read permitted on OUT endpoint
 * write      : blocking write permitted on IN endpoint
 * aio_read   : non-blocking, asynchronous read permitted on OUT endpoint
 * aio_write  : non-blocking, asynchronous write permitted on IN endpoint
 * flush      : flush data from endpoint, either direction
 * 
 * HOW TO LOAD THIS (or any) MODULE AT BOOTUP :
 * ------------------------------------------
 * Edit the /etc/modules file and add entries as the following. Note that
 * lines starting with # are comments.
 * 
    # Load the DT78xx USB gadget driver to enumerate as a DT7837 with 2 IN end
    # points and 5 OUT endpoints
    g_dt78xx idProduct=0x7837 iProduct="DT7837" inPipes=2 outPipes=5
 * 
 * 
 * NOTE :
 * ----------
 * After this gadget driver is loaded and connected to a Linux host, and you
 * execute 'lsusb' on the host, it may report the manufacturer as unknown and
 * missing product string. However, executing 'lsusb -v' and piping the results
 * to a text file will show that the strings specified by module parameters
 * iManufacturer, iProduct and iSerialNumber are reported correctly. This
 * anomaly is due to the fact that lsusb uses string definitions from the files
 * /usr/share/hwdata/usb.ids and/or /var/lib/usbutils/usb.ids and ignores the
 * strings reported by the USB string descriptors.
 *****************************************************************************/

/* #define VERBOSE_DEBUG */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/usb/composite.h>
#include <linux/fs.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/aio.h>
#include <linux/mmu_context.h>

/*****************************************************************************
 * Macros
 */
#define VERSION_STR             "1.1"
/* 
 * DO NOT REUSE THESE IDs with a protocol-incompatible driver!!
 * Instead:  allocate your own, using normal USB-IF procedures.
 */
#define DEFAULT_VENDOR_ID       0x0867		/* Data Translation */
#define DEFAULT_PRODUCT_ID      0x7855		/* DT7855 */
#define DEFAULT_DEVICE_ID       0X0000

#define DRIVER_NAME             "dt78xx"
#define DEFAULT_MANUFACTURER    "Data Translation"
#define DEFAULT_PRODUCT_NAME    "DT78xx"
#define GADGET_CLASS            "DT78xx_USB_class"

//Each endpoint pipe file under /dev will be prefixed with this name
#define EP_NAME_PREFIX  "dt"

#if 0
#define DBGPRINT(fmt, args...) yprintk(KERN_INFO, fmt, ## args)
#else
#define DBGPRINT(fmt, args...) 
#endif
/*****************************************************************************
 * Data types
 */
struct dt_usb_dev;

/*
 * The USB gadget has several pipes, each of which is represented by this
 * structure
 */
struct ep_pipe
{
    struct dt_usb_dev           *dt_dev;    //pointer to parent
    struct usb_ep               *ep;        //USB endpoint for this pipe
    struct device               *fdev;      //file in /dev for file operations
    atomic_t                    opened;     //1 if file has been opened
    struct completion           io_done;    //state of I/O completion
    size_t                      io_len;     //#of bytes read/written successfully
    int                         io_status;  //0=success => io_len has result
    spinlock_t                  pipe_lock;
};

/*
 * Single instance of custom USB gadget device
 */
struct dt_usb_dev
{
    struct usb_gadget           *gadget;
    struct class                *gadget_class;
    atomic_t                    connected;      //1 when connected to host
    dev_t                       devno;
	struct cdev                 chardev;
    struct usb_function         function;
    ushort                      num_ep_out;
    ushort                      num_ep_in;
    int                         num_ep;
    struct ep_pipe              **pipes;
    struct work_struct          xwork;
    spinlock_t                  dev_lock;
};

struct kiocb_priv 
{
	struct usb_request	*req;
	struct kiocb		*iocb;  //iocb from user
	struct mm_struct	*mm;
    struct work_struct	work;
	struct iovec        iov;    //non-contiguous buffers from user
	void                *buf;   //contiguous kernel buffer for user buffer
    struct kref         kref;   //ref counting for freeing resources
};

/*****************************************************************************
 * File scope functions
 */

//USB gadget function callbacks
static int usb_func_bind(struct usb_configuration *c,
                             struct usb_function *f);
static int usb_func_set_alt(struct usb_function *f,
                                unsigned intf, unsigned alt);
static void usb_func_disable(struct usb_function *);

//USB gadget configuration callbacks
static void usb_cfg_unbind(struct usb_configuration *);
static int  usb_cfg_bind(struct usb_configuration *);

//USB gadget composite driver callbacks
static int  gadget_unbind(struct usb_composite_dev *);
static void suspend(struct usb_composite_dev *);
static int  gadget_bind(struct usb_composite_dev *);
static void resume(struct usb_composite_dev *);

//File i/o operations on each endpoint pipe
static int ep_file_open(struct inode *, struct file *);
static int ep_file_close(struct inode *, struct file *);
static ssize_t ep_file_read(struct file *, char __user *, size_t , loff_t *);
static ssize_t ep_file_write(struct file *f, const char __user *buf, size_t len, 
                        loff_t *off);
static int ep_file_flush(struct file *, fl_owner_t id);
static ssize_t ep_file_aio_read(struct kiocb *iocb, const struct iovec *iov,
                                unsigned long nr_segs, loff_t o);
static ssize_t ep_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
                                unsigned long nr_segs, loff_t o);
static int ep_aio_cancel(struct kiocb *iocb);

static void disable_endpoints(void);
static void ep_io_complete (struct usb_ep *ep, struct usb_request *req);
static struct usb_request *alloc_ep_req(struct usb_ep *ep, int len);
static void _file_destroy_workcb(struct work_struct *work);

static inline int is_epfile_open(struct ep_pipe *p)
{
    return (atomic_read(&p->opened)==1);
}
static inline int is_host_connected(struct dt_usb_dev *p)
{
    return (atomic_read(&p->connected) ==1);
}
/*****************************************************************************
 * Global variables
 */

/*
 Default Module parameters
 */
USB_GADGET_COMPOSITE_OPTIONS();


static struct usb_configuration g_usb_config = 
{
	.label			= "dt78xx cfg",
	.unbind			= usb_cfg_unbind,
	.bConfigurationValue	= 1,
	.bmAttributes		= USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER,
};

//USB Device Descriptor
static struct usb_device_descriptor g_dev_dscr = 
{
	.bLength         =	USB_DT_DEVICE_SIZE,
	.bDescriptorType =	USB_DT_DEVICE,

	.bcdUSB         = cpu_to_le16(0x0200),
	.bDeviceClass   = USB_CLASS_VENDOR_SPEC,

	.idVendor       = cpu_to_le16(DEFAULT_VENDOR_ID),
	.idProduct      = cpu_to_le16(DEFAULT_PRODUCT_ID),
    .bcdDevice      = cpu_to_le16(DEFAULT_DEVICE_ID),
	.bNumConfigurations =	1,
};

/*
 * USB Interface Descriptor
 * Note that bNumEndpoints is overwritten at bind time with the total of
 * input and output endpoints specified with module params 
 */
static struct usb_interface_descriptor g_intf_dscr = 
{
	.bLength            = USB_DT_INTERFACE_SIZE,
	.bDescriptorType    = USB_DT_INTERFACE,
    .bAlternateSetting	= 0,
	.bNumEndpoints      = 2, //overwriten at bind time
	.bInterfaceClass    = USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass = USB_SUBCLASS_VENDOR_SPEC,	
	.bInterfaceProtocol = 0, //don't care for USB_CLASS_VENDOR_SPEC
	.iInterface         = 0, //Index of String Descriptor for this i/f
    .bInterfaceNumber   = 0, //will be assigned by bind
};
#if 0
/*
 * THERE MUST BE NUM_EP_OUT EP DESCRIPTORS !!!
 */

//Fullspeed USB Endpoint descriptor for EP1 out
static struct usb_endpoint_descriptor g_fs_ep_dscr0 = 
{
	.bLength        = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType= USB_DT_ENDPOINT,
	.bmAttributes   = USB_ENDPOINT_XFER_BULK,
    .bEndpointAddress =	USB_DIR_OUT,
};

//High speed USB Endpoint descriptor for EP1 out
static struct usb_endpoint_descriptor g_hs_ep_dscr0 = 
{
	.bLength        = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType= USB_DT_ENDPOINT,
	.bmAttributes   = USB_ENDPOINT_XFER_BULK,
    .wMaxPacketSize = cpu_to_le16(512),
    .bEndpointAddress =	USB_DIR_OUT,
};
/*
 * THERE MUST BE NUM_EP_IN EP DESCRIPTORS !!!
 */

//Fullspeed USB Endpoint descriptor for EP1 in
static struct usb_endpoint_descriptor g_fs_ep_dscr1 = 
{
	.bLength        = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType= USB_DT_ENDPOINT,
	.bmAttributes   = USB_ENDPOINT_XFER_BULK,
    .bEndpointAddress =	USB_DIR_IN,
};
//High USB Endpoint descriptor for EP1 in
static struct usb_endpoint_descriptor g_hs_ep_dscr1 = 
{
	.bLength        = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType= USB_DT_ENDPOINT,
	.bmAttributes   = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize = cpu_to_le16(512),
    .bEndpointAddress =	USB_DIR_IN,
};

//Full speed endpoint descriptors
static struct usb_descriptor_header *g_fs_dscr[] = 
{
	(struct usb_descriptor_header *) &g_intf_dscr, //I/f descriptor at index 0
	(struct usb_descriptor_header *) &g_fs_ep_dscr0,
	(struct usb_descriptor_header *) &g_fs_ep_dscr1,
	NULL
};
//High speed endpoint descriptors
static struct usb_descriptor_header *g_hs_dscr[] = 
{
	(struct usb_descriptor_header *) &g_intf_dscr, //I/f descriptor at index 0
	(struct usb_descriptor_header *) &g_hs_ep_dscr0,
	(struct usb_descriptor_header *) &g_hs_ep_dscr1,
	NULL
};
#endif
//Full speed endpoint descriptor array
static struct usb_descriptor_header **g_fs_dscr = NULL; 
//High speed endpoint descriptor array
static struct usb_descriptor_header **g_hs_dscr = NULL;

/* default serial number  */
static char g_serial[] = "0123456789";

/* string IDs are assigned dynamically */
static struct usb_string g_strings_dev[] = 
{
	[USB_GADGET_MANUFACTURER_IDX].s = DEFAULT_MANUFACTURER, //index 0
	[USB_GADGET_PRODUCT_IDX].s      = DEFAULT_PRODUCT_NAME, //index 1
	[USB_GADGET_SERIAL_IDX].s       = g_serial,             //index 2
	{  }			/* end of list */
};

static struct usb_gadget_strings g_stringtab_dev = 
{
	.language	= 0x0409,	/* en-us */
	.strings	= g_strings_dev,
};

static struct usb_gadget_strings *g_dev_strings[] = 
{
	&g_stringtab_dev,
	NULL,
};

static struct usb_string g_strings_function[] = 
{
	[0].s = "source and sink data",
	{  }			/* end of list */
};

static struct usb_gadget_strings g_stringtab_function = 
{
	.language	= 0x0409,	/* en-us */
	.strings	= g_strings_function,
};

static struct usb_gadget_strings *g_function_strings[] = 
{
	&g_stringtab_function,
	NULL,
};

static __refdata struct usb_composite_driver g_composite_driver = 
{
	.name		= DRIVER_NAME,
	.dev		= &g_dev_dscr,
	.strings	= g_dev_strings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= gadget_bind,
	.unbind		= gadget_unbind,
	.suspend	= suspend,
	.resume		= resume,
};

#ifdef _WARN_
#warning Need to add function unbind
#endif
static struct dt_usb_dev g_78xx_dev =
{
	.function.name      = "dt78xx usbg func",
	.function.bind      = usb_func_bind,     //REQUIRED
	.function.set_alt   = usb_func_set_alt, //REQUIRED
	.function.disable   = usb_func_disable, //REQUIRED
    .function.strings   = g_function_strings,
    .num_ep_out         = 1, //set by module param
    .num_ep_in          = 1, //set by module param
    .num_ep             = 2,
};
module_param_named(inPipes, g_78xx_dev.num_ep_out, ushort, S_IRUGO); 
MODULE_PARM_DESC(inPipes, "Number of bulk USB input pipes");

module_param_named(outPipes, g_78xx_dev.num_ep_in, ushort, S_IRUGO); 
MODULE_PARM_DESC(outPipes, "Number of bulk USB output pipes");

/**
 * Allocates a usb_request plus a buffer of the specified size and initializes
 * the request to point to the allocated buffer
 * @param ep    : endpoint
 * @param len   : length of data buffer
 * @return      : NULL on error, non-NULL is pointer to allocated request
 */
static struct usb_request *alloc_ep_req(struct usb_ep *ep, int len)
{
	struct usb_request *req = NULL;
    if (len <= 0)
    {
        return NULL;
    }
	req = usb_ep_alloc_request(ep, GFP_ATOMIC);
	if (req) 
    {
		req->length = len;
		req->buf = kmalloc(req->length, GFP_ATOMIC);
		if (!req->buf) 
        {
			usb_ep_free_request(ep, req);
			req = NULL;
		}
	}
	return req;
}

/**
 * Free a usb_request plus its constituent buffer
 * @param ep    : end point
 * @param req   : usb_request allocated by alloc_ep_req()
 */
void free_ep_req(struct usb_ep *ep, struct usb_request *req)
{
	kfree(req->buf);
	usb_ep_free_request(ep, req);
}

/**
 * Open the virtual file associated with the pipe corresponding to the file's
 * minor number. A file can be opened by only one reader at a time.
 * @return 
 * -ENODEV if minor number is invalid
 * -EBUSY if file is already opened
 * 0 for success, file's private_data points to corresponding ep_pipe
 */
static int ep_file_open(struct inode *inode, struct file *fd)
{
    struct ep_pipe    *pipe;
    int err = 0;
    int i;
    
    //No file I/O if disconnected from host
    if (!is_host_connected(&g_78xx_dev)) 
    {
        ERROR(&g_78xx_dev, "[%s] ERROR ENOTCONN\n", __func__);
        return (-ENOTCONN);
    }
    
    /*
     * Associate an endpoint (and pipe) with the file's minor number
     */
    i = iminor(inode);
    if (i >= g_78xx_dev.num_ep)
    {
        ERROR(&g_78xx_dev, "[%s] ERROR minor %d\n", __func__,i);
        return (-ENODEV);
    }
    
    pipe = g_78xx_dev.pipes[i];
    if (is_epfile_open(pipe))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR %s already opened\n", 
                            __func__,pipe->ep->name);
        err = -EBUSY;
    }
    else
    {
        atomic_set(&pipe->opened, 1); //file opened
        fd->private_data = pipe;
        DBG(&g_78xx_dev, "[%s] %s\n", __func__,pipe->ep->name);
    }

    return (err);
}

/**
 * Close the virtual file associated with an endpoint pipe
 * @param inode
 * @param fd
 * @return 0 always
 */
static int ep_file_close(struct inode *inode, struct file *fd)
{
    int remain;
    struct ep_pipe *pipe = fd->private_data;
    
    DBG(&g_78xx_dev, "[%s] %s\n", __func__,pipe->ep->name);
    
    atomic_set(&pipe->opened, 0); //file closed
    fd->private_data = NULL;
    /*
     * FLush any data pending in the fifo . Note that this calls
     * musb_gadget_fifo_status() which only works for OUT ep's
     */
    remain = usb_ep_fifo_status(pipe->ep);
    usb_ep_fifo_flush(pipe->ep);
    
    if (remain > 0)
    {
        DBGPRINT(&g_78xx_dev, "[%s] %s fifo remain %d\n", 
                          __func__,pipe->ep->name, remain);
    }
    
    return (0);
}
static int ep_file_flush(struct file *fd, fl_owner_t id)
{
    struct ep_pipe *pipe = fd->private_data;
    
    DBG(&g_78xx_dev, "[%s] %s\n", __func__,pipe->ep->name);
    
    usb_ep_fifo_flush(pipe->ep);
    
    return (0);
}

/*
 * Complete the aio and free resources with the kref goes to zero
 */
static void _aio_finish(struct kref *kref)
{
	struct kiocb_priv *priv;
    struct kiocb *iocb;
    struct ep_pipe *pipe;
    int status;
    unsigned int len;
    
    priv = container_of(kref, struct kiocb_priv, kref);
    iocb = priv->iocb;
    pipe = iocb->ki_filp->private_data;
    status = priv->req->status;
    len = priv->req->actual;
   
    priv->req->buf = NULL;
    usb_ep_free_request(pipe->ep, priv->req);
	kfree(priv->buf);
	kfree(priv);
    iocb->private = NULL;
    
    aio_complete(iocb, len, status);
}

static void ep_aio_cancel_worker(struct work_struct *work)
{
    int err =0;
	struct kiocb_priv *priv = container_of(work, struct kiocb_priv, work);
    struct kiocb *iocb = priv->iocb;
    struct ep_pipe *pipe = iocb->ki_filp->private_data;
    /*
     * dequeue will call either ep_aio_read_complete or ep_aio_write_complete,
     * which will do one kref_put()
     * If we fail to dequeue, it means that the request has been removed from
     * the queue  
     */
    DBG(&g_78xx_dev, "[%s] %s iocb %p status=%d actual=%d\n",
          __func__, pipe->ep->name, iocb,
          priv->req->status, priv->req->actual);
    
    err = usb_ep_dequeue (pipe->ep, priv->req);
    if (err)
    {
        ERROR(&g_78xx_dev, "[%s] ERROR iocb %p usb_ep_dequeue %d\n", 
              __func__, iocb , err);
    }
    kref_put(&priv->kref, _aio_finish);
}

/**
 * Called to cancel all outstanding reuests
 * @param iocb
 * @return 0
 */
static int ep_aio_cancel(struct kiocb *iocb)
{
    unsigned long flags;
    struct kiocb_priv *priv;
    struct ep_pipe *pipe = iocb->ki_filp->private_data;

    /* IMPORTANT !!!
     * Cannot call usb_ep_dequeue() here since that calls ep_aio_complete() that
     * in turn will aio_complete(). Since this callback already has acquired
     * the same lock which aio_complete attempts to re-acquire, the result
     * is a hang.
     * 
     * See kiocb_cancel in fs/aio.c and refer to
     * http://www.spinics.net/lists/linux-fsdevel/msg72070.html
     */
	spin_lock_irqsave(&pipe->pipe_lock, flags);
    priv = iocb->private;
    
    if (priv)
    {
        if (schedule_work(&priv->work))
        {
            kref_get(&priv->kref);
            priv->work.func = ep_aio_cancel_worker;
            DBG(&g_78xx_dev, "[%s] %s iocb %p\n",__func__, pipe->ep->name, iocb);
        }
        else 
        {
            ERROR(&g_78xx_dev, "[%s] %s iocb %p not scheduled\n",
                  __func__, pipe->ep->name, iocb);
        }
    }
	spin_unlock_irqrestore(&pipe->pipe_lock, flags);
	return 0;
}

static void ep_user_copy_worker(struct work_struct *work)
{
    unsigned int copy_len;
	struct kiocb_priv *priv;
   
    priv = container_of(work, struct kiocb_priv, work);
    copy_len = priv->req->actual;
    
    if (copy_len)
    {
        struct mm_struct *mm = priv->mm;
        if (!mm)
        {
            priv->req->status = -EHWPOISON;
        }
        else
        {
            use_mm(mm);
            if (copy_len > priv->iov.iov_len)
            {
                copy_len = priv->iov.iov_len;
            }
            if (copy_to_user(priv->iov.iov_base, priv->buf, copy_len)) 
            {
                priv->req->status = -EFAULT;
            }
            unuse_mm(mm);
        }
    }
    DBG(&g_78xx_dev, "[%s] iocb %p status=%d actual=%d\n",
          __func__, priv->iocb,
          priv->req->status, priv->req->actual);
    kref_put(&priv->kref, _aio_finish);
}

/**
 * Completion handler for every USB request submitted by ep_file_aio_read
 * @param ep    : struct usb_ep *
 * @param req   : struct usb_request *
 */
static void ep_aio_read_complete(struct usb_ep *ep, struct usb_request *req)
{
    unsigned long flags;
	struct kiocb_priv	*priv;
	struct kiocb		*iocb = req->context;
    struct ep_pipe      *pipe = iocb->ki_filp->private_data;
       
	/* lock against disconnect (and ideally, cancel) */
	spin_lock_irqsave(&pipe->pipe_lock, flags);
    priv = iocb->private;
    if (priv)
    {
        /*
         * If we fail to schedule the completion worker it means that the 
         * cancellation worker is scheduled and pending. Therefore, there will
         * be one outstanding kref_put() that would have been performed by the
         * completion handler. Hence, we kref_put() here
         */
        if (schedule_work(&priv->work))
        {
            priv->work.func = ep_user_copy_worker;
            DBG(&g_78xx_dev, "[%s] %s iocb %p status=%d actual=%d\n",
                  __func__, pipe->ep->name, iocb,
                  req->status, req->actual);
        }
        else 
        {
            kref_put(&priv->kref, _aio_finish);
            ERROR(&g_78xx_dev, "[%s] %s iocb %p status=%d actual=%d not scheduled\n",
                  __func__, pipe->ep->name, iocb,
                  req->status, req->actual);
        }
    } 
	spin_unlock_irqrestore(&pipe->pipe_lock, flags);
}

/**
 * Asynchronous read.
 * This is invoked by user code io_submit() for each struct iocb submitted.
 * 
 * @param iocb
 * @param iov       : User buffer parameters corresponding to struct iocb
 * @param nr_segs   : Always 1. See aio_setup_single_vector() in fs/aio.c
 * @param o         : Offset into buffer. Not used
 * @return -EIOCBQUEUED : request queued successfully without errors 
 *         Any other -ve value is error
 */
static ssize_t ep_file_aio_read(struct kiocb *iocb, const struct iovec *iov,
                                unsigned long nr_segs, loff_t o)
{
    int ret = 0;
    struct kiocb_priv *priv = NULL;
    struct ep_pipe *pipe = iocb->ki_filp->private_data;
    
    //Cannot read if disconnected from host
    if (!is_host_connected(&g_78xx_dev)) 
    {
        ERROR(&g_78xx_dev, "[%s] ERROR ENOTCONN\n", __func__);
        return (-ENOTCONN);
    }
    
    //Can only read from host's OUT endpoint
    if (!usb_endpoint_dir_out(pipe->ep->desc))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR %s is IN\n", __func__,pipe->ep->name);
        return (-EINVAL);
    }
    
    //sanity check
    if (nr_segs != 1)
    {
        ERROR(&g_78xx_dev, "[%s] %s segs %lu\n", __func__,pipe->ep->name,nr_segs);
        return (-EINVAL);
    }
    //allocate a kiocb_priv to manage this AIO request 
    priv = kzalloc(sizeof(struct kiocb_priv), GFP_KERNEL);
	if (unlikely(!priv)) 
    {
        ERROR(&g_78xx_dev, "[%s] ERROR kzalloc kiocb_priv\n", __func__);
        ret = -ENOMEM;
        goto aiorfinish;
    }
    //allocate a contiguous buffer for the user space buffer(s) 
    priv->buf = kmalloc(iocb->ki_nbytes, GFP_KERNEL);
	if (unlikely(!priv->buf))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR kmalloc %d bytes\n", 
                            __func__, iocb->ki_nbytes);
        ret = -ENOMEM;
        goto aiorfinish;
    }
    //allocate a USB request 
    priv->req = usb_ep_alloc_request(pipe->ep, GFP_ATOMIC);
    if (unlikely(!priv->req))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR usb_ep_alloc_request(%s,%d)\n",
                            __func__,pipe->ep->name, iocb->ki_nbytes);
        ret = -ENOMEM;
        goto aiorfinish;
    }
    
    iocb->private = priv;
    
    priv->req->complete = ep_aio_read_complete;
    priv->req->context = iocb;
	priv->req->buf = priv->buf;
	priv->req->length = iocb->ki_nbytes;
    kref_init(&priv->kref);
    priv->iocb = iocb;
    /*
     * There seems to be a bug in the kernel because the contents of the array
     * pointed by iov are nullified when this function exits. Therefore, the
     * values in the one and only entry in the array is copied and retained for
     * later completion. This is OK since nr_segs is 1
     */
	priv->iov.iov_base = iov[0].iov_base;
    priv->iov.iov_len = iov[0].iov_len;
    
	priv->mm = current->mm; 
	INIT_WORK(&priv->work, ep_user_copy_worker); 
 
	kiocb_set_cancel_fn(iocb, ep_aio_cancel);
    
    ret = usb_ep_queue(pipe->ep, priv->req, GFP_ATOMIC);
    if (ret)
    {
       ERROR(&g_78xx_dev, "[%s] ERROR %d %s usb_ep_queue\n", 
                            __func__,ret,pipe->ep->name);
       goto aiorfinish;
    }

aiorfinish :
    if (ret) //error
    {
        if (priv)
        {
            if (priv->buf)
            {
                kfree(priv->buf);
            }
            if (priv->req)
            {
                usb_ep_free_request(pipe->ep, priv->req);
            }
            kfree(priv);    
        }
    }
    else
    {
        ret = -EIOCBQUEUED; //NOTE that success is not 0
    }
    return (ret);
}

/**
 * Completion handler for every USB request submitted by ep_file_aio_write
 * @param ep    : struct usb_ep *
 * @param req   : struct usb_request *
 */
static void ep_aio_write_complete(struct usb_ep *ep, struct usb_request *req)
{
    unsigned long flags;
    struct kiocb_priv	*priv;
	struct kiocb		*iocb = req->context;
    struct ep_pipe      *pipe = iocb->ki_filp->private_data;
       
	/* lock against disconnect (and ideally, cancel) */
	spin_lock_irqsave(&pipe->pipe_lock, flags);
    priv = iocb->private;
    if (priv)
    {
        kref_put(&priv->kref, _aio_finish);
        DBG(&g_78xx_dev, "[%s] %s iocb %p status=%d actual=%d\n",
              __func__, pipe->ep->name, iocb,
              req->status, req->actual);
    }
	spin_unlock_irqrestore(&pipe->pipe_lock, flags);
}

/**
 * Asynchronous write.
 * This is invoked by user code io_submit() for each struct iocb submitted.
 * 
 * @param iocb
 * @param iov       : User buffer parameters corresponding to struct iocb
 * @param nr_segs   : Always 1. See aio_setup_single_vector() in fs/aio.c
 * @param o         : Offset into buffer. Not used
 * @return -EIOCBQUEUED : request queued successfully without errors 
 *         Any other -ve value is error
 */
static ssize_t ep_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
                                unsigned long nr_segs, loff_t o)
{
    int ret = 0;
    struct kiocb_priv *priv = NULL;
    struct ep_pipe *pipe = iocb->ki_filp->private_data;
    
    //Cannot read if disconnected from host
    if (!is_host_connected(&g_78xx_dev)) 
    {
        ERROR(&g_78xx_dev, "[%s] ERROR ENOTCONN\n", __func__);
        return (-ENOTCONN);
    }
    
    //Can only write to host's IN endpoint
    if (!usb_endpoint_dir_in(pipe->ep->desc))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR %s is OUT\n", __func__,pipe->ep->name);
        return (-EINVAL);
    }
    
    //sanity check
    if (nr_segs != 1)
    {
        ERROR(&g_78xx_dev, "[%s] %s segs %lu\n", __func__,pipe->ep->name,nr_segs);
        return (-EINVAL);
    }
    //allocate a kiocb_priv to manage this AIO request 
    priv = kzalloc(sizeof(struct kiocb_priv), GFP_KERNEL);
	if (unlikely(!priv)) 
    {
        ERROR(&g_78xx_dev, "[%s] ERROR kzalloc kiocb_priv\n", __func__);
        ret = -ENOMEM;
        goto aiowfinish;
    }
    /*
     * There seems to be a bug in the kernel because the contents of the array
     * pointed by iov are nullified when this function exits. Therefore, the
     * values in the one and only entry in the array is copied and retained for
     * later completion. This is OK since nr_segs is 1
     */
	priv->iov.iov_base = iov[0].iov_base;
    priv->iov.iov_len = iov[0].iov_len;
    
    //allocate a contiguous buffer for the user space buffer(s) 
    priv->buf = kmalloc(iocb->ki_nbytes, GFP_KERNEL);
	if (unlikely(!priv->buf))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR kmalloc %d bytes\n", 
                            __func__, iocb->ki_nbytes);
        ret = -ENOMEM;
        goto aiowfinish;
    }
    //copy the user's buffer to kernel space
    if (unlikely(copy_from_user(priv->buf, priv->iov.iov_base, 
                                priv->iov.iov_len) != 0)) 
    {
        ret = -EFAULT;
        goto aiowfinish;
    }
    //allocate a USB request 
    priv->req = usb_ep_alloc_request(pipe->ep, GFP_ATOMIC);
    if (unlikely(!priv->req))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR usb_ep_alloc_request(%s,%d)\n",
                            __func__,pipe->ep->name, iocb->ki_nbytes);
        ret = -ENOMEM;
        goto aiowfinish;
    }
    
    iocb->private = priv;
    
    priv->req->complete = ep_aio_write_complete;
    priv->req->context = iocb;
	priv->req->buf = priv->buf;
	priv->req->length = iocb->ki_nbytes;
    kref_init(&priv->kref);
    priv->iocb = iocb;
    
	priv->mm = current->mm; //not used for write
 
	kiocb_set_cancel_fn(iocb, ep_aio_cancel);
	INIT_WORK(&priv->work, ep_aio_cancel_worker); 
    
    ret = usb_ep_queue(pipe->ep, priv->req, GFP_ATOMIC);
    if (ret)
    {
       ERROR(&g_78xx_dev, "[%s] ERROR %d %s usb_ep_queue\n", 
                            __func__,ret,pipe->ep->name);
       goto aiowfinish;
    }

aiowfinish :
    if (ret) //error
    {
        if (priv)
        {
            if (priv->buf)
            {
                kfree(priv->buf);
            }
            if (priv->req)
            {
                usb_ep_free_request(pipe->ep, priv->req);
            }
            kfree(priv);    
        }
    }
    else
    {
        ret = -EIOCBQUEUED; //NOTE that success is not 0
    }
    return (ret);
}

/**
 * Read completion handler for endpoint
 * @param ep    : endpoint (driver_data points to struct ep_pipe)
 * @param req   : usb_request (context points to struct ep_pipe)
 */
static void ep_io_complete (struct usb_ep *ep, struct usb_request *req)
{
	struct ep_pipe *pipe = (struct ep_pipe *)req->context;

	if (req->status)
    {
        DBGPRINT(&g_78xx_dev, "[%s] %s status %d\n", 
                         __func__,pipe->ep->name, req->status);
		pipe->io_len = 0;
        pipe->io_status = req->status;
    }
	else
    {
		pipe->io_len = req->actual;
        pipe->io_status = 0;
    }
	complete (&pipe->io_done);
}
/**
 * Synchronous/blocking read operation on out endpoint
 * @param fd    : file handle from open(). 
 *                file's private_data points to corresponding ep_pipe
 * @param buf   : user buffer pointer
 * @param len   : length of user buffer
 * @param off   : offset IGNORED
 * @return      : >0 number of bytes returned in user buffer
 *                <=0 error
 */
static ssize_t ep_file_read(struct file *fd, char __user *buf, size_t len, 
                         loff_t *off)
{
    int ret = 0;
    struct usb_request	*req;
    struct ep_pipe *pipe = fd->private_data;
 
    //No file I/O if disconnected from host
    if (!is_host_connected(&g_78xx_dev)) 
    {
        ERROR(&g_78xx_dev, "[%s] ERROR ENOTCONN\n", __func__);
        return (-ENOTCONN);
    }
    
    //Can only read from host's OUT endpoint
    if (!usb_endpoint_dir_out(pipe->ep->desc))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR %s is IN\n", __func__,pipe->ep->name);
        return (-EINVAL);
    }
    
    //if the file was opened in non-blocking mode then return error
    if (fd->f_flags & (O_NONBLOCK|O_NDELAY))
    {
        ERROR(&g_78xx_dev, "[%s] %s ERROR EWOULDBLOCK\n", 
                            __func__,pipe->ep->name);
        return (-EWOULDBLOCK);
    }
    
    /*allocate a request and queue it. The musb_gadget will start the I/O on 
     * the first queued request
     */
    req = alloc_ep_req(pipe->ep, len);
    if (!req)
    {
        ERROR(&g_78xx_dev, "[%s] ERROR alloc_ep_req(%s,%d)\n",
                            __func__,pipe->ep->name, len);
        return (-ENOMEM);
    }
    INIT_COMPLETION(pipe->io_done);
    pipe->io_len = 0; 
    pipe->io_status = 0;
    req->complete = ep_io_complete;
    req->context = pipe; //request context points to corresponding pipe
    ret = usb_ep_queue(pipe->ep, req, GFP_ATOMIC);
    if (ret)
    {
       ERROR(&g_78xx_dev, "[%s] ERROR %d %s usb_ep_queue\n", 
                            __func__,ret,pipe->ep->name);
    }
    else 
    {
        //wait for read completion
        ret = wait_event_interruptible(pipe->io_done.wait, pipe->io_done.done);
        if (ret)
        {
            usb_ep_dequeue (pipe->ep, req);
            wait_event(pipe->io_done.wait, pipe->io_done.done);
            ERROR(&g_78xx_dev, "[%s] ERROR %d %s interrupted\n", 
                                __func__,ret,pipe->ep->name);
        }
        else if (pipe->io_status)
        {
            ret = pipe->io_status;
        }
    }
    
    if ((ret==0) && (pipe->io_len > 0))
    {
        ret = pipe->io_len;
        if (copy_to_user(buf, req->buf, ret))
        {
            ret = -EFAULT;
        }
    }
    
    free_ep_req(pipe->ep, req);
    
    return (ret);
}

static ssize_t ep_file_write(struct file *fd, const char __user *buf, size_t len, 
                        loff_t *off)
{
    int ret = 0;
    struct usb_request	*req;
    struct ep_pipe *pipe = fd->private_data;
    
    //No file I/O if disconnected from host
    if (!is_host_connected(&g_78xx_dev)) 
    {
        ERROR(&g_78xx_dev, "[%s] ERROR ENOTCONN\n", __func__);
        return (-ENOTCONN);
    }
    
    //Can only write to host's IN endpoint
    if (!usb_endpoint_dir_in(pipe->ep->desc))
    {
        ERROR(&g_78xx_dev, "[%s] ERROR %s is out\n", __func__,pipe->ep->name);
        return (-EINVAL);
    }
    
    //if the file was opened in non-blocking mode then return error
    if (fd->f_flags & (O_NONBLOCK|O_NDELAY))
    {
        ERROR(&g_78xx_dev, "[%s] %s ERROR EWOULDBLOCK\n", 
                            __func__,pipe->ep->name);
        return (-EWOULDBLOCK);
    }
    
    /*allocate a request and queue it. The musb_gadget will start the I/O on 
     * the first queued request
     */
    req = alloc_ep_req(pipe->ep, len);
    if (!req)
    {
        ERROR(&g_78xx_dev, "[%s] ERROR alloc_ep_req(%s,%d)\n",
                            __func__,pipe->ep->name, len);
        return (-ENOMEM);
    }
    if (copy_from_user(req->buf, buf, len))
    {
        free_ep_req(pipe->ep, req);
        ERROR(&g_78xx_dev, "[%s] copy_from_user(%s, %d)\n", 
                            __func__,pipe->ep->name, len);
        return (-EFAULT);
    }
    
    INIT_COMPLETION(pipe->io_done);
    pipe->io_len = 0; 
    pipe->io_status = 0;
    req->complete = ep_io_complete;
    req->context = pipe; //request context points to corresponding pipe
    ret = usb_ep_queue(pipe->ep, req, GFP_ATOMIC);
    if (ret)
    {
       ERROR(&g_78xx_dev, "[%s] ERROR %d %s usb_ep_queue\n", 
                            __func__,ret,pipe->ep->name);
    }
    else 
    {
        //wait for read completion
        ret = wait_event_interruptible(pipe->io_done.wait, pipe->io_done.done);
        if (ret)
        {
            usb_ep_dequeue (pipe->ep, req);
            wait_event(pipe->io_done.wait, pipe->io_done.done);
            ERROR(&g_78xx_dev, "[%s] ERROR %d %s interrupted\n", 
                                __func__,ret,pipe->ep->name);
        }
        else if (pipe->io_status)
        {
            ret = pipe->io_status;
            ERROR(&g_78xx_dev, "[%s] status %d %s\n", 
                                __func__,ret,pipe->ep->name);
        }
        else
        {
            ret = pipe->io_len;
            DBG(&g_78xx_dev, "[%s] %s wrote %d\n", 
                            __func__,pipe->ep->name, ret);
        }
    }
    
    free_ep_req(pipe->ep, req);
    
    return (ret);
}
/*
 * File operations permitted on endpoints
 */
static const struct file_operations g_ep_file_ops = 
{
  .owner    = THIS_MODULE,
  .open     = ep_file_open,
  .release  = ep_file_close,
  .read     = ep_file_read,
  .write    = ep_file_write,
  .flush    = ep_file_flush,
  .aio_read = ep_file_aio_read,
  .aio_write= ep_file_aio_write,
};

static void disable_endpoints(void)
{
    int i;
    struct ep_pipe *pipe;    
    for (i=0; i < g_78xx_dev.num_ep; ++i)
    {
        pipe = g_78xx_dev.pipes[i];
        if (pipe->ep->driver_data)
        {
            int err = usb_ep_disable(pipe->ep);
            if (err)
            {
                pr_err("[%s] ERROR %d\n", __func__, err);
            }
            pipe->ep->driver_data = NULL;
        }
    }
}

static void suspend(struct usb_composite_dev *cdev)
{
    DBGPRINT(cdev, "[%s]\n", __func__);
    if (is_host_connected(&g_78xx_dev))
    {
       disable_endpoints();

       INIT_WORK(&g_78xx_dev.xwork, _file_destroy_workcb); 
       schedule_work(&g_78xx_dev.xwork);
       //Gadget disconnected from USB host
       atomic_set(&g_78xx_dev.connected, 0);   
    }
#if 0    
	if (cdev->gadget->speed == USB_SPEED_UNKNOWN)
		return;
#endif    
}

static void resume(struct usb_composite_dev *cdev)
{
	DBGPRINT(cdev, "[%s]\n", __func__);
}

/**
 * Work function to create sysfs files for each endpoint pipe
 * @param work
 */
static void _file_create_workcb(struct work_struct *work)
{
    int i, err = 0;
	pr_info("%s\n", __func__);
    // Setup a sysfs files for the each endpoint pipe and register a char dev
    for (i=0; (i < g_78xx_dev.num_ep) && (err==0); ++i)
    {
        dev_t devno = MKDEV(MAJOR(g_78xx_dev.devno), (MINOR(g_78xx_dev.devno) + i));

        g_78xx_dev.pipes[i]->fdev = device_create(g_78xx_dev.gadget_class, NULL, 
                                                    devno, g_78xx_dev.pipes[i], 
                                                    "%s%x-%s",
                                                    EP_NAME_PREFIX,
                                                    g_dev_dscr.idProduct,
                                                    g_78xx_dev.pipes[i]->ep->name);
        
        if (IS_ERR(g_78xx_dev.pipes[i]->fdev)) 
        {
           err = -ENODEV;
        }
    }
}

/**
 * Work function to destroy sysfs files for each endpoint pipe
 * @param work
 */
static void _file_destroy_workcb(struct work_struct *work)
{
    int i;
	//Remove sysfs files
    for (i=0; i < g_78xx_dev.num_ep; ++i)
    {
        dev_t devno = MKDEV(MAJOR(g_78xx_dev.devno), 
                            (MINOR(g_78xx_dev.devno) + i));
        if (g_78xx_dev.pipes[i]->fdev)
        {
            device_destroy(g_78xx_dev.gadget_class, devno);
        }
    }	
}

/**
 * Select alternate interface.
 * @param func_ptr
 * @param intf
 * @param alt
 * @return 0 for success, -ENOTSUPP if intf!=0 or alt!=0
 */
static int usb_func_set_alt(struct usb_function *func, unsigned intf, 
                               unsigned alt)
{
    struct usb_composite_dev *cdev = func->config->cdev;
    struct usb_gadget * gadget = cdev->gadget;
    int i;
    int err = 0;
    struct ep_pipe *pipe;
	
    INFO(cdev, "[%s] speed=%s intf=%d alt=%d\n", __func__,
                    (gadget->speed==USB_SPEED_HIGH)?"HIGH":
                    (gadget->speed==USB_SPEED_FULL)?"FULL":"Unsupported",
                    intf, alt);
    
    if ((intf!=0)||(alt!=0))
    {
       ERROR(cdev, "[%s] ERROR cannot set i/f\n", __func__);
       return (-ENOTSUPP);
    }
       
    atomic_set(&g_78xx_dev.connected, 0);    
    disable_endpoints();
    
    INIT_WORK(&g_78xx_dev.xwork, _file_create_workcb); 
    schedule_work(&g_78xx_dev.xwork);

    for (i=0; i < g_78xx_dev.num_ep; ++i)
    {
        pipe = g_78xx_dev.pipes[i];
        err = config_ep_by_speed(gadget, &g_78xx_dev.function, pipe->ep);
        if (err)
        {
            ERROR(cdev, "[%s] ERROR %s config_ep_by_speed\n", 
                                     __func__, pipe->ep->name);   
            break;
        }
        err = usb_ep_enable(pipe->ep);
        if (err < 0)
        {
            ERROR(cdev, "[%s] ERROR %d usb_ep_enable(%s)\n", 
                                     __func__, err, pipe->ep->name);   
            break;
        }
        pipe->ep->driver_data = pipe;	/* claim */
    }
    
    //if any errors from trying to enable any endpoints, then disable all
    if (err)
    {
        disable_endpoints();
    }
    else
    {
        //Gadget connected to USB host
        atomic_set(&g_78xx_dev.connected, 1); 
        DBG(cdev, "[%s] connected & enabled\n",__func__); 
    }

	return (0);
}

static void usb_func_disable(struct usb_function *func)
{
#if 0
    struct usb_composite_dev *cdev = func->config->cdev;
    DBGPRINT(cdev, "[%s]\n", __func__);
#endif
    if (is_host_connected(&g_78xx_dev))
    {
        disable_endpoints();

        INIT_WORK(&g_78xx_dev.xwork, _file_destroy_workcb); 
        schedule_work(&g_78xx_dev.xwork);
        //Gadget disconnected from USB host
        atomic_set(&g_78xx_dev.connected, 0);   
    }
#ifdef _WARN_
#warning Need lock    
#endif
}

/**
 * Bind the USB function. This initializes all end points and assigns the 
 * fullspeed and high speed interface descriptors for the selected configuration
 * @param cfg_ptr
 * @param func_ptr
 * @return 0 for success, negative for failure
 */
static int usb_func_bind(struct usb_configuration *cfg,
                            struct usb_function *func)
{
	struct usb_composite_dev *cdev = cfg->cdev;
	int id;
    int i;
    int err = 0;
    struct ep_pipe *pipe;
    
    DBGPRINT(cdev, "[%s]\n", __func__);
    
    //Setup the interface number assigned to this configuration
	id = usb_interface_id(cfg, func);
    if (id < 0)
    {
        ERROR(cdev, "[%s] ERROR %d usb_interface_id\n", __func__, id);
        return (id);
    }
    g_intf_dscr.bInterfaceNumber = id;

    /* setup endpoints. Arrays g_fs_dscr and g_hs_dscr MUST have the correct
     * entries. Note that the 0th entry in the array is the interface descriptor
     */
    
    for (i=0; (i < g_78xx_dev.num_ep) && !err ; ++i)
    {
        pipe = g_78xx_dev.pipes[i];
        if (g_fs_dscr[i+1] && g_hs_dscr[i+1])
        {
            pipe->ep = usb_ep_autoconfig(cdev->gadget, 
                             (struct usb_endpoint_descriptor  *)g_fs_dscr[i+1]);
            if (!pipe->ep)
            {
                ERROR(cdev, "[%s] ERROR %s usb_ep_autoconfig\n", 
                                 __func__, pipe->ep->name);
                err = -ENODEV;
            }
        }
        else
        {
            ERROR(cdev, "[%s] ERROR Mismatch EP descriptor array %d\n",
                            __func__, i);
            err = -ENODEV;
        }
        
        if (!err)
        {
            pipe->ep->driver_data = pipe;	/* claim */
            ((struct usb_endpoint_descriptor  *)g_hs_dscr[i+1])->bEndpointAddress =
            ((struct usb_endpoint_descriptor  *)g_fs_dscr[i+1])->bEndpointAddress;
            DBG(cdev, "[%s] %s addr %02x\n", __func__, 
                            pipe->ep->name, pipe->ep->address);
        }
    }
    if (err)
    {
        ERROR(cdev, "[%s] ERROR %d config ep\n", __func__, err);
        return (err);
    }
    
    err = usb_assign_descriptors(func, g_fs_dscr, g_hs_dscr, NULL);
    if (err)
    {
        ERROR(cdev, "[%s] ERROR %d usb_assign_descriptors\n", __func__, err);
        return (err);
    }

	DBG(cdev, "[%s] %s max-speed %s\n", __func__, func->name,
	    (gadget_is_superspeed(cdev->gadget) ? "super" :
	     (gadget_is_dualspeed(cdev->gadget) ? "dual" : "full")) );
    
    return (0);
}
/*
 */
static void usb_cfg_unbind(struct usb_configuration *usbcfg_ptr)
{
#if 0
    struct usb_composite_dev *compdev_ptr = usbcfg_ptr->cdev;
    DBGPRINT(compdev_ptr, "[%s]\n", __func__);
#endif    
    //Remove Character Device/
	cdev_del(&g_78xx_dev.chardev);
}

/**
 * USB configuration bind
 * @param usbcfg_ptr : usb_configuration pointer
 * @return 0 on success, <0 on error 
 */
static int usb_cfg_bind(struct usb_configuration *usbcfg_ptr)
{
    struct usb_composite_dev *cdev = usbcfg_ptr->cdev;
	struct usb_gadget	*gadget = cdev->gadget;
	int	err = 0;
    g_78xx_dev.gadget = gadget;
	
    DBGPRINT(cdev, "[%s]\n", __func__);
    
	usb_ep_autoconfig_reset(gadget);
    
    /* init and add the USB function callbasks. This function returns the value
     *  of the function's bind(), which is zero for success else a negative
     *  errno value. */
    err = usb_add_function(usbcfg_ptr, &g_78xx_dev.function);
	if (err)
    {
        ERROR(cdev, "[%s] ERROR %d usb_add_function\n", __func__, err);
		return err;
    }
    
    //Register a character device for each USB endpoint
    cdev_init(&g_78xx_dev.chardev, &g_ep_file_ops);
    g_78xx_dev.chardev.owner = THIS_MODULE;
    err = cdev_add(&g_78xx_dev.chardev, g_78xx_dev.devno, g_78xx_dev.num_ep);
	if (err) 
    {
        ERROR(cdev, "[%s] ERROR %d cdev_adde\n", __func__, err);
		return err;
	}

    if (err)
    {
        usb_cfg_unbind(usbcfg_ptr);
        return (err);
    }
    
    usb_gadget_set_selfpowered(gadget);
    return (err);
}
static struct ep_pipe **alloc_pipes(int in, int out)
{
    int i, total, len1, len2;
    struct ep_pipe ** ret;
    struct ep_pipe *pipe;
    total = in + out;
    
    //length of array of pointers to struct ep_pipe
    len1 = sizeof(struct ep_pipe *) * total;
    //length of total number of struct ep_pipe
    len2 = sizeof(struct ep_pipe) * total;
    
    ret = (struct ep_pipe**)kzalloc(len1 + len2, GFP_KERNEL);
	if (unlikely(!ret)) 
    {
       return (NULL);
    }   
    pipe = (struct ep_pipe *)((void *)ret + len1);
    for (i=0; i < total; ++i, ++pipe)
    {
        //init array element to point to ep_pipe
        ret[i] = pipe;
        //init the ep_pipe struct
        atomic_set(&pipe->opened, 0);
        pipe->dt_dev = &g_78xx_dev;
        init_completion(&pipe->io_done);
        spin_lock_init(&pipe->pipe_lock);
    }
    return (ret);
}
/**
 * Allocate array of usb_endpoint_descriptor and initialize each element with
 * a pointer to an allocated usb_endpoint_descriptor
 * @param in    : #of input endpoints
 * @param out   : #of output endpoints
 * @param hs    : 1 for high speed, 0 for full speed
 * @return      : On error NULL, non-NULL is pointer that must be kfree'd
 */
static struct usb_descriptor_header **alloc_descriptors(int in, int out, int hs)
{
    int desc_len, array_len, i, total;
    struct usb_endpoint_descriptor *ep_desc;
    struct usb_descriptor_header ** ret;
    total = in + out;
    //allocate endpoint descriptors for total# of endpoints
    desc_len = sizeof(struct usb_endpoint_descriptor)*total;
    /* add space for array of pointers to descriptors. The 0th entry in the
     * array points to the Interface Descriptor and the last entry is a
     * NULL terminator. Hence the +2 below
     */
    array_len = sizeof(struct usb_descriptor_header *)*(total+2);
    
    ret = (struct usb_descriptor_header **)kzalloc(array_len + desc_len, 
                                                   GFP_KERNEL);
	if (unlikely(!ret)) 
    {
       return (NULL);
    }
    
    ep_desc = (struct usb_endpoint_descriptor *)((void *)ret + array_len);
    ret[0] = (struct usb_descriptor_header *)&g_intf_dscr; //I/f descriptor at index 0
    for (i=total; i!=0; --i, ++ep_desc)
    {
        //init array element to point to usb_endpoint_descriptor
        ret[i] = (struct usb_descriptor_header *)ep_desc;
        //init corresponding usb_endpoint_descriptor
        ep_desc->bLength        = USB_DT_ENDPOINT_SIZE;
        ep_desc->bDescriptorType= USB_DT_ENDPOINT;
        ep_desc->bmAttributes   = USB_ENDPOINT_XFER_BULK;
        if (hs)
        {
            ep_desc->wMaxPacketSize = cpu_to_le16(512);
        }
        if (i > g_78xx_dev.num_ep_out)
        {
            ep_desc->bEndpointAddress =	USB_DIR_OUT;
        }
        else
        {
            ep_desc->bEndpointAddress =	USB_DIR_IN;
        }
    }
    return (ret);
}

static int __init gadget_bind(struct usb_composite_dev *cdev)
{
	int	err = 0;
    
    DBGPRINT(cdev, "[%s]\n", __func__);
   
    //overwrite descriptor values with values in coverwrite that are non-zero
	usb_composite_overwrite_options(cdev, &coverwrite);
    
    /*Non-zero values in coverwrite are overwritten with default values for
     visibility */
    if (!coverwrite.idVendor)
    {
        coverwrite.idVendor = DEFAULT_VENDOR_ID;
    }
    else
    {
        g_dev_dscr.idVendor = cdev->desc.idVendor;
    }
    if (!coverwrite.idProduct)
    {
        coverwrite.idProduct = DEFAULT_PRODUCT_ID;
    }
    else
    {
        g_dev_dscr.idProduct = cdev->desc.idProduct;
    }
    if (!coverwrite.bcdDevice)
    {
        coverwrite.bcdDevice = DEFAULT_DEVICE_ID;
    }
    else
    {
        g_dev_dscr.bcdDevice = cdev->desc.bcdDevice;
    }
    if (!coverwrite.serial_number) 
    {
		coverwrite.serial_number = g_serial; 
    }
    else
    {
        g_dev_dscr.iSerialNumber = cdev->desc.iSerialNumber;
        g_strings_dev[USB_GADGET_SERIAL_IDX].s = coverwrite.serial_number;
    }
    if (!coverwrite.manufacturer) 
    {
		coverwrite.manufacturer = DEFAULT_MANUFACTURER; 
    }
    else
    {
        g_dev_dscr.iManufacturer = cdev->desc.iManufacturer;
        g_strings_dev[USB_GADGET_MANUFACTURER_IDX].s = coverwrite.serial_number;
    }
    if (!coverwrite.product) 
    {
		coverwrite.product = DEFAULT_PRODUCT_NAME; 
    }
    else
    {
        g_dev_dscr.iProduct = cdev->desc.iProduct;
        g_strings_dev[USB_GADGET_PRODUCT_IDX].s = coverwrite.product;
    }
    
    //initialize the total #of endpoints
    g_78xx_dev.num_ep = g_78xx_dev.num_ep_out + g_78xx_dev.num_ep_in;
    g_intf_dscr.bNumEndpoints = g_78xx_dev.num_ep;
    
    //allocate array of high speed ep descriptors and its constituent elements
    g_hs_dscr = alloc_descriptors(g_78xx_dev.num_ep_out, 
                                  g_78xx_dev.num_ep_in, 
                                  1);
    if (!g_hs_dscr)
    {
        ERROR(cdev, "[%s] alloc g_hs_dscr\n", __func__);
        return (-ENOMEM);
    }
    
    //allocate array of full speed ep descriptors and its constituent elements
    g_fs_dscr = alloc_descriptors(g_78xx_dev.num_ep_out, 
                                  g_78xx_dev.num_ep_in, 
                                  0);
    if (!g_fs_dscr)
    {
        kfree(g_hs_dscr);
        g_hs_dscr = NULL;
        ERROR(cdev, "[%s] alloc g_fs_dscr\n", __func__);
        return (-ENOMEM);
    }
    
    //allocate pipes for each end point
    g_78xx_dev.pipes = alloc_pipes(g_78xx_dev.num_ep_out, g_78xx_dev.num_ep_in);
    if (!g_78xx_dev.pipes)
    {
        kfree(g_hs_dscr);
        g_hs_dscr = NULL;
        kfree(g_fs_dscr);
        g_fs_dscr = NULL;
        ERROR(cdev, "[%s] alloc pipes\n", __func__);
        return (-ENOMEM);
    }
	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */
	err = usb_string_ids_tab(cdev, g_strings_dev);
	if (err < 0)
    {
        ERROR(cdev, "[%s] ERROR %d usb_string_ids_tab\n", __func__, err);
		return err;
    }

	g_dev_dscr.iManufacturer = g_strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	g_dev_dscr.iProduct = g_strings_dev[USB_GADGET_PRODUCT_IDX].id;
	g_dev_dscr.iSerialNumber = g_strings_dev[USB_GADGET_SERIAL_IDX].id;
    
    //This function returns the value of the configuration's bind()
    err = usb_add_config(cdev, &g_usb_config, usb_cfg_bind);
	if (err < 0)
    {
        ERROR(cdev, "[%s] ERROR %d usb_add_config\n", __func__, err);
		return err;
    }
 	DBGPRINT(cdev, "[%s] OK\n", __func__);

	return 0;
}

static int gadget_unbind(struct usb_composite_dev *cdev)
{
	DBGPRINT(cdev, "[%s]\n", __func__);
    
    //system_wq is the one used by schedule_work().
    flush_workqueue(system_wq);
    
    if (g_78xx_dev.pipes)
    {
        kfree(g_78xx_dev.pipes);
    }
    if (g_hs_dscr)
    {
        kfree(g_hs_dscr);
    }
    if (g_fs_dscr)
    {
        kfree(g_fs_dscr);
    }
	return 0;
}

static int __init gadget_init(void)
{
    __label__ LBL1, LBL2, LBL3;
	int status;
    
    atomic_set(&g_78xx_dev.connected, 0);
    spin_lock_init(&g_78xx_dev.dev_lock);
    
    //Create a device class to be associated with EP files
	g_78xx_dev.gadget_class = class_create(THIS_MODULE, GADGET_CLASS);
	if (IS_ERR(g_78xx_dev.gadget_class)) 
    {
		status = PTR_ERR(g_78xx_dev.gadget_class);
		pr_err("[%s] ERROR %d class_create\n", __func__, status);
		goto LBL1;
	}	

    //Register a range of char device numbers for the number of endpoints
	status = alloc_chrdev_region(&g_78xx_dev.devno, 0, g_78xx_dev.num_ep,
                                 "DT78xx_usb_pipe");
	if (status) 
    {
		pr_err("[%s] ERROR  %d alloc_chrdev_region\n", __func__, status);
		goto LBL2;
	}
    
    status = usb_composite_probe(&g_composite_driver);
	if (status) 
    {
		pr_err("[%s] ERROR  %d usb_composite_probe\n", __func__, status);
		goto LBL3;
	}
    INFO(&g_78xx_dev, "[%s] version %s\n", __func__, VERSION_STR);
    return (status);
    
LBL3:
    unregister_chrdev_region(g_78xx_dev.devno, g_78xx_dev.num_ep);         
LBL2:
    class_destroy(g_78xx_dev.gadget_class);         
LBL1:
    return (status);
}
module_init(gadget_init);

static void __exit gadget_exit(void)
{
	usb_composite_unregister(&g_composite_driver);
    unregister_chrdev_region(g_78xx_dev.devno, g_78xx_dev.num_ep);         
    class_destroy(g_78xx_dev.gadget_class);         
}
module_exit(gadget_exit);


MODULE_AUTHOR("Data Translation Inc.");
MODULE_DESCRIPTION ("DT78xx USB gadget driver");
MODULE_LICENSE("GPL");

MODULE_VERSION (VERSION_STR);


