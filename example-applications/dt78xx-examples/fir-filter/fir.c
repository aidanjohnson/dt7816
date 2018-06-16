/* 
 * FIR filter implementation
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the Licensef, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be usefulf,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if notf, write to the Free Software
 *****************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "fir.h"

#define SAMPLEFILTER_TAP_NUM 69

/*
Default FIR filter coefficients 
FIR filter designed with TFilter which is accessible at either of the following
http://t-filter.appspot.com 
http://t-filter.engineerjs.com/

sampling frequency: 100000 Hz

* 0 Hz - 5000 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = 4.16285854635209 dB

* 7000 Hz - 50000 Hz
  gain = 0
  desired attenuation = -50 dB
  actual attenuation = -50.02626771302218 dB
*/
#if defined FIR_USES_FLOAT        
static const SAMPLE filter_taps[] = 
{
  -0.0014404127183852448f,
  0.0005382616364442431f,
  0.0013298367836838156f,
  0.0026559864158631247f,
  0.004503586495512557f,
  0.006817813597517387f,
  0.009480950277059367f,
  0.012303953577688754f,
  0.015031007565154342f,
  0.017357416114031576f,
  0.018957770067474317f,
  0.019520003791684178f,
  0.018784493824282322f,
  0.01658833202041139f,
  0.012910878504479273f,
  0.007878503464745763f,
  0.0018018603237370905f,
  -0.004846377229804092f,
  -0.011450282514947837f,
  -0.017297081703748617f,
  -0.02163858793589608f,
  -0.023763802613738463f,
  -0.02307406706634422f,
  -0.019153875987040665f,
  -0.011830975700133816f,
  -0.0012166003892491977f,
  0.012282192238858954f,
  0.02797826170445089f,
  0.04494430386726061f,
  0.06208686365436761f,
  0.07823285982332916f,
  0.09223127671967807f,
  0.10305554284890964f,
  0.10989661028525659f,
  0.11223644794673888f,
  0.10989661028525659f,
  0.10305554284890964f,
  0.09223127671967807f,
  0.07823285982332916f,
  0.06208686365436761f,
  0.04494430386726061f,
  0.02797826170445089f,
  0.012282192238858954f,
  -0.0012166003892491977f,
  -0.011830975700133816f,
  -0.019153875987040665f,
  -0.02307406706634422f,
  -0.023763802613738463f,
  -0.02163858793589608f,
  -0.017297081703748617f,
  -0.011450282514947837f,
  -0.004846377229804092f,
  0.0018018603237370905f,
  0.007878503464745763f,
  0.012910878504479273f,
  0.01658833202041139f,
  0.018784493824282322f,
  0.019520003791684178f,
  0.018957770067474317f,
  0.017357416114031576f,
  0.015031007565154342f,
  0.012303953577688754f,
  0.009480950277059367f,
  0.006817813597517387f,
  0.004503586495512557f,
  0.0026559864158631247f,
  0.0013298367836838156f,
  0.0005382616364442431f,
  -0.0014404127183852448f,
};
#elif DT7837       
static const SAMPLE filter_taps[] = 
{
  -6186526,
  2311816,
  5711605,
  11407375,
  19342757,
  29282286,
  40720371,
  52845078,
  64557686,
  74549535,
  81423002,
  83837778,
  80678787,
  71246344,
  55451801,
  33837915,
  7738931,
  -20815032,
  -49178589,
  -74290400,
  -92937028,
  -102064755,
  -99102363,
  -82265271,
  -50813654,
  -5225259,
  52751614,
  120165719,
  193034315,
  266661049,
  336007574,
  396130317,
  442620186,
  472002347,
  482051873,
  472002347,
  442620186,
  396130317,
  336007574,
  266661049,
  193034315,
  120165719,
  52751614,
  -5225259,
  -50813654,
  -82265271,
  -99102363,
  -102064755,
  -92937028,
  -74290400,
  -49178589,
  -20815032,
  7738931,
  33837915,
  55451801,
  71246344,
  80678787,
  83837778,
  81423002,
  74549535,
  64557686,
  52845078,
  40720371,
  29282286,
  19342757,
  11407375,
  5711605,
  2311816,
  -6186526
};
#elif DT7816
static const SAMPLE filter_taps[] = 
{
-94,
  35,
  87,
  174,
  295,
  447,
  621,
  806,
  985,
  1138,
  1242,
  1279,
  1231,
  1087,
  846,
  516,
  118,
  -318,
  -750,
  -1134,
  -1418,
  -1557,
  -1512,
  -1255,
  -775,
  -80,
  805,
  1834,
  2945,
  4069,
  5127,
  6044,
  6754,
  7202,
  7356,
  7202,
  6754,
  6044,
  5127,
  4069,
  2945,
  1834,
  805,
  -80,
  -775,
  -1255,
  -1512,
  -1557,
  -1418,
  -1134,
  -750,
  -318,
  118,
  516,
  846,
  1087,
  1231,
  1279,
  1242,
  1138,
  985,
  806,
  621,
  447,
  295,
  174,
  87,
  35,
  -94    
};
#endif

