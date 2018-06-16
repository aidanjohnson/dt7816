/*
 * Kerenel Load Module for Data Translation DT7816 data acquisition module.
 * 
 * This file implements the subsystem file operations supported by the
 * /dev/dt7816_ain virtual file
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
#include <asm/uaccess.h>    //copy_to_user())
#include <linux/delay.h>    //msleep

#include "dt78xx.h"
#include "dt7816.h"
#include "dt7816_fpga.h"

/**************************************************************************
 * Macros
 */
#define AIN0    (0)
#define AIN7    (7)

/*
 * The ADC has a single potentiometer for gain calibration. The user calibration
 * and factory calibration are stored in the following non-volatile registers
 */
#define USER_CAL_REG    (0)
#define FACTORY_CAL_REG (1)
#define POT_WIPER_DELAY_MS      (100)
/**************************************************************************
 * Data structures
 */

//Data structure specific to the DT7816 analog input subsystem. 
struct dt7816_ain
{
    char    filename[32]; //name of file under /dev
    struct dt78xx_device *dt_dev;
    struct dt78xx_eep_pot *gain_pot;
};

/**************************************************************************
 * Functions
 */
static int _fopen(struct inode *inode, struct file *file);
static int _fclose(struct inode *inode, struct file *file);
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg);

/**************************************************************************
 * Globals
 */

/*
 * File operations supported by DT7816 ain subsystem
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
 * /dev/dt7816-ain
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_ain *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7816_ain *)file_to_subsys(file);
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
    return (0);
}

/*****************************************************************************
 * Handler for close() call in user application made on virtual file
 * /dev/dt7816-ain
 */
static int _fclose(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_ain *subsys;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7816_ain *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
     
    //close the underlying daq_subsystem
    dt78xx_fclose(file);
    return (0);
}

/*****************************************************************************
 * Handler for ioctl IOCTL_AIN_CFG_GET
 * Params
 *  arg : Pointer to dt78xx_ain_config_t with member ain initialized
 * len : length of buffer pointed by arg
 */
static int _ain_cfg_get(struct dt7816_ain *ainsys, void __user *arg, size_t len)
{
    dt78xx_ain_config_t cfg;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user(&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    if ((cfg.ain < AIN0) || (cfg.ain > AIN7))
        return (-EINVAL);
    
    cfg.ac_coupling = 0;
    cfg.gain = 1; //X1
    cfg.current_on = 0;
    cfg.differential = 0;
    
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
static int _ain_cfg_set(struct dt7816_ain *ainsys, void __user *arg, size_t len)
{
    dt78xx_ain_config_t cfg;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user(&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    if ((cfg.ain < AIN0) || (cfg.ain > AIN7))
        return (-EINVAL);
    //no registers to configure; all config params ignored
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_GAIN_POT_WIPER_SET
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot, and value initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_wiper_set(const struct dt78xx_eep_pot *pot, 
                                void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err = 0;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN0) || (cal.pot > AIN7))
        return (-EINVAL);    
    err =  dt78xx_potentiometer_wiper_write(pot, 0, cal.value);
    msleep(POT_WIPER_DELAY_MS); 
    return err;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_GAIN_POT_WIPER_GET
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_wiper_get(const struct dt78xx_eep_pot *pot, 
                              void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN0) || (cal.pot > AIN7))
        return (-EINVAL);    
    if ((err = dt78xx_potentiometer_wiper_read(pot, 0, &cal.value)) < 0)
        return err;
    cal.pot = AIN0; //always default
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_GAIN_POT_GET
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_get(const struct dt78xx_eep_pot *pot, void __user *arg,
                        size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN0) || (cal.pot > AIN7))
        return (-EINVAL);
    if (cal.cal.factory)
        err = dt78xx_potentiometer_cal_read(pot, 0, FACTORY_CAL_REG, &cal.value);
    else
        err = dt78xx_potentiometer_cal_read(pot, 0, USER_CAL_REG, &cal.value);
    if (err)
        return err;
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_GAIN_POT_SET
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _ain_pot_set(const struct dt78xx_eep_pot *pot, void __user *arg, 
                        size_t len)
{
    dt78xx_cal_pot_t cal;
    int err=0;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AIN0) || (cal.pot > AIN7))
        return (-EINVAL);
    if (cal.cal.factory)
        err = dt78xx_potentiometer_cal_write(pot, 0, FACTORY_CAL_REG, cal.value);
    else
        err = dt78xx_potentiometer_cal_write(pot, 0, USER_CAL_REG, cal.value);
    return err;
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7816_ain *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    size_t len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7816_ain *)file_to_subsys(file);
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
            break;
            
        case IOCTL_GAIN_POT_WIPER_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _ain_pot_wiper_set(subsys->gain_pot, (void __user *)arg, len);
            break;
            
        case IOCTL_GAIN_POT_WIPER_GET :
            retval = _ain_pot_wiper_get(subsys->gain_pot, (void __user *)arg, len);
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
 * Create the board specific output subsystem and register a file handle
 */
