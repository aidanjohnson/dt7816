/* 
 *  This example writes a single value to a specified analog output channel
 * 
 *  ===========================================================================
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed WITHOUT ANY WARRANTY; without the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * ============================================================================
 * Usage :
 *	See usage() below
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include "dt78xx_misc.h"

/*****************************************************************************
 * DA full scale, DA dev file specific to board
 */
#ifdef DT7837
    #define AOUT_DEV        "/dev/dt7837-aout"
#elif DT7816
    #define AOUT_DEV        "/dev/dt7816-aout"
#else
    #error Undefined board type
#endif
#define GAIN_1              (1)

/*****************************************************************************
 * Command line arguments
 */
static const char usage[]=
{
#ifdef DT7837
"Write single value to analog output.\n"
"Usage : %s volt\n"
"volt is the voltage output to analog output 0\n"
#elif DT7816
"Write single value(s) to analog output(s).\n"
"Usage : %s volt1 [volt2]\n"
"volt1 is the voltage output to analog output 0\n"
"volt2, if specified, is the voltage output to analog output 1\n"
#endif  
"Volt value must be less than 10.0V and greater than or equal to -10.0V\n"
};

/*****************************************************************************
 * main()
 */
int main (int argc, char** argv)
{
    int dev = -EINVAL;
    ssize_t ret;
    int err = EXIT_SUCCESS;
#ifdef DT7837
    int32_t aout[1];
#elif DT7816
    int16_t aout[2];
#endif    
    if (argc < 2)
    {
        printf(usage, argv[0]); 
        exit(EXIT_FAILURE);
    }
    
    dev = open(AOUT_DEV, O_RDWR);
    if (dev < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
#ifdef DT7837
    //The DT7837 supports read back of analog output
    ret = read(dev, (void*)aout, sizeof(aout));
    if (ret <= 0)
    {
        printf("read %s (%d)\n", strerror(errno), errno);
        goto _exit;
    }
    printf("Previous value %f V\n",raw2volts(aout[0], GAIN_1)); //gain x1=>10.0V
#endif  

    //The first value in the command line is for analog output 0
    aout[0] = volts2raw(strtof(argv[1], NULL), GAIN_1);
#ifdef DT7816
    //If a second value is specified, it is for analog output 1
    if (argc > 2)
        aout[1] = volts2raw(strtof(argv[2], NULL), GAIN_1);
#endif    
    ret = write(dev, (const void*)aout, sizeof(aout));
    if (ret <= 0)
    {
        printf("write %s (%d)\n", strerror(errno), errno);
        goto _exit;
    }
    
#ifdef DT7837
    //read analog output(s)
    ret = read(dev, (void*)aout, sizeof(aout));
    if (ret <= 0)
    {
        printf("read %s (%d)\n", strerror(errno), errno);
        goto _exit;
    }
    printf("Current value %f V\n",raw2volts(aout[0], GAIN_1));
#endif    

_exit:    
    close(dev);
    return (err);
}

