/* 
 * @file recorder_helpers.c
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

/*
 * ==== External Libraries ====
 */

#include "recorder_helpers.h"

/*
 * ==== Global variables & constants ====
 * 
 */

static int overruns = 0;        // Number of times buffer overran while acquiring
static int buffersDone = 0;     // Number of buffers done; internal counter
char filePath[LEN];             // String for output file path

/* Current file handle open */
#if AIFF
SNDFILE *file;
SF_INFO fileInfo;
#else
FILE *file;
#endif

/*
 * ==== Helper functions for recorder (DT7816) ====
 */

void isInStreamEmpty() {
    ++overruns; 
    static int overrunStop = 0; // Disabled (0) stop on buffer overrun
    if (overrunStop && (buffersDone==BUFFERS_PER_QUEUE)) { // Stop on queue empty
#if LED_ENABLED
        ledIndicators(0xff);
#endif   
        if (ioctl(inStream, IOCTL_STOP_SUBSYS, 0)) {
           perror("IOCTL_STOP_SUBSYS");
        }
        aio_stop(inAIO); // Clean up after all buffers have been dequeued 
    }
}

int isInAIODone(void *buff, int len) {
    ++buffersDone;
    static int requeue = 1; // Enabled (1) requeue of buffers after writing
    writeFile(buff, len);
    return requeue; // 1 if buffers are to be requeued, 0 if otherwise
}

static void getTime(struct tm **presentUTC, struct timeval *clockTime) {
    gettimeofday(clockTime, NULL);
    *presentUTC = gmtime(&(*clockTime).tv_sec);
}

static long getTimeEpoch(long year, int month, int day, int hour, int minute, int second) {
    struct tm *time = malloc(sizeof(struct tm));
    time->tm_year = year - 1900;
    time->tm_mon = month - 1;
    time->tm_mday = day;
    time->tm_hour = hour;
    time->tm_min = minute;
    time->tm_sec = second;
    return (long) timegm(&(*time));
}

static void timestamp() {
    struct timeval timeEpoch;
    struct tm *timeISO;
    getTime(&timeISO, &timeEpoch);
    present = timeEpoch.tv_sec; // Updates time for while loop check
    const char *outputPath = PATH_TO_STORAGE; // A set path to local storage 
    char fileTime[LEN];

#if AIFF    
    sprintf(fileTime, "_%04d%02d%02dT%02d%02d%02d%liZ.aiff", timeISO->tm_year+1900, 
            timeISO->tm_mon + 1, timeISO->tm_mday, timeISO->tm_hour, 
            timeISO->tm_min, timeISO->tm_sec, (long) timeEpoch.tv_usec);
#else
    sprintf(fileTime, "_%04d%02d%02dT%02d%02d%02d%liZ.csv", timeISO->tm_year+1900, 
            timeISO->tm_mon + 1, timeISO->tm_mday, timeISO->tm_hour, 
            timeISO->tm_min, timeISO->tm_sec, (long) timeEpoch.tv_usec); 
#endif
    
    char fileName[LEN];
    strcpy(fileName, ID);
    strcat(fileName, fileTime);
    strcpy(filePath, outputPath);
    strcat(filePath, fileName); // Concatenated resultant string of full file path
}

long getPresentTime() {
    struct tm* timeISO;
    struct timeval timeEpoch;
    getTime(&timeISO, &timeEpoch);
    return (long) timeEpoch.tv_sec;
}

static void createChanMask(int ain[], int *chOn) {
    int chIndex = 0;
    if (ain[0]) { // AIN0
        chanMask |= chan_mask_ain0;
        chOn[chIndex++] = 0;
    }
    if (ain[1]) { // AIN1
        chanMask |= chan_mask_ain1;
        chOn[chIndex++] = 1;    
    }
    if (ain[2]) { // AIN2
        chanMask |= chan_mask_ain2;
        chOn[chIndex++] = 2;
    }
    if (ain[3]) { // AIN3
        chanMask |= chan_mask_ain3;
        chOn[chIndex++] = 3;
    }
    if (ain[4]) { // AIN4
        chanMask |= chan_mask_ain4;
        chOn[chIndex++] = 4;
    }
    if (ain[5]) { // AIN5
        chanMask |= chan_mask_ain5;
        chOn[chIndex++] = 5;
    }
    if (ain[6]) { // AIN6
        chanMask |= chan_mask_ain6;
        chOn[chIndex++] = 6;
    }
    if (ain[7]) { // AIN7
        chanMask |= chan_mask_ain7;
        chOn[chIndex++] = 7;
    }
}

