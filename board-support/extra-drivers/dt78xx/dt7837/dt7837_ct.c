/*
 * Kerenel Load Module for Data Translation DT7837 data acquisition module.
 * 
 * This file implements the counter timer subsystem file operations supported
 *  by the /dev/dt7837 device
 *
 *  (C) Copyright (c) 2015 Data Translation Inc
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
#include <linux/uaccess.h>

#include "dt78xx.h"
#include "dt7837.h"
#include "dt7837_fpga.h"

/**************************************************************************
 * Macros
 */

/**************************************************************************
 * Functions
 */
static int _fopen(struct inode *, struct file *);
static int _fclose(struct inode *, struct file *);
static long _ioctl_cb(struct file *, unsigned int , unsigned long );
static ssize_t _read(struct file *, char __user *, size_t, loff_t *);
/**************************************************************************
 * Data structures
 */
struct dt7837_ct
{
    char    filename[32]; //name of file under /dev
    struct dt78xx_device *dt_dev;
    ct_gate_t gate;
};

/**************************************************************************
 * Globals
 */

//File operations supported by DT7837 counter timer subsystem
static const struct file_operations _file_ops = 
{
    .owner          = THIS_MODULE,
    .open           = _fopen,
    .release        = _fclose,
    .unlocked_ioctl = _ioctl_cb,
    .read           = _read,
};

/*****************************************************************************
 * Clear the counter interrupt status register
 * @param dev
 */
static inline void _clear_ctr_intr(struct device *dev)
{
    dt78xx_fpga_write(dev, FPGA_REG_CT_INTR_STAT, 
                           MASK_CT_INTR_STAT_OVRFLO | MASK_CT_INTR_STAT_COMPLT);    
}

/*****************************************************************************
 * Handler for open() call in user application made on virtual file
 * /dev/dt7837-ctr-tmr
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7837_ct *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = file_to_subsys(file);
     
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
 * /dev/dt7837-ctr-tmr
 */
static int _fclose(struct inode *inode, struct file *file)
{
    struct dt7837_ct *ct;
    struct device *dev;
    
    ct = file_to_subsys(file);
    dev = &ct->dt_dev->pdev->dev;
    
    //disable gate and clear interrupt status
    dt78xx_fpga_rmw(dev, FPGA_REG_CT_CTRL, MASK_CT_CTRL_GATE, 0);   
    dt78xx_fpga_write(dev, FPGA_REG_CT_CTRL, CT_CTRL_MODE_IDLE); //idle
    _clear_ctr_intr(dev); 
    //disable ouputs
    dt78xx_fpga_rmw(dev, FPGA_REG_CT_IO_CTRL, MASK_CT_IO_CTRL_OEN, 0); 
     //close the underlying daq_subsystem
    dt78xx_fclose(file);
    return (0);
}

/*****************************************************************************
 * Return the period register count when the counter is in divide-by-N mode
 * @param dev
 * @param count : user specified count 
 */
static inline uint32_t _get_period(struct device *dev)
{
    u16 regval;
    uint32_t period;
    
    regval = dt78xx_fpga_read(dev, FPGA_REG_CT_PERIOD_HI);
    period = regval << FPGA_REG_LEN_BITS;
    regval = dt78xx_fpga_read(dev, FPGA_REG_CT_PERIOD_LO);
    period |= regval;
    if (period)
    {
        period = ULONG_MAX - period;
        period += 2;
    }
    return period;
}

/*****************************************************************************
 * Set the period register with the specified count when the counter is in
 * divide-by-N mode
 * @param dev
 * @param count : user specified count 
 */
static inline void _set_period(struct device *dev, uint32_t count)
{
    count = ULONG_MAX - count;
    count += 2;
    dt78xx_fpga_write(dev, FPGA_REG_CT_PERIOD_HI, (count >> FPGA_REG_LEN_BITS));
    dt78xx_fpga_write(dev, FPGA_REG_CT_PERIOD_LO, count & U16_MAX);
}

/*****************************************************************************
 * Return the pulse register when the counter is in divide-by-N mode
 * @param dev
 */
