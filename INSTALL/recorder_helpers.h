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
#define LIBAIFF_NOCOMPAT 1 // do not use LibAiff 2 API compatibility
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

#define xstr(s) str(s)
#define str(s) #s

#define TRIG_LEVEL_V        0.0
#define DEFAULT_GAIN        1 // gain 1 => +/- 10 V; must be 1 for DT7816
#define LIBAIFF_NOCOMPAT    1 // do not use LibAiff 2 API compatibility

 /*****************************************************************************
 * Helper functions for recorder (DT7816)
 */
    
void led_indicators(uint8_t status, int streaming);

void getTime(struct tm **curTime, struct timeval *clockTime);

long getTimeEpoch(long year, int month, int day, int hour, int minute, int second);

void timestamp(char *filePath, char **argv, char *path_to_storage);

long getPresentTime();

int checkFatal(int gross_samples);

void createChanMask(int ain[], int *ch_on, chan_mask_t *chan_mask);

void configChan(dt78xx_ain_config_t ain_cfg[]);

void initTrig(dt78xx_trig_config_t trig_cfg_ai[]);

void calcSunUpDown(long *sunsets, long *sunrises, int duration_days, 
                   long safety_margin, double lon, double lat, int night_cycle);

#ifdef __cplusplus
}
#endif

#endif /* RECORDER_HELPERS_H */

