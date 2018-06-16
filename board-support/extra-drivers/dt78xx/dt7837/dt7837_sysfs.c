/*
 * sysfs files for DT7837
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
#include "dt7837.h"
#include "dt7837_fpga.h"

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
#ifdef _AD_CLK_DEBUG_
static ssize_t _ad_clk_write(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count);
#endif
#ifdef _I2C_POT_DEBUG_
static ssize_t _sysfs_ad_offset_read(struct device *dev, struct device_attribute *attr, 
                          char *buf);
static ssize_t _sysfs_ad_gain_read(struct device *dev, struct device_attribute *attr, 
                          char *buf);
static ssize_t _sysfs_ad_offset_write(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count);
int i2c_pot_read(struct i2c_client *client, u8 *buf, int len);
int i2c_pot_reg_write(struct i2c_client *client, u8 reg, u8 val);
#endif
static int _parse_addr_val(const char *buf, u32 *addr, u32 *val);

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
 * /sys/devices/ocp.2/....../DT7837/fpga
 */
static const DEVICE_ATTR(fpga, S_IRUGO | S_IWUGO,
                   _sysfs_fpga_read, _sysfs_fpga_write);
#ifdef _AD_CLK_DEBUG_
static const DEVICE_ATTR(ad_clk, S_IWUGO, NULL, _ad_clk_write);
#endif
#ifdef _I2C_POT_DEBUG_    
static const DEVICE_ATTR(ad_offset, S_IRUGO | S_IWUGO,
                        _sysfs_ad_offset_read, NULL);
static const DEVICE_ATTR(ad_gain, S_IRUGO | S_IWUGO,
                        _sysfs_ad_gain_read, NULL);
#endif
/******************************************************************************
 * Attribute list for DT7837 to be added to DT78xx's attribute list
 */
#define ATTR_LIST(x)    & dev_attr_##x.attr
static const struct attribute *g_dt7837_attr[] = 
{
    ATTR_LIST(fpga),
#ifdef _I2C_POT_DEBUG_    
    ATTR_LIST(ad_offset),
    ATTR_LIST(ad_gain),
#endif
#ifdef _AD_CLK_DEBUG_
    ATTR_LIST(ad_clk),
#endif
    NULL //mandatory terminator
};

/******************************************************************************
 * We want to add
 * this device's attributes to that group so that all attributes are under
 * the same directory under /sys/devices/ocp.2/....../DT7837/
 */
static struct attribute_group g_dt7837_attr_group = 
{
    .attrs = (struct attribute **)g_dt7837_attr,
};
/******************************************************************************
 * Create DT7837 sysfs files under /sys/devices/ocp.2/....../DT7837
 * @param pdev
 * @return 0=success, <0=failure
 */
int dt7837_sysfs_create(struct platform_device *pdev)
{
    int err = 0;
    
    g_dt7837_attr_group.name=dev_driver_string(&pdev->dev);
    err = sysfs_merge_group(&pdev->dev.kobj, &g_dt7837_attr_group);
    if (err)
    {
        dev_err(&pdev->dev, "[%s] ERROR %d\n", __func__, err);
    }
    return (err);
}

/******************************************************************************
 * Write to dev_attr_fpga
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
#ifdef _AD_CLK_DEBUG_
/*****************************************************************************
 * Prorams the AD PLL with the specified floating point clock rate in Hz.
 * Caveat : Since the kernel does not support either atof() or sprintf() with %f
 * the input and output will be the hex representation of the floating point
 * value. Use the following web pages to convert between flaoting to hex and
 * vice versa, 
 * http://babbage.cs.qc.cuny.edu/IEEE-754.old/Decimal.html
 * http://babbage.cs.qc.cuny.edu/IEEE-754.old/32bit.html
 * For example, to program the PLL to 1000.0 Hz, use the hex representation
 *  echo 447A0000 > ad_clk
 * @param dev
 * @param attr
 * @param buf
 * @param count
 * @return count
 */
static ssize_t _ad_clk_write(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    u32 rate;
    struct pll_config *cfg;

    if (count <= 0)
        return count;
    
    rate = simple_strtoul(buf, NULL, 16);  
    kernel_neon_begin();
    cfg = dt7837_ad_pll_config_init((float *)&rate);
    kernel_neon_end();
    if (!IS_ERR_OR_NULL(cfg))
    {
        dt7837_pll_config_write(dev, cfg);
        kfree(cfg);
    }
    return (count);
}
#endif

