/*
 * Kerenel Load Module for Data Translation DT7837 data acquisition module.
 * 
 * This file implements APIs to read/write the Intersil ISL22343 digital
 * potentiometers used for offset and gain calibration for the AD and DA. Due
 * to limited non-volatile storage in the ISL22343, calibration factors are
 * stored in an 24LC64 serial eeprom.
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
#include <linux/uaccess.h>

#include "dt78xx.h"
#include "dt7837.h"

/**************************************************************************
 * Macros
 */
//#define _POT_DEBUG_ (1)
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
#define ACR_REG_IVR_MASK    (0x40)

/*
 * Each ISL22343 is associated with a block of memory in the eeprom, specified
 * by the potentiometer's <reg> binding in the device tree. The eeprom stores
 * 8 user calibration factors and another 8 factory calibration factors for
 * each of the four potentiometers in the ISL22343. The following organization
 * shows the eeprom address offset corresponding to a channel, cal factor# and
 * whether the factor is user or factory calibration
 * offset   pot (or channel)    Cal#    User/Factory
 * ------   ----------------   -----    ------------
 * 0            0               0       user 
 * 1            1               0       user 
 * 2            2               0       user 
 * 3            3               0       user 
 * 4            0               1       user 
 * 5            1               1       user 
 * 6            2               1       user 
 * 7            3               1       user 
 * ....
 * 28           0               7       user 
 * 29           1               7       user 
 * 30           2               7       user 
 * 31           3               7       user 
 * ---------------------------------------------
 * 32           0               0       factory 
 * 33           1               0       factory 
 * 34           2               0       factory 
 * 35           3               0       factory 
 * 36           0               1       factory 
 * 37           1               1       factory 
 * 38           2               1       factory 
 * 39           3               1       factory 
 * ....
 * 60           0               7       factory 
 * 61           1               7       factory 
 * 62           2               7       factory 
 * 63           3               7       factory 
 * 
 * User Cal 0 is the power up default loaded to the wipers WR3:0. In addition
 * to being written to eeprom, cal0 is also written to IVR3:0
 *  Pot    Addr
 *  0      0    WR0
 *  0      0    IVR0
 *  1      1    WR1
 *  1      1    IVR1
 *  2      2    WR1
 *  2      2    IVR1
 *  3      3    WR3
 *  3      3    IVR3
 
 */
#define NUM_CAL_FACTORS     (16)
#define ISL22343_POTS       (4)
#define OFFSET_USER_CAL     (0)
#define OFFSET_FACTORY_CAL  (NUM_CAL_FACTORS * ISL22343_POTS)
#define EEPROM_END_OFFSET   (2 * OFFSET_FACTORY_CAL)

/**************************************************************************
 * Data structures
 */

/**
 * Structure used to tie an i2c potentiometer with i2c eeprom where the
 * calibration constants are stored
 */
struct dt7837_pot
{
    const struct dt78xx_device *dt_dev;
    struct i2c_client *i2c_clnt; //i2c client for pot
    struct i2c_client *eeprom;   //i2c client for eeprom
    int                num_pots; //number of potentiometers in the i2c device
    u16                eep_addr; //eeprom address @ which pot's values reside
    u16                size;     //#of bytes starting @addr
};

/**************************************************************************
 * Functions
 */

/**************************************************************************
 * Globals
 */

/*****************************************************************************
 * Return the eeprom address offset corresponding to a pot, cal factor number
 * and user or factory calibration.
 * @param pot   0 <= pot < ISL22343_POTS
 * @param cal   0 <= cal < NUM_CAL_FACTORS
 * @param fac   0 = user, 1 = factory
 * @return : 0 <= addr < EEPROM_END_OFFSET
 */
static inline u16 _eeprom_offset(int pot, int cal, int fac)
{
    return (fac*OFFSET_FACTORY_CAL + cal*ISL22343_POTS + pot);
}

/*****************************************************************************
 * Allocate and initialize an i2c potentiometer and tie it with its correspnding
 * i2c eeprom storage
 * @param dt_dev : struct dt78xx_device *
 * @param node  : i2c child node in device tree that has pot details
 * @return : >0 : success
 */
