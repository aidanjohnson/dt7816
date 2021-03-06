/*
 * Kerenel Load Module for Data Translation DT7816 data acquisition module.
 * This file implements the digital output subsystem file operations supported
 *  by the module
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
 *
 */
#include <linux/slab.h>
#include <linux/uaccess.h>

#include "dt78xx.h"
#include "dt7816.h"
#include "dt7816_fpga.h"

/**************************************************************************
 * Macros
 */

/**************************************************************************
 * Functions
 */
static int _fopen(struct inode *inode, struct file *file);
static int _fclose(struct inode *inode, struct file *file);
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t _fwrite (struct file *, const char __user *, size_t, loff_t *);
static ssize_t _fread (struct file *, char __user *, size_t, loff_t *);

/**************************************************************************
 * Data structures
 */
struct dt7816_dout
{
    char    filename[32]; //name of file under /dev
                          //Add other stuff required by the subsystem
};

/**************************************************************************
 * File operations supported by DT7816 dout subsystem
 */
static const struct file_operations _file_ops = 
{
    .owner          = THIS_MODULE,
    .open           = _fopen,
    .release        = _fclose,
    .unlocked_ioctl = _ioctl_cb,
    .write          = _fwrite,
    .read           = _fread,
};

/**************************************************************************
 * Globals
 */
    
/*****************************************************************************
 * Handler for open() call in user application made on virtual file
 * /dev/dt7816-dout
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_dout *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = file_to_subsys(file);
     
    //try to open the underlying daq_subsystem
    err = dt78xx_fopen(file);
    if (err)
    {
        dev_err(&dt_dev->pdev->dev, "[%s] ERROR %s already open\n",
                                  __func__, subsys->filename);
        return (-EBUSY);
    }
    return (0);
}

/*****************************************************************************
 * Handler for close() call in user application made on virtual file
 * /dev/dt7816-dout
 */
static int _fclose(struct inode *inode, struct file *file)
{
    //close the underlying daq_subsystem
    dt78xx_fclose(file);
    return (0);
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7816_dout *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    size_t len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7816_dout *)file_to_subsys(file);
    if (unlikely(!subsys))
        return -ENODEV;
    
    dev_lock(dt_dev);
    switch (cmd)
    {
        case IOCTL_LED_GET :
            retval = dt7816_ioctl_led_get(dev, (void __user *)arg, len);
            break;

        case IOCTL_LED_SET :
            retval = dt7816_ioctl_led_set(dev, (void __user *)arg, len);
            break;
            
        default :
            dev_err(dev, "%s IOCTL ERROR cmd=0x%x (nr=%d len=%d dir=%d)",
                     subsys->filename, cmd, _IOC_NR(cmd), len, _IOC_DIR(cmd));
            retval = -EBADRQC;   /*56 Invalid request code */
    }
    dev_unlock(dt_dev);
    return retval;
}

/*****************************************************************************
 * Synchronous write from user application made on virtual file
 * /dev/dt7816-dout
 */
static ssize_t _fwrite (struct file *file, const char __user *buff, size_t len, 
                       loff_t *off)
{
    u16 dout;
    ssize_t ret;
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    
    //Error, if the digital outputs are being driven by the output stream
    if (dt78xx_fpga_read(dev, FPGA_REG_DOUT) & MASK_DOUT_SRC)
        return (-EIO);
    //read one byte from user
    if ((ret=copy_from_user((u8 *)&dout, buff, sizeof(u8))) != 0)
        return (ret);
    
    dout &= MASK_DOUT; //Bit 8 must be 0
    dev_lock(dt_dev);
    dt78xx_fpga_write(dev, FPGA_REG_DOUT, dout);
    dev_unlock(dt_dev);
    return (sizeof(dout));
}

/*****************************************************************************
 * Synchronous read from user application 
 */
static ssize_t _fread (struct file *file, char __user *buff, size_t len, 
                       loff_t *off)
{
    u16 dout;
    ssize_t ret;
  
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    
    if (len < sizeof(u8)) //need to return 1 byte
        return -EINVAL;
    
    dev_lock(dt_dev);
    dout = dt78xx_fpga_read(dev, FPGA_REG_DOUT);
    dev_unlock(dt_dev);
    ret = copy_to_user(buff, (u8 *)&dout, sizeof(u8));
    return ret?ret:sizeof(u8);
}


/*****************************************************************************
 * Create the board specific dout subsystem and register a file handle
 */
int dt7816_dout_subsystem_create(struct daq_subsystem *daq)
{
    int err;
    struct dt7816_dout *subsys;
    struct device *dev = &daq->dt_dev->pdev->dev;

    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7816_dout), GFP_KERNEL);
    if (!subsys)
    {
        return -ENOMEM;
    }
    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    err = misc_register(&daq->miscdev);
    if (!err)
    {
        err = dev_set_drvdata(daq->miscdev.this_device, subsys);
    }
    if (err)
    {
        daq->miscdev.name = NULL;
        devm_kfree(dev, subsys);
    }
    return (err);
}
