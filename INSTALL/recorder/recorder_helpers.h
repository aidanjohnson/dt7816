/* 
 * @file recorder_helpers.h
 * @brief This is the header for the custom application for DT7816 autonomous 
 * asynchronous I/O sampling that configures the board's analog inputs. 
 * The sampled data is read asynchronously from the input stream and 
 * written to a AIFF file.
 * 
 * (c) Aidan Johnson (johnsj96@uw.edu)
 * 18 September 2018
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

/*
 * ==== External Libraries ====
 */
 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define __USE_GNU   (1)
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>  
#include <sys/types.h>
#include <sys/stat.h>  
#include <linux/aio_abi.h>	// for AIO types and constants
    
#include "dt78xx_aio.h"
#include "aio_syscall.h"
#include "dt78xx_ioctl.h"
#include "dt78xx_misc.h"
        
#ifdef DT7816
    #define BOARD_STR       "dt7816"
    #define CLK_MAX_HZ      (400000.0f)
    #define CLK_MIN_HZ      (100.0f) // Minimum for AD
#else
    #error Board not supported
#endif

/* Device files */
#define DEV_STREAM_IN   "/dev/"BOARD_STR"-stream-in"
#define DEV_STREAM_OUT  "/dev/"BOARD_STR"-stream-out"
#define DEV_AIN         "/dev/"BOARD_STR"-ain"
    
/*
 * ==== Customisable Macros ====
 */

/*
 * @brief The sample rate, active channels, number of buffers, and samples per channel
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

#define SAMPLE_RATE_HZ      (200000.0f) // Audio file sampling rate in Hz: max 400000.0f, min 100.0f
#define AIFF                1 // 1 for writing to AIFF, 0 for CSV fallback
#define PATH_TO_STORAGE     "/nfs/dt7816/INSTALL/demo/" // Predefined write path
#define FILE_TIME_S         (60) // Length of write file in seconds
#define DURATION_DAYS       21 // Default number of days of sampling
    
/*
 * On = 1, sampling only after dusk and before dawn.
 * Cycles recording on at night and off at day.
 */    
#define NIGHT_CYCLE         0
    
/* 
 * Pillow, or margin of safety, in seconds before sunset and after sunrise for 
 * NIGHT_CYCLE. Increases sampling duration by 2*SAFETY_MARGIN (in s) per day.
 */    
#define SAFETY_MARGIN       3600 

/* Location geographic coordinates of recorder */    
#define DEFAULT_LATITUDE    47.655083 // Latitude (N := +, S := -)
#define DEFAULT_LONGITUDE   -122.293194 // Longitude (E := +, W := -)

/*
 * ===== Debug Options ====
 */
#define LED_ENABLED         1 // Debug led flashed on overrun

/*
 * ==== Defaults: Change at own risk ====
 * Constraint: SAMPLES_PER_CHAN * NUM_CHANNELS * 2 = BUFFERS_SAMPLES <= 65536 samples = 2^(16 bits)
 */ 
#define BUFFERS_SAMPLES     (65536) // Do not exceed 65536 (total samples for sum of buffers), 66368 empirical max
    
#define AUTO_TRIG           1
#define TRIG_LEVEL_V        0.0
#define LEN                 512 // Default character array size 
#define MAX_AIO_EVENTS      64
    
/*
 * ==== Do not change! Unexpected outcomes will result ====
 */
        
#define xstr(s) str(s)
#define str(s) #s

/* 
 * Number of buffers queued for the AIO. increase this as sample rate is
 * increased. For true double buffer (ping-pong buffer), set to 2.
 */    
#define NUM_BUFFS           32 // min 2, max 128
    
#define DEFAULT_GAIN        1 // Gain 1 => +/- 10 V; must be 1 for DT7816
    
#define NUM_CHANNELS        (AIN0+AIN1+AIN2+AIN3+AIN4+AIN5+AIN6+AIN7) // max ch: 8 
#define SAMPLE_RATE         SAMPLE_RATE_HZ
    
#define SAMPLES_PER_FILE    (SAMPLE_RATE_HZ * FILE_TIME_S)   
#define SAMPLES_PER_BUFFER  (BUFFERS_SAMPLES / NUM_BUFFS)
#define SAMPLES_PER_CHAN    (SAMPLES_PER_BUFFER / NUM_CHANNELS)
    
