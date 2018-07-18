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

/*****************************************************************************
 * External Libraries
 */
#include "recorder_helpers.h"

 /*****************************************************************************
 * Helper functions for recorder (DT7816)
 */

void ledIndicators(uint8_t status, int streaming) {   
    dt78xx_led_t led;
    led.mask = 0xff; /// All bits are enabled (8 LEDs capable of being lit)
    led.state = (status & 0xff);
    ioctl(streaming, IOCTL_LED_SET, &led);    
}

void getTime(struct tm **pres_time, struct timeval *clock_time) {
    gettimeofday(clock_time, NULL);
    *pres_time = gmtime(&(*clock_time).tv_sec);
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

void timestamp(char *file_path, char **argv, char *path_to_storage) {
    struct timeval tv;
    struct tm *t_iso;
    getTime(&t_iso, &tv);
    const char *output_path = path_to_storage;
    const char *ID;
    ID = argv[optind];
    char file_time[LEN];

    sprintf(file_time, "_%04d%02d%02dT%02d%02d%02d%liZ.aiff", 
            t_iso->tm_year+1900, t_iso->tm_mon + 1, t_iso->tm_mday, 
            t_iso->tm_hour, t_iso->tm_min, t_iso->tm_sec, (long) tv.tv_usec); 
    char file_name[LEN];
    strcpy(file_name, ID);
    strcat(file_name, file_time);
    strcpy(file_path, output_path);
    strcat(file_path, file_name);
}

long getPresentTime() {
    struct tm* iso_time;
    struct timeval epoch_time;
    getTime(&iso_time, &epoch_time);
    return (long) epoch_time.tv_sec;
}

int checkFatal(int gross_samples) {
    if(gross_samples > 65536) {
        fprintf(stderr, "Fatal Error: exceeded 16-bits!\n");
        fprintf(stderr, "SAMPLES_PER_CHAN*NUM_BUFFS*NUM_CHANNELS = %d > 65536\n", 
                gross_samples);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
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
    dt78xx_ain_config_t ain0_cfg ={.ain=0, /// AIN0
                                  .gain=1, /// Default gain
                                  .ac_coupling=0, /// DC coupling
                                  .current_on=0, /// Current source off
                                  .differential=0
                                  }; 
    ain_cfg[0] = ain0_cfg;
    dt78xx_ain_config_t ain1_cfg ={.ain=1, /// AIN1
                                   .gain=1, /// Default gain
                                   .ac_coupling=0, /// DC coupling
                                   .current_on=0, /// Current source off
                                   .differential=0
                                  }; 
    ain_cfg[1] = ain1_cfg;
    dt78xx_ain_config_t ain2_cfg ={.ain=2, /// AIN2
                                   .gain=1, /// Default gain
                                   .ac_coupling=0, /// DC coupling
                                   .current_on=0, /// Current source off
                                   .differential=0
                                  }; 
    ain_cfg[2] = ain2_cfg;
    dt78xx_ain_config_t ain3_cfg ={.ain=3, /// AIN3
                                   .gain=1, /// Default gain
                                   .ac_coupling=0, /// DC coupling
                                   .current_on=0, /// Current source off
                                   .differential=0
                                  }; 
    ain_cfg[3] = ain3_cfg;
    dt78xx_ain_config_t ain4_cfg ={.ain=4, /// AIN4
                                   .gain=1, /// Default gain
                                   .ac_coupling=0, /// DC coupling
                                   .current_on=0, /// Current source off
                                   .differential=0
                                  }; 
    ain_cfg[4] = ain4_cfg;
    dt78xx_ain_config_t ain5_cfg ={.ain=5, /// AIN5
                                   .gain=1, /// Default gain
                                   .ac_coupling=0, /// DC coupling
                                   .current_on=0, /// Current source off
                                   .differential=0
                                  }; 
    ain_cfg[5] = ain5_cfg;
    dt78xx_ain_config_t ain6_cfg ={.ain=6, /// AIN6
                                   .gain=1, /// Default gain
                                   .ac_coupling=0, /// DC coupling
                                   .current_on=0, /// Current source off
                                   .differential=0
                                  }; 
    ain_cfg[6] = ain6_cfg;
    dt78xx_ain_config_t ain7_cfg ={.ain=7, /// AIN7
                                   .gain=1, /// Default gain
                                   .ac_coupling=0, /// DC coupling
                                   .current_on=0, /// Current source off
                                   .differential=0
                                  }; 
    ain_cfg[7] = ain7_cfg;
}

void initTrig(dt78xx_trig_config_t trig_cfg_ai[]) {
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

int configTrig(int* fd_stream, dt78xx_trig_config_t trig_cfg, int auto_trig) {
    if (auto_trig) /// default trigger == auto or software trigger
        trig_cfg.src = trig_src_sw;
    else { /// threshold trigger
        trig_cfg.src = trig_src_threshold;
        trig_cfg.src_cfg.threshold.edge_rising = 1;
        trig_cfg.src_cfg.threshold.level = volts2raw(TRIG_LEVEL_V,DEFAULT_GAIN);
    }
    return ioctl(*fd_stream, IOCTL_START_TRIG_CFG_SET, &trig_cfg);
}

void calcSunUpDown(long *sunsets, long *sunrises, int duration_days, 
                   long safety_margin, double lon, double lat, int night_cycle) {
    struct timeval epoch_present;  /// Seconds UTC relative to 1 Jan 1970 (epoch)
    struct tm *t_present = malloc(sizeof(struct tm)); /// Time in accordance to ISO 8601
    gettimeofday(&epoch_present, NULL); /// Gets current system time
    t_present = gmtime(&epoch_present.tv_sec); /// Gets current time in UTC (aka GMT or Zulu)

    int elapsed_days;
    double rise, set;
    for (elapsed_days = 0; elapsed_days < duration_days; elapsed_days++) {
        int year = 1900 + (int) t_present->tm_year;
        int month = 1 + t_present->tm_mon;
        int day = t_present->tm_mday;
                
        long epoch_day = getTimeEpoch(year, month, day, 0, 0, 0);
        long epoch_set = epoch_day;
        if (night_cycle) {
            sun_rise_set(year, month, day, lon, lat, &rise, &set);
            epoch_set += set*3600;
            sunsets[elapsed_days] = epoch_set - safety_margin;
        } else {
            sunsets[elapsed_days] = epoch_set;
        }

        time_t day_sec = 86400; /// Length of 1 day in seconds
        epoch_day += day_sec;
        t_present = gmtime(&epoch_day);
        year = 1900 + (int) t_present->tm_year;
        month = 1 + t_present->tm_mon;
        day = t_present->tm_mday;

        long epoch_rise = getTimeEpoch(year, month, day, 0, 0, 0);
        if (night_cycle) {
            sun_rise_set(year, month, day, lon, lat, &rise, &set);
            epoch_rise += rise*3600;
            sunrises[elapsed_days] = epoch_rise + safety_margin;
        } else {
            sunrises[elapsed_days] = epoch_rise;
        }
    }
}

int writeBuffer(AIFF_Ref file, struct circ_buffer buffer_object, 
                int channels_per_file, int num_buffers, int* ch_on, 
                void** buf_array, dt78xx_ain_config_t* ain_cfg) {

    int success = 0;
    int buff_done;
    for (buff_done=0; buff_done < num_buffers; ++buff_done) { 
        fprintf(stdout, "Reading buffer and writing file...\n");

        int16_t *raw = buf_array[buff_done];

        int queue, ch;
        /// Circular buffer write and read pointers lead and follow
        for (queue = 0; queue < buffer_object.num_samples + 1; queue++) {  
            for (ch = 0; ch < channels_per_file; ch++, ++raw) {
                /// Decouples input from output with circular buffer
                int ain_i = ch_on[ch];
                /// Write pointer leads read pointer by channels_per_file
                if (queue < buffer_object.num_samples) { 
                    float sample_volt = raw2volts(*raw, ain_cfg[ain_i].gain);
                    float* wptr = &sample_volt; //write pointer for input
                    buffer_object.vbuf->add(buffer_object.vbuf, wptr);
                }
                /// Read pointer lags write pointer by channels_per_file
                if (queue > 0) {
                    float* rptr = NULL; /// Read pointer for writing to file
                    buffer_object.vbuf->pull(buffer_object.vbuf, &rptr);
                    success = AIFF_WriteSamples32Bit(file, (int32_t*) &rptr, 1);
                    if (!success) break;
                }
            }
        }
    }
    return success;
}

int checkID(int argc, char** argv) {
    if (optind >= argc) {
        printf(g_usage, argv[0]);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}
int checkRate(struct circ_buffer buffer_object, char** argv) { 
    if (buffer_object.sample_rate <= 0.0f) {
        printf(g_usage, argv[0]);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}    

int openStream(int* fd_stream) {
    fprintf(stdout, "Opening stream...\n");
    *fd_stream = open(DEV_STREAM_IN, O_RDONLY);
    if (*fd_stream < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_STREAM_IN);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }    
}
int openAIN(int* fd_stream, int* fd_ain) {
    fprintf(stdout, "Opening analog input...\n");
    *fd_ain = open(DEV_AIN, O_RDONLY);
    if (*fd_ain < 0) {
        fprintf(stderr, "ERROR %d \"%s\" open %s\n", 
                errno, strerror(errno), DEV_AIN);
        close(*fd_stream);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}

void waitBuffering(int num_buffers, int g_quit, struct aio_struct** aio) {
    fprintf(stdout, "Buffering in progress...\n");
    int buff_done = 0;
    while (!g_quit && (buff_done < num_buffers)) {
        int ret = aio_wait(*aio, 0);
        if (ret < 0) /// Error
            break;
        buff_done += ret;
    }
}