/*
 * This file implements APIs to read/write the I2C digital potentiometers used for 
 * offset and gain calibration for the AD and DA. Due to limited non-volatile 
 * storage in most , calibration factors are stored in an 24LC64 serial eeprom.
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
#include <linux/i2c.h>

#include "dt78xx.h"

/**************************************************************************
 * Macros
 */
#define _POT_DEBUG_ (1)
/*
 * There are 4 potentiometers in each Intersil ISL22343.
 * The VOL bit (ACR[7]) determines whether the access to wiper registers WRi or
 * initial value registers IVRi. If VOL bit is 0, the non-volatile IVRi 
 * registers are accessible. If VOL bit is 1, only the volatile WRi are 
 * accessible. Note: value is written to IVRi register also is written to the
 * corresponding WRi. The default value of this bit is 0. The SHDN bit (ACR[6])
 * disables or enables Shutdown mode. When this bit is 0, DCPs are in Shutdown
 * mode. Default value of the SHDN bit is 1.
 */
#define ACR_REG_ADDR        (0x10)
#define ACR_REG_WPR_MASK    (0xc0)
#define ISL22343_MAX_POTS   (4)

#define ISL95810_MAX_POTS   (1)

/*
 * Each pot device is associated with a block of memory in the eeprom, specified
 * by the potentiometer's <reg> binding in the device tree. The eeprom stores
 * non-volatile calibration values, each of which is termed a "register". The
 * eeprom storage is allocated equally over each potentiometer in the device.
 * The following shows the eeprom organization for a device with 4 potentiometers
 * each with 16 registers 
 * offset   pot (or channel)    register    
 * ------   ----------------   -----    
 * 0            0               0       
 * 1            0               1        
 * 2            0               2        
  ....
 * 15           0               15        
 * 16           1               0       
 * 17           1               1        
 * 18           1               2        
  ....
 * 31           1               15        
 * ....
 * 48           3               0       
 * 49           3               1        
 * 50           3               2        
  ....
 * 63           3               15        
 */

/**************************************************************************
 * Data structures
 */

/**
 * Structure used to tie an i2c potentiometer with i2c eeprom where the
 * calibration constants are stored
 */
struct dt78xx_eep_pot
{
    const struct dt78xx_device *dt_dev;
    struct i2c_client *i2c_clnt; //i2c client for pot
    struct i2c_client *eeprom;   //i2c client for eeprom
    u32                num_pots; //number of potentiometers in the i2c device
    u32                num_regs; //#of non-volatile registers per potentiometer
    u16                eep_addr; //eeprom address @ which pot's values reside
    int (*wiper_write)(struct i2c_client *client, u8 wiper, u8 val);
    int (*wiper_read)(struct i2c_client *client, u8 wiper, u8 *val);
};

/**************************************************************************
 * Functions
 */

/*****************************************************************************
 * Write to isl22343 wiper
 * @param client
 * @param wiper : Wiper number
 * @param val   : value to write
 * @return      : <0 = error, 0=success 
 */
static int _isl22343_wiper_write(struct i2c_client *client, u8 wiper, u8 val)
{
    u8 tmp[2];
    int err;
    //To access WR register ACR must be written first
    tmp[0] = ACR_REG_ADDR;
    tmp[1] = ACR_REG_WPR_MASK;
    if ((err = i2c_master_send(client, tmp, 2)) < 0)
        return err;   
    
    //write the register address and data
    tmp[0] = wiper;
    tmp[1] = val;
    err = i2c_master_send(client, tmp, 2);
    return err;   
}

/*****************************************************************************
 * Read from the isl22343 wiper
 * @param client
 * @param wiper : Wiper number
 * @param val   : value returned here
 * @return      : <0 = error, 0=success 
 */
