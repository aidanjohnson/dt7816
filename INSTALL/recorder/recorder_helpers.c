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
 * ==== Helper functions for recorder (DT7816) ====
 */

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

int checkFatal(int fileSamples, int numBuffers) {
    int grossSamples = fileSamples * numBuffers;
    if(grossSamples > 65536) {
        fprintf(stderr, "Fatal Error: exceeded 16-bits!\n");
        fprintf(stderr, "SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS = %d > 65536\n", 
                grossSamples);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}

void createChanMask(int ain[], int *chOn, chan_mask_t *chMask) {
    int chIndex = 0;
    if (ain[0]) {
        *chMask |= chan_mask_ain0;
        chOn[chIndex++] = 0;
    }
    if (ain[1]) {
        *chMask |= chan_mask_ain1;
        chOn[chIndex++] = 1;    
    }
    if (ain[2]) {
        *chMask |= chan_mask_ain2;
        chOn[chIndex++] = 2;
    }
    if (ain[3]) {
        *chMask |= chan_mask_ain3;
        chOn[chIndex++] = 3;
    }
    if (ain[4]) {
        *chMask |= chan_mask_ain4;
        chOn[chIndex++] = 4;
    }
    if (ain[5]) {
        *chMask |= chan_mask_ain5;
        chOn[chIndex++] = 5;
    }
    if (ain[6]) {
        *chMask |= chan_mask_ain6;
        chOn[chIndex++] = 6;
    }
    if (ain[7]) {
        *chMask |= chan_mask_ain7;
        chOn[chIndex++] = 7;
    }
}

void configChan(dt78xx_ain_config_t ainConfig[]) {
    dt78xx_ain_config_t ain0Config ={.ain=0, /* AIN0 */
                                  .gain=1, /* Default gain */
                                  .ac_coupling=0, /* DC coupling */
                                  .current_on=0, /* Current source off */
                                  .differential=0
                                  }; 
    ainConfig[0] = ain0Config;
    dt78xx_ain_config_t ain1Config ={.ain=1, /* AIN1 */
                                   .gain=1, /* Default gain */
                                   .ac_coupling=0, /* DC coupling */
                                   .current_on=0, /* Current source off */
                                   .differential=0
                                  }; 
    ainConfig[1] = ain1Config;
    dt78xx_ain_config_t ain2Config ={.ain=2, /* AIN2 */
                                   .gain=1, /* Default gain */
                                   .ac_coupling=0, /* DC coupling */
                                   .current_on=0, /* Current source off */
                                   .differential=0
                                  }; 
    ainConfig[2] = ain2Config;
    dt78xx_ain_config_t ain3Config ={.ain=3, /* AIN3 */
                                   .gain=1, /* Default gain */
                                   .ac_coupling=0, /* DC coupling */
                                   .current_on=0, /* Current source off */
                                   .differential=0
                                  }; 
    ainConfig[3] = ain3Config;
    dt78xx_ain_config_t ain4Config ={.ain=4, /* AIN4 */
                                   .gain=1, /* Default gain */
                                   .ac_coupling=0, /* DC coupling */
                                   .current_on=0, /* Current source off */
                                   .differential=0
                                  }; 
    ainConfig[4] = ain4Config;
    dt78xx_ain_config_t ain5Config ={.ain=5, /* AIN5 */
                                   .gain=1, /* Default gain */
                                   .ac_coupling=0, /* DC coupling */
                                   .current_on=0, /* Current source off */
                                   .differential=0
                                  }; 
    ainConfig[5] = ain5Config;
    dt78xx_ain_config_t ain6Config ={.ain=6, /* AIN6 */
                                   .gain=1, /* Default gain */
                                   .ac_coupling=0, /* DC coupling */
                                   .current_on=0, /* Current source off */
                                   .differential=0
                                  }; 
    ainConfig[6] = ain6Config;
    dt78xx_ain_config_t ain7Config ={.ain=7, /* AIN7 */
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

int configTrig(int* inStream, dt78xx_trig_config_t trigConfig, int autoTrig) {
    if (autoTrig) /* default trigger == auto or software trigger */
        trigConfig.src = trig_src_sw;
    else { /* threshold trigger */
        trigConfig.src = trig_src_threshold;
        trigConfig.src_cfg.threshold.edge_rising = 1;
        trigConfig.src_cfg.threshold.level = volts2raw(TRIG_LEVEL_V,DEFAULT_GAIN);
    }
    return ioctl(*inStream, IOCTL_START_TRIG_CFG_SET, &trigConfig);
}

void calcSunUpDown(long *sunsets, long *sunrises, int durationDays, 
                   long safetyMargin, double lon, double lat, int nightCycle) {
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

int writeBuffer(AIFF_Ref file, struct circ_buffer ringBuffer, 
                int fileChannels, int numBuffers, int* chOn, 
                void** bufferArray, dt78xx_ain_config_t* ainConfig) {

    int success = 0;
    int rwBuffer;
    for (rwBuffer=0; rwBuffer < numBuffers; ++rwBuffer) { 
        fprintf(stdout, "Reading buffer and writing file...\n");

        int16_t *raw = bufferArray[rwBuffer];

        int queue, ch;
        /* Circular buffer write and read pointers lead and follow */
        for (queue = 0; queue < ringBuffer.num_samples + 1; queue++) {  
            for (ch = 0; ch < fileChannels; ch++, ++raw) {
                /* Decouples input from output with circular buffer */
                int chIndex = chOn[ch];
                /* Write pointer leads read pointer by fileChannels */
                if (queue < ringBuffer.num_samples) { 
                    float sampleVolt = raw2volts(*raw, ainConfig[chIndex].gain);
                    float* writePointer = &sampleVolt; //write pointer for input
                    ringBuffer.vbuf->add(ringBuffer.vbuf, writePointer);
                }
                /* Read pointer lags write pointer by fileChannels */
                if (queue > 0) {
                    float* readPointer = NULL; /* Read pointer for writing to file */
                    ringBuffer.vbuf->pull(ringBuffer.vbuf, &readPointer);
                    success = AIFF_WriteSamples32Bit(file, (int32_t*) &readPointer, 1);
                    if (!success) break;
                }
            }
        }
    }
    return success;
}

int checkID(int argc, char** argv) {
    if (optind >= argc) {
        printf(usage, argv[0]);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}
int checkRate(struct circ_buffer ringBuffer, char** argv) { 
    if (ringBuffer.sample_rate <= 0.0f) {
        printf(usage, argv[0]);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}    

int openStream(int* inStream) {
    fprintf(stdout, "Opening stream...\n");
    *inStream = open(DEV_STREAM_IN, O_RDONLY);
    if (*inStream < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }    
}
int openAIN(int* inStream, int* chIndex) {
    fprintf(stdout, "Opening analog input...\n");
    *chIndex = open(DEV_AIN, O_RDONLY);
    if (*chIndex < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(*inStream);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}

void free_iocb_buffers(struct iocb **iocbs, int num) {
    if (!iocbs)
        return;
    while (--num >= 0)
    {
        if (iocbs[num])
        {
            if (iocbs[num]->aio_buf)
                free ((void *)(uint32_t)iocbs[num]->aio_buf);
            free (iocbs[num]);
        }
    }
    free (iocbs);
}

struct iocb **alloc_iocb_buffers(int fd, int write, int numbuf, int buflen) {
    struct iocb **iocbs; //array of iocb pointers
    int i;
    int alignment = 32; //REQUIRED  
    
    //allocate array of pointers to iocb's
    iocbs = (struct iocb **)malloc(sizeof(struct iocb *) * numbuf);
    if (!iocbs)
    {
       fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
       return NULL;
    }
    memset(iocbs, 0, (sizeof(struct iocb *) * numbuf));
    
    //allocate iocb for each buffer
    for (i=0; i < numbuf; ++i)
    {
        struct iocb *cb = (struct iocb *)malloc(sizeof(struct iocb));
        if (!cb)
        {
            fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
            break;
        }
        memset(cb, 0, sizeof(struct iocb));
        iocbs[i] = cb;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
        cb->aio_buf = (__u64)memalign(alignment, buflen);
#pragma GCC diagnostic pop        
        if (!cb->aio_buf)
        {
            fprintf(stderr, "[%s(%d)] ERROR malloc\n", __func__, __LINE__);
            break;
        }
        cb->aio_fildes = fd;
        cb->aio_lio_opcode = write?IOCB_CMD_PWRITE:IOCB_CMD_PREAD;
        cb->aio_nbytes = buflen;
        cb->aio_data = write;
    }
    
    if (i == numbuf) //no errors
        return iocbs;
    
    //malloc failed
    free_iocb_buffers(iocbs, numbuf);

    return NULL;
}

void setMetadata(AIFF_Ref file, double lon, double lat, long sunset, long sunrise) {
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