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
    
#ifdef DT7816
    #define DEV_STREAM_IN   "/dev/dt7816-stream-in"
    //AIN device file
    #define DEV_AIN         "/dev/dt7816-ain"
    #define DOUT_DEV        "/dev/dt7816-dout"
#else
    #error Board not supported
#endif
    
#include "sunriset.h"
#define LIBAIFF_NOCOMPAT 1 // do not use LibAiff 2 API compatibility
#include "libaiff.h"
#include "RingBuf.h"
    
/*****************************************************************************
 * Customisable Macros
 */

/**
 * The sample rate, active channels, number of buffers, and samples per channel
 * can be set with command line flags in a terminal shell used to run this program.
 * 
 * Default analog inputs (AINx) enabled/active/on (1) or disabled/inactive/off (0)
 */
#define AIN0                1
#define AIN1                0
#define AIN2                0
#define AIN3                0
#define AIN4                0
#define AIN5                0
#define AIN6                0
#define AIN7                0
#define PATH_TO_STORAGE     "/usr/local/path/to/ssd/" /// Predefined write path
#define SAMPLE_RATE_HZ      400000.0
#define DURATION_DAYS       21 /// Default number of days of sampling
#define SAFETY_MARGIN       3600 /// Buffers in seconds before sunset and after sunrise
#define NIGHT_CYCLE         0 /// Cycles recording on at night and off at day
#define DEFAULT_LATITUDE    47.655083 /// Latitude (N := +, S := -)
#define DEFAULT_LONGITUDE   -122.293194 /// Longitude (E := +, W := -)
    
/// Constraint: SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS <= 65536 samples = 2^(16 bits)
#define SAMPLES_PER_FILE    65536 /// SAMPLES_PER_CHAN = SAMPLES_PER_FILE / NUM_CHANNELS
#define NUM_BUFFS           1 /// Number of buffers per file initialised

/*****************************************************************************
 * Defaults: Change at own risk
 */

#define NUM_CHANNELS        AIN0+AIN1+AIN2+AIN3+AIN4+AIN5+AIN6+AIN7 /// max ch: 8
#define SAMPLE_RATE         SAMPLE_RATE_HZ
#define AUTO_TRIG           1
#define LEN                 512 /// Default character array size

#define xstr(s) str(s)
#define str(s) #s

#define TRIG_LEVEL_V        0.0
#define DEFAULT_GAIN        1 /// gain 1 => +/- 10 V; must be 1 for DT7816
#define LIBAIFF_NOCOMPAT    1 /// Do not use LibAiff 2 API compatibility

/*****************************************************************************
 * Command line arguments with help
 */

static const char g_usage[] = {
"\n--------------------Autonomous Microphone Array for the DT7816 DAQ------------------\n"
"Samples channels AINx (at most 8 simultaneous channels) and writes data to\n"
"a timestamped file in AIFF format, saving it following a predefined path to\n"
"storage. The files are saved to <path>/<prefix>_<YYYY-DD-MMTHHmmssuuuuuuZ>.aiff\n"
"Usage        : %s <identifier prefix> [options] \n"
"Required     : a file or location identifier prefix, such as NORTH or 1.\n" 
"Options\n"
"-i|--inputs  : 8-bit binary string to enable and disable analog input channels.\n"
"               A channel is on if its bit is 1 and off if its bit is 0. Bit \n"
"               positions 0/1/2/3/4/5/6/7 correspond to channels AIN0/1/2/3/4/5/6/7.\n"
"               For example, 10101001 enables AIN0/2/4/7 and disables AIN1/3/5/6.\n"
"               By default, on channels AIN0 is enabled (i.e., 10000000).\n"        
"-s|--samples : number of samples per file, defaults " xstr(SAMPLES_PER_FILE) ".\n"
"               Note that you are limited to 2^(16-bits) = 65536 samples combined\n"
"               for all channels >= (samples/channel)(channels/buffer)(buffers)\n"
"-c|--clk     : sampling rate in Hz, defaults " xstr(SAMPLE_RATE_HZ) ".\n"
"-b|--buffers : number of buffers per file written, defaults " xstr(NUM_BUFFS) ".\n"
"-d|--dur     : fixed duration of sampling period in days at night as determined "
"               by sunset and sunrise times, defaults " xstr(DURATION_DAYS) " days.\n"
"-t|--trig    : when the voltage on either AIN crosses " xstr(TRIG_LEVEL_V) " V rising (threshold)\n"
"               acquisition is triggered. By default, acquisition is triggered\n"
"               when you start the analog input operation using the ioct.\n"
"-m|--margin  : margin of safety before the time of sunset and after the time of "
"               sunrise in seconds (hours*3600), defaults " xstr(SAFETY_MARGIN) " s."
"\n"
};

/*****************************************************************************
 * Circular (ring) buffer (queue) data type
 */

