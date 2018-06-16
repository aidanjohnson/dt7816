/*
 * Kerenel Load Module for Data Translation DT7837 data acquisition module.
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
#include "dt7837_fpga.h"

#include "dt78xx.h"
#include "dt7837.h"
#include "dt7837_version.h"
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
static int dt7837_remove(struct platform_device *pdev)
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
static int dt7837_probe(struct platform_device *pdev)
{
    int err = 0;
    struct dt78xx_device *dt_dev;   
    struct list_head *pos;
    
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
     * Each child node in the device tree identifies either a data acquisition
     * subsystem or a functional subsystem. The node names are used to 
     * diffrentiate them and create specific device files and data structures
     */
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);  
        if (strstr(daq->node->name, "aout"))     //Analog out
            err = dt7837_aout_subsystem_create(daq);
        else if (strstr(daq->node->name,"ain")) //Analog in
            err = dt7837_ain_subsystem_create(daq);
        else if (strstr(daq->node->name,"din")) //Digital In
            err = dt7837_din_subsystem_create(daq);
        else if (strstr(daq->node->name,"dout")) //Digital out
            err = dt7837_dout_subsystem_create(daq);
        else if (strstr(daq->node->name,"stream-in")) //input stream
            err = dt7837_stream_in_create(daq);
        else if (strstr(daq->node->name,"stream-out")) //input stream
            err = dt7837_stream_out_create(daq);
        else if (strstr(daq->node->name,"ctr-tmr")) //counter timer
            err = dt7837_ct_subsystem_create(daq);
        else if (strstr(daq->node->name,"measure")) //measure counter
            err = dt7837_measure_subsystem_create(daq);
        else if (strstr(daq->node->name,"tach")) //tachometer
            err = dt7837_tach_subsystem_create(daq);
        else
            err = -ENODEV;
        //Add additional subsystems here
        if (err)
        {
            dev_err(&pdev->dev, "[%s] ERROR %d %s\n", __func__,err,daq->node->name);
            // on error, don't bail out. This allows the base board to 
            // come up without any daughter cards.
            //break;
        }
    }
    
    /*
     * In case of error, the module is still loaded and sysfs functional, so
     * that the fpga can be accessed and the board debugged
     */
    dt7837_sysfs_create(pdev);
    
    if (!err)
        dev_info(&pdev->dev , "[%s] version %s OK\n", __func__, DT7837_VERSION);
    return (0);
}

/*
 * This matches the "compatible" binding in the device tree for the GPMC
 * child associated with the FPGA
 */
static const struct of_device_id dt7837_of_match[] = 
{
    { .compatible = "dt7837", },
    { },
};
MODULE_DEVICE_TABLE(of, dt7837_of_match);

static struct platform_driver dt7837_driver = 
{
    .probe      = dt7837_probe,
    .remove     = dt7837_remove,
    .driver     = 
    {
        .name   = "dt7837",
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(dt7837_of_match),
    },
};

module_platform_driver(dt7837_driver);

/*
 * Macros sets license, author and description
 */
MODULE_AUTHOR("(c) 2014 Data Translation");
MODULE_DESCRIPTION("DT7837 board driver");
MODULE_LICENSE("GPL"); /*REQUIRED */

MODULE_VERSION (DT7837_VERSION);
