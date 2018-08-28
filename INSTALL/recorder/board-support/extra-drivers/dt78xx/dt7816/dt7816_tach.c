/*
 * Kerenel Load Module for Data Translation DT7816 data acquisition module.
 * 
 * This file implements the tachometer subsystem file operations supported
 *  by the /dev/dt7816 device
 *
 *  (C) Copyright (c) 2015 Data Translation Inc
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
#include "dt78xx_ioctl.h"
#include "dt7816.h"
#include "dt7816_fpga.h"

/**************************************************************************
 * Macros
 */

/**************************************************************************
 * Functions
 */
static int _fopen(struct inode *, struct file *);
static int _fclose(struct inode *, struct file *);
static long _ioctl_cb(struct file *, unsigned int , unsigned long );

/**************************************************************************
 * Data structures
 */
struct dt7816_tach
{
    char    filename[32]; //name of file under /dev
    struct dt78xx_device *dt_dev;
};

/**************************************************************************
 * Globals
 */

//File operations supported by DT7816 dout subsystem
static const struct file_operations _file_ops = 
{
    .owner          = THIS_MODULE,
    .open           = _fopen,
    .release        = _fclose,
    .unlocked_ioctl = _ioctl_cb,
};

/*****************************************************************************
 * Handler for open() call in user application made on device file
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_tach *subsys;
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
 * Handler for close() call in user application made on device file
 */
static int _fclose(struct inode *inode, struct file *file)
{
    //close the underlying daq_subsystem
    dt78xx_fclose(file);
    return (0);
}

/****************************************************************************
 * Handler for ioctl IOCTL_TACH_CFG_GET
 * Params
 * arg : Pointer to dt78xx_tach_config_t
 * len : length of buffer pointed by arg
 */
static int _tach_cfg_get(struct dt7816_tach *tach, void __user *arg, size_t len)
{
    uint16_t regval;
    dt78xx_tach_config_t cfg;
    struct device *dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    memset(&cfg, 0, sizeof(cfg));
    dev = &tach->dt_dev->pdev->dev;

    regval = dt78xx_fpga_read(dev,FPGA_REG_TACH_CTR_CTRL);
    cfg.edge_rising = (regval & MASK_TACH_CTR_CTRL_EDGE_SEL) >> SHIFT_TACH_CTR_CTRL_EDGE_SEL;
    cfg.stale_flag = (regval & MASK_TACH_CTR_CTRL_STALE) >> SHIFT_TACH_CTR_CTRL_STALE;
    
    if (copy_to_user(arg, (void *)&cfg, sizeof(cfg))) 
        return (-EFAULT);

    return 0;
}

/****************************************************************************
 * Handler for ioctl IOCTL_TACH_CFG_SET
 * Params
 * arg : Pointer to dt78xx_tach_config_t
 * len : length of buffer pointed by arg
 */
static int _tach_cfg_set(struct dt7816_tach *tach, void __user *arg, size_t len)
{
    uint16_t ctrl;
    dt78xx_tach_config_t cfg;
    struct device *dev;

    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user((void *)&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    dev = &tach->dt_dev->pdev->dev;
    
    ctrl  = (cfg.stale_flag << SHIFT_TACH_CTR_CTRL_STALE) & MASK_TACH_CTR_CTRL_STALE;
    ctrl |= (cfg.edge_rising << SHIFT_TACH_CTR_CTRL_EDGE_SEL) & MASK_TACH_CTR_CTRL_EDGE_SEL;
    dt78xx_fpga_write(dev, FPGA_REG_TACH_CTR_CTRL, ctrl);
    
    return 0;
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7816_tach *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    int len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7816_tach *)file_to_subsys(file);
    if (unlikely(!subsys))
        return -ENODEV;
    
    dev_lock(dt_dev);
    
    switch (cmd)
    {
        case IOCTL_TACH_CFG_GET:
            retval = _tach_cfg_get(subsys, (void __user *)arg, len);
            break;

        case IOCTL_TACH_CFG_SET:
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _tach_cfg_set(subsys, (void __user *)arg, len);
            break;

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
 * Create the board specific tachometer subsystem and register a file handle
 */
int dt7816_tach_subsystem_create(struct daq_subsystem *daq)
{
    int err;
    struct dt7816_tach *subsys;
    struct device *dev = &daq->dt_dev->pdev->dev;

    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7816_tach), GFP_KERNEL);
    if (!subsys)
    {
        return -ENOMEM;
    }
    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    subsys->dt_dev = daq->dt_dev;
    err = misc_register(&daq->miscdev);
    if (!err)
        err = dev_set_drvdata(daq->miscdev.this_device, subsys);
    if (err)
    {
        daq->miscdev.name = NULL;
        devm_kfree(dev, subsys);
    }
    return (err);
}
