/*
 * Kerenel Load Module for Data Translation DT7837 data acquisition module.
 * 
 * This file implements the subsystem file operations supported by the
 * /dev/dt7837_aout virtual file
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
#include <asm/uaccess.h>    //put_user())

#include "dt78xx.h"
#include "dt7837.h"
#include "dt7837_fpga.h"

/**************************************************************************
 * Macros
 */

/*Max number of aout channels supported by h/w. The #of actual channels in
  the board may be less and is specified in the device tree */
#define MAX_AOUT    (2)

/**************************************************************************
 * Data structures
 */
//Data structure specific to the DT7837 analog output subsystem. 
struct dt7837_aout
{
    char     filename[32];  //name of file under /dev
    struct dt78xx_device *dt_dev;
    int      num_chans;     //#of channels in the subsystem from device tree
    struct dt7837_pot *pot; //single pot for both offset and gain
};

/* There is a single potentiometer that is used for both offset and gain
   calibration. Pot#0 controls offset and pot#1 controls gain */
typedef enum da_pot {da_offset_pot=0, da_gain_pot=1} da_pot_t;

/**************************************************************************
 * Functions
 */
static int _fopen(struct inode *inode, struct file *file);
static int _fclose(struct inode *inode, struct file *file);
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t _fread (struct file *, char __user *, size_t, loff_t *);
static ssize_t _fwrite (struct file *, const char __user *, size_t, loff_t *);
static int _da_cal_change(struct dt7837_aout *);

/**************************************************************************
 * Globals
 */

/*
 * File operations supported by DT7837 aout subsystem
 */
static const struct file_operations _file_ops = 
{
    .owner          = THIS_MODULE,
    .open           = _fopen,
    .release        = _fclose,
    .unlocked_ioctl = _ioctl_cb,
    .read           = _fread,
    .write          = _fwrite,
};
    
/*****************************************************************************
 * Handler for open() call in user application made on virtual file
 * /dev/dt7837-aout
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7837_aout *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7837_aout *)file_to_subsys(file);
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
    
    dev_dbg(&dt_dev->pdev->dev, "[%s] %s f_flags %x\n",
                                __func__, subsys->filename, file->f_flags);
    
    return (0);
}

/*****************************************************************************
 * Handler for close() call in user application made on virtual file
 * /dev/dt7837-aout
 */
