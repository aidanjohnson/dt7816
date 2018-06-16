#ifndef _DT7837_H_
#define _DT7837_H_
/*
 *  Miscelleneous definitions for DT7837 
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
 */
#include <linux/i2c.h>
#include "dt78xx_ioctl.h"

#define DEFAULT_CLK_RATE_HZ    (100000.0f)

struct pll_config;
struct dt7837_pot;


/*****************************************************************************
 * Return pointer to subsystem's private struct from the virtual device file 
 * pointer. 
 * misc_open() initializes file->private_data to point to miscdevice and before
 * registering the miscdevice, we stashed away a pointer to the subsystem's 
 * private struct in miscdevice's this_device
 */  
static inline void *file_to_subsys(struct file *file)    
{
    void *ret;
    struct miscdevice *md;
    md = (struct miscdevice *)file->private_data;
    if (WARN_ON(!md))
    {
        return NULL;
    }
    
    ret=dev_get_drvdata(md->this_device);
    if (WARN_ON(!ret))
    {
        return NULL;
    }
    return ret;
}

/*****************************************************************************
 * Create individual subsystems. These are called from the driver's probe()
 * function
 * @param daq   : resources assigned to the subsystem to create
 * @return      : 0=success, <1=failure 
 */
int dt7837_aout_subsystem_create(struct daq_subsystem *daq);
int dt7837_ain_subsystem_create(struct daq_subsystem *daq);
int dt7837_din_subsystem_create(struct daq_subsystem *daq);
int dt7837_dout_subsystem_create(struct daq_subsystem *daq);
int dt7837_stream_in_create(struct daq_subsystem *daq);
int dt7837_stream_out_create(struct daq_subsystem *daq);
int dt7837_ct_subsystem_create(struct daq_subsystem *daq);
int dt7837_measure_subsystem_create(struct daq_subsystem *daq);
int dt7837_tach_subsystem_create(struct daq_subsystem *daq);

/*****************************************************************************
 * Cleanup/destroy individual subsystems. These are called from the driver's 
 * remove() function. If the subsystem allocated any memory, it should be
 * deallocated with *care* !!
 * @param daq   :  subsystem resources
 */
void dt7837_ain_subsystem_free(struct daq_subsystem *daq);

/*****************************************************************************
 * Create DT7837 specific sysfs files for test and debug
 * @param pdev  : platform device pointer
 * @return      : 0=success, <1=failure 
 */
int dt7837_sysfs_create(struct platform_device *pdev);

/*****************************************************************************
 * Configure the PLL clock rate generator 
 * @param dt    : this device
 * @param cfg   : 0 PLL configuration allocated and initialized by calling
 *                dt78xx_ad_pll_config_init()
 * @return      : 0=success, <1=failure 
 */
int dt7837_pll_config_write(struct dt78xx_device *dt, struct pll_config *cfg);

/*****************************************************************************
 * Returns PLL configuration for the specified sampling rate
 * @param freq : Pointer to desired sampling rate. On success, the actual rate
 *               is returned here
 * @param ad   : 1 for AD PLL, 0 for DA PLL
 * @return : <=0 :failure. 
 *           >0 : success. The returned pll_config must be used in
 *              dt78xx_pll_config_write()
 * NOTES : This API must be called within a kernel_neon_begin()/kernel_neon_end.
 * The allocated structure must be deallocated by the caller 
 */
struct pll_config * __must_check dt7837_pll_config_init(float *freq, int ad);

/*****************************************************************************
 * Allocate and initialize an i2c potentiometer and tie it with its correspnding
 * i2c eeprom storage
 * @param dt : struct dt78xx_device *
 * @param node  : i2c child node in device tree that has pot details
 * @return : >0 : success 
 */
struct dt7837_pot * __must_check dt7837_pot_init(const struct dt78xx_device *dt,
                                                 struct device_node *node);

/*****************************************************************************
 * Update the AD calibration potentiometers based on sampling rate and gain.
 * THIS MUST NOT BE CALLED FROM INIT CODE i.e. until all subsystems have been
 * created.
 * @param dt_dev : struct dt78xx_device *
 * @return : 0=success, <0=error
 */
int dt7837_ad_cal_change(const struct dt78xx_device *dt_dev);

/*****************************************************************************
 * Update the DA calibration potentiometers based on sampling rate.
 * THIS MUST NOT BE CALLED FROM INIT CODE i.e. until all subsystems have been
 * created.
 * @param dt_dev : struct dt78xx_device *
 * @return : 0=success, <0=error
 */
int dt7837_da_cal_change(const struct dt78xx_device *dt_dev);

/*****************************************************************************
 * Write to the specified channel's wiper in the potentiometer 
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : Value, ls-byte only used
 * @return          : 0=success, <0 = error
 */
int dt7837_pot_wiper_write(const struct dt7837_pot *pot, u32 potnum, u32 val);

/*****************************************************************************
 * Read from the specified channel's wiper in the potentiometer 
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : 8-bit value returned here
 * @return          : 0=success, <0 = error
 */
int dt7837_pot_wiper_read(const struct dt7837_pot *pot, u32 potnum, u32 *val);

/*****************************************************************************
 * Copy a specified user calibration factor to the potentiometer's wiper
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param calnum    : User calibration register number
 * @return          : 0=success, <0 = error
 */
int dt7837_pot_cal2wiper(const struct dt7837_pot *pot, u32 potnum, u32 calnum);

/*****************************************************************************
 * Read the specified channel's user or factory calibration factor 
 * @param pot   
 * @param cal       : dt78xx_cal_pot_t with all members initialized
 * @return          : <0 = error, 0=success; value returned in cal
 */
int dt7837_pot_cal_read(const struct dt7837_pot *pot, dt78xx_cal_pot_t *cal);

/*****************************************************************************
 * Write the specified channel's user or factory calibration factor 
 * @param pot   
 * @param cal       : dt78xx_cal_pot_t with all members initialized
 * @return          : <0 = error, 0=success; value in cal written
 */
int dt7837_pot_cal_write(const struct dt7837_pot *pot, dt78xx_cal_pot_t *cal);

/*****************************************************************************
 * Read the board's LED debug register
 * @param dev : Pointer to device
 * @param arg : Pointer to dt78xx_led_t
 * @param len : length of buffer pointed by arg
 * @return    : <0 = error, 0=success
 */
int dt7837_ioctl_led_get(struct device *dev, void __user *arg, size_t len);

/*****************************************************************************
 * Write the board's LED debug register
 * @param dev : Pointer to device
 * @param arg : Pointer to dt78xx_led_t
 * @param len : length of buffer pointed by arg
 * @return    : <0 = error, 0=success
 */
int dt7837_ioctl_led_set(struct device *dev, void __user *arg, size_t len);

#endif
