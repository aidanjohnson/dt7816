/*
 * KLM for Data Translation DT78xx data acquisition module.
 * 
 * This KLM, dt78xx.ko, is used by the board specific KLM, for instance, the
 * DT7837 KLM dt7837.ko. This KLM exports APIs and data structures used by 
 * board specific KLMs. 
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
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/spinlock.h>
#include <linux/dma-mapping.h>
#include <linux/platform_data/edma.h>
#include <linux/platform_data/gpio-omap.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_dma.h>
#include <linux/of_gpio.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/kref.h>
#include <linux/fs.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <../arch/arm/mach-omap2/gpmc.h>
#include <linux/i2c.h>

#include "dt78xx.h"
#include "dt78xx_dts.h"
#include "dt78xx_version.h"
#ifndef CONFIG_OF
#error CONFIG_OF must be defined for Device Tree
#endif

/*
 * There is a clash in definitions b/w DMA_COMPLETE/DMA_CC_ERROR/DMA_TC1_ERROR/
 * DMA_TC2_ERROR in linux/platform_data/edma.h and and values in enum dma_status
 * in linux/dmaengine.h. Be careful in mixing values.The edma callback status
 * uses the definitions DMA_COMPLETE/DMA_CC_ERROR/DMA_TC1_ERROR/DMA_TC2_ERROR
 */
/**************************************************************************/
#if !(defined DMA_SUCCESS) && (defined DMA_COMPLETE)
#define DMA_SUCCESS DMA_COMPLETE
#endif

//Maximum number of EDMA PaRAM slots in the AM335x EDMA3CC that are linked
#define MAX_EDMA_PARAM     (2)

//Address not to be used
#define DMA_POISON         (0xbaadbeef)

//EDMA PaRAM default values. ACNT is the length of the scatterlist
#define BCNT    (1)     
#define CCNT    (1)
#define BCNTRLD (1)

#define DMA_CS_MASK         (0x1000)
/**************************************************************************
 * Data structures
 */

/*
 * Memory mapped device interfaced through the AM335x GPMC. The parameters are
 * specified in the device tree using the <ranges> binding in the gpmc node
 * and <reg> bindings in all children nodes of the gpmc
 */
struct gpmc_res
{
    // Virtual address of the device used by CPU access
    void __iomem  *addr_virt;
    // Physical address used for DMA 
    dma_addr_t addr_dma;
    // Address range specified in device tree 
    resource_size_t addr_range; 
};

//Generic subsystem
struct daq_dma_resource
{
    struct daq_subsystem *daq;  //parent daq subsystem
    enum dma_transfer_direction dir;    //dma direction  
    const char *name;    //parent node's type name
    int dma_chan;   //DMA channel# in the device tree <dmas> parameter
    u32 slot;       //PaRAM slot mapped to dma_chan
    u32 link;       //PaRAM link copied to PaRAM slot
    int event_irq;  //irq mapped to edma event. From "dma-interrupts" in dev tree 
    struct list_head req_list;  //List of AIO requests
    int sg_active; /* number of PaRAMs filled in the AM335x EDMA3CC. 0 means
                    * both 'slot' and 'link' are empty, 1 means 'link' is empty
                    * and 2 means both are filled */
    struct gpmc_res fifo; //fifo address
    /* EDMA transfers are triggered by dedicated inputs xdma_event_intr0/1/2 or
     * a gpio input. In case of the latter, the following additional information
     * is required. This is parsed from "dma-gpios" in the device tree */
    int gpio_trig;  //gpio pin number, if any, used as edma event input
    enum dma_status dma_status;
    struct fasync_struct *async_queue; //used by fasync_helper())
    /* FPGA register written to to clear EDMA completion. This is parsed from
     * "fpga-dma-clr" binding in the device tree */
    struct
    {
        int  reg_offset;
        u16 reg_value;
    } fpga_dma_clr;
#ifdef DEBUG    
    u32 req_submitted;
    u32 req_completed;
    u32 queue_empty;
#endif    
};

typedef void (* dma_callback)(unsigned channel, u16 ch_status, void *data);

/**************************************************************************
 * Functions
 */
static int _gpmc_resource_get(struct device *, int , struct gpmc_res *);
static int _of_parse_fpga_dma_clr(const struct device_node *, u16 *);
/**************************************************************************
 * Globals
 */
extern struct attribute_group g_dt78xx_attr_group;

//EDMA3CC REGISTERS 
static struct
{
    uint32_t    offset; //reg addr = EDMA base + offset
    uint32_t    regs;   //#of 32-bit registers starting at offset
    const char *name;   //reg name
}g_edmacc_reg[]=
{
    {0x300,  2, "EMR   "},
    {0x320,  1, "EEVAL "},
    {0x600,  3, "QSTAT "},
    {0x640,  1, "CCSTAT"},
    {0x800,  1, "MPFAR "},
    {0x804,  1, "MPFSR "},
    {0x1000, 2, "ER    "},
    {0x1020, 2, "EER   "},
    {0x1050, 2, "IER   "},
};

/**************************************************************************
 * Parse the "fpga-dma-clr" binding in the device tree" and get the fpga register
 * offset and bit pattern. At the end of edma completion, this fpga register is
 * written with the specified bit pattern to clear the fpga dma status
 * @param node : subsystem node that must have "dmas" also specified
 * @param reg_val : 16-bit fpga data returned here
 * @return : <0 = error, >0 = fpga register offset
 */
static int _of_parse_fpga_dma_clr(const struct device_node *node, u16 *reg_val)
{
	const struct property *prop;
	const __be32 *val;
	int nr, reg;
    
	prop = of_find_property(node, "fpga-dma-clr", NULL);
	if (!prop)
		return -ENODEV;
	if (!prop->value)
		return -ENODATA;
    /* There must be one tuple consisting of register offset and value */
    nr = prop->length / sizeof(u32);
	if (nr < 2) 
    {
		return -EINVAL;
	}    
    val = prop->value;
    reg = be32_to_cpup(val++);
    *reg_val = (u16)be32_to_cpup(val++);

    return (reg);
}

/**************************************************************************
 * Clear the interrupt status for the gpio pin used as interrupt input.
 * This writes to the OMAP4_GPIO_EOI register in the gpio bank in which
 * the specified gpio pin is in.
 * @param dt_dev : ptr to device
 * @param gpio   : valid gpio pin
 */
static inline void _gpio_eoi_clr(struct dt78xx_device *dt_dev, int gpio)
{
    writel(0, dt_dev->gpio_base[gpio/32] + OMAP4_GPIO_EOI);
}

/** **********************************************************************
 * FPGA register read modify write
 * @param dev   : device pointer
 * @param offset : FPGA register offset
 * @param mask  : bits set in the mask are modified
 * @param data  : data is AND-ed with mask and written to register
 * @see dt78xx_fpga_write, dt78xx_fpga_read
 */
void dt78xx_fpga_rmw(struct device *dev, u32 offset, u16 mask, u16 data)
{
    unsigned long flags;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);   
    u16 read;
    
    spin_lock_irqsave(&dt_dev->lock, flags);
    read = ioread16(dt_dev->fpga->addr_virt + offset);
    read &= ~mask;  //clear the bits which are set in mask
    data &= mask;   //keep bits which are set in mask
    data |= read;   //OR the masked read
    iowrite16(data, (dt_dev->fpga->addr_virt + offset));
    spin_unlock_irqrestore(&dt_dev->lock, flags);    
}
EXPORT_SYMBOL_GPL(dt78xx_fpga_rmw);

/**************************************************************************
 * FPGA register write
 * @param dev   : device pointer
 * @param offset : FPGA register offset
 * @param data  : data to write
 */
void dt78xx_fpga_write(struct device *dev, u32 offset, u16 data)
{
    unsigned long flags;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);    
    
    spin_lock_irqsave(&dt_dev->lock, flags);
    iowrite16(data, (dt_dev->fpga->addr_virt + offset));
    spin_unlock_irqrestore(&dt_dev->lock, flags);    
}
EXPORT_SYMBOL_GPL(dt78xx_fpga_write);

/**************************************************************************
 * FPGA register read
 * @param dev   : device pointer
 * @param offset : FPGA register offset
 * @return : 16-bit value read from register
 */