#ifdef _I2C_POT_DEBUG_
/*****************************************************************************
 * Helper function to read all registers in the given potentiometer and return
 * formatted values in the buffer
 * @param client
 * @param buf
 * @return 
 */
static ssize_t _sysfs_pot_read(struct i2c_client *client, char *buf)
{
    size_t len=0;
    u8 val[19];
    len += scnprintf(buf+len, PAGE_SIZE-len, "%s @ %#x\n",
                     client->name, client->addr);
    if (i2c_pot_read(client, val, sizeof(val)) == sizeof(val))
    {
        int i;
        //first 4 values are wipers
        for (i=0; i<4; ++i)
            len += scnprintf(buf+len, PAGE_SIZE-len, "WR%d   %#02x\n", i, val[i]);
        //next 15 values are non-volatile registers
        for (i=0; i<15; ++i)
            len += scnprintf(buf+len, PAGE_SIZE-len, "%#x   %#02x\n", i, val[4+i]);
    } 
    return len;
}

/*****************************************************************************
 * Read all registers in the AD offset pot
 * @param dev
 * @param attr
 * @param buf
 * @return 
 */
static ssize_t _sysfs_ad_offset_read(struct device *dev, struct device_attribute *attr, 
                          char *buf)
{
    size_t len=0;
    struct dt78xx_device *dt_dev;
    dt_dev = dev_get_drvdata(dev);
    
    dev_lock(dt_dev);
    dev_unlock(dt_dev);
    return (len);
}

/*****************************************************************************
 * Read all registers in the AD gain pot
 * @param dev
 * @param attr
 * @param buf
 * @return 
 */
static ssize_t _sysfs_ad_gain_read(struct device *dev, struct device_attribute *attr, 
                          char *buf)
{
    size_t len=0;
    struct dt78xx_device *dt_dev;
    struct list_head *pos;
    struct daq_subsystem *daq = NULL;
    dt_dev = dev_get_drvdata(dev);
    
    dev_lock(dt_dev);
    list_for_each(pos, &dt_dev->daq_list)
    {
        daq = list_entry(pos, struct daq_subsystem, daq_list);
        if (strstr(daq->node->name,"ain")) //Analog in
            break;
    }
    //get_gain_pot(daq);    
    dev_unlock(dt_dev);
    return (len);
}
******************************************************************************
 * Write to ad offset pot
 * Usage :
 *  echo  reg=value > /sys/devices/.../ad_offset
 *  The reg=value parameters specify the register that is written with the
 *  value. Value is always 8-bit hex. The potentiometer register can either be
 *  a hex value between 0 and e that identify the non-vl=olatile registers, or
 *  the reg can be one of wr0|wr1|wr2|wr3 to slect the volatile wiper registers
 */
static ssize_t _sysfs_ad_offset_write(struct device *dev, 
                                      struct device_attribute *attr,
                                       const char *buf, size_t count)
{
    u32 reg, data;
    struct dt78xx_device *dt_dev;
    struct dt7837_priv *priv;
    
    if (count < 3) //at least two hex digits separated by one comma
        return count;
    
    dt_dev = dev_get_drvdata(dev);
    priv = dt_dev->priv;

    if ((*buf == 'w') || (*buf == 'W'))
    {
        int i, pot;
        pot = (buf[2]-'0');
        for (i=3; (i<count)&&(buf[i] != '='); ++i);//find the = separator
        if (i==count) //no = found
            return count;
        if (kstrtou32(&buf[++i], 16, &data)) //0 is success
            return count; 
        
        dev_lock(dt_dev);
        i = dt7837_i2c_pot_write(priv->ad_pot.offset, pot, pot_wiper,(u8)data);
        if (i)
            dev_err(dev, "ERROR dt7837_i2c_pot_write\n");
        dev_unlock(dt_dev);

        return (count);
    }
    
    if (_parse_addr_val(buf, &reg, &data))
        return count;

    dev_lock(dt_dev);
    if (i2c_pot_reg_write(priv->ad_pot.offset, (u8)reg, (u8)data))
        dev_err(dev, "[%s] i2c_pot_reg_write\n", __func__);
    dev_unlock(dt_dev);
    
    return (count);
}
#endif
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
