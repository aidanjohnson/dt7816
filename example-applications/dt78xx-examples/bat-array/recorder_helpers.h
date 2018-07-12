/* 
* This is the header for the custom application for DT7816 autonomous 
* asynchronous I/O sampling that configures the board's analog inputs. 
* The sampled data is read asynchronously from the input stream and 
* written to a AIFF file.
* 
* (c) Aidan Johnson (johnsj96@uw.edu)
* 12 July 2018
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
*/

#ifndef RECORDER_HELPERS_H
#define RECORDER_HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * External Libraries
 */
    
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <malloc.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
    
#include "dt78xx_aio.h"
#include "dt78xx_ioctl.h"
#include "dt78xx_misc.h"
    
#include "sunriset.h"
#include "libaiff.h"
#include "RingBuf.h"
    
/*****************************************************************************
 * Customisable Macros
 */

// The sample rate, active channels, number of buffers, and samples per channel  
// can be set with command line flags in a terminal shell used to run this program.

//Default analog inputs (AINx) enabled/active/on (1) or disabled/inactive/off (0)
#define AIN0                1
#define AIN1                0
#define AIN2                0
#define AIN3                0
#define AIN4                0
#define AIN5                0
#define AIN6                0
#define AIN7                0
#define PATH_TO_STORAGE     "/usr/local/path/to/ssd/" //Predefined write path
#define SAMPLE_RATE_HZ      400000.0
#define DURATION_DAYS       21 //Default number of days of sampling
#define SAFETY_MARGIN       3600 //Buffers in seconds before sunset and after sunrise
#define NIGHT_CYCLE         1 //Cycles recording on at night and off at day
#define DEFAULT_LATITUDE    47.655083 //Latitude (N := +, S := -)
#define DEFAULT_LONGITUDE   -122.293194 //Longitude (E := +, W := -)
    
 //Constraint: SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS <= 65536 samples = 2^(16 bits)
#define SAMPLES_PER_FILE    65536 // SAMPLES_PER_CHAN = SAMPLES_PER_FILE / NUM_CHANNELS
#define NUM_BUFFS           1 //Number of buffers per file initialised

/*****************************************************************************
 * Defaults: Change at own risk
 */

#define NUM_CHANNELS        AIN0+AIN1+AIN2+AIN3+AIN4+AIN5+AIN6+AIN7 //max ch: 8
#define SAMPLE_RATE         SAMPLE_RATE_HZ
#define DAEMON              0
#define AUTO_TRIG           1
#define LEN                 512 //Default character array size

#ifdef DT7816
    #define DEV_STREAM_IN   "/dev/dt7816-stream-in"
    //AIN device file
    #define DEV_AIN         "/dev/dt7816-ain"
    #define DOUT_DEV        "/dev/dt7816-dout"
#else
    #error Undefined board type
#endif

#define xstr(s) str(s)
#define str(s) #s

#define TRIG_LEVEL_V        0.0
#define DEFAULT_GAIN        1 // gain 1 => +/- 10 V; must be 1 for DT7816
#define LIBAIFF_NOCOMPAT    1 // do not use LibAiff 2 API compatibility

 /*****************************************************************************
 * Helper functions for recorder (DT7816)
 */
    
void led_indicators(uint8_t status, int streaming) {
    // Updates debug LEDs (8 in total), LED ON (1) := CHANNEL is READING/WRITING
    // Viewing the DT7816 such that the debug pin row is above the user LEDs:
    //  ______ ______ ______ ______ ______ ______ ______ ______ ______ _______
    // | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN6 | PIN7 | PIN8 | PIN9 | PIN10 |
    // ***** LED7 ** LED6 ** LED5 ** LED4 ** LED3 ** LED2 ** LED1 ** LED0 *****
    //
    // LED0 := AIN0, LED1 := AIN1, LED2 := AIN2, LED3 := AIN3,
    // LED4 := AIN4, LED5 := AIN5, LED6 := AIN6, LED7 := AIN7
    //
    // where the analog input channels have the following coding returned by
    // IOCTL_CHAN_MASK_GET:
    //
    // AIN0 = 0x01, AIN1 = 0x02, AIN2 = 0x04, AIN3 = 0x08
    // AIN4 = 0x10, AIN5 = 0x20, AIN6 = 0x40, AIN7 = 0x80
    //
    // and for input header pins (J16):
    //  ___________________________________________________
    // ||  2 |  4 |  6 |  8 | 10 | 12 | 14 | 16 | 18 | 20 ||
    // ||  1 |  3 |  5 |  7 |  9 | 11 | 13 | 15 | 17 | 19 ||7; //Defaults to 7 days
    // 
    // Analog Inputs (AINs):
    //
    // PIN5 := AIN0, PIN7 := AIN1, PIN9 := AIN2, PIN11 := AIN3 
    // PIN13 := AIN4, PIN15 := AIN5, PIN17 := AIN6, PIN19 := AIN7
    //
    // Analog Grounds (AGRDs):
    //
    // PIN6 := AGRD0, PIN8 := AGRD1, PIN10 := AGRD2, PIN12 := AGRD3 
    // PIN14 := AGRD4, PIN16 := AGRD5, PIN18 := AGRD6, PIN20 := AGRD7
    
    dt78xx_led_t led;
    led.mask = 0xff;    // all bits are enabled (8 LEDs capable of being lit)
    led.state = (status & 0xff);
    ioctl(streaming, IOCTL_LED_SET, &led);    
}

