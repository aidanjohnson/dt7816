/* 
 * Calibration program for the DT7816
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
#include <time.h>

#include "dt78xx_ioctl.h"
#include "dt78xx_aio.h"
#include "dt78xx_misc.h"

#ifdef DT7816
    #define AIN_STREAM_FILE "/dev/dt7816-stream-in"
    #define AIN_FILE        "/dev/dt7816-ain"
    #define AOUT_FILE       "/dev/dt7816-aout"
    #define DEFAULT_SAMPLE_RATE_HZ     (200000.0f)
    #define DEFAULT_NUM_SAMPLES        (1000)
    #define AIN_OFFSET_MAX_COUNT       (10)
    #define AIN_9V_NOMINAL_COUNT       (29358)
    #define AIN_9V_MAX_COUNT           ((AIN_9V_NOMINAL_COUNT)+293)
    #define AIN_9V_MIN_COUNT           ((AIN_9V_NOMINAL_COUNT)-293)
    #define WIPER_MIN                  (0)
    #define WIPER_MAX                  (255)
    #define WIPER_MID                  (128)
#else
    #error Unsupported board type
#endif

/*****************************************************************************
 * Globals
 */
static int g_quit = 0;

// Command line arguments
static const char usage[]=
{
"Calibrates either the analog input or output subsystem in the DT7816\n"
"Usage : %s [options] {aout|ain}\n"
"Specify either aout or ain to calibrate analog output or input respectively\n"
"Options\n" 
"-p Prints current calibration\n"
};

/*****************************************************************************
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating abruptly
 */
static void sigint_handler(int i) 
{
   g_quit = -1;
}

/*****************************************************************************
 * Acquire one buffer and return its average value
 * @param fd_stream : file associated with DEV_STREAM_IN
 * @param aio       : Initialized AIO structures
 * @param buf       : pointer to allocated buffer
 * @param samples   : #of samples in buffer
 * @param avg       : buffer average returned here
 * @return          : <=0 error, 1=single buffer acquired 
 */
static int ain_buffer_average(int fd_stream, struct aio_struct *aio, 
                              int16_t *buf, int samples, int16_t *avg)
{
    int err, j;
    int32_t tmp;
    //submit the buffers
    if ((err = aio_start(aio)))
    {
        fprintf(stderr, "ERROR aio_start\n");
        return err;
    }  
    if ((err = ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0)))   
    {
        fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return err;
    }
    if ((err = ioctl(fd_stream, IOCTL_START_SUBSYS, 0)))
    {
        fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return err;
    }
    //wait for buffers to complete
    err = aio_wait(aio, -1); 
    
    //After completion ...
    ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);    
    aio_stop(aio);
    
    if (err <= 0)   //return any error
        return err;
    if (g_quit)     //return on Ctrl-C 
        return -1;
    //compute buffer average
    //fprintf(stdout,"samples = %d\n",samples);
    //For calibrating 8 channels, multiply samples by 8
    for (j=0, tmp=0; j <= (samples * 8) ; ++j, ++buf)
        tmp += *buf;
    *avg = tmp/(samples * 8);
    return err;   
}

/*****************************************************************************
 * Set the analog input gain potentiometer's wiper
 * @param fd_ain    : AIN file
 * @param val       : wiper value to set
 * @return          : <0 is error 
 */
static int ain_gain_wiper_set(int fd_ain, uint8_t val)
{
    dt78xx_cal_pot_t wiper;
    int err;
    
    memset(&wiper, 0, sizeof(wiper));
    wiper.pot = 0;      //AIN0
    wiper.value = val;
    err = ioctl(fd_ain, IOCTL_GAIN_POT_WIPER_SET, &wiper);
    return err;
}

/******************************************************************************
 * Analog input calibration
 */
