/* 
 * @file recorder_helpers.c
 * @brief This is the header for the custom application for DT7816 autonomous 
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

/*
 * ==== External Libraries ====
 */
#include "recorder_helpers.h"

/*
 * ==== Global variables & constants ====
 * 
 */

static int overrunStop = 1;  // Stop on buffer overrun
static int requeue = 1;      // Requeue buffers after processing      
static int overruns = 0;       // Number of times buffer overran while acquiring
static int buffersDone = 0;    // Number of buffers done

 /*
 * ==== Helper functions for recorder (DT7816) ====
 */

void isInStreamEmpty() {
    ++overruns;
#if (defined OVERRUN_LED) && (OVERRUN_LED > -1) && (OVERRUN_LED < 8)
    dt78xx_led_t led;
    led.mask = (1<<OVERRUN_LED);    
    led.state = (1<<OVERRUN_LED);
    ioctl(inStream, IOCTL_LED_SET, &led);
#endif    
    if (overrunStop && (buffersDone==2)) //Stop on queue empty
    {
        if (ioctl(inStream, IOCTL_STOP_SUBSYS, 0))
           perror("IOCTL_STOP_SUBSYS");
        aio_stop(inAIO);
    }
}

int isInAIODone(void *buff, int len) {
    ++buffersDone;
    
    //If operation was stopped on queue empty, clean up after all buffers have
    //been dequeued and processed
    if (overrunStop && overruns && (buffersDone==2)) 
    {
        if (ioctl(inStream, IOCTL_STOP_SUBSYS, 0))
           perror("IOCTL_STOP_SUBSYS");
        aio_stop(inAIO);
    }
    
    // Buffer processing here
#if (defined BUFF_DONE_LED) && (BUFF_DONE_LED > -1) && (BUFF_DONE_LED < 8)
    dt78xx_led_t led;
    led.mask = (1<<BUFF_DONE_LED);    
    led.state = (1<<BUFF_DONE_LED);
    ioctl(inStream, IOCTL_LED_SET, &led);
#endif    
    
    //Process completed buffers here  
        
#if (defined BUFF_DONE_LED) && (BUFF_DONE_LED > -1) && (BUFF_DONE_LED < 8)
    led.state = 0;
    ioctl(inStream, IOCTL_LED_SET, &led);
#endif  
    return requeue;
}

void ledIndicators(uint8_t status, int streaming) {   
    dt78xx_led_t led;
    led.mask = 0xff; /* All bits are enabled (8 LEDs capable of being lit) */
    led.state = (status & 0xff);
    ioctl(streaming, IOCTL_LED_SET, &led);    
}

#if (defined STATUS_LED) 
void updateStatusLed(int fd, int reset) {
    static uint32_t count = 0; //msb has status led on/off state
    dt78xx_led_t led;
    led.mask = (1<<STATUS_LED);  
    if (reset)
    {
        count = 0;
        led.state = 0;
        ioctl(fd, IOCTL_LED_SET, &led);
        return;
    }
    
    ++count;
    if ((count & INT32_MAX) < g_led_count)
        return;
    
    if (count & ~INT32_MAX)
    {
        led.state = 0;
        count = 0;
    }
    else
    {
        led.state = 0xff;
        count = ~INT32_MAX;
    }
    ioctl(fd, IOCTL_LED_SET, &led);
}
#endif

void getTime(struct tm **presentUTC, struct timeval *clockTime) {
    gettimeofday(clockTime, NULL);
    *presentUTC = gmtime(&(*clockTime).tv_sec);
}

long getTimeEpoch(long year, int month, int day, int hour, int minute, int second) {
    struct tm *time = malloc(sizeof(struct tm));
    time->tm_year = year - 1900;
    time->tm_mon = month - 1;
    time->tm_mday = day;
    time->tm_hour = hour;
    time->tm_min = minute;
    time->tm_sec = second;
    return (long) timegm(&(*time));
}

void timestamp(char *filePath, char **argv, char *storagePath) {
    struct timeval timeEpoch;
    struct tm *timeISO;
    getTime(&timeISO, &timeEpoch);
    const char *outputPath = storagePath;
    const char *ID;
    ID = argv[optind];
    char fileTime[LEN];

    sprintf(fileTime, "_%04d%02d%02dT%02d%02d%02d%liZ.aiff", 
            timeISO->tm_year+1900, timeISO->tm_mon + 1, timeISO->tm_mday, 
            timeISO->tm_hour, timeISO->tm_min, timeISO->tm_sec, (long) timeEpoch.tv_usec); 
    char fileName[LEN];
    strcpy(fileName, ID);
    strcat(fileName, fileTime);
    strcpy(filePath, outputPath);
    strcat(filePath, fileName);
}