void getTime(struct tm **curTime, struct timeval *clockTime) {
    gettimeofday(&(*clockTime), NULL); //Gets current time
    *curTime = gmtime(&(*clockTime).tv_sec); // UTC aka GMT in ISO 8601: Zulu
}

long getTimeEpoch(long year, int month, int day, int hour, int minute, int second) {
    //Assumes UTC time given
    struct tm *time = malloc(sizeof(struct tm));
    time->tm_year = year - 1900;
    time->tm_mon = month - 1;
    time->tm_mday = day;
    time->tm_hour = hour;
    time->tm_min = minute;
    time->tm_sec = second;
    return (long) timegm(&(*time));
}

void timestamp(char *filePath, char **argv, char *path_to_storage) {
    struct timeval tv;
    struct tm *t_iso; //Time in accordance to ISO 8601
    getTime(&t_iso, &tv); //Gets current time in UTC (aka GMT or Zulu) 
     //Time corresponding to first sample (see start of while loop)
    const char *outputPath = path_to_storage; //A set path to local storage
    const char *ID; //Identification prefix
    ID = argv[optind]; //Physical location/identity: identifier
    char fileTime[LEN];

    //YYYY-MM-DD HH:mm:ss:uuuuuu (u=microseconds)
    sprintf(fileTime, "_%04d%02d%02dT%02d%02d%02d%liZ.aiff", 
            t_iso->tm_year+1900, t_iso->tm_mon + 1, t_iso->tm_mday, 
            t_iso->tm_hour, t_iso->tm_min, t_iso->tm_sec, (long) tv.tv_usec); 
    char fileName[LEN];
    strcpy(fileName, ID); //Identify
    strcat(fileName, fileTime); //Timestamped
    strcpy(filePath, outputPath); //Directory path
    strcat(filePath, fileName); //Full file path: concatenates filename
}

long getPresentTime() {
    struct tm* isoTime;
    struct timeval epochTime;
    getTime(&isoTime, &epochTime);
    return (long) epochTime.tv_sec;
}

int checkFatal(int gross_samples) {
    //SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS <= 65536 samples = 2^(16 bits)
    if(gross_samples > 65536) {
        fprintf(stderr, "Fatal Error: exceeded 16-bits!\n");
        fprintf(stderr, "SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS = %d > 65536\n", 
                gross_samples);
        return (EXIT_FAILURE);
    }
}

void createChanMask(int ain[], int *ch_on, chan_mask_t *chan_mask) {
        int ch_index = 0;
    if (ain[0]) {
        *chan_mask |= chan_mask_ain0;
        ch_on[ch_index++] = 0;
    }
    if (ain[1]) {
        *chan_mask |= chan_mask_ain1;
        ch_on[ch_index++] = 1;    
    }
    if (ain[2]) {
        *chan_mask |= chan_mask_ain2;
        ch_on[ch_index++] = 2;
    }
    if (ain[3]) {
        *chan_mask |= chan_mask_ain3;
        ch_on[ch_index++] = 3;
    }
    if (ain[4]) {
        *chan_mask |= chan_mask_ain4;
        ch_on[ch_index++] = 4;
    }
    if (ain[5]) {
        *chan_mask |= chan_mask_ain5;
        ch_on[ch_index++] = 5;
    }
    if (ain[6]) {
        *chan_mask |= chan_mask_ain6;
        ch_on[ch_index++] = 6;
    }
    if (ain[7]) {
        *chan_mask |= chan_mask_ain7;
        ch_on[ch_index++] = 7;
    }
}

