
#include <linux/platform_device.h>
#include <linux/platform_data/edma.h>
#include <linux/platform_data/gpio-omap.h>
#include <linux/kernel.h>
#include <linux/stat.h>
#include <linux/gpio.h>
#include <linux/of_address.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/i2c.h>

#include <../arch/arm/mach-omap2/gpmc.h>

#include "dt78xx.h"

//Define this to create sysfs to read/write GPMC register settings
#define _GPMC_SYSFS_ (1)

//Define this to debug EDMA xbar and registers
//#define _XBAR_SYSFS_ (1)

//Define this to debug pinmux register
//#define _PINMUX_DBG_ (1)

//#define _FPGA_SYSFS_ (1)

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

#ifdef _XBAR_SYSFS_
static ssize_t _xbar_reg_read(struct device *dev,
                             struct device_attribute *attr, char *buf)
{
    struct device_node * node;
    struct dt78xx_device *dt_dev;
    int len =0;
    dt_dev = dev_get_drvdata(dev);
    dev_lock(dt_dev);
    
    node = of_find_node_by_name(NULL, "edma");
    if (!node)
    {
        dev_err(dev, "[%s] FAIL find node edma\n", __func__);
    }
    else
    {
        /*
         * Get resource 1 in the reg<> property of the edma node in am33xx.dtsi
         * The EDMA event mux registers are at 0x44e10f90 - 0x44e10fcf. Also see
         * Table 9-10 in the AM335x TRM
         */
        struct resource res;
        int ret = of_address_to_resource(node, 1, &res);
        if (!IS_ERR_VALUE(ret))
        {
            void *xbar = ioremap(res.start, resource_size(&res));
            if (xbar)
            {
                u32 offset;
                dev_info(dev, "[%s] start=%x end=%x virt=%x\n", 
                         __func__, res.start, res.end, (uint32_t)xbar);
                for(offset=0; 
                    res.start < res.end; 
                    res.start += sizeof(uint32_t), offset += sizeof(uint32_t))
                {
                    u32 reg_val;
                    reg_val = readl((void *)((u32)xbar + offset));
                    len += scnprintf(buf +len, PAGE_SIZE-len,
                                     "%x (tpcc_evt_mux_%d_%d) = %x\n", 
                                     res.start, offset, offset+3, reg_val); 
                }
            }
       }
       of_node_put(node); 
    }
    dev_unlock(dt_dev);
    return (len);
}
#endif
#ifdef _INTC_REG_
const struct
{
    u32  offset;     //reg offset
    char *intc_name; //register name for debug sanity
} g_intc[]=
{
    {0x80, "INTC_ITR"},
    {0x84, "INTC_MIR"},
    {0x98, "INTC_PENDING_IRQ"},
    {0x9c, "INTC_PENDING_FIQ"},
};
/*
 * Read all important intc registers
 */