static int _fclose(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7837_aout *subsys;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7837_aout *)file_to_subsys(file);
    if (!subsys)
    {
        return -ENODEV;
    }
     
    //close the underlying daq_subsystem
    dt78xx_fclose(file);
    
    dev_dbg(&dt_dev->pdev->dev, "[%s] %s", __func__, subsys->filename);
    return (0);
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_GET and IOCTL_GAIN_POT_GET
 * Params
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _aout_pot_get(const struct dt7837_pot *pot, da_pot_t da_pot, 
                        void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if (cal.pot)     //User must specify channel as 0
        return (-EINVAL);
    cal.pot = da_pot; //actual pot is either the one for offset or gain
    if ((err = dt7837_pot_cal_read(pot, &cal)) < 0)
        return err;
    cal.pot = 0;
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
static int _aout_pot_set(const struct dt7837_pot *pot, da_pot_t da_pot, 
                         void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if (cal.pot)     //User must specify aout0
        return (-EINVAL);
    cal.pot = da_pot; //actual pot is either the one for offset or gain
    if ((err = dt7837_pot_cal_write(pot, &cal)) < 0)
        return err;
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_WIPER_GET and IOCTL_GAIN_POT_WIPER_GET
 * Params
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _aout_pot_wiper_get(const struct dt7837_pot *pot, da_pot_t da_pot, 
                               void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if (cal.pot)     //User must specify channel as 0
        return (-EINVAL);
    if ((err = dt7837_pot_wiper_read(pot, da_pot, &cal.value)) < 0)
        return err;
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_WIPER_SET and IOCTL_GAIN_POT_WIPER_SET
 * Params
 * arg : Pointer to dt78xx_cal_pot_t with members pot, and value initialized
 * len : length of buffer pointed by arg
 */
static int _aout_pot_wiper_set(const struct dt7837_pot *pot, da_pot_t da_pot,
                               void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if (cal.pot)     //User must specify channel as 0
        return (-EINVAL);
    err =  dt7837_pot_wiper_write(pot, da_pot, cal.value);
    return err;
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7837_aout *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    size_t len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7837_aout *)file_to_subsys(file);
    if (unlikely(!subsys))
        return -ENODEV;
    
    dev_lock(dt_dev);
    switch (cmd)
    {
        case IOCTL_LED_GET :
            retval = dt7837_ioctl_led_get(dev, (void __user *)arg, len);
            break;

        case IOCTL_LED_SET :
            retval = dt7837_ioctl_led_set(dev, (void __user *)arg, len);
            break;
        
        case IOCTL_OFFSET_POT_GET :
            retval = _aout_pot_get(subsys->pot, da_offset_pot, 
                                   (void __user *)arg, len);
            break;
            
        case IOCTL_GAIN_POT_GET :
            retval = _aout_pot_get(subsys->pot, da_gain_pot, 
                                   (void __user *)arg, len);
            break;
        
        case IOCTL_OFFSET_POT_WIPER_GET :
            retval = _aout_pot_wiper_get(subsys->pot, da_offset_pot, 
                                         (void __user *)arg, len);
            break;
        
        case IOCTL_GAIN_POT_WIPER_GET :
            retval = _aout_pot_wiper_get(subsys->pot, da_gain_pot, 
                                         (void __user *)arg, len);
            break;

        case IOCTL_OFFSET_POT_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _aout_pot_set(subsys->pot, da_offset_pot, 
                                   (void __user *)arg, len);
            break;

        case IOCTL_GAIN_POT_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _aout_pot_set(subsys->pot, da_gain_pot, 
                                   (void __user *)arg, len);
            break;

        case IOCTL_OFFSET_POT_WIPER_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _aout_pot_wiper_set(subsys->pot, da_offset_pot, 
                                   (void __user *)arg, len);
            break;

        case IOCTL_GAIN_POT_WIPER_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _aout_pot_wiper_set(subsys->pot, da_gain_pot, 
                                   (void __user *)arg, len);
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
 * Synchronous read from user application. This reads the DA single value
 * registers in the FPGA and returns u32 values; a single u32 if the board
 * has one aout channel, two u32 if the aout has two channels
 */
static ssize_t _fread (struct file *file, char __user *buff, size_t len, 
                       loff_t *off)
{
    s32 aout;
    struct dt78xx_device *dt_dev;
    struct dt7837_aout *subsys;
    struct device *dev;
    int err;
    s32 __user *p = (s32 __user *)buff;
  
    dt_dev = file_to_dt78xx(file);
    dev = &dt_dev->pdev->dev;
    if ((err = is_output_armed(dev))) //error if the output armed
        return err;
    
    subsys = (struct dt7837_aout *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    
    if (len < (sizeof(s32)*subsys->num_chans)) 
        return -EINVAL;
    
    dev_lock(dt_dev);
    aout = dt78xx_fpga_read(dev, FPGA_REG_DAC0_LO);
    aout |= (dt78xx_fpga_read(dev, FPGA_REG_DAC0_HI) << FPGA_REG_LEN_BITS);
    dev_unlock(dt_dev);
    if ((err = put_user(aout, p)))
        return err;
    
    if (subsys->num_chans == MAX_AOUT)
    {
        dev_lock(dt_dev);
        aout = dt78xx_fpga_read(dev, FPGA_REG_DAC1_LO);
        aout |= (dt78xx_fpga_read(dev, FPGA_REG_DAC1_HI) << FPGA_REG_LEN_BITS);
        dev_unlock(dt_dev);
        if ((err = put_user(aout, ++p)))
            return err;
    }
    return (sizeof(s32)*subsys->num_chans);
}

/*****************************************************************************
 * Synchronous write from user application. This writes the DA single value
 * registers in the FPGA;  input must be a single u32 if the board
 * has one aout channel, two u32 if the aout has two channels 
 */
static ssize_t _fwrite (struct file *file, const char __user *buff, size_t len, 
                       loff_t *off)
{
    s32 aout;
    struct dt78xx_device *dt_dev;
    struct dt7837_aout *subsys;
    struct device *dev;
    int err;
    s32 __user *p = (s32 __user *)buff;
  
    dt_dev = file_to_dt78xx(file);
    dev = &dt_dev->pdev->dev;
    if ((err = is_output_armed(dev))) //error if the output armed
        return err;
    
    subsys = (struct dt7837_aout *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    
    if (len < (sizeof(s32)*subsys->num_chans)) 
        return -EINVAL;
    
    if ((err = get_user(aout, p)))
        return err;
    
    dev_lock(dt_dev);
    //unmask AOUT0 so that its is not in the stream
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_MASK, MASK_OUT_MASK_AOUT0, 0);
    dt78xx_fpga_write(dev, FPGA_REG_DAC0_LO, aout & U16_MAX);
    dt78xx_fpga_write(dev, FPGA_REG_DAC0_HI, (aout >> FPGA_REG_LEN_BITS));
    dev_unlock(dt_dev);
    
    if (subsys->num_chans == MAX_AOUT)
    {
        if ((err = get_user(aout, ++p)))
            return err;
        dev_lock(dt_dev);
        dt78xx_fpga_rmw(dev, FPGA_REG_OUT_MASK, MASK_OUT_MASK_AOUT1, 0);
        dt78xx_fpga_write(dev, FPGA_REG_DAC1_LO, aout & U16_MAX);
        dt78xx_fpga_write(dev, FPGA_REG_DAC1_HI, (aout >> FPGA_REG_LEN_BITS));
        dev_unlock(dt_dev);
    }
    
    dev_lock(dt_dev);
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL1, 
                    MASK_OUT_CTRL1_ENABLE, MASK_OUT_CTRL1_ENABLE);
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL0, 
                    MASK_OUT_CTRL0_OUT0_LOAD, MASK_OUT_CTRL0_OUT0_LOAD);
    if (subsys->num_chans == MAX_AOUT)
        dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL0, 
                        MASK_OUT_CTRL0_OUT1_LOAD, MASK_OUT_CTRL0_OUT1_LOAD);
    dev_unlock(dt_dev);

    return len;
}

/*****************************************************************************
 * Create the board specific output subsystem and register a file handle
 */
int dt7837_aout_subsystem_create(struct daq_subsystem *daq)
{
    int err = -ENODEV;
    struct dt7837_aout *subsys;
    struct device_node *node;
    struct device *dev = &daq->dt_dev->pdev->dev;
    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7837_aout), GFP_KERNEL);
    if (!subsys)
        return -ENOMEM;        
    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    subsys->dt_dev = daq->dt_dev;   
    //Read the #of channels in Aout subststem; default is 1
    if (of_property_read_u32(daq->node, "channels", &subsys->num_chans) != 0)  
        subsys->num_chans = 1;
    if (subsys->num_chans > MAX_AOUT)
    {
        err = -EINVAL;
        dev_err(dev, "%s ERROR Channels %d)",
                subsys->filename, subsys->num_chans);
        goto failure;
    }
    
    //Get the single potentiometer used for both offset and gain
    node = of_parse_phandle(daq->node,"pot", 0);
    if (IS_ERR_OR_NULL(node))
    {
        dev_err(dev, "[%s] ERROR missing pot\n", __func__);
        goto failure;
    }
    subsys->pot = dt7837_pot_init(daq->dt_dev, node);
    of_node_put(node);
    if (IS_ERR_OR_NULL(subsys->pot))
        goto failure;
    
    //force the wipers of both gain and offset pots to load power up defaults
    if ((err = _da_cal_change(subsys)) < 0)
        goto failure;
    
    if ((err = misc_register(&daq->miscdev)) < 0)
        goto failure;
    if ((err = dev_set_drvdata(daq->miscdev.this_device, subsys)) < 0)    
        goto failure;
    return 0;
    
failure :
    daq->miscdev.name = NULL;
    devm_kfree(dev, subsys);
    return (err);
}

