/* 
 * Data types, macros, APIs for FIR filter example
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * 
 * Usage :
 *	See usage() below
 *****************************************************************************/
#ifndef __FIR__
#define __FIR__
#endif
#include <stdint.h>

/* Define this for floating math in FIR funtions. For speed improvement perform 
 * math using the native data type of the board, i.e. 32-bit 2's complement in 
 * the DT7837 or 16-bit 2's complement in the DT7816
 */
//#define FIR_USES_FLOAT    1


#ifdef FIR_USES_FLOAT
#define SAMPLE      float
#elif DT7837
#define SAMPLE      int32_t
#elif DT7816
#define SAMPLE      int16_t
#endif


/******************************************************************************
 * fir_double_h: uses doubled coefficients (supplied by caller) so that the
 * filter calculation always operates on a flat buffer.
 *
 *       input    - the input sample data
 *       ntaps    - the number of taps in the filter   
 *       h[]      - the FIR coefficient array
 *       z[]      - the FIR delay line array 
 *       *p_state - the "state" of the filter; initialize this to 0 before
 *                  the first call
 */
SAMPLE fir_double_h(SAMPLE input, int ntaps, const SAMPLE h[], SAMPLE z[],
                    int *p_state);

/*******************************************************************************
 * FIR filter the buffer with the specified number of samples
 * @param buf : Buffer with samples from AD
 * @param numsamples : #of samples in buffer
 */
void fir_filter(void *buff, int32_t numsamples);

/*******************************************************************************
 * Free the filter memory
 */
void fir_filter_free(void);

/*******************************************************************************
 * Allocate and initialize FIR filter using the coefficients in the specified
 * file or use defaults. Must be called once before calling fir_filter()
 * @param file  : File with list of filter coeffs, each in a new line. If it is
 *                NULL, then the default low pass FIR coeffs are used.
 * @return      : <=0 error, >0 is #of coeffs 
 */
int fir_filter_alloc(const char *file);