static int _isl22343_wiper_read(struct i2c_client *client, u8 wiper, u8 *val)
{
    u8 tmp[2];
    int err;
    //To access WR register ACR must be written first
    tmp[0] = ACR_REG_ADDR;
    tmp[1] = ACR_REG_WPR_MASK;
    if ((err = i2c_master_send(client, tmp, 2)) < 0)
        return err;  
    
    //write the wiper address
    tmp[0] = wiper;
    if ((err = i2c_master_send(client, tmp, 1)) < 0)
        return err;   
    //read the wiper
    if ((err = i2c_master_recv(client, val, 1)) < 0)
        return err;   
    
    return err;   
}

/*****************************************************************************
 * Write to isl95810 wiper
 * @param client
 * @param wiper : Wiper number
 * @param val   : value to write
 * @return      : <0 = error, 0=success 
 */
static int _isl95810_wiper_write(struct i2c_client *client, u8 wiper, u8 val)
{
    u8 tmp[2];
    int err;
    /*When the byte at address 2 is 80h (128 decimal),a write operation to 
     * addresses 0 only writes to the corresponding volatile wiper.
     */
    tmp[0] = 0x02;
    tmp[1] = 0x80;
    if ((err = i2c_master_send(client, tmp, 2)) < 0)
        return err;   
    
    //write the register address and data
    tmp[0] = 0x00;
    tmp[1] = val;
    err = i2c_master_send(client, tmp, 2);
    return err;   
}

/*****************************************************************************
 * Read from the isl95810 wiper
 * @param client
 * @param wiper : Wiper number
 * @param val   : value returned here
 * @return      : <0 = error, 0=success 
 */
static int _isl95810_wiper_read(struct i2c_client *client, u8 wiper, u8 *val)
{
    u8 tmp[2];
    int err;
    /*When the byte at address 2 is 80h (128 decimal),a read operation to 
     *addresses 0 outputs the value of the volatile WR.
     */
    tmp[0] = 0x02;
    tmp[1] = 0x80;
    if ((err = i2c_master_send(client, tmp, 2)) < 0)
        return err;   
    //write the wiper address
    tmp[0] = 0x00;
    if ((err = i2c_master_send(client, tmp, 1)) < 0)
        return err;   
    //read the wiper
    if ((err = i2c_master_recv(client, val, 1)) < 0)
        return err;   
    
#ifdef _POT_DEBUG_    
    pr_debug("[%s] %#x\n", __func__, *val);
#endif    
    return err;   
}

/*****************************************************************************
 * Allocate and initialize an i2c potentiometer and tie it with its correspnding
 * i2c eeprom storage
 * @param dt_dev : struct dt78xx_device *
 * @param node  : i2c child node in device tree that has pot details
 * @return : >0 : success
 */
struct dt78xx_eep_pot * __must_check 
    dt78xx_potentiometer_init(const struct dt78xx_device *dt_dev,
                              struct device_node *node)
{
    struct dt78xx_eep_pot *pot;
    struct device *dev;
    struct device_node *np;  
    struct i2c_adapter *adap;
    struct i2c_board_info info;
    const char *type;
    u32 tmp;
    int err;
    
    //First check if the potentiometer type is supported
    if ((err = of_property_read_string(node, "type", &type)) != 0)
        return ERR_PTR(err);
    if ((strcmp(type, "isl95810")!=0) && (strcmp(type, "isl22343")!=0))
        return ERR_PTR(-ENOENT);
        
    dev = &dt_dev->pdev->dev;
    pot = devm_kzalloc(dev, sizeof(*pot), GFP_KERNEL);
    if (!pot)
        return ERR_PTR(-ENOMEM); 
    
    //get the i2c node 
    if (unlikely((np = of_get_parent(node)) == NULL))
    {
        devm_kfree(dev, pot);
        dev_err(dev, "[%s] ERROR of_get_parent\n", __func__);
        return ERR_PTR(-ENODEV);
    }
    