static inline uint32_t _get_pulse(struct device *dev)
{
    u16 regval;
    uint32_t pulse;
    
    regval = dt78xx_fpga_read(dev, FPGA_REG_CT_PULSE_HI);
    pulse = regval << FPGA_REG_LEN_BITS;
    regval = dt78xx_fpga_read(dev, FPGA_REG_CT_PULSE_LO);
    pulse |= regval;
    if (pulse)
    {
        pulse = ULONG_MAX - pulse;
        pulse += 1;
    }
    return pulse;
}

/*****************************************************************************
 * Set the pulse register with the specified count when the counter is in
 * divide-by-N mode
 * @param dev
 * @param count : user specified count 
 */
static inline void _set_pulse(struct device *dev, uint32_t count)
{
    count = ULONG_MAX - count;
    count += 1;
    dt78xx_fpga_write(dev, FPGA_REG_CT_PULSE_HI, (count >> FPGA_REG_LEN_BITS));
    dt78xx_fpga_write(dev, FPGA_REG_CT_PULSE_LO, count & U16_MAX);
}

static inline int __must_check _is_ctr_active(struct device *dev)
{
    u16 reg = dt78xx_fpga_read(dev, FPGA_REG_CT_CTRL);
    return ( ((reg & MASK_CT_CTRL_MODE) != CT_CTRL_MODE_IDLE) && 
             ((reg & MASK_CT_CTRL_GATE) != CT_CTRL_MODE_GATE_OFF) );
}

/*****************************************************************************
 * Handler for ioctl IOCTL_CT_CFG_GET
 * Params
 * arg : Pointer to dt78xx_ct_config_t 
 * len : length of buffer pointed by arg
 */