u16 dt78xx_fpga_read(struct device *dev, u32 offset)
{
    u16 data;
    unsigned long flags;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);    
    
    spin_lock_irqsave(&dt_dev->lock, flags);
    data = ioread16(dt_dev->fpga->addr_virt + offset);
    spin_unlock_irqrestore(&dt_dev->lock, flags);    
    
    return (data);
}
EXPORT_SYMBOL_GPL(dt78xx_fpga_read);

/**************************************************************************
 * sysfs handler to read EDMA status and registers
 * @param dev
 * @param attr  : ignored
 * @param buf   : buffer to write info into
 * @return      : length of buffer buf filled in
 */
ssize_t sysfs_edma_read(struct device *dev, struct device_attribute *attr,
                        char *buf)
{
    struct edmacc_param edma_param;
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    int len = 0;
    int i, j;
    uint32_t sl, offset;
    struct list_head *pos;
    struct device_node *node;
    struct resource res;
    void  __iomem *edma_base; 
    
    dev_lock(dt_dev);
    
    node = of_find_node_by_name(NULL, "edma");
    of_address_to_resource(node, 0, &res);
    edma_base = ioremap(res.start, resource_size(&res));
    for (i=0; i < ARRAY_SIZE(g_edmacc_reg); ++i)
    {
        offset = g_edmacc_reg[i].offset;
        for (j=0; j < g_edmacc_reg[i].regs; ++j, offset += sizeof(uint32_t))
        {
            u32 val = readl((void *)((u32)edma_base + offset));
            if (val)
            {
                len += scnprintf(buf +len, PAGE_SIZE-len,"%08x %s%d=%08x\n", 
                                 res.start+offset, g_edmacc_reg[i].name,j,val);
            }
        }
    }
    iounmap(edma_base);
    of_node_put(node);
    
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);
        //if the subsystem does not use dma, then skip it
        if (!daq->dma)
        {
            continue;
        }
        len += scnprintf(buf +len, PAGE_SIZE-len,
                         "\n%s, chan %d slot %d link %d"
                         " gpio %d irq %d "
#ifdef DEBUG            
                         " sg_active %d submitted %u complete %u Qempty %u"
#endif            
                         " (%d)%s\n", 
                         daq->dma->name,
                         daq->dma->dma_chan, daq->dma->slot, daq->dma->link,
                         daq->dma->gpio_trig, daq->dma->event_irq,
#ifdef DEBUG            
                         daq->dma->sg_active, daq->dma->req_submitted, 
                         daq->dma->req_completed, daq->dma->queue_empty,
#endif                   
                         daq->dma->dma_status,
                         (daq->dma->dma_status==DMA_SUCCESS)?"COMPLETE":
                         (daq->dma->dma_status==DMA_IN_PROGRESS)?"IN_PROGRESS":
                         (daq->dma->dma_status==DMA_PAUSED)?"PAUSED":"unknown");

        for (i=0, sl=daq->dma->slot; i < MAX_EDMA_PARAM; ++i)
        {
            edma_read_slot(sl, &edma_param);

            len += scnprintf(buf +len, PAGE_SIZE-len,
                             "EDMA PaRAM[%d] {", sl);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                             "opt %0x,",edma_param.opt);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                           "src %0x,",edma_param.src);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                           "a_b_cnt %0x,",edma_param.a_b_cnt);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                           "dst %0x,",edma_param.dst);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                           "src_dst_bidx %0x,",edma_param.src_dst_bidx);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                           "link_bcntrld %0x,",edma_param.link_bcntrld);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                           "src_dst_cidx %0x,",edma_param.src_dst_cidx);
            len += scnprintf(buf +len, PAGE_SIZE-len,
                           "ccnt %0x}\n",edma_param.ccnt);
            if (sl != daq->dma->link)
               sl = daq->dma->link; 
        }
    }   
    dev_unlock(dt_dev);
    return (len);
}

/**************************************************************************
 * sysfs function to print out the contents of each daq subsystem's request list
 * and miscelleneous important information
 * @param dev
 * @param attr
 * @param buf
 * @return : length of buffer filled in
 */
ssize_t sysfs_aio(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct dt78xx_device *dt_dev = dev_get_drvdata(dev);
    int i, len = 0;
    struct list_head *req;
    struct list_head *pos;
    
    dev_lock(dt_dev);
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        struct daq_dma_resource *dma;
        daq = list_entry(pos, struct daq_subsystem, daq_list);
        dma = daq->dma;
        if (!dma)
        {
            continue;
        }
        list_for_each(req, &dma->req_list)
        {
            struct aio_request *aio;
            aio = list_entry(req, struct aio_request, list);
            len += scnprintf(buf +len, PAGE_SIZE-len, 
                             "%s num_sgs %lu sgs_queued %lu sgs_done %lu", 
                             dma->name, aio->num_sgs, aio->sgs_queued,
                             aio->sgs_done);
            for (i=0; (i < aio->num_sgs) && (len < PAGE_SIZE); ++i)
            {
                len += scnprintf(buf +len, PAGE_SIZE-len,
                                  ",{%p %d}",
                                  (void *)sg_dma_address(&aio->sg[i]),
                                  sg_dma_len(&aio->sg[i])
                                  );
            }
            len += scnprintf(buf +len, PAGE_SIZE-len, "\n");
        }
        if (!list_empty(&dma->req_list))
        {
            u32 sl;
            for (i=0, sl=dma->slot; i < MAX_EDMA_PARAM; ++i)
            {
                struct edmacc_param edma_param;
                edma_read_slot(sl, &edma_param);

                len += scnprintf(buf +len, PAGE_SIZE-len,
                                 "EDMA PaRAM[%d] {", sl);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                                 "opt %0x,",edma_param.opt);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                               "src %0x,",edma_param.src);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                               "a_b_cnt %0x,",edma_param.a_b_cnt);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                               "dst %0x,",edma_param.dst);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                               "src_dst_bidx %0x,",edma_param.src_dst_bidx);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                               "link_bcntrld %0x,",edma_param.link_bcntrld);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                               "src_dst_cidx %0x,",edma_param.src_dst_cidx);
                len += scnprintf(buf +len, PAGE_SIZE-len,
                               "ccnt %0x}\n",edma_param.ccnt);
                if (sl != dma->link)
                   sl = dma->link; 
            }
            
        }
    }
    dev_unlock(dt_dev);
    return len;
}
#ifdef _GPMC_DT_OVERRIDE_
/**************************************************************************
 * This overrides the GPMC config register settings set by the 
 * "ti,am3352-gpmc" driver. The device tree bindings <gpmc,reg-config1> through 
 * <gpmc,reg-config7> for each chip select register are used to write directly
 * to each chip select's GPMC_CONFIG1 - GPMC_CONFIG7 registers. 
 */ 
#define GPMC_CS0_OFFSET     (0x60)
#define GPMC_CS_SIZE        (0x30)
static int _of_gpmc_config(struct device *dev)
{
    int err =0;
    struct device_node *gpmc_node;
    struct device_node *child;
    struct resource res;
    void  __iomem *gpmc_base;
    
    /*
     * Get the base address of the GPMC so that each chip select's config 
     * registers can be accessed
     */
    gpmc_node = of_find_node_by_name(NULL, "gpmc");
    err = of_address_to_resource(gpmc_node, 0, &res);
    if (IS_ERR_VALUE(err))
    {
        err =-ENODEV;
        goto gpmc_cfg_err;
    }
    gpmc_base = ioremap(res.start, resource_size(&res));
    if (!gpmc_base)
    {
        err =-ENODEV;
        goto gpmc_cfg_err;
    }
    
    for_each_available_child_of_node(gpmc_node, child) 
    {
        int cs, cfg_reg;
        uint32_t cfg_reg_offset, cfg;
        if (of_property_read_u32(child, "reg", &cs) == 0) 
        {
            char binding[] = "gpmc,reg-config1";
            //index into binding[] for numeric character
            int nx = (int)sizeof(binding)-1-1; //-1 for terminator, -1 for 0-based
            cfg_reg_offset = GPMC_CS0_OFFSET + (GPMC_CS_SIZE *cs);
            for (cfg_reg=1; cfg_reg < GPMC_CS_NUM; ++cfg_reg)
            {
                binding[nx]='0'+cfg_reg;
                if (of_property_read_u32(child, binding, &cfg) == 0) 
                {
                    writel(cfg, gpmc_base + cfg_reg_offset);
                    dev_dbg(dev, "[%s] %s %08x=%08x\n", 
                                __func__, child->full_name, cfg_reg_offset, cfg);
                }
                cfg_reg_offset += sizeof(uint32_t);
            }
        } 
        of_node_put(child);    
    }
    
    iounmap(gpmc_base);
    
gpmc_cfg_err:    
    of_node_put(gpmc_node);  

    if (err)
    {
        dev_err(dev, "[%s] FAIL err=%d\n", __func__, err);
    }
    return (err);
}
#endif

