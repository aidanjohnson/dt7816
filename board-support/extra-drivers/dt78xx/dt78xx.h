#ifndef _DT78xx_H_
#define _DT78xx_H_
/*
 * @file dt78xx.h
 * @brief Macros, data types and APIs for Data Translation DT78xx data 
 * acquisiton board
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

#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/platform_data/gpio-omap.h>
#include <linux/dma-direction.h>
#include <linux/of.h>

#define DRIVER_NAME         "DT78xx"

#define dev_lock(x)    mutex_lock(&x->mutex); 
#define dev_unlock(x)  mutex_unlock(&x->mutex); //Asynchronous IO request
struct aio_request
{
    struct scatterlist  *sg;
    unsigned long       num_sgs;
    unsigned long       sgs_queued;
    unsigned long       sgs_done;
    struct list_head    list;
    int                 status;
    unsigned long       actual;
    void                (*complete_cb)(struct aio_request *req);
};

struct gpmc_res; //fpga attached to AM335x GPMC bus

struct dt78xx_device
{
    struct platform_device  *pdev;
    struct pinctrl          *pinctrl;
    u64                     dma_mask;
    spinlock_t              lock;
    struct mutex            mutex;
    struct kref             kref;       //ref counting 
    struct gpmc_res         *fpga; //fpga address mapped via gpmc chip select
    struct list_head        daq_list; //list of daq_subsystem child nodes
    void  __iomem *gpio_base[4];    //base address of gpio0-gpio3 in device tree
    struct i2c_client       *eeprom; //i2c eeprom
    void                    *priv; //private data for board specific driver
};

/**************************************************************************
 * DMA resource used by a daq_subsystem that supports asynchronous IO (AIO)
 * read or write
 */
struct daq_dma_resource;

/**************************************************************************
 * A dt78xx_device has a list of daq_subsystem. Each subsystem is exposed as
 * a virtual file handle under /dev and supports standard file operations
 * specified in the subsystem specific struct file_operations
 */
struct daq_subsystem
{
    struct device_node *node;       //ref counted device tree node
    atomic_t   open;                //0=file closed, 1=file open
    struct dt78xx_device *dt_dev;   //container device
    struct miscdevice  miscdev;     //struct file's private_data points to this
    struct list_head   daq_list;    //list of daq_subsystem this is in
    struct daq_dma_resource *dma;   //dma resource, if subsystem uses dma
    void (*dma_callback)(struct daq_subsystem *); //subsystem specific callback
                                    //that sets up a new DMA operation
};

/**************************************************************************
 * Any daq_subsystem may have one or more i2c potentiometer device interfaced to
 * the AM335x i2c0 bus. A device has one or more individual ptentiometsr; each 
 * of which has a volatile wiper and some number of non-volatile  "registers". 
 * The non-volatile  registers are used to store factory and user calibration
 */
struct dt78xx_eep_pot;

void dt78xx_cleanup(struct kref *);

ssize_t sysfs_edma_read(struct device *, struct device_attribute *,
                               char *);
ssize_t sysfs_aio(struct device *, struct device_attribute *,char *);

int dt78xx_request_queue(struct file *, struct aio_request *);
int dt78xx_request_dequeue(struct file *, struct aio_request *);

/**************************************************************************
 * Return the name of the board. The board name is the same as the node name 
 * in the device tree
 */
static inline const char *dt78xx_board_name_get(struct dt78xx_device *dt_dev)
{
    struct device_node *node = dt_dev->pdev->dev.of_node;
    return (node->name);
}

/*
 * The following APIs are GPL exported from module dt78xx.ko
 */

/***********************************************************************
 * Return a pointer to struct dt78xx_device from the subsystem's file pointer.
 * @param f struct file pointer
 * @return pointer to struct dt78xx_device which contains the file handle of
 * the subsystem
 */
struct dt78xx_device *file_to_dt78xx(struct file *f);

/***********************************************************************
 * File operations invoked from the callbacks specified in struct file_operations
 * .open => dt78xx_fopen
 * .release => dt78xx_fclose
 * .fasync => dt78xx_fasync
 * .aio_read => dt78xx_aio
 * .aio_write => dt78xx_aio
 */
int dt78xx_fopen(struct file *);
void dt78xx_fclose(struct file *);
ssize_t dt78xx_aio(struct kiocb *, const struct iovec *, 
                          unsigned long nr_segs, enum dma_data_direction dir);
int dt78xx_fasync(int, struct file *, int );

/***********************************************************************
 * DMA control APIs called from a subsystem's start/stop action if it uses
 * DMA resources
 */
int dt78xx_edma_stop(struct file *);
int __must_check dt78xx_edma_start(struct file *);

