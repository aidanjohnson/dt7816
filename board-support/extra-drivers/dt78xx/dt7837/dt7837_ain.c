/*
 * Kerenel Load Module for Data Translation DT7837 data acquisition module.
 * 
 * This file implements the subsystem file operations supported by the
 * /dev/dt7837_ain virtual file
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
#include <linux/sched.h>
#include <asm/uaccess.h>    //copy_to_user())

#include "dt78xx.h"
#include "dt7837.h"
#include "dt7837_fpga.h"

/**************************************************************************
 * Macros
 */
#define AIN_MIN     (0)
#define AIN_MAX     (NUM_AIN-1)
#define GAIN_10     (10)
#define GAIN_1      (1)

/**************************************************************************
 * Data structures
 */

//Data structure specific to the DT7837 analog input subsystem. 
struct dt7837_ain
{
    char    filename[32]; //name of file under /dev
    struct dt78xx_device *dt_dev;
    struct dt7837_pot *offset_pot;
    struct dt7837_pot *gain_pot;
};

/**************************************************************************
 * Functions
 */
static int _fopen(struct inode *inode, struct file *file);
static int _fclose(struct inode *inode, struct file *file);
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg);
static int _ad_cal_change(struct dt7837_ain *subsys);

/**************************************************************************
 * Globals
 */

/*
 * File operations supported by DT7837 ain subsystem
 */
static const struct file_operations _file_ops = 
{
    .owner          = THIS_MODULE,
    .open           = _fopen,
    .release        = _fclose,
    .unlocked_ioctl = _ioctl_cb,
};
    
/*****************************************************************************
 * Handler for open() call in user application made on virtual file
 * /dev/dt7837-ain
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7837_ain *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7837_ain *)file_to_subsys(file);
    if (!subsys)
    {
        return -ENODEV;
    }
     
    //try to open the underlying daq_subsystem
    err = dt78xx_fopen(file);
    if (err)
    {
        dev_err(&dt_dev->pdev->dev, "[%s] ERROR %s already open\n",
                                  __func__, subsys->filename);
        return (-EBUSY);
    }
#if 0    
    dev_dbg(&dt_dev->pdev->dev, "[%s] %s f_flags %x\n",
                                __func__, subsys->filename, file->f_flags);
#endif    
    return (0);
}

/*****************************************************************************
 * Handler for close() call in user application made on virtual file
 * /dev/dt7837-ain
 */
static int _fclose(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7837_ain *subsys;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7837_ain *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
     
    //close the underlying daq_subsystem
    dt78xx_fclose(file);
#if 0    
    dev_dbg(&dt_dev->pdev->dev, "[%s] %s", __func__, subsys->filename);
#endif
    return (0);
}

/*****************************************************************************
 * Handler for ioctl IOCTL_AIN_CFG_GET
 * Params
 *  arg : Pointer to dt78xx_ain_config_t with member ain initialized
 * len : length of buffer pointed by arg
 */