long getPresentTime() {
    struct tm* timeISO;
    struct timeval timeEpoch;
    getTime(&timeISO, &timeEpoch);
    return (long) timeEpoch.tv_sec;
}

void checkFatal() {
    int grossSamples = fileSamples * 2;
    if(grossSamples > 65536) {
        fprintf(stderr, "Fatal Error: exceeded 16-bits!\n");
        fprintf(stderr, "SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS = %d > 65536\n", 
                grossSamples);
        return (EXIT_FAILURE);
    }
}

void createChanMask(int ain[], int *chOn) {
    int chIndex = 0;
    if (ain[0]) {
        chanMask |= chan_mask_ain0;
        chOn[chIndex++] = 0;
    }
    if (ain[1]) {
        chanMask |= chan_mask_ain1;
        chOn[chIndex++] = 1;    
    }
    if (ain[2]) {
        chanMask |= chan_mask_ain2;
        chOn[chIndex++] = 2;
    }
    if (ain[3]) {
        chanMask |= chan_mask_ain3;
        chOn[chIndex++] = 3;
    }
    if (ain[4]) {
        chanMask |= chan_mask_ain4;
        chOn[chIndex++] = 4;
    }
    if (ain[5]) {
        chanMask |= chan_mask_ain5;
        chOn[chIndex++] = 5;
    }
    if (ain[6]) {
        chanMask |= chan_mask_ain6;
        chOn[chIndex++] = 6;
    }
    if (ain[7]) {
        chanMask |= chan_mask_ain7;
        chOn[chIndex++] = 7;
    }
}

void configChan(dt78xx_ain_config_t ainConfig[]) {
    dt78xx_ain_config_t ain0Config = {.ain=0, /* AIN0 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[0] = ain0Config;
    dt78xx_ain_config_t ain1Config = {.ain=1, /* AIN1 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[1] = ain1Config;
    dt78xx_ain_config_t ain2Config = {.ain=2, /* AIN2 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[2] = ain2Config;
    dt78xx_ain_config_t ain3Config = {.ain=3, /* AIN3 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[3] = ain3Config;
    dt78xx_ain_config_t ain4Config = {.ain=4, /* AIN4 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[4] = ain4Config;
    dt78xx_ain_config_t ain5Config = {.ain=5, /* AIN5 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[5] = ain5Config;
    dt78xx_ain_config_t ain6Config = {.ain=6, /* AIN6 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[6] = ain6Config;
    dt78xx_ain_config_t ain7Config = {.ain=7, /* AIN7 */
                                      .gain=1, /* Default gain */
                                      .ac_coupling=0, /* DC coupling */
                                      .current_on=0, /* Current source off */
                                      .differential=0
                                     }; 
    ainConfig[7] = ain7Config;
}

void initTrig(dt78xx_trig_config_t ainTrigConfig[]) {
    dt78xx_trig_config_t trig0Config;
    ainTrigConfig[0] = trig0Config;
    dt78xx_trig_config_t trig1Config;
    ainTrigConfig[1] = trig1Config;
    dt78xx_trig_config_t trig2Config;
    ainTrigConfig[2] = trig2Config;
    dt78xx_trig_config_t trig3Config;
    ainTrigConfig[3] = trig3Config;
    dt78xx_trig_config_t trig4Config;
    ainTrigConfig[4] = trig4Config;
    dt78xx_trig_config_t trig5Config;
    ainTrigConfig[5] = trig5Config;
    dt78xx_trig_config_t trig6Config;
    ainTrigConfig[6] = trig6Config;
    dt78xx_trig_config_t trig7Config;
    ainTrigConfig[7] = trig7Config;
}

int configTrig(dt78xx_trig_config_t trigConfig) {
    if (autoTrigger) /* default trigger == auto or software trigger */
        trigConfig.src = trig_src_sw;
    else { /* threshold trigger */
        trigConfig.src = trig_src_threshold;
        trigConfig.src_cfg.threshold.edge_rising = 1;
        trigConfig.src_cfg.threshold.level = volts2raw(TRIG_LEVEL_V,DEFAULT_GAIN);
    }
    return ioctl(inStream, IOCTL_START_TRIG_CFG_SET, &trigConfig);
}