static int ain_calibration(void)
{
    int err = 0;
    struct aio_struct *aio =NULL;
    int16_t offset, avg;
    uint8_t wiper;
    int fd_stream, fd_ain;

    fd_stream = open(AIN_STREAM_FILE, O_RDONLY);
    if (fd_stream < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), AIN_STREAM_FILE);
        return (EXIT_FAILURE);
    }

    fd_ain = open(AIN_FILE, O_RDONLY);
    if (fd_ain < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), AIN_FILE);
        close(fd_stream);
        return (EXIT_FAILURE);
    }        
    
    //write channel mask
    chan_mask_t chan_mask = chan_mask_ain0 | chan_mask_ain1 | chan_mask_ain2 | 
           chan_mask_ain3 | chan_mask_ain4 | chan_mask_ain5 | chan_mask_ain6 |
           chan_mask_ain7;
    //fprintf(stdout,"channel mask = %X\n",chan_mask);
    if ((err = ioctl(fd_stream, IOCTL_CHAN_MASK_SET, &chan_mask))!=0)
    {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //configure sampling rate. 
    dt78xx_clk_config_t cfg;
    cfg.clk_freq = DEFAULT_SAMPLE_RATE_HZ;
    cfg.ext_clk = 0; //internal clock
    if ((err = ioctl(fd_stream, IOCTL_SAMPLE_CLK_SET, &cfg))!=0)
    {
        perror("IOCTL_SAMPLE_CLK_SET");    
        goto _exit;
    }
    
    //Channel gain, coupling and current source
    int ch_index;
    dt78xx_ain_config_t ain_cfg;
    ain_cfg.ain = 0;
    ain_cfg.gain = 0; //x1 gain
    ain_cfg.ac_coupling = 0; //dc coupling
    ain_cfg.current_on = 0; //current source off
    for (ch_index = 0; ch_index < 8; ch_index++)
    {
        ain_cfg.ain = ch_index;
        if ((err = ioctl(fd_ain, IOCTL_AIN_CFG_SET, &ain_cfg))!=0)
        {
        fprintf(stderr, "IOCTL_AIN_CFG_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
        }   
    }

    //configure for software trigger
    dt78xx_trig_config_t trig_cfg;
    trig_cfg.src = trig_src_sw;
    if ((err = ioctl(fd_stream, IOCTL_START_TRIG_CFG_SET, &trig_cfg))!=0)
    {
        fprintf(stderr, "IOCTL_START_TRIG_CFG_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    //Create and initialize AIO structures
    aio = aio_create(fd_stream, 0, NULL, NULL);
    if (!aio)
    {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    //size one buffer to hold about specified number of samples 
    int samples = DEFAULT_NUM_SAMPLES;
    int buflen = aio_buff_size(samples, chan_mask, &samples);
    //fprintf(stdout,"buflen = %d\n",buflen);
    void **buf_array = aio_buff_alloc(aio, 1, buflen);
    if (!buf_array)
    {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
            
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, sigint_handler);
    
    //STEP 1 : Set the AIN0 gain potentiometer wiper to mid scale
    wiper=WIPER_MID;
    if (ain_gain_wiper_set(fd_ain, wiper))
        goto _exit;
    
    //STEP 2 : Short AIN0 and measure offset
    fprintf(stdout,"Short AIN0 thru AIN7 to AGND\n");
    fprintf(stdout,"Press Enter to continue, ctrl-C to quit\n");
    getchar();
    if ((ain_buffer_average(fd_stream, aio, (int16_t *)buf_array[0], samples, &offset))<=0)
        goto _exit;    
    fprintf(stdout,"Offset %fV count %d\n", raw2volts(offset, 1), offset);
    if ((offset > AIN_OFFSET_MAX_COUNT) || (offset < -AIN_OFFSET_MAX_COUNT))
    {
        fprintf(stderr,"ERROR Offset too high\n");
        goto _exit;
    }
    
    //STEP 3 : Apply +9V to AIN0, read and average one buffer
    fprintf(stdout,"Apply +9V to AIN0 thru AIN7\n");
    fprintf(stdout,"Press Enter to continue, ctrl-C to quit\n");
    getchar();
    if ((ain_buffer_average(fd_stream, aio, (int16_t *)buf_array[0], samples, &avg))<=0)
        goto _exit;    
    fprintf(stdout,"%fV count %d wiper %d\n", raw2volts(avg, 1), avg, wiper);
    //Sanity check that it is withing the nominal 9V range
    if ((avg < AIN_9V_MIN_COUNT) || (avg > AIN_9V_MAX_COUNT)) //error
    {
        fprintf(stderr,"ERROR Cannot be calibrated\n");
        goto _exit;
    }
    
    /* STEP 4 : Tweak the gain potentiometer's wiper, read and average one
     * buffer until the average equals the nominal 9V count + offset
     */
    uint8_t delta = 128;
    while ((avg != AIN_9V_NOMINAL_COUNT) && (delta !=0))
    {
        int16_t avg2;
        uint8_t wiper2;
        delta /= 2;
        if (avg>AIN_9V_NOMINAL_COUNT)
            wiper2 = wiper+delta;
        else
            wiper2 = wiper-delta;
        ain_gain_wiper_set(fd_ain, wiper2);
        if ((ain_buffer_average(fd_stream, aio, (int16_t *)buf_array[0], samples, &avg2))<=0)
            goto _exit;  
        avg2 += offset;
        if (abs(avg-AIN_9V_NOMINAL_COUNT)>abs(avg2-AIN_9V_NOMINAL_COUNT))
        {
            avg=avg2;
            wiper= wiper2;
        }
        fprintf(stdout,"%fV count %d wiper %d\n", raw2volts(avg, 1), avg, wiper);
    }
    
    //STEP 5: Save the gain potentiometer's wiper as user calibration
    dt78xx_cal_pot_t usercal;
    memset(&usercal, 0, sizeof(usercal));
    usercal.value = wiper;
    if ((err=ioctl(fd_ain, IOCTL_GAIN_POT_SET, &usercal)) != 0)
        fprintf(stderr, "IOCTL_GAIN_POT_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
    else if (!ioctl(fd_ain, IOCTL_GAIN_POT_GET, &usercal))
        fprintf(stdout,"New calibration %d\n", usercal.value);

_exit : 
    aio_stop(aio);
    aio_destroy(aio);
    if (fd_ain > 0)
        close(fd_ain);
    if (fd_stream > 0)
        close(fd_stream);
    return err;
}

/******************************************************************************
 * Replacement for stdlib getc() that does not require carriage return
 */
int _getc(void)
{
    fflush(stdout);
    do
    {
      if(kbhit())
      {
        int c = fgetc(stdin);
        fflush(stdin);
        return c;
      }
      usleep(1000); /* Sleep for a millisecond. */
    } while(!g_quit);
    return 0;
}

/******************************************************************************
 * Called from aout_calibration() to adjust the wiper for either the offset
 * or gain potentiometer for a specific AOUT channel
 * @param fd     : AOUT file handle
 * @param chan   : 0=AOUT0, 1=AOUT1
 * @param gain   : 1=gain potentiometer, 0=offset potentiometer
 * @return       : 0=adjustment done, <0 quit 
 */
static int aout_calibration_adjust(int fd, int chan, int gain)
{
    dt78xx_cal_pot_t cal;
    memset(&cal, 0, sizeof(cal));
    cal.pot=chan;
    if ((ioctl(fd, gain?IOCTL_GAIN_POT_WIPER_GET:IOCTL_OFFSET_POT_WIPER_GET,
               &cal)) < 0)
    {
        return -1;
    }
    fprintf(stdout, "Press u/d and U/D for fine and coarse up/down adjustment\n");
    fprintf(stdout, "Press s to save calibration\n");
    fprintf(stdout, "%03d",cal.value);
    int c, delta;
    while ((c=_getc())!=0)
    {
        if ((c=='s')||(c=='S'))
        {
            if ((ioctl(fd, gain?IOCTL_GAIN_POT_SET:IOCTL_OFFSET_POT_SET, &cal)) < 0)
            {
                fprintf(stderr, "IOCTL_%s_POT_SET ERROR %d \"%s\"\n", 
                        gain?"GAIN":"OFFSET", errno, strerror(errno));
                return -1;
            }
            return 0;
        }
        delta = (c=='u')?1:(c=='U')?10:(c=='d')?-1:(c=='D')?-10:0;
        if (!delta)
            continue;
        delta += (int)cal.value;
        if (delta < WIPER_MIN)
            delta = WIPER_MIN;
        else if (delta > WIPER_MAX)
            delta = WIPER_MAX;
        cal.value = delta;

        if ((ioctl(fd, gain?IOCTL_GAIN_POT_WIPER_SET:IOCTL_OFFSET_POT_WIPER_SET, 
                    &cal)) < 0)
        {
            return -1;
        }
        ioctl(fd, gain?IOCTL_GAIN_POT_WIPER_GET:IOCTL_OFFSET_POT_WIPER_GET,&cal);
        fprintf(stdout, "\b\b\b\b\b%03d",cal.value);
    }
    return -1;
}

/******************************************************************************
 * Analog output calibration
 */
static int aout_calibration(void)
{
    int err = 0;
    int fd_aout = 0;
    int16_t aout[2];
    dt78xx_cal_pot_t cal;
    int chan;
    
    fd_aout = open(AOUT_FILE, O_RDWR);
    if (fd_aout < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), AOUT_FILE);
        return (EXIT_FAILURE);
    }        
    //Set up ctrl-C handler to terminate process gracefully
    sigaction_register(SIGINT, sigint_handler);
     
    for (chan=0; chan < 2; ++chan)
    {
        //STEP 1 : Set gain potentiometer wiper to midscale
        memset(&cal, 0, sizeof(cal));
        cal.value = WIPER_MID;
        cal.pot=chan;
        if ((err = ioctl(fd_aout, IOCTL_GAIN_POT_WIPER_SET, &cal)) < 0)
        {
            fprintf(stderr, "IOCTL_GAIN_POT_WIPER_SET ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        }
        if ((err = ioctl(fd_aout, IOCTL_OFFSET_POT_WIPER_SET, &cal)) < 0)
        {
            fprintf(stderr, "IOCTL_OFFSET_POT_WIPER_SET ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            goto _exit;
        }
        
        //STEP 2 : Output -9.9V & read it in a DVM
        aout[chan] = volts2raw(-9.9f, 1);
        if (write(fd_aout, (const void*)aout, sizeof(aout)) <= 0)
        {
            printf("write %s (%d)\n", strerror(errno), errno);
            goto _exit;
        }
        fprintf(stdout,"Note the voltage on AOUT%d\n", chan);
        fprintf(stdout, "Press any key to continue or control-C to quit\n");
        _getc();
        
        //STEP 3 : Output +9.9V & read it in a DVM
        aout[chan] = volts2raw(9.9f, 1);
        write(fd_aout, (const void*)aout, sizeof(aout));
        
        //Adjust the gain pot first
        fprintf(stdout, "Adjust AOUT%d voltage to be 19.8V plus the previous "
                        "noted reading\n", chan);
        if (aout_calibration_adjust(fd_aout, chan, 1)<0)
            goto _exit;
        fprintf(stdout, "\nAOUT%d gain calibration saved\n\n",chan);
        
        //Adjust offset potentiometer
        aout[chan] = volts2raw(0.0f, 1);
        write(fd_aout, (const void*)aout, sizeof(aout));

        fprintf(stdout, "Now adjust AOUT%d to be within +/-20uV of 0V\n", chan);
        if (aout_calibration_adjust(fd_aout, chan, 0)<0)
            goto _exit;
        fprintf(stdout, "\nAOUT%d offset calibration saved\n\n",chan);
    }
_exit : 
    if (fd_aout > 0)
        close(fd_aout);
    kbfini(); //see dt78xx_misc.h
    return err;
}

/******************************************************************************
 * Prints the gain calibration for analog inpu
 * @return <0= failure, 0=success
 */
static int print_ain_calibration(void)
{
    dt78xx_cal_pot_t cal;
    int fd = 0;
    uint32_t tmp;
    
    fd = open(AIN_FILE, O_RDWR);
    if (fd < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), AIN_FILE);
        return (-1);
    } 
    memset(&cal, 0, sizeof(cal));
    if (ioctl(fd, IOCTL_GAIN_POT_WIPER_GET, &cal))
    {
        fprintf(stderr, "IOCTL_GAIN_POT_WIPER_GET %d \"%s\"\n", 
                errno, strerror(errno));
        close(fd);
        return -1;
    }
    tmp = cal.value;
    if (ioctl(fd, IOCTL_GAIN_POT_GET, &cal))
    {
        fprintf(stderr, "IOCTL_GAIN_POT_GET %d \"%s\"\n", 
                errno, strerror(errno));
        close(fd);
        return -1;
    }
    fprintf(stdout, "AIN gain calibration %d\n", cal.value);
    if (tmp!=cal.value)
        fprintf(stdout, "ERROR wiper %d\n", tmp);
    
    close(fd);
    return 0;
}

/******************************************************************************
 * Prints the offset and gain calibrations for both analog  output channels
 * @return <0= failure, 0=success
 */
static int print_aout_calibration(void)
{
    dt78xx_cal_pot_t cal;
    int fd = 0;
    
    fd = open(AOUT_FILE, O_RDWR);
    if (fd < 0)
    {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), AOUT_FILE);
        return (-1);
    } 
    
    memset(&cal, 0, sizeof(cal));
    for (cal.pot=0; cal.pot<2; ++cal.pot)
    {
        uint32_t tmp;
        //read  gain pot wiper
        if (ioctl(fd, IOCTL_GAIN_POT_WIPER_GET, &cal))
        {
            fprintf(stderr, "IOCTL_GAIN_POT_WIPER_GET %d \"%s\"\n", 
                    errno, strerror(errno));
            close(fd);
            return -1;
        }
        tmp = cal.value;
        //read gain pot user calibration
        if (ioctl(fd, IOCTL_GAIN_POT_GET, &cal))
        {
            fprintf(stderr, "IOCTL_GAIN_POT_GET %d \"%s\"\n", 
                    errno, strerror(errno));
            close(fd);
            return -1;
        }
        fprintf(stdout, "AOUT%d gain calibration %5d\n", cal.pot, cal.value);
        if (tmp!=cal.value)
            fprintf(stdout, "ERROR wiper %d\n", tmp);
            
        //read offset pot wiper
        if (ioctl(fd, IOCTL_OFFSET_POT_WIPER_GET, &cal))
        {
            fprintf(stderr, "IOCTL_OFFSET_POT_WIPER_GET %d \"%s\"\n", 
                    errno, strerror(errno));
            close(fd);
            return -1;
        }
        tmp = cal.value;
        //read offset pot user calibration
        if (ioctl(fd, IOCTL_OFFSET_POT_GET, &cal))
        {
            fprintf(stderr, "IOCTL_OFFSET_POT_GET %d \"%s\"\n", 
                    errno, strerror(errno));
            close(fd);
            return -1;
        }
        fprintf(stdout, "AOUT%d offset calibration %3d\n", cal.pot,cal.value);
        if (tmp!=cal.value)
            fprintf(stdout, "ERROR wiper %d\n", tmp);
    }
    close(fd);
    return 0;
}
/******************************************************************************
 * Command line arguments see usage above
 */
int main (int argc, char** argv)
{
    int ret = EXIT_SUCCESS;
    int opt;
    int print = 0;
    
    while ((opt = getopt(argc, argv, "p")) != -1) 
    {
        switch (opt) 
        {
            case 'p':
                print = 1;
                break;
            default :
                printf(usage, argv[0]);
                return EXIT_FAILURE;
        }
    }  
    if (optind == argc)
    {
        printf(usage, argv[0]);
        return (EXIT_FAILURE);
    }
    
    if (strstr(argv[optind], "ain"))
    {
        if (print)
            ret = print_ain_calibration();
        else
            ret = ain_calibration();
        return (ret);
    }
    if (strstr(argv[optind], "aout"))
    {
        if (print)
            ret = print_aout_calibration();
        else
            ret = aout_calibration();
        return (ret);
    }
    printf(usage, argv[0]);
    return (EXIT_FAILURE);
}