static int _ain_cfg_get(struct dt7837_ain *ainsys, void __user *arg, size_t len)
{
    u16 regval, mask;
    dt78xx_ain_config_t cfg;
    struct device *dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user(&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    if ((cfg.ain < AIN_MIN) || (cfg.ain > AIN_MAX))
        return (-EINVAL);
    
    mask = (1<<cfg.ain);
    dev = &ainsys->dt_dev->pdev->dev;
    regval = dt78xx_fpga_read(dev, FPGA_REG_IN_SETUP0);
    cfg.ac_coupling = !!(regval & mask);
    
    regval = dt78xx_fpga_read(dev, FPGA_REG_IN_SETUP1);
    cfg.gain = (regval & mask)?GAIN_10:GAIN_1;
    
    regval = dt78xx_fpga_read(dev, FPGA_REG_IN_SETUP2);
    cfg.current_on = !!(regval & mask);
    
    if (copy_to_user(arg, (void *)&cfg, sizeof(cfg))) 
        return (-EFAULT);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_AIN_CFG_SET
 * Params
 *  arg : Pointer to dt78xx_ain_config_t with all members initialized
 * len : length of buffer pointed by arg
 */
static int _ain_cfg_set(struct dt7837_ain *ainsys, void __user *arg, size_t len)
{
    u16 mask;
    dt78xx_ain_config_t cfg;
    struct device *dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user(&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    if ((cfg.ain < AIN_MIN) || (cfg.ain > AIN_MAX))
        return (-EINVAL);
    if ((cfg.gain != GAIN_1) && (cfg.gain != GAIN_10))
        return (-EINVAL);
    
    mask = (1<<cfg.ain);
    dev = &ainsys->dt_dev->pdev->dev;
    if (cfg.ac_coupling)
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_SETUP0, mask, mask);
    else
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_SETUP0, mask, 0);
        
    if (cfg.gain==GAIN_10)
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_SETUP1, mask, mask);
    else
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_SETUP1, mask, 0);
    
    if (cfg.current_on)
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_SETUP2, mask, mask);
    else
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_SETUP2, mask, 0);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_WIPER_SET and IOCTL_GAIN_POT_WIPER_SET
 * Params
 * arg : Pointer to dt78xx_cal_pot_t with members pot, and value initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_wiper_set(const struct dt7837_pot *pot, void __user *arg, 
                              size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN_MIN) || (cal.pot > AIN_MAX))
        return (-EINVAL);
    err =  dt7837_pot_wiper_write(pot, cal.pot, cal.value);
    return err;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_WIPER_GET and IOCTL_GAIN_POT_WIPER_GET
 * Params
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_wiper_get(const struct dt7837_pot *pot, void __user *arg, 
                              size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN_MIN) || (cal.pot > AIN_MAX))
        return (-EINVAL);
    if ((err = dt7837_pot_wiper_read(pot, cal.pot, &cal.value)) < 0)
        return err;
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_GET and IOCTL_GAIN_POT_GET
 * Params
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_get(const struct dt7837_pot *pot, void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN_MIN) || (cal.pot > AIN_MAX))
        return (-EINVAL);
    if ((err = dt7837_pot_cal_read(pot, &cal)) < 0)
        return err;
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_SET and IOCTL_GAIN_POT_SET
 * Params
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_set(const struct dt7837_pot *pot, void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN_MIN) || (cal.pot > AIN_MAX))
        return (-EINVAL);
    if ((err = dt7837_pot_cal_write(pot, &cal)) < 0)
        return err;
    return 0;
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7837_ain *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    size_t len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7837_ain *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    
    dev_lock(dt_dev);
    switch (cmd)
    {
        case IOCTL_AIN_CFG_GET :
            retval = _ain_cfg_get(subsys, (void __user *)arg, len); 
            break;
            
        case IOCTL_AIN_CFG_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            if ((retval = _ain_cfg_set(subsys, (void __user *)arg, len)))
                break;
            _ad_cal_change(subsys);
            break;
            
        case IOCTL_OFFSET_POT_WIPER_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _ain_pot_wiper_set(subsys->offset_pot, (void __user *)arg, len);
            break;
        
        case IOCTL_OFFSET_POT_WIPER_GET :
            retval = _ain_pot_wiper_get(subsys->offset_pot, (void __user *)arg, len);
            break;
            
        case IOCTL_GAIN_POT_WIPER_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _ain_pot_wiper_set(subsys->gain_pot, (void __user *)arg, len);
            break;
            
        case IOCTL_GAIN_POT_WIPER_GET :
            retval = _ain_pot_wiper_get(subsys->gain_pot, (void __user *)arg, len);
            break;
        
        case IOCTL_OFFSET_POT_GET :
            retval = _ain_pot_get(subsys->offset_pot, (void __user *)arg, len);
            break;
        
        case IOCTL_OFFSET_POT_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _ain_pot_set(subsys->offset_pot, (void __user *)arg, len);
            break;
        
        case IOCTL_GAIN_POT_GET :
            retval = _ain_pot_get(subsys->gain_pot, (void __user *)arg, len);
            break;
        
        case IOCTL_GAIN_POT_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _ain_pot_set(subsys->gain_pot, (void __user *)arg, len);
            break;

        case IOCTL_LED_GET :
            retval = dt7837_ioctl_led_get(dev, (void __user *)arg, len);
            break;

        case IOCTL_LED_SET :
            retval = dt7837_ioctl_led_set(dev, (void __user *)arg, len);
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
 * Create the board specific output subsystem and register a file handle
 */
int dt7837_ain_subsystem_create(struct daq_subsystem *daq)
{
    int err = -ENODEV;
    struct dt7837_ain *subsys;
    struct device_node *node;
    struct device *dev = &daq->dt_dev->pdev->dev;

    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7837_ain), GFP_KERNEL);
    if (!subsys)
        return -ENOMEM;    

    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    subsys->dt_dev = daq->dt_dev;   
    
    //Get the gain potentiometers
    node = of_parse_phandle(daq->node,"gain", 0);
    if (IS_ERR_OR_NULL(node))
    {
        dev_err(dev, "[%s] ERROR missing gain pot\n", __func__);
        goto failure;
    }
    subsys->gain_pot = dt7837_pot_init(daq->dt_dev, node);
    of_node_put(node);
    if (IS_ERR_OR_NULL(subsys->gain_pot))
        goto failure;
    
    //Get the offset potentiometers
    node = of_parse_phandle(daq->node,"offset", 0);
    if (IS_ERR_OR_NULL(node))
    {
        dev_err(dev, "[%s] ERROR offset pot\n", __func__);
        goto failure;
    }
    subsys->offset_pot = dt7837_pot_init(daq->dt_dev, node);
    of_node_put(node);
    if (IS_ERR_OR_NULL(subsys->offset_pot))
        goto failure;
    
    //force the wipers of both gain and offset pots to load power up defaults
    if ((err = _ad_cal_change(subsys)) < 0)
        goto failure;
    
    if ((err = misc_register(&daq->miscdev)) < 0)
        goto failure;
    if ((err = dev_set_drvdata(daq->miscdev.this_device, subsys)) < 0)    
        goto failure;
    return 0;
    
