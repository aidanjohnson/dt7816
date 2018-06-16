/* 
 * Direct Digital Synthesizer to generate sine wave.
 * Refer to application notes from Analog Devices http://www.analog.com/MT-085, 
 * http://www.analog.com/library/analogDialogue/cd/vol38n3.pdf#page=8 
 * and other on-line refernces for details
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
 * ============================================================================
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "dds.h"

#include "dt78xx_misc.h"
/*****************************************************************************
 * MACROS
 */

//Look Up Table size parameters
#define N                   (16)
#define LUT_TOTAL_SIZE      (1<<N)
//What fraction of a periodic waveform is stored in the LUT
#define WAVE_FRACTION       (2)  //quarter
#define LUT_MAX_INDEX       (LUT_TOTAL_SIZE/(1<<WAVE_FRACTION))
//Truncate 32-bit phase accumulator, M, into offset into LUT
#define TRUNCATE_PHASE(M) \
                            ((M>>(32-N-WAVE_FRACTION))&(LUT_TOTAL_SIZE-1))
//Memory offset in LUT converted into table index; each entry in LUT is 4-bytes
#define LUT_INDEX(X)        (X>>2)
//Upper bits of  32-bit phase accumulator, M, used to determine segment of 
//fractional wave stored in LUT
#define LUT_SEGMENT(M) \
                        ((M >> (32-WAVE_FRACTION)) & ((1<<WAVE_FRACTION)-1))

/*****************************************************************************
 * GLOBALS
 */

//Table to stores WAVE_FRACTION of a periodic waveform
#ifdef DT7837
static uint32_t *g_wave_tab = NULL;
#elif DT7816
static int16_t *g_wave_tab = NULL;
#endif
//Tuning word or delta phase register referenced in application note
static uint32_t g_delta_phase;
//Phase accumulator referenced in application note
static uint32_t g_phase_acc;
//Type of wave form
static enum wave_type g_wav;

/*****************************************************************************
 * Free memory and other resource
 */
void dds_free(void)
{
    if (g_wave_tab)
        free(g_wave_tab);
}

/*****************************************************************************
 * Allocate and initialize the DDS lookup table
 * @param sampling_clk : Output sampling frequency in Hz
 * @param output_clk   : Frequency of generated output in Hz
 * @param amp          : Output amplitude in volts
 * @param wav          : waveform type
 * @return             : 0=success,  -ENOMEM=out of memory
 */
int dds_init(float sampling_clk, float *output_clk, float amp, enum wave_type wav)
{
    int i;
    float delta, acc;
    
    if (!g_wave_tab)
    {
#ifdef DT7837
        g_wave_tab = (uint32_t *)malloc(LUT_MAX_INDEX*sizeof(uint32_t));
#elif DT7816
        g_wave_tab = (int16_t *)malloc(LUT_MAX_INDEX*sizeof(int16_t));
#endif
        if (!g_wave_tab)
            return -ENOMEM;
    }

    g_delta_phase = (uint32_t)(*output_clk * UINT32_MAX/sampling_clk);
    g_phase_acc = 0;
    g_wav = wav;
    *output_clk = (sampling_clk * g_delta_phase)/UINT32_MAX;
    
    //Compute the first quarter cycle of each waveform
    if (wav == wave_sine)
    {
        delta = 2.0f*M_PI/LUT_TOTAL_SIZE;
        for (i=0, acc=0.0f; i < LUT_MAX_INDEX; ++i, acc+= delta)
            g_wave_tab[i] = volts2raw(amp*sinf(acc), 1);
    }
    else if (wav == wave_square)
    {
        g_wave_tab[0] = volts2raw(amp, 1);
        for (i=1; i < LUT_MAX_INDEX; ++i)
            g_wave_tab[i] = g_wave_tab[i-1];
    }
    else if (wav == wave_triangle)
    {
        delta = 1.0f/LUT_MAX_INDEX;
        for (i=0, acc=0.0f; i < LUT_MAX_INDEX; ++i, acc+= delta)
            g_wave_tab[i] = volts2raw(amp*acc, 1);
    }
    else //saw tooth
    {
        delta = 1.0f/LUT_MAX_INDEX;
        amp *= 0.5f; //a sawtooth only goes half-way over quarter,unlike triangle
        for (i=0, acc=0.0f; i < LUT_MAX_INDEX; ++i, acc+= delta)
            g_wave_tab[i] = volts2raw(amp*acc, 1);
    }

    return 0;
}

/*****************************************************************************
 * Fill the specified buffer with the waveform initialized in dds_init
 * @param buf       : pointer to buffer
 * @param buflen    : Length of buffer in bytes
 * @param numchan   : Number of channels. If one channel is specified the
 *                    buffer is filled with a segment of the analog output
 *                    signal. If two channels are specified, data for the
 *                    digital outputs are interleaved in the buffer with the
 *                    data for the analog output
 */
void dds_buff_fill(void *bufptr, int buflen, int numchan)
{
#ifdef DT7837
    int32_t *buf = (int32_t*)bufptr;  
#elif DT7816
    int16_t *buf = (int16_t*)bufptr;
#endif
    for(;buflen; ++buf, g_phase_acc+=g_delta_phase, buflen-=sizeof(*buf))
    {
        int segment = LUT_SEGMENT(g_phase_acc);
        uint32_t lut_idx = LUT_INDEX(TRUNCATE_PHASE(g_phase_acc));
        if (g_wav == wave_sawtooth)
        {
            if (segment==0)
                *buf = g_wave_tab[lut_idx];
            else if (segment==3)
                *buf = -g_wave_tab[LUT_MAX_INDEX-1-lut_idx];
            else 
            {
                uint32_t offset = g_wave_tab[LUT_MAX_INDEX-1]-g_wave_tab[0];
                if (segment==1)
                    *buf = offset + g_wave_tab[lut_idx];
                else if (segment==2)
                    *buf = -(offset+g_wave_tab[LUT_MAX_INDEX-1-lut_idx]);
            }
        }
        else
        {
            if (segment==0) 
                *buf = g_wave_tab[lut_idx];
            else if (segment==1)
                *buf = g_wave_tab[LUT_MAX_INDEX-1-lut_idx];
            else if (segment==2)
                *buf = -g_wave_tab[lut_idx];
            else
                *buf = -g_wave_tab[LUT_MAX_INDEX-1-lut_idx];
        }
        //Add waveforms for digital outputs
        if (numchan > 1)
        {
            ++buf;
            buflen-=sizeof(*buf);
            if (segment==0)
                 *buf = 0x3;
            else if (segment==1)
                 *buf = 0x5;
            else if (segment==2)
                 *buf = 0x8;
            else if (segment==3)
                 *buf = 0x10;
        }
    }
}