static ssize_t _intc_reg_read(struct device *dev, struct device_attribute *attr,
                              char *buf)
{
    struct device_node * node;
    struct dt78xx_device *dt_dev;
    struct resource res;
    int ret;
    int len =0;
    dt_dev = dev_get_drvdata(dev);
    dev_lock(dt_dev);
     
    node = of_find_node_by_name(NULL, "interrupt-controller");
    if (!node)
    {
        dev_unlock(dt_dev);
        dev_err(dev, "[%s] FAIL find node interrupt-controller\n", __func__);
        return (0);
    }
    /*
     * Get resource 0 in the reg<> property which is the base addr of intc
     */
    ret = of_address_to_resource(node, 0, &res);
    if (!IS_ERR_VALUE(ret))
    {
        void __iomem *intc = ioremap(res.start, resource_size(&res));
        if (intc)
        {
            int i, j;
            u32 offset;
            u32 reg_val;
            //read the INTC_SIR_IRQ and INTC_SIR_FIQ regs
            offset = 0x40;
            reg_val = readl((void *)((u32)intc + offset));
            len += scnprintf(buf +len, PAGE_SIZE-len,
                             "%x (INTC_SIR_IRQ) = %08x\n", 
                             res.start + offset,
                             reg_val); 
            offset = 0x44;
            reg_val = readl((void *)((u32)intc + offset));
            len += scnprintf(buf +len, PAGE_SIZE-len,
                             "%x (INTC_SIR_FIQ) = %08x\n", 
                             res.start + offset,
                             reg_val); 
             
            for (j=0; j<4; ++j)
            {
                for (i=0; i < sizeof(g_intc)/sizeof(g_intc[0]); ++i)
                {
                    offset=g_intc[i].offset + (j*0x20);
                    reg_val = readl((void *)((u32)intc + offset));

                    len += scnprintf(buf +len, PAGE_SIZE-len,
                                     "%x (%s%d) = %08x\n", 
                                     res.start + offset, 
                                     g_intc[i].intc_name, j,
                                     reg_val); 

                }
            }
        }
    }
    of_node_put(node); 

    dev_unlock(dt_dev);
    return (len);
}
static ssize_t _intc_reg_write(struct device *dev, struct device_attribute *attr,
                               const char *buf, size_t count)
{
    struct device_node * node;
    struct dt78xx_device *dt_dev;
    struct resource res;
    int err=0;
    char *term;
    u32 reg_offset, reg_data;

    if (!count || !buf)
    {
        return 0;
    }
    reg_offset = simple_strtoul(buf, &term, 16);
    if (term == NULL)
    {
        dev_err(dev, "[%s] Missing =\n", __func__);
        return (-EINVAL);
    }
    reg_data = simple_strtoul(term+1, NULL, 16);//reg_data is after '='
    
    dt_dev = dev_get_drvdata(dev);
    dev_lock(dt_dev);
     
    node = of_find_node_by_name(NULL, "interrupt-controller");
    if (!node)
    {
        dev_unlock(dt_dev);
        dev_err(dev, "[%s] FAIL find node interrupt-controller\n", __func__);
        return (-EINVAL);
    }
    /*
     * Get resource 0 in the reg<> property which is the base addr of intc
     */
    err = of_address_to_resource(node, 0, &res);
    if (!IS_ERR_VALUE(err))
    {
        void __iomem *intc = ioremap(res.start, resource_size(&res));
        if (intc)
        {
            writel(reg_data, intc + reg_offset);
            dev_info(dev, "[%s] %08x=%04x\n", __func__, res.start+reg_offset, reg_data);
            
        }
    }
    of_node_put(node); 

    dev_unlock(dt_dev);
    return ((err) ? err : count);
}
#endif //_INTC_REG_

#ifdef _FPGA_SYSFS_
static ssize_t _mem_dev_write(struct device *dev, const char *buf,size_t count,
                              struct gpmc_res * mm_dev)
{
    int err = 0;

    if (count > 0)
    {
        char *p_terminator;
        uint32_t addr_offset;

        addr_offset = simple_strtoul(buf, &p_terminator, 16);
        if (p_terminator == NULL)
        {
            dev_err(dev, "[%s] Missing =\n", __func__);
            err = -EINVAL;
        }
        else
        {
            uint32_t data;
            ++p_terminator; //point to char after =
            data = simple_strtoul(p_terminator, NULL, 16);
            data &= USHRT_MAX;
            dt78xx_fpga_write(dev, addr_offset, data);

            dev_dbg(dev, "[%s] write %X=%X\n", 
                     __func__, ((uint32_t)addr_offset),data);
        }
    }
    return (err==0) ? count : err;
}
/******************************************************************************
 * Write to dev_attr_fpga
 * Usage :
 *  echo  123=55 > /sys/devices/ocp.2/bone-cape-datx.??/fpga
 *  The <addr>=<data> parameters are two hex values separated with equal
 */
static ssize_t _fpga_write(struct device *dev,
                struct device_attribute *attr,
                const char *buf, size_t count)
{
    size_t err;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    
    dev_lock(dt_dev);
    err = _mem_dev_write(dev, buf, count, dt_dev->fpga);
    dev_unlock(dt_dev);
    
    return (err);
}