struct circ_buffer {
    float sample_rate;  
    int32_t num_samples;
    RingBuf *vbuf;  /// Buffer with raw values converted to voltage
};

 /*****************************************************************************
 * Helper functions for recorder (DT7816)
 */

/**
 * Updates debug LEDs (8 in total), LED ON (1) := CHANNEL is READING/WRITING. 
 * Viewing the DT7816 such that the debug pin row is above the user LEDs:
 *  ______ ______ ______ ______ ______ ______ ______ ______ ______ _______
 * | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN6 | PIN7 | PIN8 | PIN9 | PIN10 |
 * ***** LED7 ** LED6 ** LED5 ** LED4 ** LED3 ** LED2 ** LED1 ** LED0 *****
 * 
 * LED0 := AIN0recorder, LED1 := AIN1, LED2 := AIN2, LED3 := AIN3,
 * LED4 := AIN4, LED5 := AIN5, LED6 := AIN6, LED7 := AIN7
 * 
 * where the analog input channels have the following coding returned by
 * IOCTL_CHAN_MASK_GET:
 * 
 * AIN0 = 0x01, AIN1 = 0x02, AIN2 = 0x04, AIN3 = 0x08
 * AIN4 = 0x10, AIN5 = 0x20, AIN6 = 0x40, AIN7 = 0x80
 * 
 * and for input header pins (J16):
 *  ___________________________________________________
 * ||  2 |  4 |  6 |  8 | 10 | 12 | 14 | 16 | 18 | 20 ||
 * ||  1 |  3 |  5 |  7 |  9 | 11 | 13 | 15 | 17 | 19 ||
 * 
 * Analog Inputs (AINs):
 * 
 * PIN5 := AIN0, PIN7 := AIN1, PIN9 := AIN2, PIN11 := AIN3 
 * PIN13 := AIN4, PIN15 := AIN5, PIN17 := AIN6, PIN19 := AIN7
 * 
 * Analog Grounds (AGRDs):
 * 
 * PIN6 := AGRD0, PIN8 := AGRD1, PIN10 := AGRD2, PIN12 := AGRD3
 * PIN14 := AGRD4, PIN16 := AGRD5, PIN18 := AGRD6, PIN20 := AGRD7
 * 
 * @param status        Whether each hannel is active
 * @param streaming     1 if presently streaming
 */        
void ledIndicators(uint8_t status, int streaming);

/**
 * Retrives present time as Unix Epoch and UTC; readily formatted in ISO 8601.
 * UTC = Universal Coordinated Time (aka GMT = Greenwich Mean Time): Zulu
 * 
 * @param pres_time     Present UTC time
 * @param clock_time    Present Unix Epoch time
 */
void getTime(struct tm **pres_time, struct timeval *clock_time);

/**
 * Converts given date and time (assuming in UTC) to Unix Epoch time.
 * 
 * @param  year
 * @param  month
 * @param  day
 * @param  hour
 * @param  minute
 * @param  second
 * @return present time (GMT) in s since Unix Epoch
 */
long getTimeEpoch(long year, int month, int day, int hour, int minute, int second);

/**
 * Creates string of file path a using given directory path to storage with the
 * file name a timestamp in ISO 8601 format. It gets the present time in UTC
 * (GMT/Zulu). The timestamp corresponds to the first sample of the file (i.e., 
 * the beginning of the while loop). An identification prefix (required) is 
 * given in the command line. This ID prefix provides a physical location or 
 * identity; that is, an identifier. In general,
 * 
 * ./release/recorder <identifier prefix> [options]
 * 
 * The timestamp has the form of:
 * 
 * YYYY-MM-DD HH:mm:ss:uuuuuu 
 * (Y=year, M=month, D=day, H=hour, m=minute, s=second, u=microseconds)
 * 
 * The full file path has the form of (T is not a placeholder):
 * 
 * <path>/<prefix>_<YYYY-DD-MMTHHmmssuuuuuuZ>.aiff
 * 
 * @param file_path         Concatenated resultant string of full file path
 * @param argv              ID argument
 * @param path_to_storage   A set path to local storage
 */
void timestamp(char *file_path, char **argv, char *path_to_storage);

/**
 * Returns the present time in Unix Epoch (UTC) seconds since 1 Jan 1970
 * 
 * @return Present time (s)
 */
long getPresentTime();

/**
 * Checks that selected samples not in excess of 65536.
 * gross_samples <= 65536 samples = 2^(16 bits)
 * 
 * @param gross_samples     SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS
 * @return                  1 if successful, 0 if failure
 */
int checkFatal(int gross_samples);

/**
 * Creates channel mask for each active channel determined by ain.
 * 
 * 
 * @param ain       Array of channel states (1 = on, 0 = off) for channels 
 *                  1, 2, 3, 4, 5, 6, 7
 * @param ch_on     Array of the active/enabled/on channels given by their index
 * @param chan_mask Channel mask with a bitwise format
 */
