/****************************************************************************
 *  APIs that perform floating point operations. This must be in a separate
 *  compilation unit than the callers of the APIs
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
 *************************************************************************/

#include <linux/kernel.h>
#include "dt7816.h"
/******************************************************************************
 MACROS
 *****************************************************************************/

/******************************************************************************
 Data Types
 *****************************************************************************/
/***************************************************************************
functions                                                        
****************************************************************************/

/****************************************************************************/
/* Global variables                                                         */
/****************************************************************************/

/*****************************************************************************
 * Returns PLL configuration for the specified sampling rate
 * @param freq : Pointer to desired sampling rate. On success, the actual rate
 *               is returned here
 * @parm min : minumum clock
 * @parm max : maxmum clock
 * @return : 32-bit non-zero divisor on success, 0 if specified rate is invalid
 * NOTES : This API must be called within a kernel_neon_begin()/kernel_neon_end.
 * The allocated structure must be deallocated by the caller 
 */
uint32_t dt7816_clk_divisor(float *freq, float min, float max)
{
    uint32_t divisor;
    if (*freq < min)
        return 0;
    if (*freq > max)
        return 0;
    divisor = (uint32_t)(REF_CLK_HZ/(*freq));
    *freq = REF_CLK_HZ/(float)divisor;
    return (divisor);    
}