/*****************************************************************************
 * Read all FPGA registers
 * @param dev   
 * @param attr
 * @param buf
 * @return : #of bytes written to buf
 */
static ssize_t _fpga_read(struct device *dev, struct device_attribute *attr, 
                          char *buf)
{
    size_t len=0;
    uint32_t addr_offset, data;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    
    dev_lock(dt_dev);
 
    for (addr_offset=0x00; addr_offset <= 0x0f; addr_offset += sizeof(uint16_t))
    {
        data = dt78xx_fpga_read(dev, addr_offset);
        len += scnprintf(buf+len, PAGE_SIZE-len, "%X=%X\n",
                         addr_offset, data);
    }

    dev_unlock(dt_dev);

    dev_dbg(dev, "[%s] read returned %d bytes\n",  __func__, len);
    
    return (len);
}
#endif

#ifdef _GPMC_SYSFS_
static ssize_t gpmc_cfg_reg_read(int cs, void *virtual, char * buf)
{
    int len = 0;
    uint32_t cs_offset, offset, reg_val;
    
    //Print out the Chip Select's CONFIG 1 through CONFIG7 register
    cs_offset = 0x30 * cs;
    len += scnprintf(buf +len, PAGE_SIZE-len, 
                  "CS%d [", cs);
    for (offset=0x60; offset <= 0x78; offset += sizeof(uint32_t))
    {
       reg_val = readl((void *)((u32)virtual + offset + cs_offset));
       len += scnprintf(buf +len, PAGE_SIZE-len,
                    "%x=%x ", 
                    offset+cs_offset, reg_val); 
    }
    --len; //overwrite last space
    len += sprintf(buf+len, "]\n");
    return len;
}
static ssize_t _gpmc_reg_read(struct device *dev,
                            struct device_attribute *attr, char *buf)
{
    int len=0, ret;
    struct device_node * node;
    struct resource res;
    struct device_node *child;
    void *virt;
    uint32_t offset;
    uint32_t reg_val;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    
    node = of_find_node_by_name(NULL, "gpmc");
    if (!node)
    {
        dev_err(dev, "[%s] FAIL find node gpmc\n", __func__);
        return 0;
    }
    
    dev_lock(dt_dev);
    ret = of_address_to_resource(node, 0, &res);
    if (IS_ERR_VALUE(ret))
    {
        goto gpmc_reg_read_err;
    }

    virt = ioremap(res.start, resource_size(&res));
    if (!virt)
    {
        goto gpmc_reg_read_err;
    }

    //DPRINTF(dev, "[%s] start=%x end=%x virt=%x\n", 
    //         __func__, res.start, res.end, (uint32_t)virt);
    
    for (offset=0x10; offset <= 0x1c; offset += sizeof(uint32_t))
    {
       reg_val = readl((void *)((u32)virt + offset));
       len += scnprintf(buf +len, PAGE_SIZE-len,
                         "%x=%x ", 
                         offset, reg_val); 
    }
    len += scnprintf(buf +len, PAGE_SIZE-len,"\n");

    for (offset=0x40; offset <= 0x54; offset += sizeof(uint32_t))
    {
       reg_val = readl((void *)((u32)virt + offset));
       len += scnprintf(buf +len, PAGE_SIZE-len,
                         "%x=%x ", 
                         offset, reg_val); 
    }
    --len; //overwrite last space
    len += scnprintf(buf +len, PAGE_SIZE-len,"\n");