failure :
    if (!IS_ERR_OR_NULL(subsys->gain_pot))
        devm_kfree(dev, subsys->gain_pot);
    if (!IS_ERR_OR_NULL(subsys->offset_pot))
        devm_kfree(dev, subsys->offset_pot);
    daq->miscdev.name = NULL;
    devm_kfree(dev, subsys);
    return err;
}
#ifdef _WARN_
#warning  TBD free pot memory and i2c clients 
#endif

/*****************************************************************************
 * Update the AD calibration potentiometers based on sampling rate and gain.
 * THIS MUST NOT BE CALLED FROM INIT CODE i.e. until all subsystems have been
 * created.
 * @param dt_dev : struct dt78xx_device *
 * @return : 0=success, <0=error
 */
int dt7837_ad_cal_change(const struct dt78xx_device *dt_dev)
{
    struct list_head *pos;    
    struct dt7837_ain *subsys = NULL;
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);  
        if (strstr(daq->node->name,"ain")) //Analog in
        {
            subsys = container_of(daq->miscdev.name, struct dt7837_ain, 
                                  filename[0]);
            break;
        }
    }
    if (unlikely(!subsys))
    {
        dev_err(&dt_dev->pdev->dev, "[%s] ERROR bad subsystem\n", __func__);
        return -ENODEV;
    }
    return (_ad_cal_change(subsys));
}

/*****************************************************************************
 * Update the AD calibration potentiometers based on sampling rate and gain.
 * This writes user cal factors to each AD's gain and offset potentiometer
 * wipers
 *       Gain     Sampling rate  User cal
 *    ----------- -------------- --------
 *          1       > 52KHz         0   MASK_IN_CTRL_MODE_HS power up default
 *          10      > 52KHz         1   MASK_IN_CTRL_MODE_HS
 *          1       <= 52KHz        2   MASK_IN_CTRL_MODE_HRES
 *          10      <= 52KHz        3   MASK_IN_CTRL_MODE_HRES 
 * @param subsys
 * @return : 0=success, <0=error
 */
static int _ad_cal_change(struct dt7837_ain *subsys)
{
    u16 hres, gain;
    int i;
    int err;
    
    hres = dt78xx_fpga_read(&subsys->dt_dev->pdev->dev, FPGA_REG_IN_CTRL);
    hres = !!(hres & MASK_IN_CTRL_MODE_HRES); //note double negation
    hres *= 2; //see table above
    
    gain = dt78xx_fpga_read(&subsys->dt_dev->pdev->dev, FPGA_REG_IN_SETUP1);
    gain &= MASK_IN_SETUP1_GAIN;
    
    for (i = AIN_MIN; i <= AIN_MAX; ++i, gain >>= 1)
    {
       u32 cal = hres + (gain & IN_SETUP1_GAIN_10);
       if ((err = dt7837_pot_cal2wiper(subsys->gain_pot, i, cal)))
           break;
       if ((err = dt7837_pot_cal2wiper(subsys->offset_pot, i, cal)))
           break;
    }
    return err;
}