struct dt7837_pot * __must_check dt7837_pot_init(const struct dt78xx_device *dt_dev,
                                                 struct device_node *node)
{
    struct dt7837_pot *pot;
    struct device *dev;
    struct device_node *np;  
    struct i2c_adapter *adap;
    struct i2c_board_info info;
    u32 tmp;
    int err;
    
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
    
    memset(&info, 0, sizeof(info)); 
    //get the pot's i2c address which is 0th index in reg binding
    if ((err = of_property_read_u32_index(node, "reg", 0, &tmp)) != 0)
    {
        dev_err(dev, "[%s] ERROR missing reg1\n", __func__);
        goto error2;
    }
    info.addr = tmp;
    
    //get the eeprom address where pot's stuff is stored; 1st index in reg
    if ((err = of_property_read_u32_index(node, "reg", 1, &tmp)) != 0)
    {
        dev_err(dev, "[%s] ERROR missing reg2\n", __func__);
        goto error2;
    }
    pot->eep_addr = tmp;
    
    //get the eeprom extent; 2nd index in reg
    if ((err = of_property_read_u32_index(node, "reg", 2, &tmp)) != 0)
    {
        dev_err(dev, "[%s] ERROR missing reg3\n", __func__);
        goto error2;
    }
    if (tmp < EEPROM_END_OFFSET)
    {
        dev_err(dev, "[%s] ERROR %d bytes invalid\n", __func__, tmp);
        goto error2;
    }
    pot->size = tmp;
    
    //Get the pot type
    if ((err = of_property_match_string(node, "type", "isl22343")) < 0)
    {
        dev_err(dev, "[%s] ERROR unknow type\n", __func__);
        goto error2;
    }
    pot->num_pots = ISL22343_POTS;
    
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
                __func__, node->full_name, pot->eep_addr, pot->size);
#endif    
    return pot;

error2:    
    put_device(&adap->dev);
error1:    
    of_node_put(np);
    devm_kfree(dev, pot);
    return ERR_PTR(err);
}

/*****************************************************************************
 * Write to isl22343 wiper
 * @param client
 * @param wiper : Wiper number
 * @param val   : value to write
 * @return      : <0 = error, 0=success 
 */
static int _pot_wiper_write(struct i2c_client *client, u8 wiper, u8 val)
{
    uint8_t tmp[2];
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
 * Write to isl22343 wiper
 * @param client
 * @param wiper : Wiper number
 * @param val   : value returned here
 * @return      : <0 = error, 0=success 
 */
static int _pot_wiper_read(struct i2c_client *client, u8 wiper, u8 *val)
{
    uint8_t tmp[2];
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
#ifdef _IVR_WRITE_    
/*****************************************************************************
 * Write to isl22343 IVR register
 * @param client
 * @param wiper : IVR register number
 * @param val   : value to write
 * @return      : <0 = error, 0=success 
 */
static int _pot_ivr_write(struct i2c_client *client, u8 ivr, u8 val)
{
    uint8_t tmp[2];
    int err;
    //To access IVR register ACR must be written first
    tmp[0] = ACR_REG_ADDR;
    tmp[1] = ACR_REG_IVR_MASK;
    if ((err = i2c_master_send(client, tmp, 2)) < 0)
        return err;   
    
    //write the register address and data
    tmp[0] = ivr;
    tmp[1] = val;
    err = i2c_master_send(client, tmp, 2);
    return err;   
}
#endif
/*****************************************************************************
 * Write to the specified channel's wiper in the potentiometer 
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : Value, ls-byte only used
 * @return          : 0=success, <0 = error
 */
int dt7837_pot_wiper_write(const struct dt7837_pot *pot, u32 potnum, u32 val)
{
    int err;
    
    if (!pot || !pot->i2c_clnt || (potnum >= pot->num_pots))
        return -EINVAL;
    
    if ((err = _pot_wiper_write(pot->i2c_clnt, (u8)potnum, (u8)val)) < 0)
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR wiper write %d\n", 
                                        __func__, err);
        return err;
    }
    return 0;
}

/*****************************************************************************
 * Read from the specified channel's wiper in the potentiometer 
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param val       : 8-bit value returned here
 * @return          : 0=success, <0 = error
 */
int dt7837_pot_wiper_read(const struct dt7837_pot *pot, u32 potnum, u32 *val)
{
    int err;
    
    if (!pot || !pot->i2c_clnt || (potnum >= pot->num_pots))
        return -EINVAL;
    
    if ((err = _pot_wiper_read(pot->i2c_clnt, potnum, (u8 *)val)) < 0)
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR i2c_master_send %d\n", 
                                          __func__, err);
        return err;   
    }
    return 0;
}