    for (offset=0x1e0; offset <= 0x1fc; offset += sizeof(uint32_t))
    {
        reg_val = readl((void *)((u32)virt + offset));
        len += scnprintf(buf +len, PAGE_SIZE-len,
                          "%x=%x ", 
                          offset, reg_val); 
    }
    --len; //overwrite last space
    len += scnprintf(buf +len, PAGE_SIZE-len,"\n");
    //Print out each Chip Select's CONFIG 1 through CONFIG7 register
    for_each_available_child_of_node(node, child) 
    {
        int cs;
        if (of_property_read_u32(child, "reg", &cs) < 0) 
        {
            dev_err(dev, "[%s] %s has no 'reg' property\n",
                          __func__, child->full_name);
        } 
        else
        {
            len += gpmc_cfg_reg_read(cs, virt, buf+len);
        }
        of_node_put(child);    
    }
    len += sprintf(buf+len, "\n");

gpmc_reg_read_err:    
   of_node_put(node); 
   dev_unlock(dt_dev);
   return (len);
}
/*
 * Write to GPMC config registers
 * Usage :
 *  echo  123=55 > /sys/devices/ocp.2/bone-cape-datx.??/gpmc
 *  The <offset>=<data> parameters are two hex values separated with equal
 * The <offset> is the address offset of the GPMC register specified in
 * Table 7-54 in the AM335x TRM
 */
static ssize_t _gpmc_reg_write(struct device *dev,
                struct device_attribute *attr,
                const char *buf, size_t count)
{
    int err =0;
    char *p_terminator;
    uint32_t offset, data;
    struct device_node * node;
    struct resource res;
    void *virt;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
 
    if (!count)
    {
        return 0;
    }

    offset = simple_strtoul(buf, &p_terminator, 16);
    if (p_terminator == NULL)
    {
        dev_err(dev, "[%s] Missing =\n", __func__);
        return (-EINVAL);
    }
    offset &= 0xfff; //offset is 12-bits see Table 7-54
    
    ++p_terminator; //point to char after =
    data = simple_strtoul(p_terminator, NULL, 16);
    data &= ULONG_MAX; //32-bit register data
    
    node = of_find_node_by_name(NULL, "gpmc");
    if (!node)
    {
        dev_err(dev, "[%s] FAIL find node gpmc\n", __func__);
        return (-ENODEV);
    }
    
    dev_lock(dt_dev);
    err = of_address_to_resource(node, 0, &res);
    if (IS_ERR_VALUE(err))
    {
        err =-ENODEV;
        goto gpmc_reg_write_err;
    }
    virt = ioremap(res.start, resource_size(&res));
    if (!virt)
    {
        goto gpmc_reg_write_err;
    }
    
    writel(data, (void *)((u32)virt + offset));

gpmc_reg_write_err:
    of_node_put(node);  
    dev_unlock(dt_dev);

    dev_info(dev, "[%s] %x=%x\n", __func__, offset, data);
    return (err==0) ? count : err;
}

#endif

#ifdef _PINMUX_DBG_
static ssize_t _pinmux_reg_read(struct device *p_dev,
                            struct device_attribute *attr, char *p_buf)
{
    struct device_node * p_dev_node;
    int len =0;
    