/**************************************************************************
 * If the linked PaRAMs associated with the edma are not filled, then copy 
 * scatterlist from the queued requests to the PaRAMs. 
 * @param dma   : daq_dma_resource that has the queued requests and scatterlists
 * @param req   : Request from which scatterlist will be written to PaRAM. 
 *                If this request has no more scatterlist, then the request
 *                queue is traversed looking for a request that has pending
 *                scatterlist. Therefore, this request MUST be in the queue
 *                when this function is invoked.
 */
static void _scatterlist_queue(struct daq_dma_resource *dma, 
                               struct aio_request *req)
{    
   /*
    * If this is the first request to be queued, update the terminal count
    * and source address in the EDMA PaRAMs for direct slot and set the link
    * slot to dummy.
    * If this is the second request to be queued, update the terminal count
    * and source address in the EDMA PaRAM for link slot.
    */
    while (req && (dma->sg_active < MAX_EDMA_PARAM))
    {
        unsigned int sg_len;
        dma_addr_t sg_addr;
        //if all scatterlist in this request is done, scan subsequent queued
        //requests for the one which has at least one pending scatterlist
        while (req && (req->sgs_queued == req->num_sgs))
        {
            if (!list_is_last(&req->list, &dma->req_list))
            {
                req = list_entry(req->list.next, struct aio_request, list); 
            }
            else
            {
                req = NULL;
            }
        }
        
        //if there is a queued request, get a scatterlist from it
        if (req)
        {
            sg_addr = sg_dma_address(&req->sg[req->sgs_queued]);
            sg_len = sg_dma_len(&req->sg[req->sgs_queued]);
        }
        //if there are no more queued requests, force the PaRAM to be dummy
        else
        {
            sg_addr = DMA_POISON;
            sg_len = 0;
        }
        
        if (dma->sg_active == 0)
        {
            edma_set_transfer_params(dma->slot,sg_len,BCNT,CCNT,BCNTRLD,ASYNC);
            edma_set_transfer_params(dma->link, 0,BCNT,CCNT,BCNTRLD,ASYNC);
            if (dma->dir == DMA_DEV_TO_MEM)
            {
                edma_set_dest(dma->slot, sg_addr, INCR, W8BIT);
                edma_set_dest(dma->link, DMA_POISON, INCR, W8BIT);
            }
            else
            {
                edma_set_src(dma->slot, sg_addr, INCR, W8BIT);
                edma_set_src(dma->link, DMA_POISON, INCR, W8BIT);
            }
        }
        else
        {
            edma_set_transfer_params(dma->link,sg_len,BCNT,CCNT,BCNTRLD,ASYNC);
            if (dma->dir == DMA_DEV_TO_MEM)
            {
                edma_set_dest(dma->link, sg_addr,INCR, W8BIT);
            }
            else
            {
                edma_set_src(dma->link, sg_addr,INCR, W8BIT);
            }
        }
        if (req)
        {        
            ++dma->sg_active;
            ++req->sgs_queued;       //queued scatterlist count in request
        }
    }
}
/**************************************************************************
 * Dequeue a scatterlist that has been completed by edma
 * @param ef
 * @param req
 */
static void _scatterlist_dequeue(struct daq_dma_resource *daq, 
                                 struct aio_request *req)
{
    int pending = req->sgs_queued-req->sgs_done;
    int index = req->sgs_queued-1; //the last scatterlist in the queue
   
    while (pending && daq->sg_active)
    {
        struct edmacc_param edma_param;
        dma_addr_t sg_addr;
        sg_addr = sg_dma_address(&req->sg[index]);

        edma_read_slot(daq->link, &edma_param);
        if ((sg_addr==edma_param.src) || (sg_addr==edma_param.dst))
        {
            --daq->sg_active;
            edma_set_transfer_params(daq->link, 0,BCNT,CCNT,BCNTRLD,ASYNC);
            if (daq->dir == DMA_DEV_TO_MEM)
            {
                edma_set_dest(daq->link, DMA_POISON, INCR, W8BIT);
            }
            else
            {
                edma_set_src(daq->link, DMA_POISON, INCR, W8BIT);
            }
        }
        if (daq->sg_active)
        {
            edma_read_slot(daq->slot, &edma_param);
            if ((sg_addr==edma_param.src) || (sg_addr==edma_param.dst))
            {
#ifdef _WARN_
#warning Check if this PaRAM is in progress before nuking it    
#endif
                --daq->sg_active;
                edma_set_transfer_params(daq->slot, 0,BCNT,CCNT,BCNTRLD,ASYNC);
                if (daq->dir == DMA_DEV_TO_MEM)
                {                
                    edma_set_dest(daq->slot, DMA_POISON, INCR, W8BIT);
                }
                else
                {                
                    edma_set_src(daq->slot, DMA_POISON, INCR, W8BIT);
                }
            }
        }
        --pending;
        --index;
    }
}
/**************************************************************************
 * edma completion interrupt callback
 * @param ch        : channel
 * @param ch_status : completion status EDMA_DMA_?? from edma.h
 * @param data      : struct daq_dma_resource *
 */
static void _edma_callback(unsigned ch, u16 status, void *data)
{
    unsigned long flags;
    struct aio_request *req;
    struct aio_request *req_complete = NULL;
    struct daq_dma_resource *dma = (struct daq_dma_resource *)data;
#if 0    
    pr_info("[%s] %s status %d\n",  __func__,dma->name, status);
    //WARN_ON(status != EDMA_DMA_COMPLETE);
#endif   
    spin_lock_irqsave(&dma->daq->dt_dev->lock, flags);
    if (list_empty(&dma->req_list))
    {
        dma->dma_status = DMA_PAUSED;
        edma_pause(dma->dma_chan);
#ifdef DEBUG
        ++dma->queue_empty;
#endif    
        spin_unlock_irqrestore(&dma->daq->dt_dev->lock, flags);  
        dev_dbg_ratelimited(&dma->daq->dt_dev->pdev->dev, 
                             "[%s] %s queue empty\n", __func__,dma->name);
        if (dma->async_queue)
        {
            //pr_info("[%s] %s queue empty signal\n", __func__,dma->name);
            /* send a signal to processes that registered. By default SIGIO
             * is delivered; the user can specify some other signum using
             * fcntl(F_SETSIG) */
            kill_fasync(&dma->async_queue, SIGIO, 
                        (dma->dir==DMA_DEV_TO_MEM)?POLL_IN:POLL_OUT);
        }
        return;
    }
    
    --dma->sg_active; //one PaRAM entry done
    
    //get the request at the head of the queue & update its info
    req = list_entry(dma->req_list.next, struct aio_request, list);  
    req->actual += sg_dma_len(&req->sg[req->sgs_done]);
    ++req->sgs_done; //one scatterlist done in request
    if (status != DMA_COMPLETE) 
    {
        pr_err("[%s] ERROR %d\n", __func__,status);
        req->status = -ESTRPIPE;
    }
    
    _scatterlist_queue(dma, req);    
    
    //if this request is complete
    if (req->sgs_done == req->num_sgs)
    {
        //Dequeue this request
        list_del(&req->list); 
        req->list.next = LIST_POISON1;
        req->list.prev = LIST_POISON2;
        req_complete = req;
#ifdef DEBUG
        ++dma->req_completed;
#endif    
    }
    
    //if the edma request uses a gpio event, then clear GPIO_EOI register
    if (gpio_is_valid(dma->gpio_trig))
    {
        _gpio_eoi_clr(dma->daq->dt_dev, dma->gpio_trig);
    }
    //Clear the FPGA DMA status bit corresponding to the DMA channel
    if (dma->fpga_dma_clr.reg_offset > 0)
    {
        iowrite16(dma->fpga_dma_clr.reg_value, 
                  (dma->daq->dt_dev->fpga->addr_virt + dma->fpga_dma_clr.reg_offset));
    }
    
    spin_unlock_irqrestore(&dma->daq->dt_dev->lock, flags);

    //Call handler specific to subsystem
    if (dma->daq->dma_callback)
        dma->daq->dma_callback(dma->daq);
    
    //process any request that has been completed
    if (req_complete)
    {
#if 0        
        pr_info("[%s] %s req complete\n", __func__,dma->name);
#endif        
        if (req_complete->complete_cb)
            req_complete->complete_cb(req_complete);
    }
}