/*
 * Number of buffers must be positive and non-zero. Number of buffers must even;
 * otherwise use one fewer. Number of buffers cannot exceed MAX_AIO_EVENTS.
 */
#define BUFFERS_PER_FILE    (SAMPLES_PER_FILE / SAMPLES_PER_BUFFER) 

/*
 * ==== External, non-standard C libraries ====
 */    
#include "sunriset/sunriset.h"
#if AIFF
#include <sndfile.h>
#endif
    
/*
 * ==== Command line arguments with help ====
 */

static const char usage[] = {
"\n--------------------Autonomous Microphone Array for the DT7816 DAQ------------------\n"
"Samples channels AINx (at most 8 simultaneous channels) and writes data to\n"
"a timestamped file in AIFF format, saving it following a predefined path to\n"
"storage. The files are saved to <prefix>_<YYYYMMDD>T<HHmmssuuuuuu>Z.aiff\n"
"As a fallback recordings can be saved in CSV format (.aiff becomes .csv\n"
"Usage        : %s <identifier prefix> [options] \n"
"Required     : a file or location identifier prefix, such as NORTH or 1.\n" 
"Options\n"
"-i|--inputs  : 8-bit binary string to enable and disable analog input channels.\n"
"               A channel is on if its bit is 1 and off if its bit is 0. Bit \n"
"               positions 0/1/2/3/4/5/6/7 correspond to channels AIN0/1/2/3/4/5/6/7.\n"
"               For example, 10101001 enables AIN0/2/4/7 and disables AIN1/3/5/6.\n"
"               By default, on channels AIN0 is enabled (i.e., 10000000).\n"        
"-s|--seconds : number of seconds per file, defaults " xstr(FILE_TIME_S) ".\n"
"-c|--clk     : sampling rate in Hz, defaults " xstr(SAMPLE_RATE_HZ) ".\n"
"-d|--dur     : fixed duration of sampling period in days at night as determined "
"               by sunset and sunrise times, defaults " xstr(DURATION_DAYS) " days.\n"
"-t|--trig    : when the voltage on either AIN crosses " xstr(TRIG_LEVEL_V) " V rising (threshold)\n"
"               acquisition is triggered. By default, acquisition is triggered\n"
"               when you start the analog input operation using the ioct.\n"
"-m|--margin  : margin of safety before the time of sunset and after the time of "
"               sunrise in seconds (hours*3600), defaults " xstr(SAFETY_MARGIN) " s."
"-n|--night   : night cycling (on after sun down and off after sun up). Sun up and \n"
"               down times calculated. Defaults to disabled state (recording 24 \n"
"               hours a day).\n" 
"-p|--phi     : latitude (decimal coordinate) of recording site; defaults 47.655083.\n"
"               Northern hemisphere coordinates are positive, and southern negative.\n"
"-l|--lambda  : longitude (decimal coordinate) of recording site defaults -122.293194.\n"
"               Eastern hemisphere coordinates are positive, and western negative.\n"
"\n"
};
    
/* 
 * ==== Global Variables & Structures ====
 */
    
extern struct aio_struct *inAIO;

extern float sampleRate; // SAMPLE_RATE
extern int autoTrigger; // AUTO_TRIG
extern int fileSeconds; // FILE_TIME_S
extern int fileSamples; // SAMPLES_PER_FILE
extern int chanSamples; // SAMPLES_PER_CHAN
extern int fileBuffers; // BUFFERS_PER_FILE
extern int bufferSamples; // SAMPLES_PER_BUFFER
extern int numChannels; // NUM_CHANNELS
extern int durationDays; // DURATION_DAYS
extern int nightCycle; // NIGHT_CYCLE
extern double lat; // DEFAULT_LATITUDE
extern double lon; // DEFAULT_LONGITUDE
extern long safetyMargin; // SAFETY_MARGIN

extern dt78xx_clk_config_t clk;
extern chan_mask_t chanMask;
extern int ain[8];
extern char filePath[LEN];
const char *ID;