/*****************************************************************************
 * Update the DA calibration potentiometers based on sampling rate.
 * This writes user cal factors to the DA's gain and offset potentiometer
 * wipers; pot#0 is for offset, pot#1 is for gain
 *    Sampling rate  User cal
 * --------------    -----
 *   > 52KHz         0          MASK_OUT_CTRL0_MODE_DBL power up default
 *   <= 52KHz        1          MASK_OUT_CTRL0_MODE_NORMAL
 *   > 108KHz        2          MASK_OUT_CTRL0_MODE_QUAD 
 * @param subsys
 * @return : 0=success, <0=error
 */
static int _da_cal_change(struct dt7837_aout *subsys)
{
    u16 mode;
    int err;
    u32 cal;
    
    mode = dt78xx_fpga_read(&subsys->dt_dev->pdev->dev, FPGA_REG_OUT_CTRL0);
    mode = (mode & MASK_OUT_CTRL0_MODE); 
    
    cal = (mode == MASK_OUT_CTRL0_MODE_DBL) ? 0 :
          (mode == MASK_OUT_CTRL0_MODE_NORMAL) ? 1 : 2;

   if ((err = dt7837_pot_cal2wiper(subsys->pot, da_offset_pot, cal)))
        return err;
    if ((err = dt7837_pot_cal2wiper(subsys->pot, da_gain_pot, cal)))
        return err;
    
    return 0;
}

/*****************************************************************************
 * Update the DA calibration potentiometers based on sampling rate.
 * THIS MUST NOT BE CALLED FROM INIT CODE i.e. until all subsystems have been
 * created.
 * @param dt_dev : struct dt78xx_device *
 * @return : 0=success, <0=error
 */
int dt7837_da_cal_change(const struct dt78xx_device *dt_dev)
{
    struct list_head *pos;    
    struct dt7837_aout *subsys = NULL;
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);  
        if (strstr(daq->node->name,"aout")) //Analog out
        {
            subsys = container_of(daq->miscdev.name, struct dt7837_aout, 
                                  filename[0]);
            break;
        }
    }
    if (unlikely(!subsys))
    {
        dev_err(&dt_dev->pdev->dev, "[%s] ERROR bad subsystem\n", __func__);
        return -ENODEV;
    }
    return (_da_cal_change(subsys));
}