int dt78xx_request_queue(struct file *file, struct aio_request *req)
{
    struct daq_subsystem *daq;
    unsigned long flags;
    
    if (WARN_ON(!req->num_sgs))
    {
        return -EINVAL;
    }
    
    //file->private_data points to the miscdev member in struct daq_subsystem
    daq = container_of(file->private_data, struct daq_subsystem, miscdev);
    //if this daq_subsystem does not use dma then return error
    if (WARN_ON(!daq || !daq->dma))
    {
        return -ENODEV;
    }
    
    spin_lock_irqsave(&daq->dt_dev->lock, flags);
    req->sgs_done = 0;
    req->sgs_queued = 0;
    req->actual = 0;

    list_add_tail(&req->list, &daq->dma->req_list); 
    _scatterlist_queue(daq->dma, req);
#ifdef DEBUG
    ++daq->dma->req_submitted;
#endif    
    if (daq->dma->dma_status != DMA_PAUSED)
    {
        spin_unlock_irqrestore(&daq->dt_dev->lock, flags);
        return 0;
    }
    
    //If the DMA was paused due to queue empty, get it going again
#if 1        
    dev_dbg_ratelimited(&daq->dt_dev->pdev->dev, "[%s] %s dma unpaused\n",
         __func__, daq->dma->name);
#endif        
    daq->dma->dma_status = DMA_IN_PROGRESS;
    edma_resume(daq->dma->dma_chan);
    /*Clear FPGA DMA status bit corresponding to the DMA channel to get new
    EDMA events */
    if (daq->dma->fpga_dma_clr.reg_offset > 0)
    {
        iowrite16(daq->dma->fpga_dma_clr.reg_value, 
                  (daq->dma->daq->dt_dev->fpga->addr_virt + 
                   daq->dma->fpga_dma_clr.reg_offset));
    }
    spin_unlock_irqrestore(&daq->dt_dev->lock, flags);
    return 0;
}

int dt78xx_request_dequeue(struct file *file, struct aio_request *req)
{
    struct daq_subsystem *daq;
    unsigned long flags;
    
    //file->private_data points to the miscdev member in struct daq_subsystem
    daq = container_of(file->private_data, struct daq_subsystem, miscdev);
     
    if ((req->list.next == LIST_POISON1)||(req->list.prev == LIST_POISON2))
    {
        dev_dbg(&daq->dt_dev->pdev->dev, "[%s] queue empty\n",__func__);
        return -EINVAL;
    }
    
    //Dequeue this request and poison it to check for errors later
    list_del(&req->list); 
    req->list.next = LIST_POISON1;
    req->list.prev = LIST_POISON2;
    
    if (daq->dma)
    {
        spin_lock_irqsave(&daq->dt_dev->lock, flags);
        _scatterlist_dequeue(daq->dma, req);
#ifdef DEBUG
        --daq->dma->req_submitted;
#endif    
        spin_unlock_irqrestore(&daq->dt_dev->lock, flags);
    }
    return 0;
}

/******************************************************************************
 * File open handler for the daq subsystem. This is called from the .open
 * handler in the file_operations for each different type of subsystem or the
 * .open handler can directly point to this
 * @param file
 * @return -EBUSY if the daq_subsystem is already opened via a file, 0=success
 */
int dt78xx_fopen(struct file *file)
{
    struct daq_subsystem *daq;
    int opened;
    unsigned long flags;
    daq = container_of(file->private_data, struct daq_subsystem, miscdev);
    
    //prevent multiple concurrent opens to the same file
    opened =__atomic_add_unless(&daq->open, 1, 1);
    if (opened)
    {
        return (-EBUSY);
    }
    
    // increment our usage count for the device 
    kref_get(&daq->dt_dev->kref);
    
    //initialize othe members of the daq_subsystem
    if (daq->dma)
    {
        spin_lock_irqsave(&daq->dt_dev->lock, flags);
        daq->dma->async_queue = NULL;
#ifdef DEBUG
        daq->dma->req_submitted = 0;
        daq->dma->req_completed = 0;
        daq->dma->queue_empty = 0;
#endif    
        spin_unlock_irqrestore(&daq->dt_dev->lock, flags);
    }
    return (0);
}
EXPORT_SYMBOL_GPL(dt78xx_fopen);

/******************************************************************************
 * File close handler for the daq subsystem. This is called from the .release        = _fclose,
 * handler in the file_operations for each different type of subsystem or the
 * .release handler can directly point to this
 * @param file
 */
void dt78xx_fclose(struct file *file)
{
    struct daq_subsystem *daq;
    
    daq = container_of(file->private_data, struct daq_subsystem, miscdev);
    
    if (daq->dma)
    {
        dt78xx_edma_stop(file);
        //remove this filp from the asynchronously notified filp's
        fasync_helper(-1, file, 0, &daq->dma->async_queue);
#ifdef DEBUG
        dev_dbg(&daq->dt_dev->pdev->dev, 
                "[%s] %s sumbitted %u completed %u Qempty %u\n",
            __func__,daq->dma->name, daq->dma->req_submitted, daq->dma->req_completed,
            daq->dma->queue_empty);
#endif    
    }

    atomic_dec_return(&daq->open); 
    
    kref_put(&daq->dt_dev->kref, dt78xx_cleanup);
}
EXPORT_SYMBOL_GPL(dt78xx_fclose);

/******************************************************************************
 * This is called from the .fasync handler in the file_operations for each
 * different type of subsystem or the
 * .fasync handler can directly point to this
 * @param fd    : see file_operations .fasync()
 * @param file  : see file_operations .fasync()
 * @param on    : see file_operations .fasync()
 * @return : returns negative on error, 0 if it did no changes and positive if
 *           it added/deleted the entry
 */
int dt78xx_fasync(int fd, struct file *file, int on)
{
    int err;
    struct daq_subsystem *daq;
    daq = container_of(file->private_data, struct daq_subsystem, miscdev);

    err = fasync_helper(fd, file, on, &daq->dma->async_queue);
    /* negative on error, 0 if it did no changes and positive if it 
     * added/deleted the entry
     */
    if (err < 0)
    {
        dev_err(&daq->dt_dev->pdev->dev, "[%s] %s fasync_helper %d", 
                                __func__, daq->dma->name, err);
    }
    return err;
}
EXPORT_SYMBOL_GPL(dt78xx_fasync);

/**************************************************************************
 * Return a pointer to struct dt78xx_device from the file pointer.
 * Note that misc_open() in misc.c sets file->private_data to point to 
 * miscdev. This in turn is a member in struct daq_subsystem
 */
struct dt78xx_device * file_to_dt78xx(struct file *f)
{
    struct daq_subsystem *p;
    p = container_of(f->private_data, struct daq_subsystem, miscdev);
    return (p->dt_dev);
}
EXPORT_SYMBOL_GPL(file_to_dt78xx);

/******************************************************************************
 * This is called by from a subsystem to stop DMA operations
 * @param fd    : see file_operations 
 * @return : 0
 */