    //find the i2c bus adapter
    if ((adap = of_find_i2c_adapter_by_node(np)) == NULL)
    {
        err = -ENODEV;
        dev_err(dev,"[%s] ERROR of_find_i2c_adapter_by_node\n", __func__);
        goto error1;
    }
    //Initialize potentiometer device specifics
    if (strcmp(type, "isl22343")==0)
    {
        pot->num_pots = ISL22343_MAX_POTS;
        pot->wiper_write = _isl22343_wiper_write;
        pot->wiper_read = _isl22343_wiper_read;
    }
    else if (strcmp(type, "isl95810")==0) 
    {
        pot->num_pots = ISL95810_MAX_POTS;
        pot->wiper_write = _isl95810_wiper_write;
        pot->wiper_read = _isl95810_wiper_read;
    }
    /* get the eeprom address where pot's non-volatile values are stored; 
     * 1st index in reg binding*/
    if ((err = of_property_read_u32_index(node, "reg", 1, &tmp)) != 0)
    {
        dev_err(dev, "[%s] ERROR missing reg2\n", __func__);
        goto error2;
    }
    pot->eep_addr = tmp;
    
    //get the eeprom extent; 2nd index in reg binding
    if ((err = of_property_read_u32_index(node, "reg", 2, &tmp)) != 0)
    {
        dev_err(dev, "[%s] ERROR missing reg3\n", __func__);
        goto error2;
    }
    //eeprom storage allocated equally over all potentiometers in the device
    pot->num_regs = tmp/pot->num_pots;
    
    memset(&info, 0, sizeof(info)); 
    //get the pot's i2c address which is 0th index in reg binding
    if ((err = of_property_read_u32_index(node, "reg", 0, &tmp)) != 0)
    {
        dev_err(dev, "[%s] ERROR missing reg1\n", __func__);
        goto error2;
    }
    info.addr = tmp;
    
    //Create the i2c client for the pot
    pot->i2c_clnt = i2c_new_device(adap, &info);
    if (IS_ERR_OR_NULL(pot->i2c_clnt))
    {
        err = -ENODEV;
        dev_err(dev,"[%s] ERROR i2c_new_device\n", __func__);
        goto error2;
    }
    
    pot->eeprom = dt_dev->eeprom; //i2c_client of the serial eeprom
    pot->dt_dev = dt_dev;
    put_device(&adap->dev);
    of_node_put(np);
#ifdef _POT_DEBUG_    
    dev_dbg(dev,"[%s] %s eeprom(%#x %#x)\n", 
                __func__, node->full_name, pot->eep_addr, tmp);
#endif    
    return pot;

error2:    
    put_device(&adap->dev);
error1:    
    of_node_put(np);
    devm_kfree(dev, pot);
    return ERR_PTR(err);
}
EXPORT_SYMBOL_GPL(dt78xx_potentiometer_init);

/*****************************************************************************
 * Write to the specified channel's wiper in the potentiometer 
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : Value, ls-byte only used
 * @return          : 0=success, <0 = error
 */
int dt78xx_potentiometer_wiper_write(const struct dt78xx_eep_pot *pot, 
                                    u32 potnum, u32 val)
{
    int err;
    
    if (!pot || !pot->i2c_clnt || (potnum >= pot->num_pots))
        return -EINVAL;
    
    if ((err = pot->wiper_write(pot->i2c_clnt, (u8)potnum, (u8)val)) < 0)
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR wiper write %d\n", 
                                        __func__, err);
        return err;
    }
    return 0;
}
EXPORT_SYMBOL_GPL(dt78xx_potentiometer_wiper_write);

/*****************************************************************************
 * Read from the specified potentiometer's wiper in the i2c potentiometer device
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : 8-bit value returned here
 * @return          : 0=success, <0 = error
 */
int dt78xx_potentiometer_wiper_read(const struct dt78xx_eep_pot *pot, 
                                    u32 potnum, u32 *val)
{
    int err;
    
    if (!pot || !pot->i2c_clnt || (potnum >= pot->num_pots))
        return -EINVAL;
    *val = 0;
    if ((err = pot->wiper_read(pot->i2c_clnt, potnum, (u8 *)val)) < 0)
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR i2c_master_send %d\n", 
                                          __func__, err);
        return err;   
    }
    return 0;
}
EXPORT_SYMBOL_GPL(dt78xx_potentiometer_wiper_read);