static void configChan(dt78xx_ain_config_t ainConfig[]) {
    dt78xx_ain_config_t ain0Config = {.ain=0, // AIN0
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[0] = ain0Config;
    dt78xx_ain_config_t ain1Config = {.ain=1, // AIN1
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[1] = ain1Config;
    dt78xx_ain_config_t ain2Config = {.ain=2, // AIN2
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[2] = ain2Config;
    dt78xx_ain_config_t ain3Config = {.ain=3, // AIN3
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[3] = ain3Config;
    dt78xx_ain_config_t ain4Config = {.ain=4, // AIN4
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[4] = ain4Config;
    dt78xx_ain_config_t ain5Config = {.ain=5, // AIN5
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[5] = ain5Config;
    dt78xx_ain_config_t ain6Config = {.ain=6, // AIN6
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[6] = ain6Config;
    dt78xx_ain_config_t ain7Config = {.ain=7, // AIN7
                                      .gain=1, // Default gain
                                      .ac_coupling=0, // DC coupling
                                      .current_on=0, // Current source off
                                      .differential=0
                                     }; 
    ainConfig[7] = ain7Config;
}

static void initTrig(dt78xx_trig_config_t ainTrigConfig[]) {
    /* AIN0 */
    dt78xx_trig_config_t trig0Config;
    ainTrigConfig[0] = trig0Config;
    /* AIN1 */
    dt78xx_trig_config_t trig1Config;
    ainTrigConfig[1] = trig1Config;
    /* AIN2 */
    dt78xx_trig_config_t trig2Config;
    ainTrigConfig[2] = trig2Config;
    /* AIN3 */
    dt78xx_trig_config_t trig3Config;
    ainTrigConfig[3] = trig3Config;
    /* AIN4 */
    dt78xx_trig_config_t trig4Config;
    ainTrigConfig[4] = trig4Config;
    /* AIN5 */
    dt78xx_trig_config_t trig5Config;
    ainTrigConfig[5] = trig5Config;
    /* AIN6 */
    dt78xx_trig_config_t trig6Config;
    ainTrigConfig[6] = trig6Config;
    /* AIN6 */
    dt78xx_trig_config_t trig7Config;
    ainTrigConfig[7] = trig7Config;
}

static int configTrig(dt78xx_trig_config_t trigConfig) {
    if (autoTrigger) {// Default trigger is the auto or software trigger
        trigConfig.src = trig_src_sw;
    } else { // Otherwise use a threshold trigger
        trigConfig.src = trig_src_threshold;
        trigConfig.src_cfg.threshold.edge_rising = 1;
        trigConfig.src_cfg.threshold.level = volts2raw(TRIG_LEVEL_V,DEFAULT_GAIN);
    }
    return ioctl(inStream, IOCTL_START_TRIG_CFG_SET, &trigConfig);
}

int setupAIO(int argc) {
    int setupFailure = 0; // 0 for failure
    
    /* Creates mask for enabled channels, which has a bitwise format. */
    int *chOn = malloc(sizeof(int)*numChannels); // Array of enabled channel indices
    createChanMask(ain, chOn);
    
    /* Channel configuration */
    dt78xx_ain_config_t ainConfig[8] = {}; // Analog input configuration array
    configChan(ainConfig);
    
    /* First fatal error check: channel identity and sampling rate */
    checkID(argc);
    
    /* Second fatal error check: opening the input stream */
    openStream();
    
    /* Third fatal error check: opening analog input */
    openAIN();
    
    /* 
     * Passes all fatal error checks; proceeds to setup.
     * Graduates to graceful exit protocol: _exit. 
     */

    /* Opens asynchronous I/O (AIO) context */
    inAIO = aio_create(inStream, 0, isInAIODone, isInStreamEmpty);

    /* Configures sampling rate; actual rate is returned on success */
    if (ioctl(inStream, IOCTL_SAMPLE_CLK_SET, &clk)) {
        fprintf(stderr, "IOCTL_SAMPLE_CLK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return setupFailure;
    }
    
    dt78xx_trig_config_t ainTrigConfig[8] = {}; // Array of analog input configurations
    initTrig(ainTrigConfig); // Initialises trigger
    
    /* Configures for software trigger for all enabled channels */
    fprintf(stdout, "Configuring trigger...\n");
    int i;
    for (i = 0; i < numChannels; i++) {
        int chan = chOn[i];
        if (configTrig(ainTrigConfig[chan])) {
            fprintf(stderr, "IOCTL_START_TRIG_CFG_SET ERROR %d \"%s\"\n", 
                    errno, strerror(errno));
            return setupFailure;
        }
    }
    
    /* Writes channel mask for selected/enabled channels */
    if (ioctl(inStream, IOCTL_CHAN_MASK_SET, &chanMask)) {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return setupFailure;
    }
    
    /* Sets channel gain, coupling and current source */
    for (i = 0; i < numChannels; i++) {
        int ainIndex = chOn[i];
        if (ioctl(aInput, IOCTL_AIN_CFG_SET, &ainConfig[ainIndex])) {
            fprintf(stderr, "IOCTL_AIN%d_CFG_SET ERROR %d \"%s\"\n", 
                    ainIndex, errno, strerror(errno));
            return setupFailure;
        }
    }
    
    /* Submits AIO control buffers */
    if (submitAIO()) {
        sampleRate = clk.clk_freq;
        fprintf(stdout,"Sampling at %f Hz to %d queues of %d buffers of %d samples for %d channel %f s files\n", 
                    sampleRate, TOTAL_QUEUES, BUFFERS_PER_QUEUE, bufferSamples, numChannels, fileSeconds);
        return !setupFailure;
    }
    return setupFailure;
}

void calcSunUpDown(long *sunsets, long *sunrises) {
    struct timeval epochPresent;  // Seconds UTC relative to 1 Jan 1970 (epoch)
    struct tm *presentTime = malloc(sizeof(struct tm)); // Time in accordance to ISO 8601
    gettimeofday(&epochPresent, NULL); // Gets current system time
    presentTime = gmtime(&epochPresent.tv_sec); // Gets current time in UTC (aka GMT or Zulu)

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
            epochSet += set * 3600;
            sunsets[elapsedDays] = epochSet - safetyMargin;
        } else {
            sunsets[elapsedDays] = epochSet;
        }

        time_t daySec = 86400; // Length of 1 day in seconds
        epochDay += daySec;
        presentTime = gmtime(&epochDay);
        year = 1900 + (int) presentTime->tm_year;
        month = 1 + presentTime->tm_mon;
        day = presentTime->tm_mday;

        long epochRise = getTimeEpoch(year, month, day, 0, 0, 0);
        if (nightCycle) {
            sun_rise_set(year, month, day, lon, lat, &rise, &set);
            epochRise += rise * 3600;
            sunrises[elapsedDays] = epochRise + safetyMargin;
        } else {
            sunrises[elapsedDays] = epochRise;
        }
    }
}

static void checkID(int argc) {
    if (optind >= argc) {
        printf(usage, ID);
        exit(EXIT_FAILURE);
    }
}  

static void openStream() {
    fprintf(stdout, "Opening stream...\n");
    inStream = open(DEV_STREAM_IN, O_RDONLY);
    if (inStream < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        exit(EXIT_FAILURE);
    }    
}

static void openAIN() {
    fprintf(stdout, "Opening analog input...\n");
    aInput = open(DEV_AIN, O_RDONLY);
    if (aInput < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(inStream);
        exit(EXIT_FAILURE);
    }
}

static int submitAIO() {
    /* 
     * Size/allocate a buffer to hold the specified samples for each channel
     * where: buffSize = 16*chanSamples*numChannels/8 (in bytes, assuming 
     * chanSamples multiple of 32)
     */
    int actualSamples;
    int buffSize = aio_buff_size(chanSamples, chanMask, &actualSamples);
    chanSamples = actualSamples;
    bufferSamples = chanSamples*numChannels;
         
    /* Creates and initialises AIO stream buffers/structures */
    fprintf(stdout, "Initialising...\n");
    if ((inBuffer = aio_buff_alloc(inAIO, BUFFERS_PER_QUEUE, buffSize)) == NULL) {
        fprintf(stderr, "alloc_queue_buffers ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return 0;
    }
        
   /* Submits AIO buffers*/ 
    if (aio_start(inAIO)) {
        fprintf(stderr, "AIO start failure error\n");
        return 0;
    }
    return 1;
}

int armStartStream() {
    /* Arms the input stream */
    if (ioctl(inStream, IOCTL_ARM_SUBSYS, 0)) {
        fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
              errno, strerror(errno));
        return 0;
    }   

    /* 
     * Issues a software start for continuous input operation; this is 
     * redundant if trigger source is threshold or externally triggered 
     */
    if (ioctl(inStream, IOCTL_START_SUBSYS, 0)) {
        fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        return 0;
    }
    return 1;
}

int stopStream() {
    return ioctl(inStream, IOCTL_STOP_SUBSYS, 0); // Stop stream
}

#if AIFF
static int setFile(SNDFILE *file) {
    int failure = 1;
    char metadata[LEN];
    sprintf(metadata, "%f", lon);
    failure = sf_set_string(file, SF_STR_TITLE, metadata);
    sprintf(metadata, "%f", lat);
    failure = sf_set_string(file, SF_STR_ARTIST, metadata);
    sprintf(metadata, "%ld", sunset); // Sunset time (in Unix Epoch time, seconds)
    failure = sf_set_string(file, SF_STR_COMMENT, metadata); // Set as copyright attribute
    sprintf(metadata, "%ld", sunrise); // Sunrise time
    failure = sf_set_string(file, SF_STR_COPYRIGHT, metadata); // Set as annotation attribute
    return !failure;
}

static SNDFILE* createAIFF() {
    timestamp(); // Timestamp: Time of first sample recording
    fileInfo.channels = numChannels;
    fileInfo.format = (SF_FORMAT_AIFF | SF_FORMAT_PCM_16);
    fileInfo.samplerate = sampleRate;
    fileInfo.frames = fileSamples / numChannels;
    SNDFILE* file = sf_open(filePath, SFM_WRITE, &fileInfo); // AIFF file opened
    if (file) {
        if (!setFile(file)) {
            sf_close(file);
            fprintf(stderr, "ERROR audio_format_set");
            return NULL;
        }
    } else {
        fprintf(stderr, "ERROR audio_file_open");
        return NULL;
    }
    return file;
}

static int writeAIFF(void *raw, SNDFILE *file) {
    int written = 0;
    int i, j;
    for (i=0; i < chanSamples; i++) {
        for (j = 0; j < numChannels; j++) {
            written += sf_write_int(file, (int *)raw, 1);
            raw += sizeof(int16_t);
        }
    }
    ++fileBuffer;
    return written;
}

static int finishAIFF(SNDFILE *file) {                    
    if (!sf_close(file)) {
        fileBuffer = 0;
        ++fileNum;
        fprintf(stdout, "%d total .aiff files written\n", fileNum);
        fprintf(stdout, "File closed\n");
        fprintf(stdout, "File at %s\n", filePath);
    } else {
        fprintf(stderr, "ERROR audio_file_close");
        return 0;
    }
    return 1;
}

#else
static FILE *createCSV() {
    timestamp(); // Timestamp: Time of first sample recording
    FILE *file = fopen(filePath, "w");
    fprintf(file,"Sample"); // CSV file header
    int ch;
    for (ch = 0; ch < 8; ch++) {
        if (ain[ch]) {
            fprintf(file, ", AIN%d (V)", ch);
            fprintf(file, ", AIN%d (count)", ch);
        }
    }
    fprintf(file,"\n"); 
    return file;
}

static void writeCSV(void *raw, FILE *file) {
    int i, j;
    for (i = 0; i < chanSamples; i++) {
        int sample = i + chanSamples * (fileNum * fileBuffers + fileBuffer);
        fprintf(file, "%6d", sample);
        for (j = 0; j < numChannels; j++) {
            float volt = raw2volts(*(int16_t *)raw, 1); 
            fprintf(file, ", %.5f", volt);
            fprintf(file, ", %hd", *(int16_t *)raw);
            raw += sizeof(int16_t);
        }
        fprintf(file,"\n");     
    }
    ++fileBuffer;
}

static int finishCSV(FILE *file) {                   
    if (fclose(file)) {
        fprintf(stderr, "ERROR ending writing .csv file");
        return 0;
    } else {
        fileBuffer = 0;
        ++fileNum;
        fprintf(stdout, "File closed\n");
        fprintf(stdout, "File at %s\n", filePath);
        fprintf(stdout, "%d total .csv files written\n", fileNum);
    }
    return 1;
}
#endif

void writeFile(void *buff, int len) {  
    /* 
     * Write ping (then pong, then ping, and so on) buffer to file
     * The ping buffer is the initial fill buffer, and the pong buffer 
     * is the initial write buffer.
     */
    if (fileBuffer == 0) { // New file created
#if AIFF
        file = createAIFF();
#else
        file = createCSV();     
#endif   
        
#if LED_ENABLED
    ledIndicators(chanMask);
#endif  
    }
    
#if AIFF // Writes buffer to file
    writeAIFF(buff, file);
#else
    writeCSV(buff, file);  
#endif 
    
    if (fileBuffer == fileBuffers) { // File closed
#if AIFF
        int written = finishAIFF(file);
        int dropped = len - written;
        if (dropped != 0) {
            fprintf(stdout, "Dropped %d samples during writing\n", dropped);
        }
#else      
        finishCSV(file);    
#endif  
        
#if LED_ENABLED
    ledIndicators(0x00);
#endif         
    }
}

void closeFile() {
    if (file != NULL) {
#if AIFF
        finishAIFF(file);     
#else        
        finishCSV(file); 
#endif
    }
}

void ledIndicators(uint8_t status) {
    dt78xx_led_t led;
    led.mask = 0xff; // All bits are enabled (8 LEDs capable of being lit)
    led.state = (status & 0xff);
    ioctl(inStream, IOCTL_LED_SET, &led); 
}