int dt78xx_edma_stop(struct file *file)
{
    struct daq_subsystem *daq;
    unsigned long flags;
    
    daq = container_of(file->private_data, struct daq_subsystem, miscdev);
    
    if (daq->dma)
    {
        spin_lock_irqsave(&daq->dt_dev->lock, flags);

        edma_stop(daq->dma->dma_chan);
        if (daq->dma->event_irq)
        {
            disable_irq(daq->dma->event_irq);
        }
        daq->dma->dma_status = DMA_SUCCESS;
        spin_unlock_irqrestore(&daq->dt_dev->lock, flags);
#if 0
        dev_dbg(&daq->dt_dev->pdev->dev, "[%s] %s\n", __func__,daq->dma->name);
#endif        
    }
    return 0;
}
EXPORT_SYMBOL_GPL(dt78xx_edma_stop);

/******************************************************************************
 * This is called from a subsystem to start DMA operations
 * @param fd    : see file_operations 
 * @return : 0 for success, <0 for failure
 */
int __must_check dt78xx_edma_start(struct file *file)
{
    struct daq_subsystem *daq;
    unsigned long flags;
    int err = 0;
    
    daq = container_of(file->private_data, struct daq_subsystem, miscdev);
    
    if (daq->dma)
    {
        spin_lock_irqsave(&daq->dt_dev->lock, flags);

        err = (daq->dma->dma_status == DMA_SUCCESS)?0:-EBUSY;
        if (!err)
        {
            //if the edma request uses a gpio event, then clear GPIO_EOI register
            if (gpio_is_valid(daq->dma->gpio_trig))
            {
                _gpio_eoi_clr(daq->dt_dev, daq->dma->gpio_trig);
            }
            //Clear the FPGA DMA status bit corresponding to the DMA channel
            if (daq->dma->fpga_dma_clr.reg_offset > 0)
            {
                iowrite16(daq->dma->fpga_dma_clr.reg_value, 
                          (daq->dma->daq->dt_dev->fpga->addr_virt + 
                           daq->dma->fpga_dma_clr.reg_offset));
            }
            daq->dma->dma_status = DMA_IN_PROGRESS;
            if (daq->dma->event_irq)
            {
                enable_irq(daq->dma->event_irq);
            }
            edma_start(daq->dma->dma_chan);
        }
        spin_unlock_irqrestore(&daq->dt_dev->lock, flags);
        if (err)
            dev_err(&daq->dt_dev->pdev->dev, "[%s] %s dma_status %d\n", 
                                     __func__,daq->dma->name, daq->dma->dma_status);
    }
    return err;
}
EXPORT_SYMBOL_GPL(dt78xx_edma_start);

/***************************************************************************
 * Allocate and initialize edma resources for a subsystem. Refer to section
 * 11.3 in AM335x Technical Ref Manual
 * @param pdev
 * @param dma
 * @param dir
 * @param callback : callback handling DMA completion
 * @param event_q
 * @return 0=success, <0 = error
 */
static int __must_check _edma_init(struct platform_device *pdev, 
                                   struct daq_dma_resource *dma, 
                                   enum dma_transfer_direction dir, 
                                   dma_callback callback, 
                                   enum dma_event_q event_q)
{
    int ret, i;
    struct edmacc_param edma_params;
    
    // Allocate parameter slot in the Parameter RAM (PaRAM) that is paired with
    // the DMA channel
    ret = edma_alloc_channel(dma->dma_chan, callback, dma, event_q);
    if (ret < 0) 
    {
        dma->dma_chan = 0;
        dma->link = 0;
        dev_err(&pdev->dev, "[%s] ERROR edma_alloc_channel\n", __func__);
        return ret;
    }
    dma->slot = ret;

    /* allocate link channels */
    ret = edma_alloc_slot(EDMA_CTLR(dma->slot), EDMA_SLOT_ANY);
    if (ret < 0) 
    {
        edma_free_channel(dma->slot);
        dma->dma_chan = 0;
        dma->link = 0;
        dev_err(&pdev->dev, "[%s] ERROR edma_alloc_slot\n", __func__);
        return ret;
    }
    dma->link = ret;
    dma->dir = dir;
    INIT_LIST_HEAD(&dma->req_list);
    dma->sg_active = 0;
    dma->dma_status = DMA_SUCCESS;
    
    //Initialize the PaRAM entries for the edma channel
    for (i=0; i< MAX_EDMA_PARAM; ++i)
    {
        u32 slot = (i==0) ? dma->slot : dma->link; 
        if (dir == DMA_DEV_TO_MEM)
        {
            //read from external fifo
            edma_set_src(slot, //parameter RAM slot being configured
                         dma->fifo.addr_dma, //src physical addr
                         INCR,
                         W8BIT);
        }
        else
        {
            //write to external fifo
            edma_set_dest(slot, //parameter RAM slot being configured
                         dma->fifo.addr_dma, //dest physical addr
                         INCR,
                         W8BIT);
        }

        edma_set_src_index(slot, 0, 0);
        edma_set_dest_index(slot, 0, 0);

        //Dummy PaRAM Set. See section 11.3.3.4 in AM335x TRM. acnt loaded when
        //async IO request is queued
        edma_set_transfer_params(slot, 0,BCNT, CCNT,BCNTRLD, ASYNC);
        //Link between slots; dma->slot=>dma->link, dma->link=>dma->link
        edma_link(slot, dma->link);
        /*
         * Issue transfer completion IRQ when the channel completes
         * a transfer, and then always reload from the same slot
         */
        edma_read_slot(slot, &edma_params);
        edma_params.opt &= ~(TCCMODE |EDMA_TCC(0x3f) |ITCINTEN |TCCHEN |ITCCHEN);
        edma_params.opt |= (TCINTEN |
                           EDMA_TCC(EDMA_CHAN_SLOT(dma->slot)));
        edma_write_slot(slot, &edma_params);
    }
   
    return 0;
}

/***************************************************************************
 * Deallocate and clean up edma resource
 * @param pdev
 * @param ef
 */
static void _edma_free(struct platform_device * pdev, struct daq_dma_resource *ef)
{
    if (ef)
    {
        if (ef->link)
        {
            edma_free_slot(ef->link);
        }
        if (ef->slot)
        {
            edma_free_channel(ef->slot);
        }
        if (ef->event_irq)
        {
            disable_irq(ef->event_irq);
            devm_free_irq(&pdev->dev, ef->event_irq, ef);
        }
        if (gpio_is_valid(ef->gpio_trig))
        {
            gpio_free(ef->gpio_trig);
        }
    }
}

/***************************************************************************
 * Verify that the specified edma channel has an external event mapped in the
 * xbar registers tpcc_evt_mux_0_3 through tpcc_evt_mux_60_63
 *
 * There is a bug in the 3.13.2 kernel that fails to parse the device tree and
 * set the registers. The bug was patched with code from 3.8. However, there is
 * no guarantee that it will not resurface in some other kernel version. Hence,
 * the need to sanity check
 * @param chan : non-zero EDMA channel
 * @return : 0 = success, <0 failure
 */
static int __must_check _of_check_xbar(struct platform_device *pdev, int edma_chan)
{
    struct device *dev = &pdev->dev;
    struct device_node *node;
    int err = -EINVAL;
    struct property *prop;
    size_t len;
    u32 *val;
    
    node = of_find_node_by_name(NULL, "edma");
    if (!node)
    {
        return -ENODEV;
    }
    prop = of_find_property(node, "ti,edma-xbar-event-map", &len);
    if (!prop)
    {
        dev_err(dev, "[%s] ERROR \"ti,edma-xbar-event-map\" missing\n", __func__);
        err = -EINVAL;
        goto of_check_xbar_fail;
    }
    if (!prop->value)
    {
        dev_err(dev, "[%s] ERROR \"ti,edma-xbar-event-map\" value\n", __func__);
        err = -ENODATA;
        goto of_check_xbar_fail;
    }
    /*
     * The edma-xbar-event-map specifies an array of tuples <event, chan>
     * where event is the external event that is mapped to the edma chan.
     */
    val = (u32 *)prop->value;
    len /= sizeof(u32);
    while (len)
    {
        s16 chan, event;
        event = be32_to_cpu(*val++);
        chan = be32_to_cpu(*val++);
        len -= 2;;
        if (chan == edma_chan) //edma-xbar-event-map channel matches 
        {
            struct resource res;
            int ret;
            /*
             * Verify the xbar setting in the corresponding 
             * tpcc_evt_mux_xx_xx reg
             */
            ret = of_address_to_resource(node, 1, &res);
            if (!IS_ERR_VALUE(ret))
            {
                void *xbar = ioremap(res.start, resource_size(&res));
                if (xbar)
                {
                    u32 reg_val, offset;
                    offset = (chan/sizeof(u32))*sizeof(u32);
                    reg_val = readl((void *)((u32)xbar + offset));
                    reg_val >>= (chan - offset)*8;
                    reg_val &= 0xff;
                    if (reg_val == event)
                    {
                        dev_dbg(dev, "[%s] event %d mapped to chan %d\n",
                                 __func__, event, chan);
                        err =0;
                    }
                }
            }
            break;
        }
    }

of_check_xbar_fail:   
    of_node_put(node); 
    
    return (err);
}