    p_dev_node = of_find_node_by_name(NULL, "am33xx_pinmux");
    if (!p_dev_node)
    {
        dev_err(p_dev, "[%s] FAIL find node am33xx_pinmux\n", __func__);
    }
    else
    {
        /*
         * Get resource 0 in the reg<> property of the am33xx_pinmux node in 
         * am33xx.dtsi
         * The pinctrl registers are at 0x44e10800 - 0x44e10a38. Also see
         * Table 9-10 in the AM335x TRM
         */
        struct resource res;
        int ret = of_address_to_resource(p_dev_node, 0, &res);
        if (!IS_ERR_VALUE(ret))
        {
            void *xbar = ioremap(res.start, resource_size(&res));
            if (xbar)
            {
                uint32_t offset;
                dev_info(p_dev, "[%s] start=%x end=%x virt=%x\n", 
                         __func__, res.start, res.end, (uint32_t)xbar);
                for(offset=0; 
                    res.start < res.end; 
                    res.start += sizeof(uint32_t), offset += sizeof(uint32_t))
                {
                    uint32_t reg_val = readl((void *)((u32)xbar + offset));
                    len += scnprintf(p_buf +len, PAGE_SIZE-len,
                                     "%x = %x\n", 
                                     res.start & 0xfff, reg_val & 0xff); 
                }
            }
       }
       of_node_put(p_dev_node); 
    }
    return (len);
}
#endif 
static const struct
{
    u32         reg_offset;
    const char *reg_name;
}g_gpioreg[]=
{
    {0x0010,  "SYSCONFIG      "},
    {0X0020 , "EOI            "},
    {0x0024,  "IRQSTATUS_RAW_0"},
    {0x0028,  "IRQSTATUS_RAW_1"},
    {0x002c,  "IRQSTATUS_0    "},
    {0x0030,  "IRQSTATUS_1    "},
    {0x0034,  "IRQSTATUSSET_0 "},
    {0x0038,  "IRQSTATUSSET_1 "},
    {0x003c,  "IRQSTATUSCLR_0 "},
    {0x0040,  "IRQSTATUSCLR_1 "},
    {0x0130,  "CTRL           "},
    {0x0134,  "OE             "},
    {0x0138,  "DATAIN         "},
    {0x013c,  "DATAOUT        "},
    {0x0140,  "LEVELDETECT0   "},
    {0x0144,  "LEVELDETECT1   "},
    {0x0148,  "RISINGDETECT   "},
    {0x014c,  "FALLINGDETECT  "},
    {0x0150,  "DEBOUNCENABLE  "},
    {0x0154,  "DEBOUNCINGTIME "},
    {0x0190,  "CLEARDATAOUT   "},
    {0x0194,  "SETDATAOUT     "},
};
static ssize_t _gpio_reg_read(struct device *dev,
                            struct device_attribute *attr, char *buf, 
                            int bank)
{
    int len, reg;
    uint32_t reg_val;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    void  __iomem *virt = dt_dev->gpio_base[bank];
    
    dev_lock(dt_dev);
    
    for (reg=0, len=0; reg<sizeof(g_gpioreg)/sizeof(g_gpioreg[0]) ; ++reg)
    {
        reg_val = readl(virt + g_gpioreg[reg].reg_offset);
        len += scnprintf(buf +len, PAGE_SIZE-len,
                         "%04x GPIO%d_%s %08x\n", 
                         g_gpioreg[reg].reg_offset, 
                         bank, 
                         g_gpioreg[reg].reg_name, reg_val); 
        if (len >= PAGE_SIZE)
        {
            break;
        }
    }
    dev_unlock(dt_dev);
    return (len);
}
static ssize_t _gpio_reg_write(struct device *dev, struct device_attribute *attr,
                               const char *buf, size_t count,int bank)
{
    char *p_terminator;
    uint32_t offset, data_wr, data_rd;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
 
    if (!count)
    {
        return 0;
    }

    offset = simple_strtoul(buf, &p_terminator, 16);
    if (p_terminator == NULL)
    {
        dev_err(dev, "[%s] Missing =\n", __func__);
        return (-EINVAL);
    }
    offset &= 0xfff; //offset is 12-bits
    
    ++p_terminator; //point to char after =
    data_wr = simple_strtoul(p_terminator, NULL, 16);
    data_wr &= ULONG_MAX; //32-bit register data
    
    dev_lock(dt_dev);
    writel(data_wr, (void *)((u32)dt_dev->gpio_base[bank] + offset));
    data_rd = readl((void *)((u32)dt_dev->gpio_base[bank] + offset));
    dev_unlock(dt_dev);

    dev_info(dev, "[%s] write %x=%x read %x=%x \n", 
         __func__, offset, data_wr, offset, data_rd);
    return count;
}

static ssize_t _gpio0_reg_read(struct device *dev,
                            struct device_attribute *attr, char *buf)
{
    return _gpio_reg_read(dev, attr, buf, 0);    
}
static ssize_t _gpio1_reg_read(struct device *dev,
                            struct device_attribute *attr, char *buf)
{
    return _gpio_reg_read(dev, attr, buf, 1);    
}
static ssize_t _gpio1_reg_write(struct device *dev, struct device_attribute *attr,
                               const char *buf, size_t count)
{
    return _gpio_reg_write(dev, attr, buf, count,1); //write gpio_base[1]
}
static ssize_t _gpio2_reg_read(struct device *dev,
                            struct device_attribute *attr, char *buf)
{
    return _gpio_reg_read(dev, attr, buf, 2);    
}
static ssize_t _gpio3_reg_read(struct device *dev,
                            struct device_attribute *attr, char *buf)
{
    return _gpio_reg_read(dev, attr, buf, 3);    
}

