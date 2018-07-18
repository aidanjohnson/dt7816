/* 
 * @file main.c
 * @brief This is a custom application for DT7816 autonomous asynchronous I/O sampling
 * that configures the board's analog inputs. The sampled data is read 
 * asynchronously from the input stream and written to a AIFF file. See:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
 * for additional details on (a)synchronous I/O.
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
 * 
 * ============================================================================
 * Usage :
 *	See usage() below
 */

/* Contains helper functions, global constants (macros), and required libraries */
#include "recorder_helpers.h" 

static int g_quit = 0; /* Force exit or quit (ctrl+c) */

/*
 * ==== Signal handler for ctrl-c prevents the abrupt termination of processes ====
 */

static void sigint_handler(int i) {
    g_quit = -1;
}

/*
 * ==== Simultaneous 8-channel analog input signal AIFF recorder ====
 */

int main (int argc, char** argv) {
    
    uint8_t sys_status = 0x00;
    int ret = EXIT_SUCCESS;
    int auto_trig = AUTO_TRIG;
    int samples_per_file = SAMPLES_PER_FILE;
    int num_buffers = NUM_BUFFS;
    int num_channels = NUM_CHANNELS;
    int duration_days = DURATION_DAYS;
    double lat = DEFAULT_LATITUDE;
    double lon = DEFAULT_LONGITUDE;
    long safety_margin = SAFETY_MARGIN;
    
    struct circ_buffer buffer_object = {.sample_rate = SAMPLE_RATE, .vbuf = NULL};
    
    dt78xx_clk_config_t clk = {.ext_clk=0, /* Internal clock */
                               .ext_clk_din=0, 
                               .clk_freq=SAMPLE_RATE
                              };
   
    int ain[8] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7};
    int ch_code; /* 8 bit binary; channel on := 1, channel off := 0 */
    int opt = 0;
    while ((opt = getopt(argc, argv, "s:c:d:b:t:i:m:l:")) != -1) {
        switch (opt) {
            case 's':
                samples_per_file = strtoul(optarg, NULL, 10);
                if (samples_per_file <= 0) {
                    printf(g_usage, argv[0]);
                    return (EXIT_FAILURE);
                }
                break;
            case 'c':
                clk.clk_freq = atof(optarg);
                buffer_object.sample_rate = clk.clk_freq;
                break;
            case 'd' :
                duration_days = atoi(optarg);
                break; 
            case 'b' :
                num_buffers = atoi(optarg);
                break;
            case 't' :
                auto_trig = 0;
                break;
            case 'i' :
                ch_code = atoi(optarg);
                int d;
                num_channels = 0;
                for (d = 0; d < 8; d++) {
                    int digit = ch_code % 10;
                    ain[7-d] = digit;
                    if (digit) num_channels++;
                    ch_code /= 10;
                }
                break;
            case 'm' :
                safety_margin = atol(optarg);
                break;
            default :
                printf(g_usage, argv[0]);
                return EXIT_FAILURE;
        }
    }
    
    /* Creates mask for enabled channels */
    const int channels_per_file = num_channels; /* aka Block Size */
    chan_mask_t chan_mask = 0x0;
    int *ch_on = malloc(sizeof(int)*channels_per_file);
    createChanMask(ain, ch_on, &chan_mask);
    
    int samples_per_chan = samples_per_file / channels_per_file;
    checkFatal(samples_per_file * num_buffers);
   
    dt78xx_ain_config_t ain_cfg[8] = {};
    configChan(ain_cfg);
    
    checkID(argc, argv);
    checkRate(buffer_object, argv);
    
    int fd_stream;
    openStream(&fd_stream);
    int fd_ain;
    openAIN(&fd_stream, &fd_ain);
            
    /* Set up ctrl-c handler to terminate process gracefully */
    sigaction_register(SIGINT, sigint_handler);

    /* Configure sampling rate. The actual rate is returned on success */
    clk.clk_freq = buffer_object.sample_rate;
    if (ioctl(fd_stream, IOCTL_SAMPLE_CLK_SET, &clk)) {
        perror("IOCTL_SAMPLE_CLK_SET");    
        goto _exit;
    }
    buffer_object.sample_rate = clk.clk_freq; /* Actual rate */
       
    dt78xx_trig_config_t trig_cfg_ai[8] = {};
    initTrig(trig_cfg_ai);
    
    /* Configure for software trigger for all enabled channels */
    fprintf(stdout, "Configuring trigger...\n");
    int i;
    for (i = 0; i < channels_per_file; i++) {
        int chan = ch_on[i];
        if (configTrig(&fd_stream, trig_cfg_ai[chan], auto_trig)) {
            perror("IOCTL_START_TRIG_CFG_SET");    
            goto _exit;
        }
    }
    
    /* Write channel mask for selected/enabled channels */
    if (ioctl(fd_stream, IOCTL_CHAN_MASK_SET, &chan_mask)) {
        fprintf(stderr, "IOCTL_CHAN_MASK_SET ERROR %d \"%s\"\n", 
                errno, strerror(errno));
        goto _exit;
    }
    
    /* Channel gain, coupling and current source */
    for (i = 0; i < channels_per_file; i++) {
        int ain_i = ch_on[i];
        if (ioctl(fd_ain, IOCTL_AIN_CFG_SET, &ain_cfg[ain_i])) {
            fprintf(stderr, "IOCTL_AIN%d_CFG_SET ERROR %d \"%s\"\n", 
                    ain_i, errno, strerror(errno));
            goto _exit;
        }
    }
    
    /* Create and initialise AIO structures */
    fprintf(stdout, "Initialising...\n");
    struct aio_struct *aio = aio_create(fd_stream, 0, NULL, NULL);
    if (!aio) {
        fprintf(stderr, "ERROR aio_create\n");
        goto _exit;
    }
    
    /* Size/allocate a buffer to hold the specified samples for each channel */
    /* where: buflen = 16*samples_per_chan*channels_per_file/8 */ 
    /* (in bytes, assuming samples_per_chan multiple of 32) */
    int buflen = aio_buff_size(samples_per_chan, chan_mask, 
                                &buffer_object.num_samples);
    fprintf(stdout,"Sampling at %f Hz to buffer of %d samples for %d channels...\n", 
                    clk.clk_freq, buffer_object.num_samples, channels_per_file);
    void **buf_array = aio_buff_alloc(aio, num_buffers, buflen);
    if (!buf_array) {
        fprintf(stderr, "ERROR aio_buff_alloc\n");
        goto _exit;
    }
    
    /* Allocate a circular/ring buffer/queue to hold the recorded values in Volts */
    const int vbuf_len = samples_per_chan * channels_per_file;
    buffer_object.vbuf = RingBuf_new(sizeof(float), vbuf_len);
    if (!buffer_object.vbuf) {
        fprintf(stderr, "ERROR buffer_object.vbuf\n");
        goto _exit;
    }
    
    /* Wait for user input to start or abort */
    fprintf(stdout,"Press s to start, any other key to quit\n");
    while (1) {
        int c = getchar();
        if (c == 's') {
            break;
        }
        goto _exit;
    }
    
    /* Calculates sunset (sunsclipse) and sunrise (sunsight) times based on: */
    /* (1) Date and (2) Latitude and Longitude coordinates */
    long *sunsets = malloc(sizeof(long)*duration_days);
    long *sunrises = malloc(sizeof(long)*duration_days);
    calcSunUpDown(sunsets, sunrises, duration_days, safety_margin, lon, lat, NIGHT_CYCLE);
    
    int elapsed_days = 0; /* Resets counter */
    ret = 0;
    int file_num = 0; /* Diagnostic/debugging file counter */
    
    /* Infinite loop until aborted by ctrl-C */
    while (!g_quit && duration_days > elapsed_days) {
        long present = getPresentTime();
        long sunset = sunsets[elapsed_days];
        long sunrise = sunrises[elapsed_days];
        int night = 0;

        /* If after dusk and before dawn (entering night) */
        while (!g_quit && (present < sunrise && present >= sunset)) {           
            if (g_quit) {
                goto _exit;
            } else {
                night = 1;
            }
            /* Gets time of first sample recording for timestamp */
            char file_path[LEN];
            timestamp(file_path, argv, PATH_TO_STORAGE);

            /* Submit the buffers */
            fprintf(stdout, "\nCommencing buffer...\n");
            if (aio_start(aio)) {
                fprintf(stderr, "ERROR aio_start\n");
                goto _exit;
            }

            /* ARM */
            if ((ioctl(fd_stream, IOCTL_ARM_SUBSYS, 0))) {
                fprintf(stderr, "IOCTL_ARM_SUBSYS ERROR %d \"%s\"\n", 
                        errno, strerror(errno));
                goto _exit;
            }

            /* Issue a software start; this is redundant if trigger source is */
            /* threshold trigger or external trigger */
            if ((ioctl(fd_stream, IOCTL_START_SUBSYS, 0))) {
                fprintf(stderr, "IOCTL_START_SUBSYS ERROR %d \"%s\"\n", 
                        errno, strerror(errno));
                goto _exit;
            }

            waitBuffering(num_buffers, g_quit, &aio);

            /* Gets current active channels, indicating status on LEDs */
            chan_mask_t active_chan;
            if (ioctl(fd_stream, IOCTL_CHAN_MASK_GET, &active_chan)) {
                perror("IOCTL_CHAN_MASK_GET");    
                goto _exit;
            }
            sys_status = active_chan;
            ledIndicators(sys_status, fd_stream);

            /* Stop streaming after buffer completion */
            fprintf(stdout, "Completing...\n");
            ioctl(fd_stream, IOCTL_STOP_SUBSYS, 0);  
            aio_stop(aio);

            /* Write acquired data to the specified .aiff output file */
            AIFF_Ref file = malloc(sizeof(AIFF_Ref));

            char sun_times[LEN];
            sprintf(sun_times, "%ld-%ld", sunset, sunrise);
            AIFF_SetAttribute(file, AIFF_ANNO, sun_times);

            file = AIFF_OpenFile(file_path, F_WRONLY);
            if (file) {
                file_num += 1;
                fprintf(stdout, "Opened .aiff file...\n");

                /* Sets formatting */
                if (!AIFF_SetAudioFormat(file, channels_per_file, 
                                        (double) buffer_object.sample_rate, 
                                        sizeof(float))) {
                    AIFF_CloseFile(file);
                    fprintf(stderr, "ERROR audio_format_set");
                    goto _exit;
                }
            } else {
                fprintf(stderr, "ERROR audio_file_open");
                goto _exit; 
            }

            if (!AIFF_StartWritingSamples(file)) {
                fprintf(stderr, "ERROR starting writing .aiff file");
                goto _exit;
            }
            
            /* Writes buffer to intermediate circular buffer to be written to file */
            if (!writeBuffer(file, buffer_object, channels_per_file, 
                             num_buffers, ch_on, buf_array, ain_cfg)) {
                fprintf(stderr, "ERROR writing .aiff file");
                goto _exit;
            }

            if (!AIFF_EndWritingSamples(file)) {
                fprintf(stderr, "ERROR ending writing .aiff file");
                goto _exit;
            } else {
                fprintf(stdout, "%do .aiff file written\n", file_num);
            }
            
            /* Stops writing */
            if (AIFF_CloseFile(file)) {
                fprintf(stdout, "Closed file...\n");
                sys_status = 0x00; /* All off */
                ledIndicators(sys_status, fd_stream);
                fprintf(stdout, "File at %s\n", file_path);
            } else {
                fprintf(stderr, "ERROR audio_file_close");
                goto _exit;
            }
            
            present = getPresentTime(); /* Updates time for while loop check */
        }
        if (night) elapsed_days++; /* If after dawn (leaving night), 1 day elapsed */
    }

/* Exit protocol and procedure */
_exit :
    sys_status = 0x00;
    ledIndicators(sys_status, fd_stream);
    aio_stop(aio);
    aio_destroy(aio);
    if (fd_ain > 0)
        close(fd_ain);
    if (fd_stream > 0)
        close(fd_stream);
    return (ret);
}

