/* 
 * Direct Digital Synthesizer APIs
 * See http://www.analog.com/MT-085 and other on-line refernces for details
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

#ifndef DDS_H
#define	DDS_H

#ifdef	__cplusplus
extern "C"
{
#endif

/*
 * Waveform types
 */
enum wave_type {wave_sine, wave_triangle, wave_sawtooth, wave_square};
    


/*****************************************************************************
 * Free memory and other resource
 */
void dds_free(void);

/*****************************************************************************
 * Allocate and initialize the DDS llokup table
 * @param sampling_clk : Output sampling frequency in Hz
 * @param output_clk   : Frequency of generated output in Hz
 * @param amp          : Output amplitude in volts
 * @param wav          : waveform type
 * @return             : 0=success,  -ENOMEM=out of memory
 */
int dds_init(float sampling_clk, float *output_clk, float amp, 
             enum wave_type type);

/*****************************************************************************
 * Fill the specified buffer with the waveform initialized in dds_init()
 * @param buf       : pointer to buffer
 * @param buflen    : Length of buffer in bytes
 * @param numchan   : Number of channels. If one channel is specified the
 *                    buffer is filled with a segment of the analog output
 *                    signal. If two channels are specified, data for the
 *                    digital outputs are interleaved in the buffer with the
 *                    data for the analog output
 */
void dds_buff_fill(void *buf, int buflen, int numchan);

#ifdef	__cplusplus
}
#endif

#endif	/* DDS_H */

