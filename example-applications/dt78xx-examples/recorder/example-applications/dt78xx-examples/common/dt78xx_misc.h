#ifndef _MISC_H_
#define	_MISC_H_
/*****************************************************************************
 * Miscelleneous APIs, data structures and macros used in DT78XX embedded 
 * application 
 * 
 * Copyright (C) 2015 Data Translation Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * You are free to use this source code under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 */

#include <stdint.h>
#include <signal.h>
#include <limits.h>

/*****************************************************************************
 * Register a signal handler for a specific signal
 */
int sigaction_register(int sig, void (* handler)(int));

/*****************************************************************************
 * Register a signal handler for a specific signal for the specified file
 */
int file_sigaction_register(int fd, int sig, void (* handler)(int));

/*****************************************************************************
 * Non-blocking check for key entry
 * @return 0=no key entered. 1=key pressed, fgetc(stdin) will return character 
 */
int kbhit(void);

/*****************************************************************************
 * Must be called once to restore terminal settings when main() exits
 */
void kbfini(void);

#ifdef DT7837
//Resolution of AD and DA
#define DT7837_AD_RES_BITS  (24)
#define DT7837_DA_RES_BITS  (24)
//AD full scale volts for gain of 1 and 10. DA full scale is always 10.0
#define DT7837_X1_FS_V      (10.0f)
#define DT7837_X10_FS_V     (1.0f)

/*****************************************************************************
 * Convert 32-bit two's complement to volts
 * @param raw           : 32-bit two's complement value to be converted
 * @param gain          : 1 or 10
 * @return              : volt; -fs <= volt <= fs
 */
static inline float raw2volts(int32_t raw, int gain)
{
    float volts = (gain==10) ? DT7837_X10_FS_V : DT7837_X1_FS_V;
    volts *= (float)raw;
    volts /= (1<<(DT7837_AD_RES_BITS-1));
    return (volts);
}

/*****************************************************************************
 * Convert volts to 32-bit 2's complement
 * @param volt          : volts to be converted, -fs <= volt <= fs
 * @param gain          : ignored
 * @return              : 32-bit 2's complement value; least significant 24-bits
 *                        are used with bit 23 sign extended to bits 31:24
 */
static inline int32_t volts2raw(float volts, int gain)
{
    int32_t ret;
    if (volts >= DT7837_X1_FS_V)
    {
        ret = ((1<<(DT7837_DA_RES_BITS-1))-1); //return +ve full scale
    }
    else if (volts < -DT7837_X1_FS_V)
    {
        ret =  (~((1<<DT7837_DA_RES_BITS)-1) | (1<<(DT7837_DA_RES_BITS-1)));
    }
    else
    {
        volts /= DT7837_X1_FS_V;
        ret = (int32_t)(volts*(1<<(DT7837_DA_RES_BITS-1)));
    }
    return (ret);
}

#elif DT7816
/* ADC calibration : To ensure a +/-10V range can be covered with expected gain
 * and offset errors, the ADC is scaled to produce a nominal full scale of 
 * +/- 10.0452V
 */
#define DT7816_AD_FS_V      (10.0452f)
#define DT7816_AD_RES_BITS  (16)

#define DT7816_DA_FS_V      (10.0f)
#define DT7816_DA_RES_BITS  (16)

/*****************************************************************************
 * Convert 16-bit two's complement to volts
 * @param raw           : 16-bit two's complement value to be converted
 * @param gain          : ignored
 * @return              : volt; -fs <= volt <= fs
 */
static inline float raw2volts(int16_t raw, int gain)
{
    float f = ((float)raw*DT7816_AD_FS_V)/(1<<(DT7816_AD_RES_BITS-1));
    return (f);
}

/*****************************************************************************
 * Convert volts to 16-bit 2's complement
 * @param volt          : volts to be converted, -fs <= volt <= fs
 * @param gain          : ignored
 * @return              : 16-bit 2's complement value
 */
static inline int16_t volts2raw(float volts, int gain)
{
    int16_t ret;
    if (volts >= DT7816_DA_FS_V)
    {
        ret = ((1<<(DT7816_DA_RES_BITS-1))-1); //+ve full scale
    }
    else if (volts < -DT7816_DA_FS_V)
    {
        ret = (1<<(DT7816_DA_RES_BITS-1)); //-ve full scale
    }
    else
    {
        /* Need to compute ((volts/DT7816_DA_FS_V)*(1<<(DT7816_DA_RES_BITS-1))) 
         * However, to eliminate a large step size around 0 due to truncation, the 
         * following is used instead */
        int32_t raw = ((volts+DT7816_DA_FS_V)/(2.0f*DT7816_DA_FS_V)*((1<<DT7816_DA_RES_BITS)-1));
        ret = (int16_t)(raw-(1<<(DT7816_DA_RES_BITS-1)));
    }
    return ret;
}
#endif

#endif