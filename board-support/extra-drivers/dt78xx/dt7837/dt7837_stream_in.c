/*
 * Kerenel Load Module for Data Translation DT7837 data acquisition module.
 * 
 * This file implements the stream operations supported by the
 * /dev/dt7837_stream_in virtual file
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
#include <asm/neon.h>

#include "dt78xx.h"
#include "dt7837.h"
#include "dt7837_fpga.h"

/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 * Data structures
 **************************************************************************/

//Data structure specific to the DT7837 stream. 
struct dt7837_stream_in
{
    char    filename[32]; //name of file under /dev
    float   clock;        //sample clock rate
    struct dt78xx_device *dt_dev;
};

/**************************************************************************
 * Functions
 **************************************************************************/
static long _ioctl_cb(struct file *file, unsigned int cmd, 
                             unsigned long arg);
static ssize_t _aio_read(struct kiocb *iocb, const struct iovec *iov,
                               unsigned long nr_segs, loff_t o);
static int _fopen(struct inode *inode, struct file *file);
static int _fclose(struct inode *inode, struct file *file);
static int _fasync (int, struct file *, int);

/**************************************************************************
 * Globals
 **************************************************************************/

/**************************************************************************
 * File operations supported by DT7837 stream
 */
static const struct file_operations _file_ops = 
{
    .owner          = THIS_MODULE,
    .open           = _fopen,
    .release        = _fclose,
    .unlocked_ioctl = _ioctl_cb,
    .aio_read       = _aio_read,
    .fasync         = _fasync,
};
    
/*****************************************************************************
 * Handler for open() call in user application made on virtual file
 * /dev/dt7837-stream*
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7837_stream_in *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7837_stream_in *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
     
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
 * /dev/dt7837-stream*
 */
static int _fclose(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7837_stream_in *subsys;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7837_stream_in *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    
    //clear I/O Operation Control Register bit InputArm
    dt78xx_fpga_rmw(&dt_dev->pdev->dev, FPGA_REG_IO_CTRL, MASK_IO_CTRL_IN_ARM, 0);
    dt78xx_edma_stop(file);
     
    //close the underlying daq_subsystem
    dt78xx_fclose(file);
    return (0);
}

/*****************************************************************************
 * Handler for ioctl IOCTL_TRIG_CFG_GET
 */