#ifdef _PLL_REG_
// PLL registers
static struct 
{
    const char          *name;
    resource_size_t     addr;
}g_pll_regs[]=
{
    {"CM_IDLEST_DPLL_MPU",  0x44e00420},
    {"CM_CLKSEL_DPLL_MPU",  0x44e0042c},
    {"CM_CLKMODE_DPLL_MPU", 0x44e00488},
    {"CM_DIV_M2_DPLL_MPU",  0x44e004a8},
};
static ssize_t _pll_reg_read(struct device *dev, struct device_attribute *attr,
                             char *buf)
{
    int len=0, i;
    void __iomem *virt;
    uint32_t reg_val;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    
    dev_lock(dt_dev);

    for (i=0; i< sizeof(g_pll_regs)/sizeof(g_pll_regs[0]); ++i)
    {
        virt = ioremap(g_pll_regs[i].addr, sizeof(uint32_t));
        if (virt)
        {
            reg_val = readl(virt);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                              "[%08x] %s %08x\n", 
                               g_pll_regs[i].addr,g_pll_regs[i].name, reg_val); 
            iounmap(virt);
        }
    }
   dev_unlock(dt_dev);
   return (len);
}
#endif /* _PLL_REG_ */

static u32 _eeprom_addr =0x0; //kluge! Store address set by "echo eeprom"
/******************************************************************************
 * Write to eeprom
 * Usage :
 *  To write value to a specific address
 *  echo  addr=value > /sys/devices/.../eeprom
 *  To set the address at which the next cat operation will start
 *  echo  addr > /sys/devices/.../eeprom
 */
static ssize_t _eeprom_write(struct device *dev, struct device_attribute *attr,
                             const char *buf, size_t count)
{
    u32 val;
    u8 tmp;
    int err;
    struct dt78xx_device *dt_dev;
    
    dt_dev = dev_get_drvdata(dev);
    err = _parse_addr_val(buf, &_eeprom_addr, &val);
    if (err)
        return (count);
    
    dev_lock(dt_dev);
    tmp = (u8)val;
    if (dt78xx_eeprom_write(dt_dev->eeprom, _eeprom_addr, &tmp, 1) != 1)
        dev_err(dev, "[%s] dt78xx_eeprom_write\n", __func__);
    dev_unlock(dt_dev);
    return (count);
}

/*****************************************************************************
 * Read from i2c eeprom
 * @param dev
 * @param attr
 * @param buf
 * @return 
 */
static ssize_t _eeprom_read(struct device *dev, struct device_attribute *attr, 
                          char *buf)
{
    size_t len = 0;
    int i,j;
    struct dt78xx_device *dt_dev;
    u8 tmp[16];
    
    dt_dev = dev_get_drvdata(dev);
    dev_lock(dt_dev);
    for (i=0; i < 256; i += sizeof(tmp), _eeprom_addr += sizeof(tmp))
    {
        if (dt78xx_eeprom_read (dt_dev->eeprom, _eeprom_addr, tmp, sizeof(tmp))
                                < sizeof(tmp))
        {
            dev_err(dev, "[%s] ERROR dt78xx_eeprom_read\n", __func__);
            goto failure;
        }
        len += scnprintf(buf+len, PAGE_SIZE-len, "%4x:", _eeprom_addr);
        for (j=0; j < sizeof(tmp); ++j)
            len += scnprintf(buf+len, PAGE_SIZE-len, "%02x ", tmp[j]);
        len += scnprintf(buf+len, PAGE_SIZE-len, "\n");
    }
failure:    
    dev_unlock(dt_dev);
    return (len);
}