void createChanMask(int ain[], int *ch_on, chan_mask_t *chan_mask);

/**
 * Configures all channels even if not enabled and used. Configuration in
 * comprised of its number, gain, DC or AC coupling, current source, and 
 * differential.
 * 
 * @param ain_cfg   Array of the configurations for all eight channels
 */
void configChan(dt78xx_ain_config_t ain_cfg[]);

/**
 * Initialises the software trigger for all enabled channles individually.
 * 
 * @param trig_cfg_ai   Array of trigger configurations for all channels
 */
void initTrig(dt78xx_trig_config_t trig_cfg_ai[]);

/**
 * Configures the passed channel individually (of the ones enabled).
 * 
 * @param fd_stream     Input stream
 * @param trig_cfg      Trigger configuration
 * @param auto_trig     If automatically triggered or not
 * @return              1 if successful, 0 if failure
 */
int configTrig(int* fd_stream, dt78xx_trig_config_t trig_cfg, int auto_trig);

/**
 * Calculates the sunset and sunrise time (offset by a safety margin) according
 * to a location on Earth given by longitude and latitude coordinates. 
 * Note:
 *      year,month,date = calendar date, 1801-2099 only.
 *      Eastern longitude positive, Western longitude negative
 *      Northern latitude positive, Southern latitude negative
 * 
 * @param sunsets       Array of sunset times in Unix Epoch time
 * @param sunrises      Array of sunrise times in Unix Epoch time
 * @param duration_days Number of days for sampling/recording
 * @param safety_margin Increases sampling duration by 2*safety_margin (in s)
 * @param lon           Longitude coordinate
 * @param lat           Latitude coordinate
 * @param night_cycle   On = 1, sampling only after dusk and before dawn
 */
void calcSunUpDown(long *sunsets, long *sunrises, int duration_days, 
                   long safety_margin, double lon, double lat, int night_cycle);

/**
 * Writes input samples to AIFF files
 * 
 * 1) Reads input data from linear array buffer
 * 2) Writes data to (intermediate) circular buffer
 * 3) Writes advances by one value
 * 4) Continues to write until it has writtent number of channels per file data
 * 5) Reads first data written to circular buffer, and writes to file
 * 6) Reads advances by one value, simultaneously with writes
 * 7) Continues to write (simultaneously) for next input array buffer
 * 8) Continues to read, lagging behind writing by the number of channels per file
 * 
 * The order of the data in the input (AIN) buffer is as follows,
 * assuming that all channels are enabled in the input stream:
 * Analog input channels 0 through 7. Each analog input sample is a
 * 16-bit, two’s complement value.
 * 
 * Simultaneously analog input (channel) samples put 
 * inline and sequentially for AIFF recording like so:
 *  ___________ ___________ ___________ ___________
 * |           |           |           |           |
 * | Channel 1 | Channel 2 | Channel 1 | Channel 2 | ...
 * |___________|___________|___________|___________|
 *  <---------> <---------> <---------> <--------->  ...
 *    Segment     Segment     Segment     Segment
 *  <---------------------> <--------------------->  ...
 *      Sample frame 1          Sample frame 2  
 * 
 * @param file              File opject/reference
 * @param buffer_object     Circular buffer object
 * @param channels_per_file Number of (enabled) channels per file
 * @param num_buffers       Number of buffers set
 * @param ch_on             Indices of channels that are on/enabled
 * @param buf_array         Linear input buffer array
 * @param ain_cfg           Configuration of analog input
 * @return                  1 if successful, 0 if failure
 */
int writeBuffer(AIFF_Ref file, struct circ_buffer buffer_object, 
                int channels_per_file, int num_buffers, int* ch_on, 
                void** buf_array, dt78xx_ain_config_t* ain_cfg);

/**
 * Checks for missing AIFF file identifier.
 * 
 * @param argc
 * @param argv
 * @return      1 if successful, 0 if failure
 */
int checkID(int argc, char** argv);

/**
 * Checks that sample rate is positive and non-zero.
 * 
 * @param buffer_object     Sample rate for input buffer
 * @param argv
 * @return                  1 if successful, 0 if failure
 */
int checkRate(struct circ_buffer buffer_object, char** argv);   

/**
 * Opens input stream.
 * 
 * @param   fd_stream       Input stream
 * @return  1 if successful, 0 if failure
 */
int openStream(int* fd_stream);

/**
 * Opens analog input.
 * 
 * @param    fd_stream
 * @param    fd_ain
 * @return   1 if successful, 0 if failure
 */
int openAIN(int* fd_stream, int* fd_ain);

/**
 * Waits for all buffers to complete.
 * 
 * @param num_buffers   number of active buffers
 * @param g_quit        
 * @param aio_struct    analog input/output API
 */
void waitBuffering(int num_buffers, int g_quit, struct aio_struct**);

#ifdef __cplusplus
}
#endif

#endif /* RECORDER_HELPERS_H */