static int _ct_cfg_get(struct dt7837_ct *ct, void __user *arg, size_t len)
{
    u16 regval, mode, out_pol;
    dt78xx_ct_config_t cfg;
    struct device *dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    memset(&cfg, 0, sizeof(cfg));
    dev = &ct->dt_dev->pdev->dev;
    
    //get the mode, clk source, gate
    regval = dt78xx_fpga_read(dev, FPGA_REG_CT_CTRL);
    cfg.gate = ct->gate; //NOTE : not read from register !!!
    cfg.ext_clk = (regval & CT_CTRL_MODE_CLK_EXT);
    mode = regval & MASK_CT_CTRL_MODE;
    out_pol = regval & MASK_CT_CTRL_POL;
    //get the ext clk, ext gate and divider/1shot output pins
    regval = dt78xx_fpga_read(dev,FPGA_REG_CT_IO_CTRL);
    cfg.ext_clk_din = (regval & MASK_CT_IO_CTRL_CLK) >> SHIFT_CT_IO_CTRL_CLK;
    cfg.ext_gate_din = (regval & MASK_CT_IO_CTRL_GATE) >> SHIFT_CT_IO_CTRL_GATE;
    
    if (mode == CT_CTRL_MODE_DIVIDER)
    {
        cfg.mode = ct_mode_divider;
        cfg.divider.out = (regval & MASK_CT_IO_CTRL_OUT) >> SHIFT_CT_IO_CTRL_OUT;
        cfg.divider.period = _get_period(dev);
        cfg.divider.pulse = _get_pulse(dev);
        cfg.divider.out_hi = !!out_pol;
    }
    else if (mode == CT_CTRL_MODE_1SHOT)
    {
        cfg.mode = ct_mode_1shot;
        cfg.one_shot.out = (regval & MASK_CT_IO_CTRL_OUT) >> SHIFT_CT_IO_CTRL_OUT;
        cfg.one_shot.period = _get_period(dev);
        cfg.one_shot.pulse = _get_pulse(dev);
        cfg.one_shot.retriggerable = 0;
        cfg.one_shot.out_hi = !!out_pol;
    }
    else if (mode == CT_CTRL_MODE_COUNTER)
        cfg.mode = ct_mode_counter;
    else if (mode != CT_CTRL_MODE_IDLE)
        dev_err(dev, "[%s] ERROR mode=0x%x", __func__, mode);
    
    
    if (copy_to_user(arg, (void *)&cfg, sizeof(cfg))) 
        return (-EFAULT);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_CT_CFG_SET. 
 * This configures the following FPGA registers,
 * FPGA_REG_CT_CTRL : Clock source select, mode. NOTE that the gate is disabled
 *                    and configured in response to IOCTL_START_SUBSYS
 * FPGA_REG_CT_IO_CTRL : External clock in, gate in pins selected, output
 *                       bit selected AND enabled in divider and 1shot mode
 * Params
 * arg : Pointer to dt78xx_ct_config_t 
 * len : length of buffer pointed by arg
 */
static int _ct_cfg_set(struct dt7837_ct *ct, void __user *arg, size_t len)
{
    dt78xx_ct_config_t cfg;
    u16 ctrl;
    struct device *dev = &ct->dt_dev->pdev->dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user((void *)&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    if ((cfg.mode < ct_mode_idle) || (cfg.mode > ct_mode_measure))
        return (-EINVAL);
#ifdef _WARN_
#warning Measure && retriggerable 1shot modes NOT implemented yet   
#endif
    if (cfg.mode == ct_mode_measure)
        return (-ENOSYS);
    if (cfg.mode == ct_mode_divider)
    {
        if (!cfg.divider.pulse || (cfg.divider.pulse > cfg.divider.period))
            return (-EINVAL);   
    }
    if (cfg.mode == ct_mode_1shot)
    {
        if (!cfg.one_shot.pulse || (cfg.one_shot.pulse > cfg.one_shot.period))
            return (-EINVAL);   
    }
    ct->gate = cfg.gate; //NOTE : gate is saved and updated when start command
    
    //clear everything first
    dt78xx_fpga_write(dev, FPGA_REG_CT_CTRL, CT_CTRL_MODE_IDLE); //idle
    _clear_ctr_intr(dev); //interrupts
    
    //in idle mode, disable ouputs and quit
    if (cfg.mode == ct_mode_idle)
    {
        dt78xx_fpga_rmw(dev, FPGA_REG_CT_IO_CTRL, MASK_CT_IO_CTRL_OEN, 0); 
        return 0;
    }
        
    //write the ext clk DIN configuration
    dt78xx_fpga_rmw(dev, FPGA_REG_CT_IO_CTRL, MASK_CT_IO_CTRL_CLK,
                    (cfg.ext_clk_din << SHIFT_CT_IO_CTRL_CLK));
    //write the ext gate DIN configuration
    dt78xx_fpga_rmw(dev, FPGA_REG_CT_IO_CTRL, MASK_CT_IO_CTRL_GATE,
                    (cfg.ext_gate_din << SHIFT_CT_IO_CTRL_GATE));
    
    /* Counter control register updated with the gate disabled. Start command
     * will configure the gate */
    if (cfg.mode == ct_mode_divider)
    {
        //write the pulse and period registers
        _set_pulse(dev, cfg.divider.pulse);
        _set_period(dev, cfg.divider.period);
        
        ctrl = CT_CTRL_MODE_DIVIDER; //control mode
        if (cfg.ext_clk)
            ctrl |= CT_CTRL_MODE_CLK_EXT;
        if (cfg.divider.out_hi)
            ctrl |= CT_CTRL_MODE_OUT_POL_HI;
        dt78xx_fpga_write(dev, FPGA_REG_CT_CTRL, ctrl);
        
        //write dout pin and enable output
        dt78xx_fpga_rmw(dev, FPGA_REG_CT_IO_CTRL, 
                        (MASK_CT_IO_CTRL_OEN | MASK_CT_IO_CTRL_OUT), 
                        (MASK_CT_IO_CTRL_OEN | 
                        (cfg.divider.out << SHIFT_CT_IO_CTRL_OUT)));
    }
    else if (cfg.mode == ct_mode_1shot)
    {
        //write the pulse and period registers
        _set_pulse(dev, cfg.one_shot.pulse);
        _set_period(dev, cfg.one_shot.period);
        
        ctrl = CT_CTRL_MODE_1SHOT; 
        if (cfg.ext_clk)
            ctrl |= CT_CTRL_MODE_CLK_EXT;
        if (cfg.one_shot.out_hi)
            ctrl |= CT_CTRL_MODE_OUT_POL_HI;
        dt78xx_fpga_write(dev, FPGA_REG_CT_CTRL, ctrl);
        
        //write dout pin and enable output
        dt78xx_fpga_rmw(dev, FPGA_REG_CT_IO_CTRL, 
                        (MASK_CT_IO_CTRL_OEN | MASK_CT_IO_CTRL_OUT), 
                        (MASK_CT_IO_CTRL_OEN | 
                        (cfg.one_shot.out << SHIFT_CT_IO_CTRL_OUT)));
    }
    else if (cfg.mode == ct_mode_counter)
    {
        //write the period register to 0
        dt78xx_fpga_write(dev, FPGA_REG_CT_PERIOD_HI, 0x0);
        dt78xx_fpga_write(dev, FPGA_REG_CT_PERIOD_LO, 0x0);
        //write the pulse register to 0xffffffff
        dt78xx_fpga_write(dev, FPGA_REG_CT_PULSE_HI, U16_MAX);
        dt78xx_fpga_write(dev, FPGA_REG_CT_PULSE_LO, U16_MAX);

        ctrl = CT_CTRL_MODE_COUNTER; //control mode
        if (cfg.ext_clk)
            ctrl |= CT_CTRL_MODE_CLK_EXT;
        dt78xx_fpga_write(dev, FPGA_REG_CT_CTRL, ctrl);
        
        dt78xx_fpga_rmw(dev, FPGA_REG_CT_IO_CTRL, MASK_CT_IO_CTRL_OEN, 0); 
    }
    

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_START_SUBSYS. This configures the gate selection
 * in FPGA_REG_CT_CTRL to the setting saved by IOCTL_CT_CFG_SET
 * Params
 * arg : unused 
 * len : unused
 */
static int _ct_start(struct dt7837_ct *ct, void __user *arg, int len)
{
    struct device *dev;
    u16 reg;
    
    dev = &ct->dt_dev->pdev->dev;
    //if subsystem is idle, then do return error
    reg = dt78xx_fpga_read(dev, FPGA_REG_CT_CTRL) & MASK_CT_CTRL_MODE;
    if (reg == CT_CTRL_MODE_IDLE)
        return -EREMOTEIO;
    //else configure the gate based on the saved gate info
    switch (ct->gate)
    {
        case ct_gate_ext_hi:
            reg = CT_CTRL_MODE_GATE_EXT;
            break;

        case ct_gate_ext_lo:
            reg = CT_CTRL_MODE_GATE_EXT_INV;
            break;

        case ct_gate_none:
        default:
            reg = CT_CTRL_MODE_GATE_SW;
            break;
    }
    dt78xx_fpga_rmw(dev, FPGA_REG_CT_CTRL, MASK_CT_CTRL_GATE, reg); 

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_STOP_SUBSYS. This configures the gate selection
 * in FPGA_REG_CT_CTRL to disabled thereby stopping the counter. 
 * The gate setting, saved by IOCTL_CT_CFG_SET, is restored in 
 * IOCTL_START_SUBSYS 
 * Params
 * arg : unused 
 * len : unused
 */
static int _ct_stop(struct dt7837_ct *ct, void __user *arg, int len)
{
    struct device *dev;
 
    dev = &ct->dt_dev->pdev->dev;
    //disable gate and clear interrupt status
    dt78xx_fpga_rmw(dev, FPGA_REG_CT_CTRL, MASK_CT_CTRL_GATE, 0);   
    _clear_ctr_intr(dev);
    return 0;
}

/*****************************************************************************
 * Main IOCTL handler 
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7837_ct *ctr;
    long retval = -EBADRQC;   /*56 Invalid request code */
    size_t len = _IOC_SIZE(cmd);
    
    ctr = (struct dt7837_ct *)file_to_subsys(file);
    if (unlikely(!ctr))
        return -ENODEV;
    
    dev_lock(dt_dev);
    
    switch (cmd)
    {
        case IOCTL_CT_CFG_GET :
            retval = _ct_cfg_get(ctr, (void __user *)arg, len); 
            break;
            
        case IOCTL_CT_CFG_SET :
            if (_is_ctr_active(&ctr->dt_dev->pdev->dev))
                retval = -EALREADY;
            else
                retval = _ct_cfg_set(ctr, (void __user *)arg, len); 
            break;
        
        case IOCTL_ARM_SUBSYS:  //Ignore and don't return error
            retval = 0;
            break;
            
        case IOCTL_START_SUBSYS:
            if (_is_ctr_active(&ctr->dt_dev->pdev->dev))
                retval = -EALREADY;
            else
                retval = _ct_start(ctr, (void __user *)arg, len); 
            break;
        
        case IOCTL_STOP_SUBSYS:
            retval = _ct_stop(ctr, (void __user *)arg, len);
            break;
            
        case IOCTL_LED_GET :
            retval = dt7837_ioctl_led_get(dev, (void __user *)arg, len);
            break;

        case IOCTL_LED_SET :
            retval = dt7837_ioctl_led_set(dev, (void __user *)arg, len);
            break;
            
        default :
            dev_err(dev, "[%s] IOCTL ERROR cmd=0x%x (nr=%d len=%d dir=%d)",
                     ctr->filename, cmd, _IOC_NR(cmd), len, _IOC_DIR(cmd));
            retval = -EBADRQC;   /*56 Invalid request code */
    }
    dev_unlock(dt_dev);
    return retval;
}

/*****************************************************************************
 * Create the board specific timer counter subsystem and register a file handle
 */
int dt7837_ct_subsystem_create(struct daq_subsystem *daq)
{
    int err;
    struct dt7837_ct *subsys;
    struct device *dev = &daq->dt_dev->pdev->dev;

    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7837_ct), GFP_KERNEL);
    if (!subsys)
    {
        return -ENOMEM;
    }
    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    subsys->dt_dev = daq->dt_dev;
    subsys->gate = ct_gate_none;
    err = misc_register(&daq->miscdev);
    if (!err)
    {
        err = dev_set_drvdata(daq->miscdev.this_device, subsys);
    }
    if (err)
    {
        daq->miscdev.name = NULL;
        devm_kfree(dev, subsys);
    }
    return (err);
}

/*****************************************************************************
 * Read the 32-bit counter register. This returns a value only in counter mode;
 * in other modes neither data nor any errors are returned. The 32-bit count
 * from registers FPGA_REG_CT_COUNT_HI/LO are returned if the counter has not
 * overflowed. If the counter has oveflowed, returns -ETIME
 * @param file
 * @param buffer
 * @param count
 * @param offset
 * @return >=0 : number of bytes read, <0 : error
 */
static ssize_t _read(struct file *file, char __user *buffer, size_t bufflen, 
                     loff_t *offset)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7837_ct *subsys;
    ssize_t result = 0;   
    u16 mode;
    uint32_t count;
    
    subsys = (struct dt7837_ct *)file_to_subsys(file);
    if (unlikely(!subsys))
        return -ENODEV;
    
    dev_lock(dt_dev);
 
    mode = dt78xx_fpga_read(dev, FPGA_REG_CT_CTRL) & MASK_CT_CTRL_MODE;
    if (mode == CT_CTRL_MODE_COUNTER)
    {
        if (bufflen < sizeof(uint32_t))
            result = -EINVAL;
        else if (dt78xx_fpga_read(dev, FPGA_REG_CT_INTR_STAT) & MASK_CT_INTR_STAT_OVRFLO)
            result = -ETIME;
        else
        {
            count = dt78xx_fpga_read(dev, FPGA_REG_CT_COUNT_LO);
            count |= (dt78xx_fpga_read(dev, FPGA_REG_CT_COUNT_HI)<<FPGA_REG_LEN_BITS);
            if (copy_to_user((void*)buffer, (const void *)&count, sizeof(count))) 
                result = -EFAULT;
            else
                result = sizeof(count);
        }
    }
    dev_unlock(dt_dev);
    
    return result;
}