#ifdef _PINMUX_DBG_
/*
 * Device attribute to print out pin control register details
 */
static const DEVICE_ATTR(pinmux, 
                   S_IRUGO,
                   _pinmux_reg_read, 
                   NULL);
#endif

#ifdef _XBAR_SYSFS_
/*
 * Device attribute to print out EDMA register details
 */
static const DEVICE_ATTR(xbar, 
                   S_IRUGO,
                   _xbar_reg_read, 
                   NULL);
#endif

/*
 * Device attribute to initialize and arm DMA or turn it off
 * File :
 * /sys/devices/ocp.2/....../edma
 */
static const DEVICE_ATTR(edma, 
                   S_IRUGO,
                   sysfs_edma_read, 
                   NULL);
#if 0
static const DEVICE_ATTR(fifo, 
                   S_IRUGO | S_IWUGO,
                    _fifo_read, 
                   _fifo_write);

#endif
#ifdef _GPMC_SYSFS_
static const DEVICE_ATTR(gpmc, 
                   S_IRUGO| S_IWUGO,
                   _gpmc_reg_read, 
                   _gpmc_reg_write);
#endif
#ifdef _FPGA_SYSFS_
/*
 * Device attribute to read/write registers in the FPGA
 * File :
 * /sys/devices/ocp.2/....../fpga
 */
static const DEVICE_ATTR(fpga, S_IRUGO | S_IWUGO,
                   _fpga_read, _fpga_write);
#endif
#ifdef _INTC_REG_
/*
 * Device attribute to read/write INTC registers
 * File :
 * /sys/devices/ocp.2/....../intc_reg
 */
static const DEVICE_ATTR(intc_reg, 
                    S_IWUGO | S_IRUGO,
                    _intc_reg_read,
                    _intc_reg_write);
#endif
static const DEVICE_ATTR(aio, 
                    S_IRUGO,
                    sysfs_aio,
                    NULL);

static const DEVICE_ATTR(gpio0_reg, 
                    S_IRUGO,
                    _gpio0_reg_read,
                    NULL);

static const DEVICE_ATTR(gpio1_reg, 
                    S_IWUGO | S_IRUGO,
                    _gpio1_reg_read,
                    _gpio1_reg_write);

static const DEVICE_ATTR(gpio2_reg, 
                    S_IRUGO,
                    _gpio2_reg_read,
                    NULL);

static const DEVICE_ATTR(gpio3_reg, 
                    S_IRUGO,
                    _gpio3_reg_read,
                    NULL);
static const DEVICE_ATTR(eeprom, 
                    S_IWUGO | S_IRUGO,
                    _eeprom_read,
                    _eeprom_write);
#ifdef _PLL_REG_
static const DEVICE_ATTR(pll_reg, 
                    S_IRUGO,
                    _pll_reg_read,
                    NULL);
#endif
#define ATTR_LIST(x)    & dev_attr_##x.attr
static const struct attribute * g_dt78xx_attr[] = 
{
    ATTR_LIST(eeprom),
    ATTR_LIST(edma),
    ATTR_LIST(aio),
    //ATTR_LIST(gpio0_reg),
    ATTR_LIST(gpio1_reg),
    //ATTR_LIST(gpio2_reg),
    //ATTR_LIST(gpio3_reg),
#ifdef _PLL_REG_
    ATTR_LIST(pll_reg),
#endif
#ifdef _INTC_REG_
    ATTR_LIST(intc_reg),
#endif
#ifdef _FPGA_SYSFS_
    ATTR_LIST(fpga),
#endif
#ifdef _XBAR_SYSFS_
    ATTR_LIST(xbar),
#endif 
#ifdef _GPMC_SYSFS_
    ATTR_LIST(gpmc),
#endif  
#ifdef _PINMUX_DBG_
    ATTR_LIST(pinmux),
#endif  
#if 0    
    ATTR_LIST(fifo),
#endif    
    NULL
};

struct attribute_group g_dt78xx_attr_group = 
{
    .attrs = (struct attribute **)g_dt78xx_attr,
};

