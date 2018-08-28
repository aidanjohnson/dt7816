/*
 * Kerenel Load Module for Data Translation DT7816 data acquisition module.
 * 
 * This file is the starting point of the KLM and implements the .probe
 * and .remove callbacks. This KLM works in conjunction with the base KLM
 * dt78xx.ko and uses APIs exported from it. 
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
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <../arch/arm/include/asm/delay.h> //udelay() for ARM

#include "dt78xx.h"
#include "dt7816.h"
#include "dt7816_version.h"
#include "dt7816_fpga.h"
#ifndef CONFIG_OF
#error CONFIG_OF must be defined for Device Tree
#endif

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

/**************************************************************************
* Driver remove
*/
static int dt7816_remove(struct platform_device *pdev)
{
    struct dt78xx_device *dt_dev;    
    struct list_head *pos;
    
    dt_dev = platform_get_drvdata(pdev);
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);  
#ifdef _WARN_
#warning  TBD free subsystems 
#endif
    }    
    dt78xx_free(pdev);
    return 0;
}

/**************************************************************************
* Driver probe
*/
static int dt7816_probe(struct platform_device *pdev)
{
    int err = 0;
    struct dt78xx_device *dt_dev;   
    struct list_head *pos;
    u16 tmp;
    
    //Base driver parses the device tree and allocates all daq subsystems with
    //common data structures
    err = dt78xx_init(pdev);
    if (err)
    {
        pr_err("ERROR %d dt78xx_init\n", err);
        return err;
    }
   
    dt_dev = platform_get_drvdata(pdev);
    
    /*
     * Initialization that affects all subsystems. (a) Turn on internal 96MHz
     * reference clock and wait for it to settle
     */
    dt78xx_fpga_write(&dt_dev->pdev->dev, FPGA_REG_IO_CTRL, 0);
#ifdef _WARN_
#warning  FIX 96MHz clock valid delay 
#endif
    udelay(50); 
    tmp = dt78xx_fpga_read(&dt_dev->pdev->dev, FPGA_REG_INTR_STAT);
    err = ((tmp & MASK_INTR_STAT_REF_CLK_OK)==MASK_INTR_STAT_REF_CLK_OK)?0:-EIO;
    if (err)
        dev_err(&pdev->dev, "[%s] ERROR %d 96MHz ref clk fail\n", __func__,err);
            
    /*
     * Each child node in the device tree identifies either a data acquisition
     * subsystem or a functional subsystem. The node names are used to 
     * diffrentiate them and create specific device files and data structures
     */
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);  
        if (strstr(daq->node->name,"din")) //Digital In
            err = dt7816_din_subsystem_create(daq);
        else if (strstr(daq->node->name,"dout")) //Digital out
            err = dt7816_dout_subsystem_create(daq);
        else if (strstr(daq->node->name,"ctr-tmr")) //counter timer
            err = dt7816_ct_subsystem_create(daq);
        else if (strstr(daq->node->name,"ain")) //Analog in
            err = dt7816_ain_subsystem_create(daq);
        else if (strstr(daq->node->name,"stream-in")) //input stream
            err = dt7816_stream_in_create(daq);
        else if (strstr(daq->node->name,"measure")) //measure counter
            err = dt7816_measure_subsystem_create(daq);
        else if (strstr(daq->node->name,"tach")) //tachometer
            err = dt7816_tach_subsystem_create(daq);
        else if (strstr(daq->node->name, "aout"))     //Analog out
            err = dt7816_aout_subsystem_create(daq);
        else if (strstr(daq->node->name,"stream-out")) //output stream
            err = dt7816_stream_out_create(daq);
        else
            err = -ENODEV;
        //Add additional subsystems here
        if (err)
        {
            dev_err(&pdev->dev, "[%s] ERROR %d %s\n", __func__,err,daq->node->name);
            // on error, don't bail out. This allows the sysfs i/f for debug
            //break;
        }
    }
    
    /*
     * In case of error, the module is still loaded and sysfs functional, so
     * that the fpga can be accessed and the board debugged
     */
    dt7816_sysfs_create(pdev);
    
    if (!err)
        dev_info(&pdev->dev , "[%s] version %s OK\n", __func__, DT7816_VERSION);
    return (0);
}

/*
 * This matches the "compatible" binding in the device tree for the GPMC
 * child associated with the FPGA
 */
static const struct of_device_id dt7816_of_match[] = 
{
    { .compatible = "dt7816", },
    { },
};
MODULE_DEVICE_TABLE(of, dt7816_of_match);

static struct platform_driver dt7816_driver = 
{
    .probe      = dt7816_probe,
    .remove     = dt7816_remove,
    .driver     = 
    {
        .name   = "dt7816",
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(dt7816_of_match),
    },
};

module_platform_driver(dt7816_driver);

/*
 * Macros sets license, author and description
 */
MODULE_AUTHOR("(c) 2014 Data Translation");
MODULE_DESCRIPTION("DT7816 board driver");
MODULE_LICENSE("GPL"); /*REQUIRED */

MODULE_VERSION (DT7816_VERSION);
