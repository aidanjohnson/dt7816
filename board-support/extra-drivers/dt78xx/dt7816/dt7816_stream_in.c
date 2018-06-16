/*
 * Kerenel Load Module for Data Translation DT7816 data acquisition module.
 * 
 * This file implements the stream operations supported by the
 * /dev/dt7816_stream_in virtual file
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
#include "dt7816.h"
#include "dt7816_fpga.h"

/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 * Data structures
 **************************************************************************/

//Data structure specific to the DT7816 stream. 
struct dt7816_stream_in
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
 * File operations supported by DT7816 stream
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
 * /dev/dt7816-stream*
 */
static int _fopen(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_stream_in *subsys;
    int err;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7816_stream_in *)file_to_subsys(file);
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
 * /dev/dt7816-stream*
 */
static int _fclose(struct inode *inode, struct file *file)
{
    struct dt78xx_device *dt_dev;
    struct dt7816_stream_in *subsys;
    
    dt_dev = file_to_dt78xx(file);
    subsys = (struct dt7816_stream_in *)file_to_subsys(file);
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
 * arg : Pointer to dt78xx_trig_config_t with members initialized
 * len : length of buffer pointed by arg
 */
static int _start_trig_cfg_get(struct dt7816_stream_in *stream, void __user *arg, 
                         size_t len)
{
    dt78xx_trig_config_t trig_cfg;
    u16 trig_src, tmp;
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
        tmp = dt78xx_fpga_read(dev, FPGA_REG_THOLD1_TRIG);
        trig_cfg.src_cfg.threshold.ain = (tmp & MASK_THOLD1_TRIG_SRC)>>SHIFT_THOLD1_TRIG_SRC;
        trig_cfg.src_cfg.threshold.level = 
            threshold_2_twos_comp((tmp & MASK_THOLD1_TRIG_LVL)>>SHIFT_THOLD1_TRIG_LVL);
    }
    //external rising or falling
    else if ((trig_src == TRIG_CTRL_EXT_FALLING) ||
             (trig_src == TRIG_CTRL_EXT_RISING))
    {
        trig_cfg.src = trig_src_ext;
        if (trig_src == TRIG_CTRL_EXT_RISING)
            trig_cfg.src_cfg.ext.edge_rising = 1;
        tmp = dt78xx_fpga_read(dev, FPGA_REG_DIN_GPIO1) & MASK_DIN_GPIO1_IN_TRIG1;
        trig_cfg.src_cfg.ext.din = (tmp >> SHIFT_DIN_GPIO1_IN_TRIG1);
    }
    
    if (copy_to_user(arg, (void *)&trig_cfg, sizeof(trig_cfg))) 
        return (-EFAULT);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_TRIG_CFG_SET
 * Params :
 * arg : Pointer to dt78xx_trig_config_t with members initialized
 * len : length of buffer pointed by arg
 */
static int _start_trig_cfg_set(struct dt7816_stream_in *stream, void __user *arg, 
                                size_t len)
{
    dt78xx_trig_config_t cfg;
    u16 tmp;
    struct device *dev;
    
    dev = &stream->dt_dev->pdev->dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user(&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);
    
    switch (cfg.src)
    {
        case trig_src_threshold:
            //AIN channel selection
            if (cfg.src_cfg.threshold.ain > NUM_AIN-1)
                return (-EINVAL);
            //disable DIN trigger selection
            dt78xx_fpga_rmw(dev, FPGA_REG_DIN_GPIO1, 
                            MASK_DIN_GPIO1_IN_TRIG1_EN|MASK_DIN_GPIO1_IN_TRIG1,
                            0);
            tmp = (twos_comp_2_threshold(cfg.src_cfg.threshold.level) << SHIFT_THOLD1_TRIG_LVL) & MASK_THOLD1_TRIG_LVL;
            tmp |= (cfg.src_cfg.threshold.ain << SHIFT_THOLD1_TRIG_SRC) & MASK_THOLD1_TRIG_SRC;
            dt78xx_fpga_write(dev, FPGA_REG_THOLD1_TRIG, tmp);
            tmp = cfg.src_cfg.threshold.edge_rising ? TRIG_CTRL_THOLD_RISING :
                                                      TRIG_CTRL_THOLD_FALLING;
            break;
        case trig_src_ext:
            //DIN selection, must be 0-7 both inclusive
            if (cfg.src_cfg.ext.din > NUM_DOUT-1)
                return (-EINVAL);
            dt78xx_fpga_rmw(dev, FPGA_REG_DIN_GPIO1, 
                            MASK_DIN_GPIO1_IN_TRIG1_EN|MASK_DIN_GPIO1_IN_TRIG1,
                            MASK_DIN_GPIO1_IN_TRIG1_EN | 
                            (cfg.src_cfg.ext.din << SHIFT_DIN_GPIO1_IN_TRIG1));
            tmp = cfg.src_cfg.ext.edge_rising ? TRIG_CTRL_EXT_RISING :
                                                TRIG_CTRL_EXT_FALLING;
            break;
        default:
            //disable DIN trigger selection
            dt78xx_fpga_rmw(dev, FPGA_REG_DIN_GPIO1, 
                            MASK_DIN_GPIO1_IN_TRIG1_EN|MASK_DIN_GPIO1_IN_TRIG1,
                            0);
            tmp = TRIG_CTRL_SW;
    }
    tmp <<= SHIFT_TRIG_CTRL_IN_START;
    dt78xx_fpga_rmw(dev, FPGA_REG_TRIG_CTRL, MASK_TRIG_CTRL_IN_START, tmp);
    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_START_SUBSYS
 * Params :
 * arg : If not NULL, pointer to uint32_t Non-zero value will software trigger
 *       both input and output streams simultaneously
 * len : length of buffer pointed by arg
 */
static int _sw_start(struct dt7816_stream_in *stream, void __user *arg, size_t len)
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
static int _chan_mask_get(struct dt7816_stream_in *stream, void __user *arg, 
                         size_t len)
{
    u16 regval;
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
    if (regval & MASK_IN_MASK_AIN7)
        mask |= chan_mask_ain7;
    if (regval & MASK_IN_MASK_AIN6)
        mask |= chan_mask_ain6;
    if (regval & MASK_IN_MASK_AIN5)
        mask |= chan_mask_ain5;
    if (regval & MASK_IN_MASK_AIN4)
        mask |= chan_mask_ain4;
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
static int _chan_mask_set(struct dt7816_stream_in *stream, void __user *arg, 
                         size_t len)
{
    chan_mask_t mask;
    struct device *dev;
    u16 regval;
    
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
    if (mask & chan_mask_ain7)
        regval |= MASK_IN_MASK_AIN7;
    if (mask & chan_mask_ain6)
        regval |= MASK_IN_MASK_AIN6;
    if (mask & chan_mask_ain5)
        regval |= MASK_IN_MASK_AIN5;
    if (mask & chan_mask_ain4)
        regval |= MASK_IN_MASK_AIN4;
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
 * arg : Pointer to dt78xx_clk_config_t 
 * len : length of buffer pointed by arg
 */
static int _clock_get(struct dt7816_stream_in *stream, void __user *arg, 
                      size_t len)
{
    dt78xx_clk_config_t cfg;
    struct device *dev;
    u16 regval;
    
    dev = &stream->dt_dev->pdev->dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    regval = dt78xx_fpga_read(dev, FPGA_REG_IN_CTRL);
    memset(&cfg, 0, sizeof(cfg));
    if (regval & MASK_IN_CTRL_EXT_CLK)
    {
        cfg.ext_clk = (regval & MASK_IN_CTRL_EXT_CLK_INV)?2:1;
        regval = dt78xx_fpga_read(dev, FPGA_REG_DIN_GPIO1);
        cfg.ext_clk_din = (regval & MASK_DIN_GPIO1_IN_CLK)>>SHIFT_DIN_GPIO1_IN_CLK;
    }
    cfg.clk_freq = stream->clock;
    
    if (copy_to_user(arg, (void *)&cfg, sizeof(cfg))) 
        return (-EFAULT);

    return 0;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_SAMPLE_CLK_SET
 * Params
 * arg : Pointer to dt78xx_clk_config_t 
 * len : length of buffer pointed by arg
 */
static int _clock_set(struct dt7816_stream_in *stream, void __user *arg, 
                      size_t len)
{
    dt78xx_clk_config_t cfg;
    uint32_t divisor;
    struct device *dev;
    int err;
    
    dev = &stream->dt_dev->pdev->dev;
    
    if (len < sizeof(cfg))
        return (-EINVAL);
    
    if (copy_from_user((void *)&cfg, arg, sizeof(cfg))) 
        return (-EFAULT);

    //Ext clock ignores sepecified clock freq
    if (cfg.ext_clk)
    {
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, 
                    MASK_IN_CTRL_EXT_CLK | MASK_IN_CTRL_EXT_CLK_INV, 
                    MASK_IN_CTRL_EXT_CLK | 
                    ((cfg.ext_clk==2)?MASK_IN_CTRL_EXT_CLK_INV:0));    
        dt78xx_fpga_rmw(dev, FPGA_REG_DIN_GPIO1, 
                        MASK_DIN_GPIO1_IN_CLK_EN|MASK_DIN_GPIO1_IN_CLK,
                        MASK_DIN_GPIO1_IN_CLK_EN | 
                        (cfg.ext_clk_din << SHIFT_DIN_GPIO1_IN_CLK));
        cfg.clk_freq = stream->clock;
    }
    else
    {
        kernel_neon_begin();
        divisor = dt7816_clk_divisor(&cfg.clk_freq, AD_CLK_HZ_MIN, AD_CLK_HZ_MAX);
        kernel_neon_end();

        if (!divisor) //invalid clock rate
            return (-EINVAL);
        stream->clock = cfg.clk_freq;
        //disable GPIO inputs for external clock input
        dt78xx_fpga_rmw(dev, FPGA_REG_DIN_GPIO1, 
                        MASK_DIN_GPIO1_IN_CLK_EN|MASK_DIN_GPIO1_IN_CLK,
                        0);
        //disable the clock generator and external clock source
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, 
                    MASK_IN_CTRL_EXT_CLK | MASK_IN_CTRL_EXT_CLK_INV |MASK_IN_CTRL_CLK_EN, 
                    0);    
        //program the clock dividers
        dt78xx_fpga_write(dev, FPGA_REG_IN_CLK_LO, (u16)divisor);
        dt78xx_fpga_write(dev, FPGA_REG_IN_CLK_HI, 
                           (u16)(divisor>>FPGA_REG_LEN_BITS));
        //enable clock generator
        dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, MASK_IN_CTRL_CLK_EN, MASK_IN_CTRL_CLK_EN);
    }
        
    if (copy_to_user(arg, (void *)&cfg, sizeof(cfg))) 
        return (-EFAULT);
    return err;
}

/*****************************************************************************
 * Handler for ioctl IOCTL_ACQ_STATUS_GET
 * Params :
 * arg :   Pointer to acq_status_t. 
 * len : length of buffer pointed by arg
 */
static int _get_status(struct dt7816_stream_in *stream, void __user *arg, 
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
 * Main IOCTL handler for /dev/dt7816-stream*
 */
static long _ioctl_cb(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct dt78xx_device *dt_dev = file_to_dt78xx(file);
    struct device *dev = &dt_dev->pdev->dev;
    struct dt7816_stream_in *subsys;
    long retval = -EBADRQC;   /*56 Invalid request code */
    int len = _IOC_SIZE(cmd);
    
    subsys = (struct dt7816_stream_in *)file_to_subsys(file);
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
            dt78xx_fpga_write(dev, FPGA_REG_IN_FIFO_CTRL1, 
                                MASK_IN_FIFO_CTRL1_RESET);
            //clear Interrupt Status Register bits InputTriggered, InputOverflow
            dt78xx_fpga_write(dev, FPGA_REG_INTR_STAT, 
                              MASK_INTR_STAT_IN_TRIG|MASK_INTR_STAT_IN_OVRFL|
                              MASK_INTR_STAT_IN_COMPLETE);

            // prime the edma. 
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
            retval = dt7816_ioctl_led_get(dev, (void __user *)arg, len);
            break;

        case IOCTL_LED_SET :
            retval = dt7816_ioctl_led_set(dev, (void __user *)arg, len);
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
 * Async IO read handler for /dev/dt7816-stream*
 */
static ssize_t _aio_read(struct kiocb *iocb, const struct iovec *iov,
                               unsigned long nr_segs, loff_t o)
{
    return dt78xx_aio(iocb, iov, nr_segs, DMA_FROM_DEVICE); 
}

/*****************************************************************************
 * Async notification handler for /dev/dt7816-stream*.
 * Reference http://www.makelinux.net/ldd3/chp-6-sect-4
 */
static int _fasync(int fd, struct file *file, int on)
{
    int err;
    struct dt7816_stream_in *subsys;

    subsys = (struct dt7816_stream_in *)file_to_subsys(file);
    if (!subsys)
        return -ENODEV;
    err = dt78xx_fasync(fd, file, on);
    return (err);
}

/*****************************************************************************
 * Create the board specific stream and register a file handle
 */
int dt7816_stream_in_create(struct daq_subsystem *daq)
{
    int err;
    struct dt7816_stream_in *subsys;
    const char *dir;
    struct device *dev = &daq->dt_dev->pdev->dev;
    
    //Must have DMA resources assigned in device tree
    if (!daq->dma)
        return -ENODEV;
    dir = (const char *)of_get_property(daq->node, "dma-names", NULL);
    if (strcmp(dir, "in"))
        return -EINVAL;
     
    //Allocated memory for subsystem will be free'd by dt78xx_cleanup())
    subsys = devm_kzalloc(dev, sizeof(struct dt7816_stream_in), GFP_KERNEL);
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
    
    //set the default sampling clock rate
    subsys->clock = DEFAULT_CLK_RATE_HZ;
    dt78xx_fpga_write(dev, FPGA_REG_IN_CLK_LO, 
                        (u16)(REF_CLK_HZ/DEFAULT_CLK_RATE_HZ));
    dt78xx_fpga_write(dev, FPGA_REG_IN_CLK_HI,0);
    //enable internal clock generator
    dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, MASK_IN_CTRL_CLK_EN, MASK_IN_CTRL_CLK_EN);
        
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
