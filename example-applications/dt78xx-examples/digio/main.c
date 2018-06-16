/* 
 * This is a simple test of the digital input and output in the DT78xx family.
 * This example writes the value specified in the command line to the digital
 * output device file /dev/dt78xx-dout and reads back from the digital input 
 * file /dev/dt78xx-din. It also writes the lower 8 bits of the data
 * to the debug LEDs on the base board.
 * 
 * The digital outputs should be connected to the digital inputs to verify that
 * the value written is read back.
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
 *      See usage() below
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include "dt78xx_ioctl.h"

#ifdef DT7837
    #define DOUT_DEV  "/dev/dt7837-dout"
    #define DIN_DEV   "/dev/dt7837-din"
#elif DT7816
    #define DOUT_DEV  "/dev/dt7816-dout"
    #define DIN_DEV   "/dev/dt7816-din"
#else
#error BOARD_TYPE not defined!!
#endif

/*
 * Command line arguments
 */
static void usage(const char *filename)
{
    fprintf(stderr,"Read digital inputs and optionally write digital outputs\n");
    fprintf(stderr,"Usage\n%s [hex-value]\n", filename);
    fprintf(stderr,"hex-value, if specified, is written to the digital output\n");
}

/*
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    int fdin = -EINVAL;
    int fdout= -EINVAL;  
    uint16_t dout = 0;
    uint16_t din = 0;
    ssize_t ret;

    if ((argc > 1) && (!isalnum(*argv[1])))
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    //digital input device file
    fdin = open(DIN_DEV, O_RDONLY);
    if (fdin < 0)
    {
        fprintf(stderr, "Failed open %s \"%s\"\n", DIN_DEV, strerror(errno));
        exit(EXIT_FAILURE);
    }
                
    //digital ouput device file
    fdout = open(DOUT_DEV, O_WRONLY);
    if (fdout < 0)
    {
        close(fdin);
        fprintf(stderr, "Failed open %s \"%s\"\n", DOUT_DEV, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //write to digital out
    if (argc > 1)
    {
        dout = strtoul(argv[1], NULL, 16); //hex value to write
        if (write(fdout, (const void*)&dout, sizeof(dout)) <= 0)
            fprintf(stderr, "Failed write \"%s\"\n", strerror(errno));
        //update debug leds
        dt78xx_led_t led;
        led.mask = 0xff;    // all bits are enabled
        led.state = (unsigned char) (dout & 0xff);
        if ((ret = ioctl(fdout, IOCTL_LED_SET, &led)))
            perror("write to led");
    }
 
    //read from digital input
    if (read(fdin, (void*)&din, sizeof(din)) <= 0)
        perror("read");
    
    if (argc > 1)
        printf("write %#02x read %#02x\n", dout, din);
    else
        printf("read %#02x\n", din);
    
    close(fdin);
    close(fdout);
    return (EXIT_SUCCESS);
}