/**************************************************************************
 * ISR for the edma event input.
 * @param irq
 * @param data : struct daq_subsystem *
 * @return IRQ_HANDLED
 */
static irqreturn_t _edma_event_handler(int irq, void *data)
{
#if 0    
    unsigned long flags;
    struct daq_dma_resource * dma = (struct daq_dma_resource *)data;
    
    spin_lock_irqsave(&dma->spnlk, flags);
    spin_unlock_irqrestore(&dma->spnlk, flags);
    pr_info("[%s] %s\n", __func__, dma->name);
#endif    
    
    //Add functionality here.
    
    return IRQ_HANDLED;
}

/**************************************************************************
 * Parse the device tree for a daq subsystem child node. See the device tree
 * bindings documented in dt78xx.dts
 * @param pdev : struct platform_device *
 * @param child : daq susbsystem child node
 * @return : NULL = error, non-NULL = pointer to allocated struct daq_subsystem
 * with all defaults members initailized
 */
static struct daq_subsystem * __must_check _daq_subsys_alloc(
                    struct platform_device *pdev,  struct device_node *node)
{
    struct daq_subsystem *daq = NULL;
    struct device *dev = &pdev->dev;
    struct of_phandle_args dma_spec;
    int err = 0;
    int cs;
    const char *dma_dir;    
    
    daq = devm_kzalloc(dev, sizeof(struct daq_subsystem), GFP_KERNEL);
    if (!daq)
    {
        return NULL;
    }
    daq->dt_dev = platform_get_drvdata(pdev);
    daq->node = node;
    of_node_get(daq->node); //IMPORTANT : increment node's ref count
    daq->miscdev.parent = dev;
    
    //If the subsystem does not use DMA then we're done initializating
    if (!of_find_property(node, "dmas", NULL))
    {
        return daq;
    }
    
    //"dmas" binding must also have a "dma-names" property in device tree with
    //value either "in" or "out"
    dma_dir = (const char *)of_get_property(daq->node, "dma-names", NULL);
    if (!dma_dir || (strcmp(dma_dir, "in") && strcmp(dma_dir, "out")))
    {
        dev_err(dev, "[%s] ERROR %s dma-names binding\n", __func__, node->name);
        goto _subsys_err;
    }
   
    //If the subsystem uses DMA, then DMA channel is mandatory
    memset(&dma_spec, 0, sizeof(dma_spec));
    err = of_parse_phandle_with_args(node, "dmas", "#dma-cells", 0, &dma_spec);
    if (err || (dma_spec.args_count < 1))
    {
        goto _subsys_err;
    }
    //Get the mandatory chip select for this subsystem's fifo
    if (of_property_read_u32(node, "fifo-cs", &cs))
    {
        dev_err(dev, "[%s] ERROR %s fifo-cs missing\n", __func__, node->name);
        goto _subsys_err;
    }
    
    daq->dma = devm_kzalloc(dev, sizeof(struct daq_dma_resource), GFP_KERNEL);
    if (!daq->dma)
    {
        goto _subsys_err;
    }

    daq->dma->daq = daq; //tie the dma back to the daq subsystem
    daq->dma->name = node->name;
    daq->dma->dma_chan = dma_spec.args[0];

    //check that the external event is mapped to the DMA channel
    err = _of_check_xbar(pdev, daq->dma->dma_chan);
    if (err)
    {
        goto _subsys_err;
    }
    of_node_put(dma_spec.np);
    
    /* Does the DMA channel use a gpio as event input instead of 
     * x_dma_event_intr0/1/2 ?? This is defined by the "dma-gpios" binding in the
     * device tree. If the binding is absent, the following will return 
     * -ENOENT */
    daq->dma->gpio_trig = of_get_named_gpio(node, "dma-gpios", 0);
    if (gpio_is_valid(daq->dma->gpio_trig)) //EDMA event generated by gpio
    {
        //request the gpio and set its direction to input
        err = gpio_request(daq->dma->gpio_trig, NULL);
        if (err)
        {
            dev_err(dev, "[%s] ERROR %d gpio_request\n",__func__, err);
            goto _subsys_err;
        }
        err = gpio_direction_input(daq->dma->gpio_trig);
        if (err)
        {
            dev_err(dev, "[%s] ERROR %d gpio_direction_input\n",__func__, err);
            goto _subsys_err;
        }
        _gpio_eoi_clr(daq->dt_dev, daq->dma->gpio_trig);
   
       /* 
        * If a gpio is used as the edma event, then map it to the corresponding 
        * interrupt. 
        */
        daq->dma->event_irq = gpio_to_irq(daq->dma->gpio_trig);
    }
    else
    {
        /* Parse the "interrupts" property to find interrupts corresponding to
         * edma events.  For xdma_event_intr1/2, map the non-zero
         * interrupt specified in the node's device tree "interrupts" property
         */ 
        daq->dma->event_irq = irq_of_parse_and_map(node, 0); 
    }
    
    //Install interrupt handler, if an interrupt is specified
    if (daq->dma->event_irq > 0)
    {
        err = devm_request_irq(dev, daq->dma->event_irq, _edma_event_handler, 
                               IRQF_TRIGGER_RISING , NULL, daq->dma);
        if (err)
        {
            dev_err(dev, "[%s] ERROR %d devm_request_irq\n", __func__, err);
            goto _subsys_err;
        }
        disable_irq(daq->dma->event_irq);
    }
    
    //Get the FIFO address mapped to the GPMC chip select
    err = _gpmc_resource_get(dev, cs, &daq->dma->fifo);
    if (err)
    {
        dev_err(dev, "[%s] %s CS%d fifo resource allocation failed\n", 
                 __func__, node->name, cs);
        goto _subsys_err;
    }
    
    //Initailze the edma chip's PaRAM registers according to DMA direction
    if (!strcmp(dma_dir, "out"))
    {
        err = _edma_init(pdev, daq->dma, DMA_MEM_TO_DEV,_edma_callback,
                         EVENTQ_DEFAULT);
        if (err)
        {
            dev_err(dev, "[%s] ERROR %d _edma_init out\n", __func__, err);
            goto _subsys_err;
        }
    }
    else if (!strcmp(dma_dir, "in"))
    {
        err = _edma_init(pdev, daq->dma, DMA_DEV_TO_MEM,_edma_callback,
                         EVENTQ_DEFAULT);
        if (err)
        {
            dev_err(dev, "[%s] ERROR %d _edma_init in\n", __func__, err);
            goto _subsys_err;
        }
    }

    //If the device tree specifies an fpga reg & data to clear edma completion
    err = _of_parse_fpga_dma_clr(node, &daq->dma->fpga_dma_clr.reg_value);
    daq->dma->fpga_dma_clr.reg_offset = err;
    
    dev_dbg(dev, "[%s] %s chan %d irq %d dma addr %x fpga_dma_clr{%#x=%#x}\n", 
            __func__, daq->dma->name, daq->dma->dma_chan, daq->dma->event_irq,
            daq->dma->fifo.addr_dma, daq->dma->fpga_dma_clr.reg_offset,
            daq->dma->fpga_dma_clr.reg_value);
    return (daq);
    
_subsys_err:
    of_node_put(dma_spec.np);
    if (daq->dma)
    {
        devm_kfree(dev, daq->dma);
    }
    devm_kfree(dev, daq);
    return NULL;
}

/**************************************************************************
 * Deallocates all resources and cleans up. This must be called from the .remove
 * handler of the device specific KLM as the *LAST* step
 * @param pdev : platform device pointer
 */