int dt7816_ain_subsystem_create(struct daq_subsystem *daq)
{
    int err = -ENODEV;
    struct dt7816_ain *subsys;
    struct device_node *node;
    struct device *dev = &daq->dt_dev->pdev->dev;

    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7816_ain), GFP_KERNEL);
    if (!subsys)
        return -ENOMEM;    

    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    subsys->dt_dev = daq->dt_dev;   
    
    //Get the gain potentiometer
    node = of_parse_phandle(daq->node,"gain", 0);
    if (IS_ERR_OR_NULL(node))
    {
        dev_err(dev, "[%s] ERROR missing gain pot\n", __func__);
        goto failure;
    }
    subsys->gain_pot = dt78xx_potentiometer_init(daq->dt_dev, node);
    of_node_put(node);
    if (IS_ERR_OR_NULL(subsys->gain_pot))
        goto failure;
    //force the wiper of gain pot to load user cal
    if ((err = dt78xx_potentiometer_cal2wiper(subsys->gain_pot, 0, USER_CAL_REG)) < 0)
        goto failure;
    if ((err = misc_register(&daq->miscdev)) < 0)
        goto failure;
    if ((err = dev_set_drvdata(daq->miscdev.this_device, subsys)) < 0)    
        goto failure;
    return 0;
    
failure :
    if (!IS_ERR_OR_NULL(subsys->gain_pot))
        devm_kfree(dev, subsys->gain_pot);
    daq->miscdev.name = NULL;
    devm_kfree(dev, subsys);
    return err;
}
#ifdef _WARN_
#warning  TBD free pot memory and i2c clients 
#endif

/*****************************************************************************
 * Called from read of sysfs file ad_gain_pot
 * @param dt_dev
 * @return : AD gain pot's wiper value
 */
u32 sysfs_ad_gain_pot_read(const struct dt78xx_device *dt_dev)
{
    u32 val;
    struct list_head *pos;    
    struct dt7816_ain *subsys = NULL;
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);  
        if (strstr(daq->node->name,"ain")) //Analog in
        {
            subsys = container_of(daq->miscdev.name, struct dt7816_ain, 
                                  filename[0]);
            break;
        }
    }
    if (unlikely(!subsys))
    {
        dev_err(&dt_dev->pdev->dev, "[%s] ERROR bad subsystem\n", __func__);
        return 0;
    }
    if (dt78xx_potentiometer_wiper_read(subsys->gain_pot, 0, &val))
        return 0;
    return val;    
}

/*****************************************************************************
 * Called from write to sysfs file ad_gain_pot
 * @param dt_dev
 * @return : AD gain pot's wiper value
 */
void sysfs_ad_gain_pot_write(const struct dt78xx_device *dt_dev, u32 val)
{
    struct list_head *pos;    
    struct dt7816_ain *subsys = NULL;
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);  
        if (strstr(daq->node->name,"ain")) //Analog in
        {
            subsys = container_of(daq->miscdev.name, struct dt7816_ain, 
                                  filename[0]);
            break;
        }
    }
    if (unlikely(!subsys))
    {
        dev_err(&dt_dev->pdev->dev, "[%s] ERROR bad subsystem\n", __func__);
        return;
    }
    dt78xx_potentiometer_wiper_write(subsys->gain_pot, 0, val);
}
