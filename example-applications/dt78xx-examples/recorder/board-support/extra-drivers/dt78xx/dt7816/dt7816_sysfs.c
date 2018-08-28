/*
 * sysfs files for DT7816
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
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <asm/neon.h>
#include <linux/slab.h>

#include "dt78xx.h"
#include "dt7816.h"
#include "dt7816_fpga.h"

/**************************************************************************/


/**************************************************************************
 * Data structures
 */


/**************************************************************************
 * Functions
 */
static ssize_t _sysfs_fpga_read(struct device *dev, struct device_attribute *attr, 
                          char *buf);
static ssize_t _sysfs_fpga_write(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count);
static int _parse_addr_val(const char *buf, u32 *addr, u32 *val);
static ssize_t _ad_gain_pot_read(struct device *dev, struct device_attribute *attr, 
                          char *buf);
static ssize_t _ad_gain_pot_write(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count);
extern u32 sysfs_ad_gain_pot_read(const struct dt78xx_device *);
extern void sysfs_ad_gain_pot_write(const struct dt78xx_device *, u32 val);

/**************************************************************************
 * Globals
 */

#undef FPGA_REG
#define FPGA_REG(a,b)   {#a, b},
static struct
{
    const char *name;
    u32    offset;
} g_fpga_regs[]=
{
    FPGA_REG_TAB
    {NULL, 0}
};

/******************************************************************************
 * Device attribute to read/write registers in the FPGA
 * File :
 * /sys/devices/ocp.2/....../DT7816/fpga
 */
static const DEVICE_ATTR(fpga, S_IRUGO | S_IWUGO,
                   _sysfs_fpga_read, _sysfs_fpga_write);

/******************************************************************************
 * Device attribute to read/write ADC gain potentiometer's wiper
 */
static const DEVICE_ATTR(ad_gain_pot, S_IRUGO | S_IWUGO,
                   _ad_gain_pot_read, _ad_gain_pot_write);

/******************************************************************************
 * Attribute list for DT7816 to be added to DT78xx's attribute list
 */
#define ATTR_LIST(x)    & dev_attr_##x.attr
static const struct attribute *g_dt7816_attr[] = 
{
    ATTR_LIST(fpga),
    ATTR_LIST(ad_gain_pot),
    NULL //mandatory terminator
};

/******************************************************************************
 * We want to add
 * this device's attributes to that group so that all attributes are under
 * the same directory under /sys/devices/ocp.2/....../DT7816/
 */
static struct attribute_group g_dt7816_attr_group = 
{
    .attrs = (struct attribute **)g_dt7816_attr,
};
/******************************************************************************
 * Create DT7816 sysfs files under /sys/devices/ocp.2/....../DT7816
 * @param pdev
 * @return 0=success, <0=failure
 */
int dt7816_sysfs_create(struct platform_device *pdev)
{
    int err = 0;
    
    g_dt7816_attr_group.name=dev_driver_string(&pdev->dev);
    err = sysfs_merge_group(&pdev->dev.kobj, &g_dt7816_attr_group);
    if (err)
    {
        dev_err(&pdev->dev, "[%s] ERROR %d\n", __func__, err);
    }
    return (err);
}

/******************************************************************************
 * Write to FPGA register
 * Usage :
 *  echo  123=55 > /sys/devices/ocp.2/.../fpga
 *  The <addr>=<data> parameters are two hex values separated with equal
 */
static ssize_t _sysfs_fpga_write(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    u32 offset, data;
    struct dt78xx_device *dt_dev;
    
    if (count <= 0)
        return count;
    if (_parse_addr_val(buf, &offset, &data))
        return count;
    
    dt_dev = dev_get_drvdata(dev);

    dev_lock(dt_dev);
    dt78xx_fpga_write(dev, offset, (u16)data);
    dev_unlock(dt_dev);
    
    return (count);
}

/*****************************************************************************
 * Read all FPGA registers
 * @param dev   
 * @param attr
 * @param buf
 * @return : #of bytes written to buf
 */
static ssize_t _sysfs_fpga_read(struct device *dev, struct device_attribute *attr, 
                          char *buf)
{
    size_t len=0;
    u32 data;
    int i,j;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    
    dev_lock(dt_dev);
  
    //board fpga registers 
    for (i=0; (i < ARRAY_SIZE(g_fpga_regs)&&(len<PAGE_SIZE));  ++i)
    {
        if (g_fpga_regs[i].name)
        {
            data = dt78xx_fpga_read(dev, g_fpga_regs[i].offset);
			j = len;
            len += scnprintf(buf+len, PAGE_SIZE-len, "%04x %s",
                             g_fpga_regs[i].offset, g_fpga_regs[i].name);
			j = 20 -(len -j);
			memset(buf+len, ' ', j);
			len += j;
            len += scnprintf(buf+len, PAGE_SIZE-len, "%04x\n", data);
        }
    }
    
    dev_unlock(dt_dev);
    
    return (len);
}

static int _parse_addr_val(const char *buf, u32 *addr, u32 *val)
{
    char *term;
    *addr = simple_strtoul(buf, &term, 16);
    if (term == NULL)
        return -EINVAL;
    if (*term != '=')
        return -EINVAL;
    ++term; //point to char after =
    *val = simple_strtoul(term, NULL, 16);
    return 0;
}

/******************************************************************************
 * Write to AD gain pot's wiper
 * Usage :
 *  echo  number > /sys/devices/ocp.2/.../ad_gain
 *  The number is in decimal
 */
static ssize_t _ad_gain_pot_write(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    u32 val;
    struct dt78xx_device *dt_dev;
    if (count <= 0)
        return count;
    val = simple_strtoul(buf, NULL, 10);
    dt_dev = dev_get_drvdata(dev);

    dev_lock(dt_dev);
    sysfs_ad_gain_pot_write(dt_dev, val);
    dev_unlock(dt_dev);
    
    return (count);
}

/*****************************************************************************
 * Read AD gain pot's wiper
 * @param dev   
 * @param attr
 * @param buf
 * @return : #of bytes written to buf
 */
static ssize_t _ad_gain_pot_read(struct device *dev, struct device_attribute *attr, 
                          char *buf)
{
    size_t len;
    u32 val;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    
    dev_lock(dt_dev);
    val = sysfs_ad_gain_pot_read(dt_dev);
    dev_unlock(dt_dev);
    len = scnprintf(buf, PAGE_SIZE, "%d (%#x)\n", val, val);
    return (len);
}