void calcSunUpDown(long *sunsets, long *sunrises) {
    struct timeval epochPresent;  /* Seconds UTC relative to 1 Jan 1970 (epoch) */
    struct tm *presentTime = malloc(sizeof(struct tm)); /* Time in accordance to ISO 8601 */
    gettimeofday(&epochPresent, NULL); /* Gets current system time */
    presentTime = gmtime(&epochPresent.tv_sec); /* Gets current time in UTC (aka GMT or Zulu) */

    int elapsedDays;
    double rise, set;
    for (elapsedDays = 0; elapsedDays < durationDays; elapsedDays++) {
        int year = 1900 + (int) presentTime->tm_year;
        int month = 1 + presentTime->tm_mon;
        int day = presentTime->tm_mday;
                
        long epochDay = getTimeEpoch(year, month, day, 0, 0, 0);
        long epochSet = epochDay;
        if (nightCycle) {
            sun_rise_set(year, month, day, lon, lat, &rise, &set);
            epochSet += set*3600;
            sunsets[elapsedDays] = epochSet - safetyMargin;
        } else {
            sunsets[elapsedDays] = epochSet;
        }

        time_t daySec = 86400; /* Length of 1 day in seconds */
        epochDay += daySec;
        presentTime = gmtime(&epochDay);
        year = 1900 + (int) presentTime->tm_year;
        month = 1 + presentTime->tm_mon;
        day = presentTime->tm_mday;

        long epochRise = getTimeEpoch(year, month, day, 0, 0, 0);
        if (nightCycle) {
            sun_rise_set(year, month, day, lon, lat, &rise, &set);
            epochRise += rise*3600;
            sunrises[elapsedDays] = epochRise + safetyMargin;
        } else {
            sunrises[elapsedDays] = epochRise;
        }
    }
}

void checkID(int argc, char** argv) {
    if (optind >= argc) {
        printf(usage, argv[0]);
        return (EXIT_FAILURE);
    }
}

void checkRate(struct circular_queue buffer, char** argv) { 
    if (buffer.sample_rate <= 0.0f) {
        printf(usage, argv[0]);
        return (EXIT_FAILURE);
    }
}    

void openStream() {
    fprintf(stdout, "Opening stream...\n");
    inStream = open(DEV_STREAM_IN, O_RDONLY);
    if (inStream < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    }    
}
void openAIN() {
    fprintf(stdout, "Opening analog input...\n");
    aInput = open(DEV_AIN, O_RDONLY);
    if (aInput < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(inStream);
        return (EXIT_FAILURE);
    }
}

void setMetadata(AIFF_Ref file, long sunset, long sunrise) {
    char metadata[LEN];
    sprintf(metadata, "%f", lon);
    AIFF_SetAttribute(file, AIFF_NAME, metadata);
    sprintf(metadata, "%f", lat);
    AIFF_SetAttribute(file, AIFF_AUTH, metadata);
    sprintf(metadata, "%ld", sunset);
    AIFF_SetAttribute(file, AIFF_ANNO, metadata);
    sprintf(metadata, "%ld", sunrise);
    AIFF_SetAttribute(file, AIFF_COPY, metadata);
}

struct circular_queue getFileQueue(dt78xx_ain_config_t ainConfig[8], dt78xx_clk_config_t clk, int size) {
        struct circular_queue fileQueue;
        fileQueue.buffer = RingBuf_new(sizeof(float), size);
        fileQueue.chanConfig = ainConfig;
        fileQueue.num_samples = size;
        fileQueue.sample_rate = clk.clk_freq;
        return fileQueue;
}

void writeFileQueue(void *raw, struct circular_queue writeQueue) {
    int sample;
    float volts;
    void *vptr;
    for (sample = 0; sample < chanSamples; ++sample) {
        if (chanMask & chan_mask_ain0) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[0].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t);
        }
        if (chanMask & chan_mask_ain1) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[1].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t);  
        }
        if (chanMask & chan_mask_ain2) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[2].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t); 
        }
        if (chanMask & chan_mask_ain3) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[3].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t);
        }
        if (chanMask & chan_mask_ain4) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[4].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t); 
        }
        if (chanMask & chan_mask_ain5) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[5].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t); 
        }
        if (chanMask & chan_mask_ain6) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[6].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t);  
        }                    
        if (chanMask & chan_mask_ain7) {
            volts = raw2volts(*(int16_t *)raw, writeQueue.chanConfig[7].gain);
            vptr = &volts;
            writeQueue.buffer->add(writeQueue.buffer, &vptr);
            raw += sizeof(int16_t);
        }                    
    }
}
    