static struct
{
    SAMPLE *double_h;
    SAMPLE *history;
    int taps;
    int state;
}g_filter = {NULL, NULL, 0, 0};

/*******************************************************************************
 * FIR filter the buffer with the specified number of samples
 * @param buf : Buffer with samples from AD
 * @param numsamples : #of samples in buffer
 */
void fir_filter(void *buf, int32_t numsamples)
{
    int i;
#ifdef DT7837
    int32_t *adbuf = (int32_t *)buf;
    for (i=0; i < numsamples; ++i, ++adbuf)
    {
        *adbuf = (int32_t)fir_double_h((SAMPLE)*adbuf, g_filter.taps, 
                                        g_filter.double_h, g_filter.history,  
                                        &g_filter.state);
    }
#elif DT7816
    int16_t *adbuf = (int16_t *)buf;
    for (i=0; i < numsamples; ++i, ++adbuf)
    {
        *adbuf = (int16_t)fir_double_h((SAMPLE)*adbuf, g_filter.taps, 
                                        g_filter.double_h, g_filter.history,  
                                        &g_filter.state);
    }
#else
    #error Undefined board type
#endif    
}

/*******************************************************************************
 * Allocate and initialize FIR filter using the coefficients in the specified
 * file or use defaults. Must be called once before calling fir_filter()
 * @param file  : File with list of filter coeffs, each in a new line. If it is
 *                NULL, then the default low pass FIR coeffs are used.
 * @return      : <=0 error, >0 is #of coeffs 
 */
int fir_filter_alloc(const char *filename)
{
    SAMPLE *buf;
    if (!filename)
    {
        buf = (SAMPLE *)malloc(3*SAMPLEFILTER_TAP_NUM * sizeof(SAMPLE));
        if (!buf)
            return -ENOMEM;
        g_filter.double_h = buf;
        g_filter.history = buf + (2*SAMPLEFILTER_TAP_NUM);
        g_filter.taps = SAMPLEFILTER_TAP_NUM;
        memcpy(g_filter.double_h, filter_taps, g_filter.taps*sizeof(SAMPLE));
        memcpy(g_filter.double_h+g_filter.taps, filter_taps, 
               g_filter.taps*sizeof(SAMPLE));
        memset(g_filter.history, 0, SAMPLEFILTER_TAP_NUM * sizeof(SAMPLE));
        return g_filter.taps;
    }
    
    FILE *fd = fopen(filename, "r");
    if (!fd)
    {
        fprintf(stderr, "Cannot open %s\n", filename);
        return -ENOENT;
    }
    
    //initial malloc to be resized as we read the file
    int allocation = 32;
    buf = (SAMPLE *)malloc(allocation * sizeof(SAMPLE));
    if (!buf)
        return -ENOMEM;    
    
    char *lineptr = NULL;
    size_t nbytes = 0;
    int taps = 0;
    char *endptr;
    while (getline (&lineptr, &nbytes, fd) > 0)
    {
        //skip lines that can't be parsed as a number
#if defined FIR_USES_FLOAT        
        buf[taps] = strtof(lineptr, &endptr);
#else
        buf[taps] = (SAMPLE)strtol(lineptr, &endptr, 10);
#endif
        if (lineptr == endptr)
        {
            fprintf(stdout, "%s", lineptr);
            continue;
        }
        ++taps;
        //reallocate memory to hold more coeffs read from the file
        if (taps < allocation)
            continue;
        allocation *= 2;
        buf= (SAMPLE *)realloc((void *)buf, allocation*sizeof(SAMPLE));
        if (!buf)
            break;
    }
    fclose(fd);
    if (!buf)
        return -ENOMEM;  
    
    //Finally, resize the allocated memory to exactly what is required
    buf = (SAMPLE *)realloc((void *)buf, 3*taps*sizeof(SAMPLE));
    if (!buf)
        return -ENOMEM;  
    g_filter.double_h = buf;
    g_filter.history = buf + (2*taps);
    g_filter.taps = taps;
    memcpy(g_filter.double_h+taps, g_filter.double_h, taps*sizeof(SAMPLE));
    memset(g_filter.history, 0, taps * sizeof(SAMPLE));
    fprintf(stdout, "Read %d coeffs from %s\n", taps, filename);
    return g_filter.taps;
}

/*******************************************************************************
 * Free the filter memory
 */
void fir_filter_free(void)
{
    if (g_filter.double_h)
        free (g_filter.double_h);
}
