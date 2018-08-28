/*
 * Data Translation DT78xx data acquisition module, miscelleneous APIs
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
 */
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/jiffies.h>

#include "dt78xx.h"

/**************************************************************************
 * Macros
 */

/* 
 * 24LC64  Page write operations are limited to writing bytes within a single
 * physical page, regardless of the number of bytes actually being written. 
 * Physical page boundaries start at addresses that are integer multiples of the
 * page buffer size (or ‘page size’) and end at addresses that are integer 
 * multiples of [page size – 1]. If a Page Write command attempts to write
 * across a physical page boundary, the result is that the data wraps around to 
 * the beginning of the current page (overwriting data previously stored there),
 * instead of being written to the next page, as might be expected. It is 
 * therefore necessary for the application software to prevent page write
 * operations that would attempt to cross a page boundary.
 */
#define EEPROM_PAGE_SIZE        (32)

//24LC64 Twc time
#define EEPROM_WRITE_TIME_MS    (5)    
/**************************************************************************
 * Data structures
 */

/**************************************************************************
 * Functions
 */

/**************************************************************************
 * Globals
 */

/**************************************************************************
 * Read from i2c eeprom
 * @param eeprom : i2c client
 * @param addr   : eeprom address 
 * @param buff   : buffer to read into
 * @param count    : #of bytes to read
 * @return       : <0 = failure , count on success
 */
int dt78xx_eeprom_read(const struct i2c_client *eeprom, u16 addr, u8 *buff, 
                       size_t count)
{
    u8 tmp[2];
    int err;
    unsigned long timeout;
    
    if (unlikely(!eeprom || !buff || !count))
        return -EINVAL;
    
    //write the address first
    tmp[0] = (addr >> 8)&0xff;
    tmp[1] = (addr & 0xff);
    timeout = jiffies + msecs_to_jiffies(EEPROM_WRITE_TIME_MS);
    while ((err = i2c_master_send(eeprom, tmp, 2)) < 2)
    {
        if (time_after(jiffies, timeout)) 
        {
            dev_err(&eeprom->dev, "[%s] ERROR i2c_master_send %d\n", __func__,err);
            return -ETIMEDOUT;
        }
        msleep_interruptible(1); 
    }
   
    //read 
    if ((err = i2c_master_recv(eeprom, buff, count)) < count)
    {
        dev_err(&eeprom->dev, "[%s] ERROR i2c_master_recv %d<%d\n", 
                __func__,err, count);
        return err;
    }
    return count;
}
EXPORT_SYMBOL_GPL(dt78xx_eeprom_read);

/**************************************************************************
 * Write one page or fraction of page form the specified buffer
 * @param client
 * @param offset : if offset is alligned to EEPROM_PAGE_SIZE, then writes a
 *                 maximum of EEPROM_PAGE_SIZE bytes to offset. If offset is
 *                 not aligned to EEPROM_PAGE_SIZE, then writes a max number of
 *                 bytes to the end of the page containing offset
 * @param buf
 * @param count
 * @return : <0 = failure, success = number of bytes written 
 */
static ssize_t _eeprom_page_write(const struct i2c_client *client, u16 offset, 
                                const u8 *buf, ssize_t count)
{
	struct i2c_msg msg;
    u8 tmp[EEPROM_PAGE_SIZE];
    int i;
	int err;   
    u32 next_page;
    unsigned long timeout;
    
    //write at most one page
    if (count > EEPROM_PAGE_SIZE)
		count = EEPROM_PAGE_SIZE;
    // Never roll over backwards, to the start of this page 
	next_page = roundup(offset + 1, EEPROM_PAGE_SIZE);
	if (offset + count > next_page)
		count = next_page - offset;
    
    //two-byte address to write at
    tmp[0] = (offset >> 8)&0xff;
    tmp[1] = (offset & 0xff);
    //followed by the actual data
    for (i=2; i < count+2; ++i, ++buf)
        tmp[i] = *buf;

    //message w/t actual buffer prepended with 2-byte address
	msg.addr = client->addr;
	msg.flags = client->flags & I2C_M_TEN;
	msg.len = count+2;
	msg.buf = (char *)tmp;
    /*
	 * Writes fail if the previous one didn't complete yet. Since there is no
     * ACK polling at the end of a write, it is possible that in back-to-back
     * writes the second write will encounter NACKs and must retry until a
     * timeout
	 */
 	timeout = jiffies + msecs_to_jiffies(EEPROM_WRITE_TIME_MS);
	while ((err = i2c_transfer(client->adapter, &msg, 1)) < 0) 
    {
        if (time_after(jiffies, timeout)) 
        {
            dev_err(&client->dev, "[%s] ERROR i2c_transfer %d\n", __func__,err);
            return -ETIMEDOUT;
        }
        msleep_interruptible(1); 
	}
    if (err == 1) //#of i2c messages sent
       return count;

    dev_err(&client->dev, "[%s] ERROR \n", __func__);
    return -EREMOTEIO;
}

/**************************************************************************
 * Write to i2c eeprom
 * @param eeprom : i2c client
 * @param addr   : eeprom address 
 * @param buff   : buffer to write
 * @param count    : #of bytes to write
 * @return       : 0=success, <0 = failure 
 */
int dt78xx_eeprom_write(const struct i2c_client *eeprom, u16 addr, 
                        const u8 *buf, ssize_t count)
{
	ssize_t retval = 0;
    
    if (unlikely(!eeprom || !buf || !count))
        return -EINVAL;
    
    /* Write one page at a time */
	while (count) 
    {
		ssize_t	status;
		status = _eeprom_page_write(eeprom, addr, buf, count);
		if (status <= 0) 
        {
			if (retval == 0)
				retval = status;
			break;
		}
		buf += status;
		addr += status;
		count -= status;
		retval += status;
	}
    return retval;
}
EXPORT_SYMBOL_GPL(dt78xx_eeprom_write);
