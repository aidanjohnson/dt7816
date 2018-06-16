/*
 * Kerenel Load Module for Data Translation DT7816 data acquisition module.
 * 
 * This file implements the subsystem file operations supported by the
 * /dev/dt7816_aout virtual file
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
#include <asm/uaccess.h>    //put_user())
#include <linux/delay.h>    //msleep

#include "dt78xx.h"
#include "dt7816.h"
#include "dt7816_fpga.h"

/**************************************************************************
 * Macros
 */

#define AOUT0  (0)
#define AOUT1  (1)
#define LTC2752_SPAN_BIP_10     (0x3)
/*
 * There is a single ISL22343 4-potentiometer device that is used for gain and
 * offset calibration, as follows
 * Pot channel 0 => AOUT0 gain
 * Pot channel 1 => AOUT1 gain
 * Pot channel 2 => AOUT0 offset
 * Pot channel 3 => AOUT1 offset
 */
#define AOUT0_GAIN_POT      (0)
#define AOUT1_GAIN_POT      (1)
#define AOUT0_OFFSET_POT    (2)
#define AOUT1_OFFSET_POT    (3)

//Delays after adjusting wipers in gain and offset potentiometer
#define OFFSET_WIPER_DELAY_MS   (10)
#define GAIN_WIPER_DELAY_MS     (50)
/*
 * The user calibration and factory calibration are stored in non-volatile 
 * registers
 */
#define USER_CAL_REG    (0)
#define FACTORY_CAL_REG (1)

/**************************************************************************
 * Data structures
 */

//Data structure specific to the DT7816 analog output subsystem. 
struct dt7816_aout
{
    char     filename[32];  //name of file under /dev
    struct dt78xx_device *dt_dev;
    s16    ch0; //Channel 0 value for "pseudo" single value read back
    s16    ch1; //Channel 1 value for "pseudo" single value read back
    struct dt78xx_eep_pot *pot; //single I2C potentiometer device (See note above)
};

//LTC2752 DAC commands
enum ltc2752_cmd
{
    ltc2752_cmd_write_span = 0x20,
    ltc2752_cmd_write_code = 0x30,
    ltc2752_cmd_update     = 0x40,
};

//LTC2752 DAC channel address
enum ltc2752_addr{ltc2752_addr_a=0x0, ltc2752_addr_b=0x2, ltc2752_addr_ab=0xf};

/**************************************************************************
 * Functions
 */
static int _fopen(struct inode *inode, struct file *file);
static int _fclose(struct inode *inode, struct file *file);
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t _fwrite (struct file *, const char __user *, size_t, loff_t *);
static ssize_t _fread (struct file *, char __user *, size_t, loff_t *);

/**************************************************************************
 * Globals
 */

/*
 * File operations supported by DT7816 aout subsystem
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

/*****************************************************************************
 * Signed 16-bit to 16-bit offset binary
 * @param s : 16-bit 2's complement
 * @return 16-bit offset binary
 */
static inline u16 s16_to_offbin(s16 s)
{
    return s^SHRT_MIN;
}

/*****************************************************************************
 * Write a 24-bit configuration code to the LTC2752 DAC
 * @param dev
 * @param cmd   : LTC2752 command code
 * @param addr  : LTC2752 address code
 * @param data  : 
 * @return : 0=success
 */
static int ltc2752_config_write(struct device *dev, enum ltc2752_cmd cmd, 
                                enum ltc2752_addr addr, u16 data)
{
    int i = 8;
    dt78xx_fpga_write(dev, FPGA_REG_DA_CFG_LO, data);
    dt78xx_fpga_write(dev, FPGA_REG_DA_CFG_HI, (u16)(cmd|addr));
    dt78xx_fpga_write(dev, FPGA_REG_OUT_CTRL, MASK_OUT_CTRL_CFG_WR);
    while (i--)
    {
        if ((dt78xx_fpga_read(dev, FPGA_REG_OUT_CTRL)&MASK_OUT_CTRL_CFG_WR)==0)
            break;
    }
    return (i!=0)?0:-EIO;
}

