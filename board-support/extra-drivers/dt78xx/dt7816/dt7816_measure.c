/*
 * Kerenel Load Module for Data Translation DT7816 data acquisition module.
 * 
 * This file implements the measure counter subsystem file operations supported
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
struct dt7816_mctr
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
    struct dt7816_mctr *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
     
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
 * Handler for ioctl IOCTL_MCTR_CFG_GET
 * Params
 * arg : Pointer to dt78xx_mctr_config_t
 * len : length of buffer pointed by arg
 */
static int _mctr_cfg_get(struct dt7816_mctr *mctr, void __user *arg, size_t len)
{
    uint16_t regval, din;
    dt78xx_mctr_config_t cfg;
    struct device *dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    memset(&cfg, 0, sizeof(cfg));
    dev = &mctr->dt_dev->pdev->dev;
    regval = dt78xx_fpga_read(dev,FPGA_REG_MSR_CTR_CTRL);
    //start edge
    cfg.start_sel = (regval & MASK_MSR_CTR_CTRL_START_SEL) >> SHIFT_MSR_CTR_CTRL_START_SEL;
    if (cfg.start_sel == MSR_CTR_CTRL_TACH_F)
        cfg.start_sel = mctr_sel_tach_falling;
    else if (cfg.start_sel == MSR_CTR_CTRL_TACH_R)
        cfg.start_sel = mctr_sel_tach_rising;
    else if (cfg.start_sel == MSR_CTR_CTRL_ADC_DONE)
        cfg.start_sel = mctr_sel_adc_complete;
    else //DIN rising or falling
    {
        din = dt78xx_fpga_read(dev,FPGA_REG_DIN_GPIO3) & MASK_DIN_GPIO3_MSR_CTR_EDGE1;
        din >>= SHIFT_DIN_GPIO3_MSR_CTR_EDGE1; //din is 0-7
        if (cfg.start_sel == MSR_CTR_CTRL_DIN_R)
        { //don't rely on bit patterns in mctr_sel_t that could be redefined
            cfg.start_sel = (din==7)?mctr_sel_din7_rising:
                            (din==6)?mctr_sel_din6_rising:
                            (din==5)?mctr_sel_din5_rising:
                            (din==4)?mctr_sel_din4_rising:
                            (din==3)?mctr_sel_din3_rising:
                            (din==2)?mctr_sel_din2_rising:
                            (din==1)?mctr_sel_din1_rising:mctr_sel_din0_rising;
        }
        else
        {
            cfg.start_sel = (din==7)?mctr_sel_din7_falling:
                            (din==6)?mctr_sel_din6_falling:
                            (din==5)?mctr_sel_din5_falling:
                            (din==4)?mctr_sel_din4_falling:
                            (din==3)?mctr_sel_din3_falling:
                            (din==2)?mctr_sel_din2_falling:
                            (din==1)?mctr_sel_din1_falling:mctr_sel_din0_falling;
            
        }
    }
    //stop edge
    cfg.stop_sel = (regval & MASK_MSR_CTR_CTRL_STOP_SEL) >> SHIFT_MSR_CTR_CTRL_STOP_SEL;
    if (cfg.stop_sel == MSR_CTR_CTRL_TACH_F)
        cfg.stop_sel = mctr_sel_tach_falling;
    else if (cfg.stop_sel == MSR_CTR_CTRL_TACH_R)
        cfg.stop_sel = mctr_sel_tach_rising;
    else if (cfg.stop_sel == MSR_CTR_CTRL_ADC_DONE)
        cfg.stop_sel = mctr_sel_adc_complete;
    else //DIN rising or falling
    {
        din = dt78xx_fpga_read(dev,FPGA_REG_DIN_GPIO3) & MASK_DIN_GPIO3_MSR_CTR_EDGE2;
        din >>= SHIFT_DIN_GPIO3_MSR_CTR_EDGE2; //din is 0-7
        if (cfg.stop_sel == MSR_CTR_CTRL_DIN_R)
        {
            cfg.stop_sel =  (din==7)?mctr_sel_din7_rising:
                            (din==6)?mctr_sel_din6_rising:
                            (din==5)?mctr_sel_din5_rising:
                            (din==4)?mctr_sel_din4_rising:
                            (din==3)?mctr_sel_din3_rising:
                            (din==2)?mctr_sel_din2_rising:
                            (din==1)?mctr_sel_din1_rising:mctr_sel_din0_rising;
        }
        else
        {
            cfg.stop_sel =  (din==7)?mctr_sel_din7_falling:
                            (din==6)?mctr_sel_din6_falling:
                            (din==5)?mctr_sel_din5_falling:
                            (din==4)?mctr_sel_din4_falling:
                            (din==3)?mctr_sel_din3_falling:
                            (din==2)?mctr_sel_din2_falling:
                            (din==1)?mctr_sel_din1_falling:mctr_sel_din0_falling;
        }
    }
    if (regval & MASK_MSR_CTR_CTRL_STALE)
        cfg.stale_flag = 1;
    if (copy_to_user(arg, (void *)&cfg, sizeof(cfg))) 
        return (-EFAULT);
    return 0;
}