extern int inStream;
extern int aInput;
extern int outStream;

extern long sunset;
extern long sunrise;
extern long present;

extern int fileBuffer;
extern int fileNum;
extern void **inBuffer;

/*
 * ==== Helper functions for recorder (DT7816) ====
 * Static functions are intended to be private.
 */

/*
 * Input stream empty signal handler
 */
void isInStreamEmpty();

/*
 * AIO buffer done callback. An AIO buffer streams like this:
 * 
 * 0--------------------------------------------------------------------------------------> time
 *  |________16-bit_2's_complement_raw_A/D_________||_32-bit_unsigned_||_16-bit_unsigned_|
 *  [AIN0][AIN1][AIN2][AIN3][AIN4][AIN5][AIN6][AIN7][TACH][COUNT]......[DIN].............. ...
 *  
 * @param buff  pointer to buffer with samples from enabled channels
 * @param len   length of buffer; this is an integral multiple of equal number
 *              of samples from all enabled channels
 * @return      The return value determines whether this buffer will be 
 *              resubmitted for continued AIO operations 
 *              0 = do not requeue, 1= requeue 
 */
int isInAIODone(void *buff, int len);

///*
// * Updates debug LEDs (8 in total), LED ON (1) := CHANNEL is READING/WRITING. 
// * Viewing the DT7816 such that the debug pin row is above the user LEDs:
// *  ______ ______ ______ ______ ______ ______ ______ ______ ______ _______\n
// * | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN6 | PIN7 | PIN8 | PIN9 | PIN10 |\n
// * ***** LED7 ** LED6 ** LED5 ** LED4 ** LED3 ** LED2 ** LED1 ** LED0 *****\n
// * 
// * LED0 := AIN0, LED1 := AIN1, LED2 := AIN2, LED3 := AIN3,
// * LED4 := AIN4, LED5 := AIN5, LED6 := AIN6, LED7 := AIN7
// * 
// * where the analog input channels have the following coding returned by
// * IOCTL_CHAN_MASK_GET:
// * 
// * AIN0 = 0x01, AIN1 = 0x02, AIN2 = 0x04, AIN3 = 0x08
// * AIN4 = 0x10, AIN5 = 0x20, AIN6 = 0x40, AIN7 = 0x80
// * 
// * and for input header pins (J16):
// *  ___________________________________________________\n
// * ||  2 |  4 |  6 |  8 | 10 | 12 | 14 | 16 | 18 | 20 ||\n
// * ||  1 |  3 |  5 |  7 |  9 | 11 | 13 | 15 | 17 | 19 ||\n
// * 
// * Analog Inputs (AINs):
// * 
// * PIN5 := AIN0, PIN7 := AIN1, PIN9 := AIN2, PIN11 := AIN3 
// * PIN13 := AIN4, PIN15 := AIN5, PIN17 := AIN6, PIN19 := AIN7
// * 
// * Analog Grounds (AGRDs):
// * 
// * PIN6 := AGRD0, PIN8 := AGRD1, PIN10 := AGRD2, PIN12 := AGRD3
// * PIN14 := AGRD4, PIN16 := AGRD5, PIN18 := AGRD6, PIN20 := AGRD7
// * 
// * @param status        Whether each channel is active
// * @param streaming     1 if presently streaming
// */        
//
//void ledIndicators(uint8_t status, int streaming) {   
//    dt78xx_led_t led;
//    led.mask = 0xff; // All bits are enabled (8 LEDs capable of being lit)
//    led.state = (status & 0xff);
//    ioctl(streaming, IOCTL_LED_SET, &led);    
//}

/*
 * Retrieves present time as Unix Epoch and UTC; readily formatted in ISO 8601.
 * UTC = Universal Coordinated Time (aka GMT = Greenwich Mean Time): Zulu
 * 
 * @param presentUTC   Present UTC time
 * @param clockTime    Present Unix Epoch time
 */
static void getTime(struct tm **presentUTC, struct timeval *clockTime);