/*****************************************************************************
 * Initialize the span of both channels in the LTC 2752 DAC to +/- 10V and set
 * the output to 0V
 * @param dev
 * @return : 0=success
 */
static int ltc2752_init(struct device *dev)
{
    //both channels span set to +/- 10V
    if (ltc2752_config_write(dev, ltc2752_cmd_write_span, ltc2752_addr_ab, 
                             LTC2752_SPAN_BIP_10))
        return -EIO;
    //both channels value 0V == mid scale offset binary
    if (ltc2752_config_write(dev, ltc2752_cmd_write_code, ltc2752_addr_ab, 
                             s16_to_offbin(0)))
        return -EIO;
    //update both channels
    if (ltc2752_config_write(dev, ltc2752_cmd_update, ltc2752_addr_ab, 0))
        return -EIO;
    return 0;
}

/*****************************************************************************
 * Handler for open() call in user application made on virtual file
 * /dev/dt7816-aout
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_aout *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7816_aout *)file_to_subsys(file);
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
 * /dev/dt7816-aout
 */
static int _fclose(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_aout *subsys;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7816_aout *)file_to_subsys(file);
    if (!subsys)
    {
        return -ENODEV;
    }
     
    //close the underlying daq_subsystem
    dt78xx_fclose(file);
    return (0);
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_GET
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _offset_pot_get(const struct dt78xx_eep_pot *pot, void __user *arg,
                        size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    err = dt78xx_potentiometer_cal_read
            (pot, 
            (cal.pot==AOUT0)?AOUT0_OFFSET_POT:AOUT1_OFFSET_POT, 
            cal.cal.factory?FACTORY_CAL_REG:USER_CAL_REG, 
            &cal.value);
    if (err)
        return err;
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_SET
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _offset_pot_set(const struct dt78xx_eep_pot *pot, void __user *arg, 
                        size_t len)
{
    dt78xx_cal_pot_t cal;
    int err=0;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    err = dt78xx_potentiometer_cal_write
            (pot, 
            (cal.pot==AOUT0)?AOUT0_OFFSET_POT:AOUT1_OFFSET_POT, 
            cal.cal.factory?FACTORY_CAL_REG:USER_CAL_REG, 
            cal.value);
    return err;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_GAIN_POT_GET
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _gain_pot_get(const struct dt78xx_eep_pot *pot, void __user *arg,
                        size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    err = dt78xx_potentiometer_cal_read
            (pot, 
            (cal.pot==AOUT0)?AOUT0_GAIN_POT:AOUT1_GAIN_POT, 
            cal.cal.factory?FACTORY_CAL_REG:USER_CAL_REG, 
            &cal.value);
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
static int _gain_pot_set(const struct dt78xx_eep_pot *pot, void __user *arg, 
                        size_t len)
{
    dt78xx_cal_pot_t cal;
    int err=0;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    err = dt78xx_potentiometer_cal_write
            (pot, 
            (cal.pot==AOUT0)?AOUT0_GAIN_POT:AOUT1_GAIN_POT, 
            cal.cal.factory?FACTORY_CAL_REG:USER_CAL_REG, 
            cal.value);
    return err;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_WIPER_GET 
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _offset_pot_wiper_get(const struct dt78xx_eep_pot *pot, 
                                 void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    if ((err = dt78xx_potentiometer_wiper_read
                    (pot, (cal.pot==AOUT0)?AOUT0_OFFSET_POT:AOUT1_OFFSET_POT, 
                    &cal.value)) < 0)
        return err;
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_OFFSET_POT_WIPER_SET 
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot, and value initialized
 * len : length of buffer pointed by arg
 */
static int _offset_pot_wiper_set(const struct dt78xx_eep_pot *pot,
                               void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    err = dt78xx_potentiometer_wiper_write
                    (pot, (cal.pot==AOUT0)?AOUT0_OFFSET_POT:AOUT1_OFFSET_POT, 
                    cal.value);
    msleep(OFFSET_WIPER_DELAY_MS); 
    return err;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_GAIN_POT_WIPER_GET 
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot initialized
 * len : length of buffer pointed by arg
 */
static int _gain_pot_wiper_get(const struct dt78xx_eep_pot *pot, 
                                 void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    if ((err = dt78xx_potentiometer_wiper_read
                    (pot, (cal.pot==AOUT0)?AOUT0_GAIN_POT:AOUT1_GAIN_POT, 
                    &cal.value)) < 0)
        return err;
    if (copy_to_user(arg, (void *)&cal, sizeof(cal))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_GAIN_POT_WIPER_SET 
 * Params
 * pot : pointer to dt78xx_eep_pot
 * arg : Pointer to dt78xx_cal_pot_t with members pot, and value initialized
 * len : length of buffer pointed by arg
 */
static int _gain_pot_wiper_set(const struct dt78xx_eep_pot *pot,
                               void __user *arg, size_t len)
{
    dt78xx_cal_pot_t cal;
    int err;

    if (len < sizeof(cal))
         return (-EINVAL);
    
    if (copy_from_user(&cal, arg, sizeof(cal))) 
        return (-EFAULT);
    if ((cal.pot < AOUT0) || (cal.pot > AOUT1))
        return (-EINVAL);    
    err = dt78xx_potentiometer_wiper_write
                    (pot, (cal.pot==AOUT0)?AOUT0_GAIN_POT:AOUT1_GAIN_POT, 
                    cal.value);
    msleep(GAIN_WIPER_DELAY_MS); 
    return err;
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7816_aout *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    size_t len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7816_aout *)file_to_subsys(file);
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
        
        case IOCTL_OFFSET_POT_GET :
            retval = _offset_pot_get(subsys->pot, (void __user *)arg, len);
            break;

        case IOCTL_OFFSET_POT_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _offset_pot_set(subsys->pot, (void __user *)arg, len);
            break;
        
        case IOCTL_GAIN_POT_GET :
            retval = _gain_pot_get(subsys->pot, (void __user *)arg, len);
            break;

        case IOCTL_GAIN_POT_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _gain_pot_set(subsys->pot, (void __user *)arg, len);
            break;

        case IOCTL_OFFSET_POT_WIPER_GET :
            retval = _offset_pot_wiper_get(subsys->pot, (void __user *)arg, len);
            break;

        case IOCTL_OFFSET_POT_WIPER_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _offset_pot_wiper_set(subsys->pot, (void __user *)arg, len);
            break;
            
        case IOCTL_GAIN_POT_WIPER_GET :
            retval = _gain_pot_wiper_get(subsys->pot, (void __user *)arg, len);
            break;

        case IOCTL_GAIN_POT_WIPER_SET :
            if ((retval = is_output_armed(dev))) //error if output armed
                break;
            retval = _gain_pot_wiper_set(subsys->pot, (void __user *)arg, len);
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
 * Synchronous read from user application. This returns the channel single
 * values cached in a prior write
 */
static ssize_t _fread (struct file *file, char __user *buff, size_t len, 
                       loff_t *off)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_aout *subsys;
    struct device *dev;
    int err, r;
    s16 __user *p = (s16 __user *)buff;
  
    dt_dev = file_to_dt78xx(file);
    dev = &dt_dev->pdev->dev;
    if ((err = is_output_armed(dev))) //error if the output armed
        return err;
    
    subsys = (struct dt7816_aout *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    if (len < sizeof(s16)) 
        return -EINVAL;
    if ((err = put_user(subsys->ch0, p++)))
        return err;
    r = sizeof(s16);
    if (len >= sizeof(s32))
    {
        if ((err = put_user(subsys->ch1, p++)))
            return err;
        r += sizeof(s16);
    }
    return (r);
}

/*****************************************************************************
 * Synchronous write from user application. If input is a single s16 value,
 * channel 0 only is updated, two s16 values channels 0 and 1 are updated
 * 
 */
static ssize_t _fwrite (struct file *file, const char __user *buff, size_t len, 
                       loff_t *off)
{
    s16 aout;
    struct dt78xx_device *dt_dev;
    struct dt7816_aout *subsys;
    struct device *dev;
    int err;
    s16 __user *p = (s16 __user *)buff;
  
    dt_dev = file_to_dt78xx(file);
    dev = &dt_dev->pdev->dev;
    if ((err = is_output_armed(dev))) //error if the output armed
        return err;
    
    subsys = (struct dt7816_aout *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    
    if (len < sizeof(s16)) 
        return -EINVAL;
    if ((err = get_user(aout, p)))
        return err;
    
    dev_lock(dt_dev);
    //unmask AOUT0 so that its is not in the stream
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_MASK, 
                    MASK_OUT_MASK_AOUT0, ~MASK_OUT_MASK_AOUT0);
    err = ltc2752_config_write(dev, ltc2752_cmd_write_code, ltc2752_addr_a, 
                               s16_to_offbin(aout));
    dev_unlock(dt_dev);
    if (err)
        return -EIO;
    subsys->ch0 = aout; //cache the value for readback
    if (len >= sizeof(s32)) //update AOUT1 also
    {
        if ((err = get_user(aout, ++p)))
            return err;
        dev_lock(dt_dev);
        dt78xx_fpga_rmw(dev, FPGA_REG_OUT_MASK, 
                        MASK_OUT_MASK_AOUT1, ~MASK_OUT_MASK_AOUT1);
        err = ltc2752_config_write(dev, ltc2752_cmd_write_code, ltc2752_addr_b,
                                   s16_to_offbin(aout));
        dev_unlock(dt_dev);
        if (err)
            return -EIO;
        subsys->ch1 = aout; //cache the value for readback
    }
    
    //simultaneous update of either or both channels
    dev_lock(dt_dev);
    err = ltc2752_config_write(dev, ltc2752_cmd_update, ltc2752_addr_ab, 0);
    dev_unlock(dt_dev);
    if (err)
        return -EIO;
    
    return len;
}

/*****************************************************************************
 * Create the board specific output subsystem and register a file handle
 */
int dt7816_aout_subsystem_create(struct daq_subsystem *daq)
{
    int err = -ENODEV;
    struct dt7816_aout *subsys;
    struct device_node *node;
    struct device *dev = &daq->dt_dev->pdev->dev;
    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7816_aout), GFP_KERNEL);
    if (!subsys)
        return -ENOMEM;        
    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    subsys->dt_dev = daq->dt_dev;   
   
    //Get the single potentiometer used for both offset and gain
    node = of_parse_phandle(daq->node,"gain-offset", 0);
    if (IS_ERR_OR_NULL(node))
    {
        dev_err(dev, "[%s] ERROR missing pot\n", __func__);
        goto failure;
    }
    subsys->pot = dt78xx_potentiometer_init(daq->dt_dev, node);
    of_node_put(node);
    if (IS_ERR_OR_NULL(subsys->pot))
        goto failure;

    //initialize DAC range to +/-10V and output 0V
    if (ltc2752_init(dev))
    {
        err = -EIO;
        goto failure;
    }
    //force the wipers of gain and offset potentiometers to load user cal
    if ((err = dt78xx_potentiometer_cal2wiper(subsys->pot, AOUT0_GAIN_POT, 
                                              USER_CAL_REG)) < 0)
        goto failure;
    if ((err = dt78xx_potentiometer_cal2wiper(subsys->pot, AOUT1_GAIN_POT, 
                                              USER_CAL_REG)) < 0)
        goto failure;
    if ((err = dt78xx_potentiometer_cal2wiper(subsys->pot, AOUT0_OFFSET_POT, 
                                              USER_CAL_REG)) < 0)
        goto failure;
    if ((err = dt78xx_potentiometer_cal2wiper(subsys->pot, AOUT1_OFFSET_POT, 
                                              USER_CAL_REG)) < 0)
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