/****************************************************************************
 * Handler for ioctl IOCTL_MCTR_CFG_SET
 * Params
 * arg : Pointer to dt78xx_mctr_config_t
 * len : length of buffer pointed by arg
 */
static int _mctr_cfg_set(struct dt7816_mctr *mctr, void __user *arg, size_t len)
{
    uint16_t ctrl=0, start=0, stop=0;
    dt78xx_mctr_config_t cfg;
    struct device *dev;

    if (len < sizeof(cfg))
        return (-EINVAL);

    if (copy_from_user((void *)&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    //validate start edge
    if ((cfg.start_sel < mctr_sel_adc_complete) ||
        ((cfg.start_sel > mctr_sel_adc_complete) && (cfg.start_sel < mctr_sel_tach_falling)) ||
        ((cfg.start_sel > mctr_sel_tach_rising) && (cfg.start_sel < mctr_sel_din0_falling)) ||
        (cfg.start_sel > mctr_sel_din7_rising))
        return (-EINVAL);
    //validate stop edge
    if ((cfg.stop_sel < mctr_sel_adc_complete) ||
        ((cfg.stop_sel > mctr_sel_adc_complete) && (cfg.stop_sel < mctr_sel_tach_falling)) ||
        ((cfg.stop_sel > mctr_sel_tach_rising) && (cfg.stop_sel < mctr_sel_din0_falling)) ||
        (cfg.stop_sel > mctr_sel_din7_rising))
        return (-EINVAL);

    // The stale flag only works when the start and stop edges are identical. 
    if ((cfg.stale_flag != 0) && (cfg.start_sel != cfg.stop_sel))
        return (-EINVAL);
    //stale flag
    if (cfg.stale_flag != 0) 
        ctrl |= MASK_MSR_CTR_CTRL_STALE;
    //start edge
    if (cfg.start_sel == mctr_sel_tach_falling)
        ctrl |= (MSR_CTR_CTRL_TACH_F << SHIFT_MSR_CTR_CTRL_START_SEL);
    else if (cfg.start_sel == mctr_sel_tach_rising)
        ctrl |= (MSR_CTR_CTRL_TACH_R << SHIFT_MSR_CTR_CTRL_START_SEL);
    else if (cfg.start_sel == mctr_sel_adc_complete)
        ctrl |= (MSR_CTR_CTRL_ADC_DONE << SHIFT_MSR_CTR_CTRL_START_SEL);
    else 
    {
        if ((cfg.start_sel==mctr_sel_din7_rising) ||
            (cfg.start_sel==mctr_sel_din6_rising) ||
            (cfg.start_sel==mctr_sel_din5_rising) ||
            (cfg.start_sel==mctr_sel_din4_rising) ||
            (cfg.start_sel==mctr_sel_din3_rising) ||
            (cfg.start_sel==mctr_sel_din2_rising) ||
            (cfg.start_sel==mctr_sel_din1_rising) ||
            (cfg.start_sel==mctr_sel_din0_rising) )
        {
            ctrl |= (MSR_CTR_CTRL_DIN_R << SHIFT_MSR_CTR_CTRL_START_SEL);
        }
        else
        {
            ctrl |= (MSR_CTR_CTRL_DIN_F << SHIFT_MSR_CTR_CTRL_START_SEL);
        }
        start = ((cfg.start_sel==mctr_sel_din7_rising)||
                 (cfg.start_sel==mctr_sel_din7_falling))? 7:
                ((cfg.start_sel==mctr_sel_din6_rising)||
                 (cfg.start_sel==mctr_sel_din6_falling))? 6:                     
                ((cfg.start_sel==mctr_sel_din5_rising)||
                 (cfg.start_sel==mctr_sel_din5_falling))? 5:                     
                ((cfg.start_sel==mctr_sel_din4_rising)||
                 (cfg.start_sel==mctr_sel_din4_falling))? 4:                     
                ((cfg.start_sel==mctr_sel_din3_rising)||
                 (cfg.start_sel==mctr_sel_din3_falling))? 3:                     
                ((cfg.start_sel==mctr_sel_din2_rising)||
                 (cfg.start_sel==mctr_sel_din2_falling))? 2:                     
                ((cfg.start_sel==mctr_sel_din1_rising)||
                 (cfg.start_sel==mctr_sel_din1_falling))? 1:0;
        start <<= SHIFT_DIN_GPIO3_MSR_CTR_EDGE1;
        start |= MASK_DIN_GPIO3_MSR_CTR_EDGE1_EN;
    }
    //stop edge
    if (cfg.stop_sel == mctr_sel_tach_falling)
        ctrl |= (MSR_CTR_CTRL_TACH_F << SHIFT_MSR_CTR_CTRL_STOP_SEL);
    else if (cfg.stop_sel == mctr_sel_tach_rising)
        ctrl |= (MSR_CTR_CTRL_TACH_R << SHIFT_MSR_CTR_CTRL_STOP_SEL);
    else if (cfg.stop_sel == mctr_sel_adc_complete)
        ctrl |= (MSR_CTR_CTRL_ADC_DONE << SHIFT_MSR_CTR_CTRL_STOP_SEL);
    else 
    {
        if ((cfg.stop_sel==mctr_sel_din7_rising) ||
            (cfg.stop_sel==mctr_sel_din6_rising) ||
            (cfg.stop_sel==mctr_sel_din5_rising) ||
            (cfg.stop_sel==mctr_sel_din4_rising) ||
            (cfg.stop_sel==mctr_sel_din3_rising) ||
            (cfg.stop_sel==mctr_sel_din2_rising) ||
            (cfg.stop_sel==mctr_sel_din1_rising) ||
            (cfg.stop_sel==mctr_sel_din0_rising) )
        {
            ctrl |= (MSR_CTR_CTRL_DIN_R << SHIFT_MSR_CTR_CTRL_STOP_SEL);
        }
        else
        {
            ctrl |= (MSR_CTR_CTRL_DIN_F << SHIFT_MSR_CTR_CTRL_STOP_SEL);
        }
        stop = ((cfg.stop_sel==mctr_sel_din7_rising)||
                 (cfg.stop_sel==mctr_sel_din7_falling))? 7:
                ((cfg.stop_sel==mctr_sel_din6_rising)||
                 (cfg.stop_sel==mctr_sel_din6_falling))? 6:                     
                ((cfg.stop_sel==mctr_sel_din5_rising)||
                 (cfg.stop_sel==mctr_sel_din5_falling))? 5:                     
                ((cfg.stop_sel==mctr_sel_din4_rising)||
                 (cfg.stop_sel==mctr_sel_din4_falling))? 4:                     
                ((cfg.stop_sel==mctr_sel_din3_rising)||
                 (cfg.stop_sel==mctr_sel_din3_falling))? 3:                     
                ((cfg.stop_sel==mctr_sel_din2_rising)||
                 (cfg.stop_sel==mctr_sel_din2_falling))? 2:                     
                ((cfg.stop_sel==mctr_sel_din1_rising)||
                 (cfg.stop_sel==mctr_sel_din1_falling))? 1:0;
        stop <<= SHIFT_DIN_GPIO3_MSR_CTR_EDGE2;
        stop |= MASK_DIN_GPIO3_MSR_CTR_EDGE2_EN;
    }
    //write the control reg
    dev = &mctr->dt_dev->pdev->dev;
    dt78xx_fpga_write(dev, FPGA_REG_MSR_CTR_CTRL, ctrl);
    //configure external start/stop edge if either is enabled
    dt78xx_fpga_rmw(dev, FPGA_REG_DIN_GPIO3, 
                        (MASK_DIN_GPIO3_MSR_CTR_EDGE1_EN |
                        MASK_DIN_GPIO3_MSR_CTR_EDGE1 |
                        MASK_DIN_GPIO3_MSR_CTR_EDGE2_EN |
                        MASK_DIN_GPIO3_MSR_CTR_EDGE2),
                        start|stop);
   
    return 0;
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7816_mctr *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    int len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7816_mctr *)file_to_subsys(file);
    if (unlikely(!subsys))
        return -ENODEV;
    
    dev_lock(dt_dev);
    
    switch (cmd)
    {
        case IOCTL_MCTR_CFG_GET:
            retval = _mctr_cfg_get(subsys, (void __user *)arg, len);
            break;

        case IOCTL_MCTR_CFG_SET:
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _mctr_cfg_set(subsys, (void __user *)arg, len);
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
 * Create the board specific measure counter subsystem and register a file handle
 */
int dt7816_measure_subsystem_create(struct daq_subsystem *daq)
{
    int err;
    struct dt7816_mctr *subsys;
    struct device *dev = &daq->dt_dev->pdev->dev;

    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7816_mctr), GFP_KERNEL);
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