/*
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
static long getTimeEpoch(long year, int month, int day, int hour, int minute, int second);

/*
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
 * The full file path has the form of (T and Z are not placeholders):
 * 
 * <path>/<prefix>_<YYYYMMDD>T<HHmmssuuuuuu>Z.aiff
 * 
 * or
 * 
 * <path>/<prefix>_<YYYYMMDD>T<HHmmssuuuuuu>Z.csv
 * 
 */
static void timestamp();

/*
 * Returns the present time in Unix Epoch (UTC) seconds since 1 Jan 1970
 * 
 * @return Present time (s)
 */
long getPresentTime();

/*
 * Creates channel mask for each active channel determined by AIN. The mask is
 * a 32-bit number where bits 0 to 7 of the channel mask correspond to 
 * analog input channels 0 to 7, bit 8 with the tachometer, bit 10 with the 
 * measure counter, and bit 11 with the digital input port. Bits 16 to 19 
 * correspond to analog outputs 0 to 3, and bits 24 to 31 with digital 
 * outputs 0 to 7. That is, the mask is in bit-wise format, or in hex:
 * 
 * 0x00000001 := AIN0, 0x00000002 := AIN1, 0x00000004 := AIN2, 
 * 0x00000008 := AIN3, 0x00000010 := AIN4, 0x00000020 := AIN5,
 * 0x00000040 := AIN6, 0x00000080 := AIN7, 0x00000100 := TACH,
 * 0x00000200 := ~RESERVED~, 0x00000400 := MEASURE COUNTER,
 * 0x00000800 := DIN, 0x00001000 := ~RESERVED~, 0x00002000 := ~RESERVED~,
 * 0x00004000 := ~RESERVED~, 0x00008000 := ~RESERVED~, 0x00010000 := AOUT0, 
 * 0x00020000 := AOUT1, 0x00040000 := AOUT2, 0x00080000 := AOUT3,
 * 0x00100000 := ~UNUSED~, 0x00200000 := ~UNUSED~, 0x00400000 := ~UNUSED~,
 * 0x00800000 := ~UNUSED~, 0x01000000 := DOUT0, 0x02000000 := DOUT1, 
 * 0x04000000 := DOUT2, 0x08000000 := DOUT3, 0x10000000 := DOUT4,
 * 0x20000000 := DOUT5, 0x40000000 := DOUT6, 0x80000000 := DOUT7
 * 
 * @param ain       Array of channel states (1 = on, 0 = off) for analog input
 *                  channels 1, 2, 3, 4, 5, 6, 7
 * @param chOn      Array of the active/enabled/on channels given by their index
 */
static void createChanMask(int ain[], int *chOn);

/*
 * Configures all channels even if not enabled and used. Configuration in
 * comprised of its number, gain, DC or AC coupling, current source, and 
 * differential.
 * 
 * @param ainConfig   Array of the configurations for all eight channels
 */
static void configChan(dt78xx_ain_config_t ainConfig[]);

/*
 * Initialises the software trigger for all enabled channels individually.
 * 
 * @param ainTrigConfig   Array of trigger configurations for all channels
 */
static void initTrig(dt78xx_trig_config_t ainTrigConfig[]);

/*
 * Configures the passed channel individually (of the ones enabled).
 * 
 * @param trigConfig    Trigger configuration
 * @return              1 if successful, 0 if failure
 */
static int configTrig(dt78xx_trig_config_t trigConfig);

/*
 * Setups AIO: trigger, channels, buffer queue, etc.
 * 
 * @param argc  file ID provided in command line
 * @return  1 for success, 0 for failure
 */
int setupAIO(int argc);

/*
 * Calculates the sunset and sunrise time (offset by a safety margin) according
 * to a location on Earth given by longitude and latitude coordinates. 
 * 
 * Note:
 *      year,month,date is the calendar date, 1801-2099 only.
 *      Eastern longitude positive, Western longitude negative
 *      Northern latitude positive, Southern latitude negative
 * 
 * @param sunsets       Array of sunset times in Unix Epoch time
 * @param sunrises      Array of sunrise times in Unix Epoch time
 */
void calcSunUpDown(long *sunsets, long *sunrises);

/*
 * Checks for missing AIFF file identifier.
 * 
 * @param argc  file ID provided in command line
 */
static void checkID(int argc);

/*
 * Opens input stream.
 */
static void openStream();