/***********************************************************************
 * This MUST be called as the first step from the board specific drivers's
 * .probe handler. This does the following
 * @li configure GPMC register values defined in the device tree
 * @li map each GPMC child's memory resources defined in the device tree
 * @li Allocate subsystems specified in the device tree as children of the
 * GPMC child node tied to the fpga
 * @li Create sysfs links for debug. Note that the group name reflects the
 * name of the device which invokes dt78xx_init()
 * 
 * @param pdev pointer to platform_device
 * @return 0 for success, negative for error
 * @see dt78xx_free
 */
 int __must_check dt78xx_init(struct platform_device *pdev);

/**  *********************************************************************
 * Deallocates all resources and cleans up. This must be called from the .remove
 * handler of the device specific KLM as the *LAST* step
 * @param pdev platform device pointer
 */
 void dt78xx_free(struct platform_device *pdev);

 /** **********************************************************************
 * FPGA register write
 * @param dev   : device pointer
 * @param offset : FPGA register offset
 * @param data  : data to write
 * @see dt78xx_fpga_read, dt78xx_fpga_rmw
 */
void dt78xx_fpga_write(struct device *dev, u32 offset, u16 data);

/** **********************************************************************
 * FPGA register read
 * @param dev   : device pointer
 * @param offset : FPGA register offset
 * @return : 16-bit value read from register
 * @see dt78xx_fpga_write, dt78xx_fpga_rmw
 */
u16 dt78xx_fpga_read(struct device *dev, u32 offset);

/** **********************************************************************
 * FPGA register read modify write
 * @param dev   : device pointer
 * @param offset : FPGA register offset
 * @param mask  : bits set in the mask are modified
 * @param data  : data is AND-ed with mask and written to register
 * @see dt78xx_fpga_write, dt78xx_fpga_read
 */
void dt78xx_fpga_rmw(struct device *dev, u32 offset, u16 mask, u16 data);

/**************************************************************************
 * Read from i2c eeprom
 * @param eeprom : i2c client
 * @param addr   : eeprom address 
 * @param buff   : buffer to read into
 * @param count    : #of bytes to read
 * @return       : <0 = failure , count on success
 */
int dt78xx_eeprom_read(const struct i2c_client *eeprom, u16 addr, u8 *buff, 
                       size_t count);

/**************************************************************************
 * Write to i2c eeprom
 * @param eeprom : i2c client
 * @param addr   : eeprom address 
 * @param buff   : buffer to write
 * @param count    : #of bytes to write
 * @return       : 0=success, <0 = failure 
 */
int dt78xx_eeprom_write(const struct i2c_client *eeprom, u16 addr, 
                        const u8 *buf, ssize_t count);

/*****************************************************************************
 * Allocate and initialize an i2c dt7837_potentiometer
 * @param dt : struct dt78xx_device *
 * @param node  : i2c child node in device tree that has potentiometer details
 * @return : >0 : success 
 */
struct dt78xx_eep_pot * __must_check 
    dt78xx_potentiometer_init(const struct dt78xx_device *,struct device_node *);

/*****************************************************************************
 * Write to the specified potentiomete's wiper in the i2c potentiometer device
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : Value, ls-byte only used
 * @return          : 0=success, <0 = error
 */
int dt78xx_potentiometer_wiper_write(const struct dt78xx_eep_pot *pot, 
                                    u32 potnum, u32 val);
/*****************************************************************************
 * Read from the specified potentiometer's wiper in the i2c potentiometer device
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : 8-bit value returned here
 * @return          : 0=success, <0 = error
 */
int dt78xx_potentiometer_wiper_read(const struct dt78xx_eep_pot *pot, 
                                    u32 potnum, u32 *val);

/*****************************************************************************
 * Read the specified potentiometer's non-volatile register 
 * @param pot
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param reg       : 0 <= reg < max #of registers per potentiometer
 * @param val       : register value returned here
 * @return          : 0=success <0 is error
 */
int dt78xx_potentiometer_cal_read(const struct dt78xx_eep_pot *pot, 
                                  u32 potnum, u32 reg, u32 *val);

/*****************************************************************************
 * Write the specified potentiometer's non-volatile register 
 * @param pot
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param reg       : 0 <= reg < max #of registers per potentiometer
 * @param val       : register value to write
 * @return          : 0=success <0 is error
 */
int dt78xx_potentiometer_cal_write(const struct dt78xx_eep_pot *pot, 
                                  u32 potnum, u32 reg, u32 val);

/*****************************************************************************
 * Copy a specified non-volatile register's value to the potentiometer's wiper
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param calnum    : User calibration register number
 * @return          : 0=success, <0 = error
 */
int dt78xx_potentiometer_cal2wiper(const struct dt78xx_eep_pot *pot, 
                                    u32 potnum, u32 reg);

#endif //_DT78xx_H_