/*****************************************************************************
 * Read the specified potentiometer's non-volatile register 
 * @param pot
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param reg       : 0 <= reg < max #of registers per potentiometer
 * @param val       : register value returned here
 * @return          : 0=success <0 is error
 */
int dt78xx_potentiometer_cal_read(const struct dt78xx_eep_pot *pot, 
                                  u32 potnum, u32 reg, u32 *val)
{
    struct device *dev; 
    u16 eep_addr;
    int ret;
    
    if (!pot || !pot->i2c_clnt)
        return -EINVAL;
    if (potnum >= pot->num_pots)
        return -EINVAL;
    if (reg >= pot->num_regs)
        return -EINVAL;
    
    dev = &pot->dt_dev->pdev->dev;
    eep_addr = pot->eep_addr + (potnum*pot->num_regs + reg);
    *val = 0;
    ret = dt78xx_eeprom_read(pot->eeprom, eep_addr, (u8 *)val, sizeof(u8));
    if (ret < (int)sizeof(u8)) //!! sizeof return type is size_t
    {
        dev_err(dev, "[%s] ERROR dt78xx_eeprom_read %d\n", __func__, ret);
        return ret;
    }
    
    return 0;
}
EXPORT_SYMBOL_GPL(dt78xx_potentiometer_cal_read);

/*****************************************************************************
 * Write the specified potentiometer's non-volatile register 
 * @param pot
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param reg       : 0 <= reg < max #of registers per potentiometer
 * @param val       : register value to write
 * @return          : 0=success <0 is error
 */
int dt78xx_potentiometer_cal_write(const struct dt78xx_eep_pot *pot, 
                                  u32 potnum, u32 reg, u32 val)
{
    struct device *dev; 
    u16 eep_addr;
    int ret;
    
    if (!pot || !pot->i2c_clnt)
        return -EINVAL;
    if (potnum >= pot->num_pots)
        return -EINVAL;
    if (reg >= pot->num_regs)
        return -EINVAL;
    
    dev = &pot->dt_dev->pdev->dev;
    eep_addr = pot->eep_addr + (potnum*pot->num_regs + reg);
    
    ret = dt78xx_eeprom_write(pot->eeprom, eep_addr, (u8 *)&val, sizeof(u8));
    if (ret < (int)sizeof(u8)) //!! sizeof return type is size_t
    {
        dev_err(dev, "[%s] ERROR dt78xx_eeprom_write %d\n", __func__, ret);
        return ret;
    }
    
    return 0;
}
EXPORT_SYMBOL_GPL(dt78xx_potentiometer_cal_write);

/*****************************************************************************
 * Copy a specified non-volatile register's value to the potentiometer's wiper
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param calnum    : User calibration register number
 * @return          : 0=success, <0 = error
 */
int dt78xx_potentiometer_cal2wiper(const struct dt78xx_eep_pot *pot, 
                                    u32 potnum, u32 reg)
{
    struct device *dev; 
    u16 eep_addr;
    int err;
    u8 val;
    
    if (!pot || !pot->i2c_clnt)
        return -EINVAL;
    if (potnum >= pot->num_pots)
        return -EINVAL;
    if (reg >= pot->num_regs)
        return -EINVAL;
    
    dev = &pot->dt_dev->pdev->dev;
    eep_addr = pot->eep_addr + (potnum*pot->num_regs + reg);
    
    err = dt78xx_eeprom_read(pot->eeprom, eep_addr, &val, sizeof(u8));
    if (err < (int)sizeof(u8)) //!! sizeof return type is size_t
    {
        dev_err(dev, "[%s] ERROR dt78xx_eeprom_read %d\n", __func__, err);
        return err;
    }
    if ((err = pot->wiper_write(pot->i2c_clnt, (u8)potnum, val)) < 0)
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR wiper write %d\n", 
                                        __func__, err);
        return err;
    }
    return 0;
}
EXPORT_SYMBOL_GPL(dt78xx_potentiometer_cal2wiper);