/*
 * Opens analog input.
 * 
 * The order of the data in the input (AIN) buffer is as follows,
 * assuming that all channels are enabled in the input stream:
 * Analog input channels 0 through 7. Each analog input sample is a
 * 16-bit, two’s complement value.
 * 
 * Simultaneously analog input (channel) samples put 
 * in line and sequentially for AIFF recording like so:
 *  ___________ ___________ ___________ ___________
 * |           |           |           |           |
 * | Channel 1 | Channel 2 | Channel 1 | Channel 2 | ...
 * |___________|___________|___________|___________|
 *  <---------> <---------> <---------> <--------->  ...
 *    Segment     Segment     Segment     Segment
 *  <---------------------> <--------------------->  ...
 *      Sample frame 1          Sample frame 2  
 * 
 */
static void openAIN();

/*
 * Allocates buffers and submits AIO request.
 * 
 * @return  1 if successful, 0 if failure
 */
static int submitAIO();

/*
 * Arms input stream and then issues a software start for continuous input
 * operation; this is redundant if trigger source is threshold or externally 
 * triggered.
 * 
 * @return  1 if stream armed and started successfully, 0 if failed
 */
int armStartStream();

/*
 * Stops input stream.
 * 
 * @return  1 for success, 0 for failure
 */
int stopStream();

#if AIFF
/*
 * Sets AIFF file metadata and file formatting.
 * 
 * @param file  AIFF file pointer
 * @return      success of file format setting (1 for success, 0 for failure)
 */
static int setFile(SNDFILE *file);

/*  
 * Creates new file for acquired data at the specified .aiff path.
 * 
 * @return  SNDFILE file if successful, NULL is failure
 * 
 */
static SNDFILE* createAIFF();

/*
 * Writes buffer to AIFF file.
 * 
 * @param raw    input buffer
 * @param file   SNDFILE file reference pointer
 * @param len    number of samples to be written
 */
static void writeAIFF(void *raw, SNDFILE *file, int len);

/*
 * Cleans up file writing processes.
 * 
 * @param file  AIFF file reference pointer
 * @return      1 for success, 0 for failure
 */
static int finishAIFF(SNDFILE *file);

#else
/*  
 * Creates new file for acquired data at the specified .csv path.
 * 
 * @return  FILE if successful, NULL is failure
 * 
 */
static FILE *createCSV();

/*
 * Writes buffer to CSV file.
 * 
 * @param raw   input buffer
 * @param file  FILE file structure
 * @param len    number of samples to be written
 */
static void writeCSV(void *raw, FILE *file, int len);

/*
 * Cleans up file writing processes.
 * 
 * @param file  CSV file reference
 * @return      1 for success, 0 for failure
 */  
static int finishCSV(FILE *file);
#endif

/*
 * Closes currently opened file, if open, for graceful exit.
 */
void closeFile();

/*
 * Writes buffer to file (CSV or AIFF)
 * @param *buff pointer to buffer of length len
 * @param len   length of buffer to be written &buff
 */
void writeFile(void *buff, int len);

/*
 * Updates debug LEDs (8 in total), LED ON (1) := CHANNEL is READING/WRITING. 
 * Viewing the DT7816 such that the debug pin row is above the user LEDs:
 *  ______ ______ ______ ______ ______ ______ ______ ______ ______ _______\n
 * | PIN1 | PIN2 | PIN3 | PIN4 | PIN5 | PIN6 | PIN7 | PIN8 | PIN9 | PIN10 |\n
 * ***** LED7 ** LED6 ** LED5 ** LED4 ** LED3 ** LED2 ** LED1 ** LED0 *****\n
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
 *  ___________________________________________________\n
 * ||  2 |  4 |  6 |  8 | 10 | 12 | 14 | 16 | 18 | 20 ||\n
 * ||  1 |  3 |  5 |  7 |  9 | 11 | 13 | 15 | 17 | 19 ||\n
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
 * All 7 flash on and then shut off if a buffer overrun occurs.
 * 
 * @param status        Whether each channel is active
 */        
void ledIndicators(uint8_t status);

#ifdef __cplusplus
}
#endif

#endif /* RECORDER_HELPERS_H */

