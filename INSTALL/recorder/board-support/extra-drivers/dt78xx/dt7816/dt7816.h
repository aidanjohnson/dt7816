#ifndef _DT7816_H_
#define _DT7816_H_
/*
 *  Miscelleneous definitions for DT7816 
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
#include "dt78xx.h"
#include "dt78xx_ioctl.h"

#define REF_CLK_HZ             (48000000.0f)   
#define DEFAULT_CLK_RATE_HZ    (100000.0f)

struct pll_config;
struct dt7816_pot;


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
int dt7816_aout_subsystem_create(struct daq_subsystem *daq);
int dt7816_ain_subsystem_create(struct daq_subsystem *daq);
int dt7816_din_subsystem_create(struct daq_subsystem *daq);
int dt7816_dout_subsystem_create(struct daq_subsystem *daq);
int dt7816_stream_in_create(struct daq_subsystem *daq);
int dt7816_stream_out_create(struct daq_subsystem *daq);
int dt7816_ct_subsystem_create(struct daq_subsystem *daq);
int dt7816_measure_subsystem_create(struct daq_subsystem *daq);
int dt7816_tach_subsystem_create(struct daq_subsystem *daq);

/*****************************************************************************
 * Cleanup/destroy individual subsystems. These are called from the driver's 
 * remove() function. If the subsystem allocated any memory, it should be
 * deallocated with *care* !!
 * @param daq   :  subsystem resources
 */
void dt7816_ain_subsystem_free(struct daq_subsystem *daq);

/*****************************************************************************
 * Create DT7816 specific sysfs files for test and debug
 * @param pdev  : platform device pointer
 * @return      : 0=success, <1=failure 
 */
int dt7816_sysfs_create(struct platform_device *pdev);

/*****************************************************************************
 * Read the board's LED debug register
 * @param dev : Pointer to device
 * @param arg : Pointer to dt78xx_led_t
 * @param len : length of buffer pointed by arg
 * @return    : <0 = error, 0=success
 */
int dt7816_ioctl_led_get(struct device *dev, void __user *arg, size_t len);

/*****************************************************************************
 * Write the board's LED debug register
 * @param dev : Pointer to device
 * @param arg : Pointer to dt78xx_led_t
 * @param len : length of buffer pointed by arg
 * @return    : <0 = error, 0=success
 */
int dt7816_ioctl_led_set(struct device *dev, void __user *arg, size_t len);

/*****************************************************************************
 * Returns PLL configuration for the specified sampling rate
 * @param freq : Pointer to desired sampling rate. On success, the actual rate
 *               is returned here
 * @parm min : minumum clock
 * @parm max : maxmum clock
 * @return : 32-bit non-zero divisor on success, 0 if specified rate is invalid
 * NOTES : This API must be called within a kernel_neon_begin()/kernel_neon_end.
 * The allocated structure must be deallocated by the caller 
 */
uint32_t dt7816_clk_divisor(float *freq, float min, float max);

#endif