void dt78xx_free(struct platform_device *pdev)
{
    struct dt78xx_device *dt_dev = platform_get_drvdata(pdev);
    if (dt_dev)
    {
        kref_put(&dt_dev->kref, dt78xx_cleanup);
    }
    pr_debug(DRIVER_NAME ": %s\n", __func__);
}
EXPORT_SYMBOL_GPL(dt78xx_free);

/**************************************************************************
 * Get the base addresses of the gpio chip in the AM335x by parsing the
 * device tree
 * @param pdev : platform device pointer
 * @return : 0=success, -ve=error
 */
static int __must_check _of_gpio_get(struct platform_device *pdev)
{
    struct dt78xx_device *dt_dev;
    struct resource res;
    const char *hwmods;
    int ret;
    void  __iomem *base;  
    int i;
    struct device_node *node;
    struct device *dev;
    
    dev = &pdev->dev;
    node =NULL; //start at the top of the dts
    dt_dev = platform_get_drvdata(pdev);
    
    for (i=0; i<4; ++i) //for each of node "gpio0"..."gpio3"
    {
        node = of_find_node_by_name(node, "gpio");
        if (!node) //no more nodes named "gpio"
        {
            ret = -ENODEV;
            dev_err(dev, "[%s] ERROR of_find_node_by_name gpio%d\n", 
                    __func__, i);
            break;
        }
        ret = of_address_to_resource(node, 0, &res);
        if (IS_ERR_VALUE(ret))
        {
            of_node_put(node);
            ret = -EINVAL;
            dev_err(dev, "[%s] ERROR of_address_to_resource gpio%d\n", 
                    __func__, i);
            break;
        }        
        base = ioremap(res.start, resource_size(&res));
        hwmods = of_get_property(node, "ti,hwmods",NULL);
        //the gpio nodes can be in any order in the dts; hence compare and
        //select the corresponding array index
        if (of_prop_cmp(hwmods, "gpio1") == 0)
        {
            dt_dev->gpio_base[0]=base;
        }
        else if (of_prop_cmp(hwmods, "gpio2") == 0)
        {
            dt_dev->gpio_base[1]=base;
        }
        else if (of_prop_cmp(hwmods, "gpio3") == 0)
        {
            dt_dev->gpio_base[2]=base;
        }
        else if (of_prop_cmp(hwmods, "gpio4") == 0)
        {
            dt_dev->gpio_base[3]=base;
        }
        else
        {
            of_node_put(node);
            ret = -EINVAL;
            dev_err(dev, "[%s] ERROR %s unknown\n",__func__, hwmods);
            break;
        }
        of_node_put(node);
    }
    return (ret);
}

static int __must_check _gpmc_resource_get(struct device *dev, int cs, struct gpmc_res *ret)
{
    void __iomem  *virt;
    struct resource  res;
    struct device_node *gpmc_node, *child;
    int tmp;
    int err = -ENODEV;
    
    gpmc_node = of_find_node_by_name(NULL, "gpmc");
    for_each_available_child_of_node(gpmc_node, child) 
    {   
        if (of_property_read_u32(child, "reg", &tmp) == 0)
        {
            if ((tmp==cs) && !of_address_to_resource(child, 0, &res))
            {
                virt = ioremap(res.start, resource_size(&res));
                ret->addr_dma = res.start;
                ret->addr_virt = virt;
                ret->addr_range = resource_size(&res);
                of_node_put(child);
                err = 0;
                dev_dbg(dev,"[%s] cs%d addr_dma=%x range=%x addr_virt=%p\n",
                         __func__, cs, res.start, resource_size(&res),virt);
                break; //done
            }
        }
        of_node_put(child);
    }
    of_node_put(gpmc_node);
    
    if (err)
    {
        dev_err(dev, "[%s] ERROR alloc CS%d resource\n", __func__, cs);
    }
    return (err);
}
/**************************************************************************
 * Unmap the virtual addr and memory allocated to a GPMC child node. 
 * @param pdev
 * @param gpmcd
 */
static void _gpmc_resource_free(struct platform_device *pdev, 
                             struct gpmc_res *gpmcd)
{
    if (!gpmcd)
    {
        return;
    }
    if (gpmcd->addr_virt)
    {
        iounmap(gpmcd->addr_virt);
    }
}

/**************************************************************************
 * Get the i2c client for the serial eeprom
 * @param pdev
 * @return : <0 =error
 */
static int __must_check _of_eeprom_get(struct platform_device *pdev)
{
    struct dt78xx_device *dt_dev;
    struct device_node *node, *node1;
    struct device *dev;
    int err = -ENODEV;
    
    dev = &pdev->dev;
    dt_dev = platform_get_drvdata(pdev);
    
    node1 = NULL; //start at the top of the dts
    while ((node = of_find_node_by_name(node1, "i2c")) != NULL) 
    {
        struct i2c_adapter *adap;
        struct device_node *child;
        adap = of_find_i2c_adapter_by_node(node);
        for_each_available_child_of_node(node, child)
        {
            if (child->name && (strncasecmp(child->name, "eeprom", 6) == 0))
            {
                u32 addr;
                struct i2c_board_info info;
                memset(&info, 0, sizeof(info));
                
                if ((err=of_property_read_u32_index(child, "reg", 0, &addr)) < 0)
                    dev_err(dev, "[%s] ERROR missing addr", __func__);
                else
                {
                    info.addr = addr;
                    strlcpy(info.type, "eeprom", I2C_NAME_SIZE);
                    dt_dev->eeprom = i2c_new_device(adap, &info);
                    err = 0;
                    break;
                }
            }
            of_node_put(child);
        }
        
        if (adap)
            put_device(&adap->dev);
        of_node_put(node1);
        node1 = node;
        if (!dt_dev->eeprom)
            break;
    }
    of_node_put(node);
    
    if (err)
        dev_err(dev, "[%s] ERROR %d\n", __func__, err);
    
    return (err);
}

/**************************************************************************
 * This MUST be called as the first step from the board specific drivers's
 * .probe handler.
 */