void configChan(dt78xx_ain_config_t ain_cfg[]) {
    //Configures all channels even if not enabled and used
    dt78xx_ain_config_t ain0_cfg ={.ain=0, //AIN0
                                  .gain=1, //Default gain
                                  .ac_coupling=0, //DC coupling
                                  .current_on=0, //Current source off
                                  .differential=0
                                  }; 
    ain_cfg[0] = ain0_cfg;
    dt78xx_ain_config_t ain1_cfg ={.ain=1, //AIN1
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    ain_cfg[1] = ain1_cfg;
    dt78xx_ain_config_t ain2_cfg ={.ain=2, //AIN2
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    ain_cfg[2] = ain2_cfg;
    dt78xx_ain_config_t ain3_cfg ={.ain=3, //AIN3
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    ain_cfg[3] = ain3_cfg;
    dt78xx_ain_config_t ain4_cfg ={.ain=4, //AIN4
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    ain_cfg[4] = ain4_cfg;
    dt78xx_ain_config_t ain5_cfg ={.ain=5, //AIN5
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    ain_cfg[5] = ain5_cfg;
    dt78xx_ain_config_t ain6_cfg ={.ain=6, //AIN6
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    ain_cfg[6] = ain6_cfg;
    dt78xx_ain_config_t ain7_cfg ={.ain=7, //AIN7
                                   .gain=1, //Default gain
                                   .ac_coupling=0, //DC coupling
                                   .current_on=0, //Current source off
                                   .differential=0
                                  }; 
    ain_cfg[7] = ain7_cfg;
}


void initTrig(dt78xx_trig_config_t trig_cfg_ai[]) {
    //Configure for software trigger for all enabled channels
    dt78xx_trig_config_t trig0_cfg;
    trig_cfg_ai[0] = trig0_cfg;
    dt78xx_trig_config_t trig1_cfg;
    trig_cfg_ai[1] = trig1_cfg;
    dt78xx_trig_config_t trig2_cfg;
    trig_cfg_ai[2] = trig2_cfg;
    dt78xx_trig_config_t trig3_cfg;
    trig_cfg_ai[3] = trig3_cfg;
    dt78xx_trig_config_t trig4_cfg;
    trig_cfg_ai[4] = trig4_cfg;
    dt78xx_trig_config_t trig5_cfg;
    trig_cfg_ai[5] = trig5_cfg;
    dt78xx_trig_config_t trig6_cfg;
    trig_cfg_ai[6] = trig6_cfg;
    dt78xx_trig_config_t trig7_cfg;
    trig_cfg_ai[7] = trig7_cfg;
}

void calcSunUpDown(long *sunsets, long *sunrises, int duration_days, long safety_margin, double lon, double lat, int night_cycle) {
    struct timeval epoch_present;  //Seconds UTC relative to 1 Jan 1970 (epoch)
    struct tm *t_present = malloc(sizeof(struct tm)); //Time in accordance to ISO 8601
    gettimeofday(&epoch_present, NULL); //Gets current system time
    t_present = gmtime(&epoch_present.tv_sec); //Gets current time in UTC (aka GMT or Zulu)

    int elapsed_days;
    double rise, set;
    for (elapsed_days = 0; elapsed_days < duration_days; elapsed_days++) {
        int year = 1900 + (int) t_present->tm_year;
        int month = 1 + t_present->tm_mon;
        int day = t_present->tm_mday;
//        fprintf(stdout, "%d-%d-%d\n", year, month, day);
                
        long epoch_day = getTimeEpoch(year, month, day, 0, 0, 0);
        long epoch_set = epoch_day;
        if (night_cycle) {
            sun_rise_set(year, month, day, lon, lat, &rise, &set);
    //        fprintf(stdout, "%f, %f\n", rise, set);
            epoch_set += set*3600;
            sunsets[elapsed_days] = epoch_set - safety_margin;
        } else {
            sunsets[elapsed_days] = epoch_set;
        }

        time_t day_sec = 86400; //Length of 1 day in seconds
        epoch_day += day_sec;
        t_present = gmtime(&epoch_day);
        year = 1900 + (int) t_present->tm_year;
        month = 1 + t_present->tm_mon;
        day = t_present->tm_mday;
//        fprintf(stdout, "%d-%d-%d\n", year, month, day);

        long epoch_rise = getTimeEpoch(year, month, day, 0, 0, 0);
        if (night_cycle) {
            sun_rise_set(year, month, day, lon, lat, &rise, &set);
    //        fprintf(stdout, "%f, %f\n", rise, set);
            epoch_rise += rise*3600;
            sunrises[elapsed_days] = epoch_rise + safety_margin;
        } else {
            sunrises[elapsed_days] = epoch_rise;
        }
//        fprintf(stdout, "%ld; %ld; day %d; sunset %ld; sunrise %ld\n", epoch_present.tv_sec, epoch_day, elapsed_days, sunsets[elapsed_days], sunrises[elapsed_days]);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* RECORDER_HELPERS_H */