static int _start_trig_cfg_get(struct dt7837_stream_in *stream, void __user *arg, 
                         size_t len)
{
    dt78xx_trig_config_t trig_cfg;
    uint16_t trig_src, tmp;
    struct device *dev;
    
    if (len < sizeof(trig_cfg))
        return (-EINVAL);
    
    memset(&trig_cfg, 0, sizeof(trig_cfg));
    dev = &stream->dt_dev->pdev->dev;
    trig_src = dt78xx_fpga_read(dev, FPGA_REG_TRIG_CTRL);
    
    trig_src &= MASK_TRIG_CTRL_IN_START;
    trig_src >>= SHIFT_TRIG_CTRL_IN_START;
    //analog threshold either rising or falling
    if ((trig_src == TRIG_CTRL_THOLD_FALLING) ||
        (trig_src == TRIG_CTRL_THOLD_RISING))
    {
        trig_cfg.src = trig_src_threshold;
        if (trig_src == TRIG_CTRL_THOLD_RISING)
            trig_cfg.src_cfg.threshold.edge_rising = 1;
        trig_cfg.src_cfg.threshold.ain = 
            dt78xx_fpga_read(dev, FPGA_REG_THOLD_TRIG_SEL) & MASK_THOLD_TRIG_SEL;
        tmp = dt78xx_fpga_read(dev, FPGA_REG_THOLD_TRIG_LVL) & MASK_THOLD_TRIG_LVL;
        trig_cfg.src_cfg.threshold.level = threshold_2_twos_comp(tmp);
    }
    //external rising or falling
    else if ((trig_src == TRIG_CTRL_EXT_FALLING) ||
             (trig_src == TRIG_CTRL_EXT_RISING))
    {
        trig_cfg.src = trig_src_ext;
        if (trig_src == TRIG_CTRL_EXT_RISING)
            trig_cfg.src_cfg.ext.edge_rising = 1;
        tmp = dt78xx_fpga_read(dev, FPGA_REG_IN_CTRL) & MASK_IN_CTRL_DIN_TRIG;
        trig_cfg.src_cfg.ext.din = (tmp >> SHIFT_IN_CTRL_DIN_TRIG);
    }
    
    if (copy_to_user(arg, (void *)&trig_cfg, sizeof(trig_cfg))) 
        return (-EFAULT);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_TRIG_CFG_SET
 * Params :
 * arg : Pointer to ioctl_trig_config_t with members initialized
 * len : length of buffer pointed by arg
 */
static int _start_trig_cfg_set(struct dt7837_stream_in *stream, void __user *arg, 
                                size_t len)
{
    dt78xx_trig_config_t cfg;
    uint16_t src, tmp;
    struct device *dev;
    
    dev = &stream->dt_dev->pdev->dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user(&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    switch (cfg.src)
    {
        case trig_src_threshold:
            //AIN selection, must be 0-3 both inclusive
            if (cfg.src_cfg.threshold.ain > NUM_AIN-1)
                return (-EINVAL);
            tmp = twos_comp_2_threshold(cfg.src_cfg.threshold.level);
            dt78xx_fpga_write(dev, FPGA_REG_THOLD_TRIG_LVL, tmp & MASK_THOLD_TRIG_LVL);
            dt78xx_fpga_write(dev, FPGA_REG_THOLD_TRIG_SEL, 
                              cfg.src_cfg.threshold.ain & MASK_THOLD_TRIG_SEL);
            src = cfg.src_cfg.threshold.edge_rising ? TRIG_CTRL_THOLD_RISING :
                                                      TRIG_CTRL_THOLD_FALLING;
            break;
        case trig_src_ext:
            //DIN selection, must be 0-7 both inclusive
            if (cfg.src_cfg.ext.din > NUM_DIN-1)
                return (-EINVAL);
            cfg.src_cfg.ext.din <<= SHIFT_IN_CTRL_DIN_TRIG;
            dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, MASK_IN_CTRL_DIN_TRIG,
                            (cfg.src_cfg.ext.din & MASK_IN_CTRL_DIN_TRIG));
            src = cfg.src_cfg.ext.edge_rising ? TRIG_CTRL_EXT_RISING :
                                                TRIG_CTRL_EXT_FALLING;
            break;
        default:
            src = TRIG_CTRL_SW;
    }

    src <<= SHIFT_TRIG_CTRL_IN_START;
    dt78xx_fpga_rmw(dev, FPGA_REG_TRIG_CTRL, MASK_TRIG_CTRL_IN_START, src);
    
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_START_SUBSYS
 * Params :
 * arg : If not NULL, pointer to uint32_t Non-zero value will software trigger
 *       both input and output streams simultaneously
 * len : length of buffer pointed by arg
 */
static int _sw_start(struct dt7837_stream_in *stream, void __user *arg, size_t len)
{
    struct device *dev;
    uint32_t simultaneous = 0;
    
    dev = &stream->dt_dev->pdev->dev;
   
    if (arg)
    {
        if (len < sizeof(uint32_t))
            return (-EINVAL);

        if (copy_from_user(&simultaneous, arg, sizeof(uint32_t))) 
            return (-EFAULT);
    }
    
    if (simultaneous)
    {
        dt78xx_fpga_rmw(dev, FPGA_REG_IO_CTRL, 
                        MASK_IO_CTRL_OUT_SW_TRIG|MASK_IO_CTRL_IN_SW_TRIG, 
                        MASK_IO_CTRL_OUT_SW_TRIG|MASK_IO_CTRL_IN_SW_TRIG);    
    }
    else
    {
        dt78xx_fpga_rmw(dev, FPGA_REG_IO_CTRL, 
                        MASK_IO_CTRL_IN_SW_TRIG, 
                        MASK_IO_CTRL_IN_SW_TRIG);    
    }
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_CHAN_MASK_GET
 * Params
 *  arg : Pointer to chan_mask_t 
 * len : length of buffer pointed by arg
 */
static int _chan_mask_get(struct dt7837_stream_in *stream, void __user *arg, 
                         size_t len)
{
    uint16_t regval;
    chan_mask_t mask;
    struct device *dev;
    
    if (len < sizeof(mask))
        return (-EINVAL);
    
    dev = &stream->dt_dev->pdev->dev;
    regval = dt78xx_fpga_read(dev, FPGA_REG_IN_MASK);
    mask = 0;
    if (regval & MASK_IN_MASK_DIN)
        mask |= chan_mask_din;
    if (regval & MASK_IN_MASK_MSR_CTR)
        mask |= chan_mask_meas_ctr;
    if (regval & MASK_IN_MASK_TACH)
        mask |= chan_mask_tach;
    if (regval & MASK_IN_MASK_AIN3)
        mask |= chan_mask_ain3;
    if (regval & MASK_IN_MASK_AIN2)
        mask |= chan_mask_ain2;
    if (regval & MASK_IN_MASK_AIN1)
        mask |= chan_mask_ain1;
    if (regval & MASK_IN_MASK_AIN0)
        mask |= chan_mask_ain0;
    if (copy_to_user(arg, (void *)&mask, sizeof(mask))) 
        return (-EFAULT);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_CHAN_MASK_SET
 * Params
 *  arg : Pointer to chan_mask_t 
 * len : length of buffer pointed by arg
 */
static int _chan_mask_set(struct dt7837_stream_in *stream, void __user *arg, 
                         size_t len)
{
    chan_mask_t mask;
    struct device *dev;
    uint16_t regval;
    
    dev = &stream->dt_dev->pdev->dev;
    
    if (len < sizeof(mask))
        return (-EINVAL);
    
    if (copy_from_user(&mask, arg, sizeof(mask))) 
        return (-EFAULT);
    regval = 0;
    if (mask & chan_mask_din)
        regval |= MASK_IN_MASK_DIN;
    if (mask & chan_mask_meas_ctr)
        regval |= MASK_IN_MASK_MSR_CTR;
    if (mask & chan_mask_tach)
        regval |= MASK_IN_MASK_TACH;
    if (mask & chan_mask_ain3)
        regval |= MASK_IN_MASK_AIN3;
    if (mask & chan_mask_ain2)
        regval |= MASK_IN_MASK_AIN2;
    if (mask & chan_mask_ain1)
        regval |= MASK_IN_MASK_AIN1;
    if (mask & chan_mask_ain0)
        regval |= MASK_IN_MASK_AIN0;
    
    dt78xx_fpga_write(dev, FPGA_REG_IN_MASK, regval);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_SAMPLE_CLK_GET
 * Params
 *  arg : Pointer to float 
 * len : length of buffer pointed by arg
 */
static int _clock_get(struct dt7837_stream_in *stream, void __user *arg, 
                      size_t len)
{
    dt78xx_clk_config_t cfg;
    if (len < sizeof(cfg))
        return (-EINVAL);
    memset(&cfg, 0, sizeof(cfg));
    cfg.clk_freq = stream->clock;
    if (copy_to_user(arg, (void *)&cfg, sizeof(cfg))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_SAMPLE_CLK_SET
 * Params
 *  arg : Pointer to float 
 * len : length of buffer pointed by arg
 */
static int _clock_set(struct dt7837_stream_in *stream, void __user *arg, 
                      size_t len)
{
    dt78xx_clk_config_t clk;
    struct device *dev;
    struct pll_config *cfg;
    int err;
    
    dev = &stream->dt_dev->pdev->dev;
    
    if (len < sizeof(clk))
        return (-EINVAL);
    
    if (copy_from_user((void *)&clk, arg, sizeof(clk))) 
        return (-EFAULT);

    kernel_neon_begin();
    cfg = dt7837_pll_config_init(&clk.clk_freq, 1);
    kernel_neon_end();
    if (IS_ERR_OR_NULL(cfg))
        return (PTR_ERR(cfg));
    
    stream->clock = clk.clk_freq;
    err = dt7837_pll_config_write(stream->dt_dev, cfg);
    kfree(cfg);
    if (err)
        return err;
    
    if (copy_to_user(arg, (void *)&clk, sizeof(clk))) 
        return (-EFAULT);
    
    //Sampling rate changes require all AD pots to be updated
    err = dt7837_ad_cal_change(stream->dt_dev);
    return err;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_ACQ_STATUS_GET
 * Params :
 * arg :   Pointer to acq_status_t. 
 * len : length of buffer pointed by arg
 */
static int _get_status(struct dt7837_stream_in *stream, void __user *arg, 
                       size_t len)
{
    struct device *dev;
    u16 val;
    acq_status_t status = 0;
    
    dev = &stream->dt_dev->pdev->dev;
    if (len < sizeof(status))
        return (-EINVAL);
    if (is_input_armed(dev))
        status |= acq_status_armed;
    val = dt78xx_fpga_read(dev, FPGA_REG_IN_STAT);
    if (val & MASK_IN_STAT_ACTIVE)
        status |= acq_status_triggered;
    if (val & MASK_IN_STAT_FIFO_EMPTY)
        status |= acq_status_fifo_empty;
    if (val & MASK_IN_STAT_FIFO_FULL)
        status |= acq_status_fifo_full;
    if (copy_to_user(arg, (void *)&status, sizeof(status))) 
        return (-EFAULT);
    return 0;
}

/*****************************************************************************
 * Main IOCTL handler for /dev/dt7837-stream*
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7837_stream_in *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    int len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7837_stream_in *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    
    dev_lock(dt_dev);
    
    switch (cmd)
    {
        case IOCTL_STOP_SUBSYS:
            //clear I/O Operation Control Register bit InputArm
            dt78xx_fpga_rmw(dev, FPGA_REG_IO_CTRL, MASK_IO_CTRL_IN_ARM, 0);
            retval = dt78xx_edma_stop(file);
            break;
        
        case IOCTL_ARM_SUBSYS:
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            if (!dt78xx_fpga_read(dev, FPGA_REG_IN_MASK)) //no enabled chans
            {
                retval = -EIO;
                break;
            }
            //clear Input FIFO Status Register
            dt78xx_fpga_write(dev, FPGA_REG_IN_FIFO_STAT, 0x0000);
            //clear Interrupt Status Register bits InputTriggered, InputOverflow
            dt78xx_fpga_write(dev, FPGA_REG_INTR_STAT, 
                              MASK_INTR_STAT_IN_TRIG|MASK_INTR_STAT_IN_OVRFL);
            /* prime the edma. This also clears the bit associated with this 
             subsystem's EDMA channel in the DMA Request Status Register*/
            if ((retval = dt78xx_edma_start(file)))
                break;
            //set I/O Operation Control Register bit InputArm
            dt78xx_fpga_rmw(dev, FPGA_REG_IO_CTRL, 
                            MASK_IO_CTRL_IN_ARM, MASK_IO_CTRL_IN_ARM);
            break;
        
        case IOCTL_START_TRIG_CFG_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _start_trig_cfg_set(subsys, (void __user *)arg, len);    
            break;
        
        case IOCTL_START_TRIG_CFG_GET:
            retval = _start_trig_cfg_get(subsys, (void __user *)arg, len);  
            break;
        
        case IOCTL_START_SUBSYS:
            //Ignore if trigger source is not s/w
            if (((dt78xx_fpga_read(dev, FPGA_REG_TRIG_CTRL)&MASK_TRIG_CTRL_IN_START)>>
                                   SHIFT_TRIG_CTRL_IN_START)!=TRIG_CTRL_SW)
            {
                retval = 0; //no error
                break;
            }
            if ((retval = is_input_active(dev)))   //error if input active
                break;
            if (!is_input_armed(dev))   //error if input NOT armed
                return (-EIO);
            retval = _sw_start(subsys, (void __user *)arg, len); 
            break;
        
        case IOCTL_CHAN_MASK_GET :
            retval = _chan_mask_get(subsys, (void __user *)arg, len); 
            break;
        
        case IOCTL_CHAN_MASK_SET :
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _chan_mask_set(subsys, (void __user *)arg, len); 
            break;
        
        case IOCTL_SAMPLE_CLK_GET:
            retval = _clock_get(subsys, (void __user *)arg, len); 
            break;
        
        case IOCTL_SAMPLE_CLK_SET:
            if ((retval = is_input_armed(dev))) //error if the input armed
                break;
            retval = _clock_set(subsys, (void __user *)arg, len); 
            break;
        
        case IOCTL_ACQ_STATUS_GET:
            retval = _get_status(subsys, (void __user *)arg, len);
            break;
            
        case IOCTL_LED_GET :
            retval = dt7837_ioctl_led_get(dev, (void __user *)arg, len);
            break;

        case IOCTL_LED_SET :
            retval = dt7837_ioctl_led_set(dev, (void __user *)arg, len);
            break;
            
        default :
            dev_err(dev, "IOCTL ERROR %s cmd=0x%x (nr=%d len=%d dir=%d)",
                     subsys->filename, cmd, _IOC_NR(cmd), len, _IOC_DIR(cmd));
             retval = -EBADRQC;   /*56 Invalid request code */
    }
    dev_unlock(dt_dev);
    
    return retval;
}

/*****************************************************************************
 * Async IO read handler for /dev/dt7837-stream*
 */
static ssize_t _aio_read(struct kiocb *iocb, const struct iovec *iov,
                               unsigned long nr_segs, loff_t o)
{
    return dt78xx_aio(iocb, iov, nr_segs, DMA_FROM_DEVICE); 
}

/*****************************************************************************
 * Async notification handler for /dev/dt7837-stream*.
 * Reference http://www.makelinux.net/ldd3/chp-6-sect-4
 */
static int _fasync(int fd, struct file *file, int on)
{
    int err;
    struct dt7837_stream_in *subsys;

    subsys = (struct dt7837_stream_in *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
#if 0    
    {
        struct device *dev = &subsys->dt_dev->pdev->dev;
        dev_info(dev, "[%s] %s pid=%d on=0x%x", 
                    __func__, subsys->filename, task_pid_nr(current), on);
    }
#endif    
    err = dt78xx_fasync(fd, file, on);
    return (err);
}

/*****************************************************************************
 * Create the board specific stream and register a file handle
 */
int dt7837_stream_in_create(struct daq_subsystem *daq)
{
    int err;
    struct dt7837_stream_in *subsys;
    const char *dir;
    struct pll_config *cfg;
    struct device *dev = &daq->dt_dev->pdev->dev;
    
    //Must have DMA resources assigned in device tree
    if (!daq->dma)
        return -ENODEV;
    dir = (const char *)of_get_property(daq->node, "dma-names", NULL);
    if (strcmp(dir, "in"))
        return -EINVAL;
     
    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7837_stream_in), GFP_KERNEL);
    if (!subsys)
        return -ENOMEM;
    
    snprintf(subsys->filename, sizeof(subsys->filename), "%s-%s", 
             dt78xx_board_name_get(daq->dt_dev),daq->node->name);
    daq->miscdev.name = subsys->filename;
    daq->miscdev.minor = MISC_DYNAMIC_MINOR;
    daq->miscdev.fops = &_file_ops;
    subsys->dt_dev = daq->dt_dev;
    if ((err = misc_register(&daq->miscdev)))
        goto _create_err;
    
    //set the default PLL clock rate
    subsys->clock = DEFAULT_CLK_RATE_HZ;
    kernel_neon_begin();
    cfg = dt7837_pll_config_init(&subsys->clock, 1);
    kernel_neon_end();
    if (IS_ERR_OR_NULL(cfg))
    {
        err = PTR_ERR(cfg);
        goto _create_err;
    }
    dt7837_pll_config_write(subsys->dt_dev, cfg);
#ifdef _WARN_
#warning replace kfree w/t devm_kfree!!   
#endif
    kfree(cfg);
        
    err = dev_set_drvdata(daq->miscdev.this_device, subsys);
    if (err)
        goto _create_err;
    
    return (0);
    
_create_err:
    if (err)
    {
        daq->miscdev.name = NULL;
        devm_kfree(dev, subsys);
    }
    return (err);
}