int __must_check dt78xx_init(struct platform_device *pdev)
{
    struct dt78xx_device *dt_dev;
    struct device_node *node, *c_node;
    struct device *dev;
    int err = 0;
    int alloc, cs;

    dev = &pdev->dev;
    /* we only support OF */
    node = pdev->dev.of_node;
    if (node == NULL) 
    {
        dev_err(dev, "[%s] ERROR platform of_node!\n", __func__);
        return -ENODEV;
    }
    dev_dbg(dev, "[%s] platform_device %s device_node %s full_name %s\n", 
                            __func__, pdev->name,node->name, node->full_name);

#ifdef _GPMC_DT_OVERRIDE_
    //configure and/or override GPMC config reg values set by "ti,am3352-gpmc"
    _of_gpmc_config(dev);
#endif
    //Allocate a block of memory for struct dt78xx_device 
    alloc = sizeof(struct dt78xx_device);//for core device
    dt_dev = devm_kzalloc(dev, alloc, GFP_KERNEL);
    if (dt_dev == NULL)
    {
        dev_err(dev, "[%s] ERROR alloc device\n", __func__);
        return (-ENOMEM);
    }
    
    dt_dev->pdev = pdev;
    pdev->dev.platform_data = dt_dev; //Not used anymore
    platform_set_drvdata(pdev, dt_dev); //calls dev_set_drvdata
    spin_lock_init(&dt_dev->lock);
    mutex_init(&dt_dev->mutex);
    kref_init(&dt_dev->kref);
    INIT_LIST_HEAD(&dt_dev->daq_list);  
    /* 
     * Must check if the DMA controller can properly address 32-bit
     * addresses. See Documentation/DMA-API-HOWTO.txt and
     * section 7.1.3.3.8.1 Chip-Select Base Address and Region Size in the 
     * AM335x TRM. Note that checking for 28 to 31 bit address fails
     * 
     * See "DMA addressing limitations" in DMA-API-HOWTO.txt, the kernel assumes
     * that your device can address the full 32-bits. 
     */
    pdev->dev.dma_mask = &dt_dev->dma_mask;
    pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
    if (dma_set_mask(dev, DMA_BIT_MASK(32))) 
    {
        dev_err(dev, "[%s] ERROR dma_set_mask\n", __func__);
        err = -EINVAL;
        goto probe_fail;
    }
    if (dma_set_coherent_mask(dev, DMA_BIT_MASK(32))) 
    {
        dev_err(dev, "[%s] ERROR dma_set_coherent_mask\n", __func__);
        err = -EINVAL;
        goto probe_fail;
    }

    dt_dev->pinctrl = devm_pinctrl_get_select_default(&pdev->dev);
    if (IS_ERR(dt_dev->pinctrl))
    {
        dt_dev->pinctrl = NULL;
        dev_err(dev,
                 "[%s] pins are not configured from the driver\n", 
                 __func__);
        goto probe_fail;
    }
        
    // Get the base address of the gpio chip
    if ((err = _of_gpio_get(pdev)))
        goto probe_fail;
    
    //Get the FPGA's address
    if (of_property_read_u32(node, "fpga-cs", &cs))
    {
        dev_err(dev, "[%s] ERROR fpga-cs missing\n",  __func__);
        goto probe_fail;
    }
    dt_dev->fpga = devm_kzalloc(dev, sizeof(struct gpmc_res), GFP_KERNEL);
    if (!dt_dev->fpga)
    {
        dev_err(dev, "[%s] ERROR FPGA malloc failed\n", __func__);
    }
    if (_gpmc_resource_get(dev, cs, dt_dev->fpga))
    {
        dev_err(dev, "[%s] ERROR FPGA resource allocation failed\n",__func__);
        goto probe_fail;
    }
    
    if ((err = _of_eeprom_get(pdev)))
        goto probe_fail;
        
    /*************** Allocate subsystems  ***************
     * The subsystems are specified in the device tree as children of the
     * GPMC child node tied to the fpga
     */
    for_each_available_child_of_node(node, c_node) 
    { 
        struct daq_subsystem *daq;
        dev_dbg(dev, "[%s] child name %s full %s\n", 
                 __func__, c_node->name, c_node->full_name);
        daq = _daq_subsys_alloc(pdev, c_node);
        if (daq)
        {
            list_add_tail(&daq->daq_list, &dt_dev->daq_list); 
        }
        of_node_put(c_node);
    }
    
    /*
     * Create sysfs links for debug. Note that the group name reflects the
     * name of the device which invokes dt78xx_init()
     */
    g_dt78xx_attr_group.name = dev_driver_string(dev);
    err = sysfs_create_group(&pdev->dev.kobj, &g_dt78xx_attr_group);
    if (err != 0)
    {
        dev_err(dev, "\n[%s] ERROR sysfs_create_group\n", __func__);
    }

    dev_info(dev , "[%s] version %s OK\n", __func__, DT78XX_VERSION);
    return 0;

probe_fail:
    dt78xx_free(pdev);
    pr_err("[%s] ERROR %d\n",  __func__, err);
   
    return err;
}
EXPORT_SYMBOL_GPL(dt78xx_init);

/**************************************************************************
 * Clean up when the reference count on the device goes to zero
 */
void dt78xx_cleanup(struct kref *kref)
{
    struct dt78xx_device *dt_dev;
    struct platform_device *pdev;
    struct list_head *pos;
    int i;
    dt_dev = container_of(kref, struct dt78xx_device, kref);
    pdev = dt_dev->pdev;
      
    dev_info(&pdev->dev, "%s\n", __func__);

    platform_set_drvdata(pdev, NULL);
    pdev->dev.platform_data = NULL;
    if (dt_dev->pinctrl)
    {
         devm_pinctrl_put(dt_dev->pinctrl);
    }
    _gpmc_resource_free(pdev, dt_dev->fpga);
    devm_kfree(&pdev->dev, dt_dev->fpga);
    //destroy each subsystem
    list_for_each(pos, &dt_dev->daq_list)
    {
        struct daq_subsystem *daq;
        daq = list_entry(pos, struct daq_subsystem, daq_list);
        if (daq->dma)
        {
            _gpmc_resource_free(pdev, &daq->dma->fifo);
        }
        if (daq->miscdev.name)
        {
            void *data = dev_get_drvdata(daq->miscdev.this_device);
            if (data) //free subsystem's private data
            {
                devm_kfree(&pdev->dev, data);
            }
            misc_deregister(&daq->miscdev);
        }
        of_node_put(daq->node);
        if (daq->dma)
        {
            _edma_free(pdev, daq->dma);
            devm_kfree(&pdev->dev, daq->dma);
        }
        devm_kfree(&pdev->dev, daq);
    }
    
    if (dt_dev->eeprom)
        i2c_unregister_device(dt_dev->eeprom);
    for (i=0; i<4; ++i)
    {
        if (dt_dev->gpio_base[i])
        {
            iounmap(dt_dev->gpio_base[i]);
        }
    }
    if (g_dt78xx_attr_group.name)
    {
        if (sysfs_get_dirent(pdev->dev.kobj.sd, NULL, g_dt78xx_attr_group.name))
            sysfs_remove_group(&pdev->dev.kobj, &g_dt78xx_attr_group);
    }
    if (dt_dev->priv)
        devm_kfree(&pdev->dev, dt_dev->priv);
    mutex_destroy(&dt_dev->mutex);

    devm_kfree(&pdev->dev, dt_dev);
}

/**************************************************************************
 * DT78xx base driver probe used to progarm the fpga's eeprom. 
 * This is invoked from the device tree, dt78xx_fpga_prog.dtb, that has a device
 * node with the following binding
 * compatible = "dt78xx";
 * 
 * This function drives the gpio pin to hold the fpga in reset so that spi0
 * can be used to program the mtd eeprom.
 *
 * If this probe is successful, the following mtd commands can be used to access
 * the eeprom. See the man pages for details.
 * mtdinfo -a  : list all mtd devices
 * mtd_debug read /dev/mtd0 <offset> <len> <file name> : read eeprom to file
 * mtd_debug write /dev/mtd0 <offset> <len> <file name> : write eeprom from file
 * mtd_debug erase /dev/mtd0 0 <len> : erase <len> must be multiple of 264
 * 
 * After the eeprom is programmed and verified, uEnv.txt must be edited so that
 * dt78xx_fpga_prog.dtb is no longer loaded, and instead the device's "real"
 * device tree is loaded. Then the board MUST be reset.
 */
static int dt78xx_probe(struct platform_device *pdev)
{
    struct device *dev;
    struct device_node *node;
    int fpga_reset_pin;
    enum of_gpio_flags flags;
    
    dev = &pdev->dev;
    node = pdev->dev.of_node;
    if (node == NULL) 
    {
        dev_err(dev, "[%s] No platform of_node!\n", __func__);
        return -ENODEV;
    }
    
    //Get the gpio pin that resets the fpga
    fpga_reset_pin = of_get_named_gpio_flags(node,"dt78xx,fpga_reset", 0, &flags);
    if (!gpio_is_valid(fpga_reset_pin)) 
    {
        dev_err(dev, "[%s] ERROR fpga reset pin unspecified\n", __func__);
    }
    else if (gpio_request(fpga_reset_pin, "fpga_reset"))
    {
        dev_err(dev, "[%s] ERROR gpio_request\n", __func__);
    }
    else if (gpio_direction_output(fpga_reset_pin, (flags>0))) //set gpio value
    {
        dev_err(dev, "[%s] ERROR could not set pin\n", __func__);
    }
    else
    {
        dev_dbg(dev, "[%s] fpga reset gpio%d_%d=%d\n", 
                        __func__, fpga_reset_pin/32, fpga_reset_pin%32, flags);
    }
    return 0;
}
static const struct of_device_id dt78xx_of_match[] = 
{
    { .compatible = "dt78xx", },
    { },
};
MODULE_DEVICE_TABLE(of, dt78xx_of_match);

static struct platform_driver dt78xx_driver = 
{
    .probe      = dt78xx_probe,
    .driver     = 
    {
        .name   = "dt78xx",
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(dt78xx_of_match),
    },
};

module_platform_driver(dt78xx_driver);


/*
 * Macros sets license, author and description
 */
MODULE_AUTHOR("(c) 2014 Data Translation");
MODULE_DESCRIPTION("DT78xx base driver");
MODULE_LICENSE("GPL"); /*REQUIRED */

MODULE_VERSION (DT78XX_VERSION);