/*****************************************************************************
 * Read the specified channel's user or factory calibration factor 
 * @param pot   
 * @param cal       : dt78xx_cal_pot_t with all members initialized
 * @return          : <0 = error, 0=success; value returned in cal
 */
int dt7837_pot_cal_read(const struct dt7837_pot *pot, dt78xx_cal_pot_t *cal)
{
    struct device *dev; 
    u16 addr;
    int ret;
    
    if (!pot || !pot->i2c_clnt)
        return -EINVAL;
    if ((cal->pot < 0) || (cal->pot >= pot->num_pots))
        return -EINVAL;
    if (cal->cal.reg >= NUM_CAL_FACTORS)
        return -EINVAL;
    
    dev = &pot->dt_dev->pdev->dev;
    addr = _eeprom_offset(cal->pot, cal->cal.reg, cal->cal.factory);
    addr += pot->eep_addr;
    
    ret = dt78xx_eeprom_read(pot->eeprom, addr, (u8 *)&cal->value, sizeof(u8));
    if (ret < (int)sizeof(u8)) //!! sizeof return type is size_t
    {
        dev_err(dev, "[%s] ERROR dt78xx_eeprom_read %d\n", __func__, ret);
        return ret;
    }
    
    return 0;
}

/*****************************************************************************
 * Write the specified channel's user or factory calibration factor 
 * @param pot   
 * @param cal       : dt78xx_cal_pot_t with all members initialized
 * @return          : <0 = error, 0=success; value in cal written
 */
int dt7837_pot_cal_write(const struct dt7837_pot *pot, dt78xx_cal_pot_t *cal)
{
    u16 addr;
    int ret;
    
    if (!pot || !pot->i2c_clnt)
        return -EINVAL;
    if ((cal->pot < 0) || (cal->pot >= pot->num_pots))
        return -EINVAL;
    if (cal->cal.reg >= NUM_CAL_FACTORS)
        return -EINVAL;

    addr = _eeprom_offset(cal->pot, cal->cal.reg, cal->cal.factory);
    addr += pot->eep_addr;
    
    ret = dt78xx_eeprom_write(pot->eeprom, addr, (u8 *)&cal->value, sizeof(u8));
    if (ret < (int)sizeof(u8)) 
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR dt78xx_eeprom_write %d\n", 
                                         __func__, ret);
        return ret;
    }
#ifdef _IVR_WRITE_    
    //user cal 0 is also written to the ISL22343's IVR register
    if (cal->cal.reg != 0)
        return 0;
    
    if ((ret = _pot_ivr_write(pot->i2c_clnt, cal->pot, (u8)cal->value)) < 0)
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR _pot_ivr_write %d\n", 
                                         __func__, ret);
#endif    
    return (ret);
}

/*****************************************************************************
 * Copy a specified user calibration factor to the potentiometer's wiper
 * @param pot   
 * @param potnum    : 0 <= potnum < max potentiometers in the i2c device
 * @param calnum    : User calibration register number
 * @return          : 0=success, <0 = error
 */
int dt7837_pot_cal2wiper(const struct dt7837_pot *pot, u32 potnum, u32 calnum)
{
    u16 addr;
    u8 val;
    int ret;
    
    if (!pot || !pot->i2c_clnt)
        return -EINVAL;
    if ((potnum < 0) || (potnum >= pot->num_pots))
        return -EINVAL;
    if (calnum >= NUM_CAL_FACTORS)
        return -EINVAL;
    
    addr = _eeprom_offset(potnum, calnum, 0);
    addr += pot->eep_addr;
    
    ret = dt78xx_eeprom_read(pot->eeprom, addr, &val, sizeof(val));
    if (ret < (int)sizeof(val)) 
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR dt78xx_eeprom_read %d\n", 
                                        __func__, ret);
        return ret;
    }
    
    if ((ret = _pot_wiper_write(pot->i2c_clnt, potnum, val)) < 0)
    {
        dev_err(&pot->dt_dev->pdev->dev, "[%s] ERROR wiper write %d\n", 
                                        __func__, ret);
        return ret;
    }
    return 0;
}