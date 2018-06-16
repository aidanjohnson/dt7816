/*
 * Kerenel Load Module for Data Translation DT7837 data acquisition module.
 * 
 * This file implements functions common to the various subsystems.
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

/**************************************************************************
 * Data structures
 */

/**************************************************************************
 * Functions
 */

/**************************************************************************
 * Globals
 */


/****************************************************************************
 * Handler for ioctl IOCTL_LED_GET
 * This is shared by all subsystems
 * Params
 * dev : Pointer to device
 * arg : Pointer to dt78xx_led_t
 * len : length of buffer pointed by arg
 */
int dt7837_ioctl_led_get(struct device *dev, 
                         void __user *arg,
                         size_t len)
{
    uint16_t regval;
    dt78xx_led_t led_value;
    
    if (len < sizeof(led_value))
        return (-EINVAL);
    
    memset(&led_value, 0, sizeof(led_value));

    regval = dt78xx_fpga_read(dev, FPGA_REG_LED);
    led_value.state = (uint8_t) (regval & 0xff);
    led_value.mask = 0xff;   // does not apply to "get"
    if (copy_to_user(arg, (void *)&led_value, sizeof(led_value))) 
        return (-EFAULT);

    return 0;
}

/****************************************************************************
 * Handler for ioctl IOCTL_LED_SET
 * This is shared by all subsystems
 * Params
 * dev : Pointer to device
 * arg : Pointer to dt78xx_led_t
 * len : length of buffer pointed by arg
 */
int dt7837_ioctl_led_set(struct device *dev, 
                         void __user *arg, 
                         size_t len)
{
    dt78xx_led_t led_value;

    if (len < sizeof(led_value))
        return (-EINVAL);
    
    if (copy_from_user((void *)&led_value, arg, sizeof(led_value))) 
        return (-EFAULT);
    
    dt78xx_fpga_rmw(dev, FPGA_REG_LED, led_value.mask, led_value.state);
    
    return 0;
}

