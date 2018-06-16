/*
 * This is a stand-alone calibration tool for the DT7837. There is no 
 * graphical user interface; everything is done via the command line.
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
#include <stdbool.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>         	/* for syscall() */
#include <sys/syscall.h>	/* for __NR_* definitions */
#include <linux/aio_abi.h>	/* for AIO types and constants */
#include <malloc.h>
#include "dt78xx_ioctl.h"
#include "aio_syscall.h"
#define DT7837
#include "dt78xx_misc.h"


/* General comments:
 *
 * Most functions return a boolean rather than an integer error code:
 * "true" on success and "false" on failure.
 * Functions that fail are responsible for writing an error 
 * message to the user unless the error came from a function it called.
 *
 * Each potentiometer (pot) is programmable via an 8 bit value; thus there are 
 * 256 possible values for each pot. 
 *
 * We calibrate 8 pots per analog input channel - there are two gain 
 * settings (1 and 10), each with an offset and gain pot. The ADC operates
 * in two modes covering 2 frequency bands. Each band (low and high) has its
 * own set of pot values. The calibration frequency is set to the middle
 * of each band. So 2 gains X 2 types x 2 frequencies = 8.
 *
 * There are 2 pots per analog output channel - offset and gain. There is 
 * only one gain and two frequency bands to deal with.
 *
 * Each pot value has three values - a read-only "Factory" value which is 
 * programmed at the factory and represents a known accurate configuration, 
 * a "User" value which can be modified by the user via this utility,
 * and a "Wiper" which is the current value. In everyday use, the Wiper 
 * and User values are always the same. They differ only during the actual
 * calibration process when the Wiper is tweaked until the desired value is
 * reached.
 *
 * Each analog input pot has 8 slots, of which the first 4 are used (the others 
 * are reserved for future use).
 *  slot   gain   frequency
 *   0      1      > 52734
 *   1     10      > 52734
 *   2      1      <= 52734
 *   3     10      <= 52734
 *
 * Each analog output pot has 3 slots for frequency dependency. 
 * There is no dependency on gain as there is only 1 gain (1).
 *  slot   frequency (KHz)
 *   0       54 < f <= 108
 *   1       30 < f <=  54
 *   2      108 < f <= 216
 *
 * Each reading from an analog input channel is really an average of many samples.
 * We do this to minimize the effect of noise.
 *
 * Depending on the actual circuit, some boards have a response slope that is
 * positive while others are negative. This "slope" refers to how the input
 * measurement changes with a change in the pot - does an increase in the pot value
 * cause an increase or decrease in the measured input. When porting this code
 * from one board to another, be aware of the "slope" of the board.
 *
 * Buffers of data are in units of samples. Each sample is 4 bytes.
 */


// This is what our hardware looks like. 
#define NUM_AIN                 (4)
#define NUM_AOUT                (1)

#define OFFSET_POT              (0)
#define GAIN_POT                (1)
const int NUM_POTS              = 2;
const int POT_VALUES[]          = {OFFSET_POT, GAIN_POT};

const int NUM_INPUT_GAINS       = 2;
const int INPUT_GAIN_VALUES[]   = {1, 10};
const int NUM_OUTPUT_GAINS      = 1; 

#define WIPER_ARM               (-1)
#define USER_CAL_REG            (0)
#define FACTORY_CAL_REG         (1)

#define EEPOT_RES               (8)
#define NUM_POT_STEPS           (256)
#define CAL_STARTING_VAL        (NUM_POT_STEPS >> 1)

#define CAL_POT_MIN             (0)
#define CAL_POT_MAX             (NUM_POT_STEPS - 1)
#define CAL_POT_RESET		CAL_POT_MAX

#define NUM_SAMPLES_AVG         (128)
#define NUM_BYTES_PER_SAMPLE    (4)
    
// It can take some time for a write eeprom to finish. In microseconds
#define I2C_WRITE_USLEEP        (13000)

#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#define MAX_CONCURRENT_IO       (8)

// The low frequency band is 195 Hz to 52,734 Hz
// The high frequency band is 52,734 Hz.to 105,469 Hz
// Our calibration frequency is near the middle of each band
#define CAL_AIN_FREQ_LOW        (25000)
#define CAL_AIN_FREQ_HIGH       (75000)
#define NUM_AIN_FREQ            (2)
const int LOW_FREQ_BOOL[]       = {true, false};
const float AIN_FREQS[]         = {CAL_AIN_FREQ_LOW, CAL_AIN_FREQ_HIGH};

// The 3 frequency bands for the DAC are
// 30K to 54K (low, slot 1)
// 54K to 108K (mid, slot 0)
// 108K to 216K (high, slot 2)
// Factory calibration will be at the midpoint of each range
#define CAL_AOUT_FREQ_MIN       (30000)
#define CAL_AOUT_FREQ_INT1      (54000)
#define CAL_AOUT_FREQ_INT2      (108000)
#define CAL_AOUT_FREQ_MAX       (216000)

// the frequency table is indexed by the slot so it goes mid/low/high.
#define CAL_AOUT_FREQ_LOW       ((CAL_AOUT_FREQ_MIN + CAL_AOUT_FREQ_INT1) / 2)
#define CAL_AOUT_FREQ_MID       ((CAL_AOUT_FREQ_INT1 + CAL_AOUT_FREQ_INT2) / 2)
#define CAL_AOUT_FREQ_HIGH      ((CAL_AOUT_FREQ_INT2 + CAL_AOUT_FREQ_MAX) / 2)
const float AOUT_FREQS[]        = {CAL_AOUT_FREQ_MID, CAL_AOUT_FREQ_LOW, CAL_AOUT_FREQ_HIGH};

#define CAL_AOUT_SLOT_LOW       (1)
#define CAL_AOUT_SLOT_MID       (0)
#define CAL_AOUT_SLOT_HIGH      (2)
#define NUM_AOUT_FREQ		(3)

// calibration voltages to use
#define TEST_V_OFFSET           (0.0)
#define TEST_V_FULLSCALE_1      (9.375)
#define TEST_V_FULLSCALE_10     (0.9375)
const float GAIN_FS_VOLTAGE[]   = {TEST_V_FULLSCALE_1, TEST_V_FULLSCALE_10};

// DT7837 analog and stream input and output device files.
#define DEV_STREAM_IN    "/dev/dt7837-stream-in"
#define DEV_AIN          "/dev/dt7837-ain"
#define DEV_STREAM_OUT   "/dev/dt7837-stream-out"
#define DEV_AOUT         "/dev/dt7837-aout"

// Make the file descriptors global to make our lives easier
int g_ain_file, g_stream_in_file, g_aout_file, g_stream_out_file;

bool g_factory = false;  // it's easier to remove a global later if we want to

/*
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating so that io_getevents() can be interrupted and return
 */
static void intHandler(int i) 
{
}


// Free array of IO control blocks
void free_iocbs(struct iocb ** cbs, int num_iocb)
{
    int i;
    for (i=0; i < num_iocb; ++i)
    {
        struct iocb *cb = cbs[i];
        if (cb) 
        {
            if (cb->aio_buf)
                free((void *)(cb->aio_buf));
            free(cb);
        }
    }
    free(cbs);
}


struct iocb **allocate_iocbs(int write, 
                             int num_iocb, 
                             int buff_len)   // length in samples
{
    struct iocb **cbs;
    int i;
    int num_bytes = buff_len * NUM_BYTES_PER_SAMPLE;
    
    cbs = (struct iocb **)malloc(sizeof(struct iocb *) * num_iocb);
    if (!cbs)
    {
        fprintf(stderr, "*** ERROR malloc cbs\n");
        return (NULL);
    }
    memset(cbs, 0, (sizeof(struct iocb *) * num_iocb));

    // setup I/O control blocks
    int page = getpagesize();  
    for (i=0; i < num_iocb; ++i)
    {
        struct iocb *cb = (struct iocb *)malloc(sizeof(struct iocb));
        if (!cb)
        {
            fprintf(stderr, "*** ERROR malloc cb\n");
            break;
        }
        memset(cb, 0, sizeof(struct iocb));

        cbs[i] = cb;
        uint8_t *buff = (uint8_t *)memalign(page, num_bytes);
        if (!buff)
        {
            fprintf(stderr, "*** ERROR malloc buff of len %d bytes\n", num_bytes);
            break;
        }

        cb->aio_fildes = g_stream_in_file;
        cb->aio_lio_opcode = (write ? IOCB_CMD_PWRITE : IOCB_CMD_PREAD);
        cb->aio_buf = (__u64)(__u32)(void *)buff;
        cb->aio_offset = 0;
        cb->aio_nbytes = num_bytes;
        cb->aio_data = 1; //user identifier
    }
    
    //Handle memory allocation failures
    if (i < num_iocb)
    {
        free_iocbs(cbs, i);
        return NULL;
    }
    
    return cbs;
}


// Return a pot "slot" given an ADC frequency and gain. 
// There are 8 slots, 4 of which are used. See block header (above)
// for more information
// Note - no parameter error checking
int GetAinPotSlot(int gain, bool lowFreq)
{
    // slot   gain   frequency
    //   0      1      > 52734 (high)
    //   1     10      > 52734 (high)
    //   2      1      <= 52734 (low)
    //   3     10      <= 52734 (low)
    int slot = 0;
    if (gain == 10)
        slot = 1;
    if (lowFreq)
        slot += 2;
    return slot;
}


// Return a pot "slot" given a DAC frequency. 
// There are 3 slots defined
// Note - no parameter error checking; assumed to be within min/max range
int GetAoutPotSlot(float frequency)
{
    // slot   frequency range (KHz)
    //   0    54  < f <= 108 (mid)
    //   1    30  < f <= 54 (low)
    //   2    108 < f <= 216 (high)
    int slot = 0;
    if (frequency <= CAL_AOUT_FREQ_INT1)
       slot = 1;
    else if (frequency <= CAL_AOUT_FREQ_INT2)
       slot = 0;
    else
       slot = 2;
    return slot;
}


// This function is used to update the sampling rate (frequency).
// All other configurations remain the same.
bool SetFreq(int g_stream_file, float rate)
{
    dt78xx_clk_config_t clk;
    memset(&clk, 0, sizeof(clk));
    clk.clk_freq=rate;
    // Set the sample rate, then read it back and compare
    if (ioctl(g_stream_file, IOCTL_SAMPLE_CLK_SET, &clk))
    {
        fprintf(stdout, "*** ERROR failed to set sample rate\n");
        return false;
    }

#if 0
    // if you want to read it back for confirmation
    if (ioctl(g_stream_file, IOCTL_SAMPLE_CLK_GET, &clk))
    {
        fprintf(stdout, "*** ERROR failed to get sample rate\n");
        return false;
    }
#endif
    return true;
}


// This function is used to update the gain of the desired channel only. All 
// other configurations remain the same.
// NOTE - there is no error checking on the inputs
bool InSetGain(int channel, int gain)
{
    // Channel gain, coupling and current source
    dt78xx_ain_config_t ain_cfg;
    ain_cfg.ain = channel;
    ain_cfg.gain = gain;
    ain_cfg.ac_coupling = 0;   // dc coupling
    ain_cfg.current_on = 0;    // current source off
    if (ioctl(g_ain_file, IOCTL_AIN_CFG_SET, &ain_cfg))
    {
        fprintf(stdout, "*** ERROR failed to update channel gain \n");
        return false;
    }
    return true;
}


// initialize the input stream hardware with given settings
bool InSetHardware(int channel, int gain, float freq)
{
    bool status;

    status = SetFreq(g_stream_in_file, freq);
    if (!status)
        return false;

    // configure for software trigger
    dt78xx_trig_config_t trig_cfg;
    trig_cfg.src = trig_src_sw;
    if (ioctl(g_stream_in_file, IOCTL_START_TRIG_CFG_SET, &trig_cfg))
    {
        fprintf(stdout, "*** ERROR failed to set software trigger \n");
        return false;
    }

    // write channel mask
    chan_mask_t chan_mask = (channel==3)?chan_mask_ain3:
                            (channel==2)?chan_mask_ain2:
                            (channel==1)?chan_mask_ain1:chan_mask_ain0;
    if (ioctl(g_stream_in_file, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stdout, "*** ERROR failed to set channel mask \n");
        return false;
    }
    
    // Channel gain, coupling and current source
    status = InSetGain(channel, gain);
    if (!status)
        return false;

    return true;
}


// initialize the output hardware. Write single values
// to the DAC; no streaming needed. 
// channel: always 0 for DT7837. Assumed to be correct.
bool OutSetHardware(int channel, float freq)
{
    bool status;

    status = SetFreq(g_stream_out_file, freq);
    if (!status)
        return false;

    // No need to set the trigger or channel mask as with InSetHardware()
    // since we're writing single values.
    
    return true;
}


bool OpenFiles()
{
    g_stream_in_file = open(DEV_STREAM_IN, O_RDONLY);
    if (g_stream_in_file < 0)
    {
        fprintf(stdout, "*** ERROR Failed to open analog input stream\n");
        return false;
    }
    
    g_ain_file = open(DEV_AIN, O_RDONLY);
    if (g_ain_file < 0)
    {
        fprintf(stdout, "*** ERROR Failed to open analog input \n");
        return false;
    }

    g_stream_out_file = open(DEV_STREAM_OUT, O_WRONLY);
    if (g_stream_out_file < 0)
    {
        fprintf(stdout, "*** ERROR Failed to open analog output stream\n");
        return false;
    }
    
    g_aout_file = open(DEV_AOUT, O_WRONLY);
    if (g_aout_file < 0)
    {
        fprintf(stdout, "*** ERROR Failed to open analog output \n");
        return false;
    }
    return true;
}


bool CloseFiles()
{
    if (g_ain_file)
        close(g_ain_file);
    if (g_stream_in_file)
        close(g_stream_in_file);
    if (g_aout_file)
        close(g_aout_file);
    if (g_stream_out_file)
        close(g_stream_out_file);
    g_ain_file = 0;
    g_stream_in_file = 0;
    g_aout_file = 0;
    g_stream_out_file = 0;
    return true;
}


// Get a buffer from the stream input containing numSamples.
// Return the average voltage of that buffer.
bool GetBuffer(int num_samples, float *voltage, float gain)
{
    int status;
    int i;
    bool ret = true;
    aio_context_t ctx;   // Asynchronous I/O context
    struct iocb **iocbs = NULL;
    struct io_event *events = NULL;

    // Acquire one buffer. The code is generalized for any number of buffers
    // but here we only use one.
    const int num_buf = 1;

    // allocation events to read asynchronous completion
    events = malloc(sizeof(struct io_event) * num_buf);
    if (!events)
    {
        fprintf(stdout, "*** ERROR Failed to malloc event\n");
        ret = false;
        goto Finish;
    }

    // Create the asynchronous IO context
    ctx = 0;
    status = io_setup(num_buf, &ctx); 
    if (status < 0)
    {
        fprintf(stdout, "*** ERROR Failed io_setup for async I/O\n");
        ret = false;
        goto Finish;
    }

    // allocate an array of IO control blocks for AIO operation
    iocbs = allocate_iocbs(0, num_buf, num_samples);
    if (!iocbs)
    {
        fprintf(stdout, "*** ERROR Failed to malloc iocbs for async I/O\n");
        ret = false;
        goto Finish;
    }

    // submit our request
    int blocks_done = 0;
    
    status = io_submit(ctx, num_buf, iocbs);
    if (status != num_buf) 
    {
        fprintf(stdout, "*** ERROR: Failed io_submit (%d) for async I/O\n", 
                status);
        ret = false;
        goto Finish;
    }

    // arm and trigger acquisition
    status = ioctl(g_stream_in_file, IOCTL_ARM_SUBSYS, 0);   
    if (status)
    {
        fprintf(stdout, "*** ERROR Failed to arm acquisition\n");
        ret = false;
        goto Finish;
    }
    status = ioctl(g_stream_in_file, IOCTL_START_SUBSYS, 0);
    if (status)
    {
        fprintf(stdout, "*** ERROR Failed to trigger acquisition\n");
        ret = false;
        goto Finish;
    }
	
    // wait for acquisition to complete
    struct iocb *p = NULL;
    while (blocks_done != num_buf)
    {
        // <TBD> set timeout value here
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 0; 
        ret = io_getevents(ctx, 1, num_buf, events, &ts);
        if (ret == 0)   // aio not complete yet
            continue;

        if (ret < 0)   // if ctrl-C is hit and the wait interrupted
        {
            // this should not happen. Report an error
            fprintf(stderr, "*** ERROR io_getevent failed (%d) \n", ret);
            ret = false;
            goto Finish;
        }

        // process completed block.
        ++blocks_done;
        p = (struct iocb *)events[0].obj;

        if (events[0].res2 != 0) 
        {
            fprintf(stdout, "*** ERROR event res2 error (%d) \n", 
                    (int)(events[0].res2));
            ret = false;
            goto Finish;
        }
        if (p->aio_data != events[0].data)
        {
            fprintf(stdout, "*** ERROR wrong aio data value (%d, %d)\n", 
                    (int)(p->aio_data), (int)(events[0].data));
            ret = false;
            goto Finish;
        }
    }

    // stop the acquisition engine
    ioctl(g_stream_in_file, IOCTL_STOP_SUBSYS, 0);    

    // if we got here, there's nothing to clean up 'cause everything went well
    // Compute the average voltage.
    int32_t *raw = (int32_t *)p->aio_buf;
    float v = 0;
    for (i = 0; i < num_samples; ++i, ++raw)
        v += raw2volts(*raw, gain);
    *voltage = v / num_samples;

Finish : 
    if (events)
        free(events);
    if (iocbs)
        free_iocbs(iocbs, num_buf);
    io_destroy(ctx);

    return true;
}


// Get a buffer from the stream input containing numSamples.
// This buffer contains contents from all four channels.
// Return the average voltage of each channel from the buffer.
bool GetFourBuffer(int num_samples, float *voltages, int gain)
{
    int status;
    int i;
    bool ret = true;
    aio_context_t ctx;   // Asynchronous I/O context
    struct iocb **iocbs = NULL;
    struct io_event *events = NULL;
    int total_samples = num_samples * NUM_AIN;

    // Acquire one buffer. The code is generalized for any number of buffers
    // but here we only use one. The one buffer will contain data from all 
    // four channels.
    const int num_buf = 1;

    // allocation events to read asynchronous completion
    events = malloc(sizeof(struct io_event) * num_buf);
    if (!events)
    {
        fprintf(stdout, "*** ERROR Failed to malloc event\n");
        ret = false;
        goto Finish;
    }

    // Create the asynchronous IO context
    ctx = 0;
    status = io_setup(num_buf, &ctx); 
    if (status < 0)
    {
        fprintf(stdout, "*** ERROR Failed io_setup for async I/O\n");
        ret = false;
        goto Finish;
    }

    // allocate an array of IO control blocks for AIO operation
    iocbs = allocate_iocbs(0, num_buf, total_samples);
    if (!iocbs)
    {
        fprintf(stdout, "*** ERROR Failed to malloc iocbs for async I/O\n");
        ret = false;
        goto Finish;
    }

    // submit our request
    int blocks_done = 0;
    
    status = io_submit(ctx, num_buf, iocbs);
    if (status != num_buf) 
    {
        fprintf(stdout, "*** ERROR: Failed io_submit (%d) for async I/O\n", 
                status);
        ret = false;
        goto Finish;
    }

    // arm and trigger acquisition
    status = ioctl(g_stream_in_file, IOCTL_ARM_SUBSYS, 0);   
    if (status)
    {
        fprintf(stdout, "*** ERROR Failed to arm acquisition\n");
        ret = false;
        goto Finish;
    }
    int simultaneous = 0;   // not simultaneous start
    status = ioctl(g_stream_in_file, IOCTL_START_SUBSYS, &simultaneous);
    if (status)
    {
        fprintf(stdout, "*** ERROR Failed to trigger acquisition\n");
        ret = false;
        goto Finish;
    }
	
    // wait for acquisition to complete
    struct iocb *p = NULL;
    while (blocks_done != num_buf)
    {
        // <TBD> set timeout value here
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 0; 
        ret = io_getevents(ctx, 1, num_buf, events, &ts);
        if (ret == 0)   // aio not complete yet
            continue;

        if (ret < 0)   // if ctrl-C is hit and the wait interrupted
        {
            // this should not happen. Report an error
            fprintf(stderr, "*** ERROR io_getevent failed (%d) \n", ret);
            ret = false;
            goto Finish;
        }

        // process completed block.
        ++blocks_done;
        p = (struct iocb *)events[0].obj;

        if (events[0].res2 != 0) 
        {
            fprintf(stdout, "*** ERROR event res2 error (%d) \n", 
                    (int)(events[0].res2));
            ret = false;
            goto Finish;
        }
        if (p->aio_data != events[0].data)
        {
            fprintf(stdout, "*** ERROR wrong aio data value (%d, %d)\n", 
                    (int)(p->aio_data), (int)(events[0].data));
            ret = false;
            goto Finish;
        }
    }

    // stop the acquisition engine
    ioctl(g_stream_in_file, IOCTL_STOP_SUBSYS, 0);    

#ifdef DEBUG_DATA
    // for debug only
    // write the entire buffer out to a file
    FILE * fstuff;
    fstuff = fopen("/home/caldata.txt", "a");
    fprintf(fstuff, "----start----\n");
    uint32_t *tmp = (uint32_t *)p->aio_buf;
    for (i = 0; i < num_samples; i++)
        fprintf(fstuff, "%d, %d, %d, %d \n", *tmp++, *tmp++, *tmp++, *tmp++);
    fprintf(fstuff, "----stop----\n");
    fclose(fstuff);
#endif

    // if we got here, there's nothing to clean up 'cause everything went well
    // Compute the average voltages.
    int j;
    for (j = 0; j < NUM_AIN; j++)
    {
        int32_t *raw = (int32_t *)p->aio_buf + j;
        float v = 0;
        for (i = 0; i < num_samples; ++i, raw += NUM_AIN)
            v += raw2volts(*raw, gain);
        voltages[j] = v / num_samples;
    }

Finish : 
    if (events)
        free(events);
    if (iocbs)
        free_iocbs(iocbs, num_buf);
    io_destroy(ctx);

    return true;
}


bool SetValue(float tvolt)
{
    int status;
    uint32_t raw;

    raw = volts2raw(tvolt, 1);
    status = write(g_aout_file, (void*)(&raw), sizeof(raw));
    if (status != sizeof(raw))
    {
        fprintf(stdout, "*** ERROR failed to write voltage to DAC; errno=%d, status=%d\n", 
                errno, status);
        return false;
    }
    return true;
}


// Generic function that waits for 'C' to continue
// Note that this function does not allow the user to bail out.
// At the point where this is used, the user has already had
// the option to cancel the operation.
void WaitForC()
{
    while (true)
    {
        char c = getchar();
        while(getchar() != '\n')
            ;
        if ((c == 'c') || (c == 'C'))
            break;
    }
}


// Write a pot value for a particular channel to its wiper. 
// Return true if successful.
// Note - no error parameter error checking
bool WriteCalWiper(int fd, int channel, int pot, int value)
{
    dt78xx_cal_pot_t cal;
    int cmd = IOCTL_GAIN_POT_WIPER_SET;   // default to gain pot

    if (pot == OFFSET_POT)
        cmd = IOCTL_OFFSET_POT_WIPER_SET;   // override to offset pot

    // use ioctl to write wiper.
    cal.pot = channel;
    cal.value = value;
    if (ioctl(fd, cmd, &cal))
    {
        fprintf(stdout, "*** ERROR writing calibration pot wiper to driver\n");
        return false;
    }

    return true;
}


// Write a pot value for a particular channel to eeprom. 
// Writing to Factory register is not allowed!
// Return true if successful.
bool WriteCalEeprom(int fd, int channel, int pot, int reg, int slot, int value)
{
    dt78xx_cal_pot_t cal;
    int cmd = IOCTL_GAIN_POT_SET;   // default to gain pot

    // only for use with "user" register (unless in Factory mode)
    if ((reg != USER_CAL_REG) && (!g_factory))
    {
        fprintf(stdout, "*** ERROR WriteCalEeprom() invalid target = %d\n", reg);
        return false;
    }

    if (pot == OFFSET_POT)
        cmd = IOCTL_OFFSET_POT_SET;   // override to offset pot

    // use ioctl to write cal to eeprom.
    cal.pot = channel;
    cal.value = value;
    cal.cal.factory = (reg == FACTORY_CAL_REG) ? 1 : 0;
    cal.cal.reg = slot;
    if (ioctl(fd, cmd, &cal))
    {
        fprintf(stdout, "*** ERROR writing calibration pot eeprom to driver\n");
        return false;
    }
    usleep(I2C_WRITE_USLEEP);
    return true;
}


// Read a pot value for a particular channel from eeprom. 
// Reading from user and factory register is allowed.
// Return true if successful.
bool ReadCalEeprom(int fd, int channel, int pot, int reg, int slot, int *value)
{
    dt78xx_cal_pot_t cal;
    int cmd = IOCTL_GAIN_POT_GET;   // default to gain pot

    // only for use with "user" or "factory" register
    if ((reg != USER_CAL_REG) && (reg != FACTORY_CAL_REG))
    {
        fprintf(stdout, "*** ERROR ReadCalEeprom() invalid target = %d\n", reg);
        return false;
    }

    if (pot == OFFSET_POT)
        cmd = IOCTL_OFFSET_POT_GET;   // override to offset pot

    // use ioctl to read cal from eeprom.
    cal.pot = channel;
    cal.value = 0;
    cal.cal.factory = (reg == FACTORY_CAL_REG) ? 1 : 0;
    cal.cal.reg = slot;
    if (ioctl(fd, cmd, &cal))
    {
        fprintf(stdout, "*** ERROR writing calibration pot eeprom from driver\n");
        return false;
    }

    *value = cal.value;
    return true;
}


// Calibration function for a single pot for a single channel.
// This function handles one pot at a time (either offset or gain).
// Calibration ends with the best possible pot value (for minimum error).
// There is no pass/fail; no error margin to calibrate to.
bool AinCalibrateOnePot(int inChannel,   // 0-3
                        int inTestPot,   // 0 (offset) or 1 (gain)
                        int inSlot,      // 0-3
                        float inGain,    // 1 or 10
                        float inTestVoltage)
{
    bool status;
    float voltage;
    bool polarity;
    float currentError = 0;       
    int potValue = CAL_STARTING_VAL;   // the current pot value to use
    int potInc = CAL_STARTING_VAL;   // increment to pot value for each pass
    int i;
    bool potSlope;
    	
    // Do sanity check - check both ends of the pot's range. If the target voltage
    // does not lie to between the two ends, it's impossible to calibrate this pot.
    float min_voltage = 0;
    float max_voltage = 0;
    status = WriteCalWiper(g_ain_file, inChannel, inTestPot, CAL_POT_MIN);
    if (!status)
        return false;
                
    status = GetBuffer(NUM_SAMPLES_AVG, &min_voltage, inGain);
    if (!status)
        return false;

    status = WriteCalWiper(g_ain_file, inChannel, inTestPot, CAL_POT_MAX);
    if (!status)
        return false;
                
    status = GetBuffer(NUM_SAMPLES_AVG, &max_voltage, inGain);
    if (!status)
        return false;

    if (((inTestVoltage < min_voltage) && (inTestVoltage < max_voltage)) ||
        ((inTestVoltage > min_voltage) && (inTestVoltage > max_voltage)))
    {
        fprintf(stdout, "*** ERROR %s calibration is unreachable\n", 
                (inTestPot == 0) ? "offset" : "gain");
        fprintf(stdout, "   min possible V=%f, max possible V=%f, target=%f\n", 
                min_voltage, max_voltage, inTestVoltage);
        return false;
    }

    // On this board, the slope is different between offset and gain pot
    potSlope = (inTestPot == OFFSET_POT) ? true : false;

    // There are different ways to do the cal. Here we simply start from the middle pot
    // value and divide and conquer.
    for (i = 0; i < EEPOT_RES; i++)
    {
        status = WriteCalWiper(g_ain_file, inChannel, inTestPot, potValue);
        if (!status)
            return false;
                
        status = GetBuffer(NUM_SAMPLES_AVG, &voltage, inGain);
        if (!status)
            return false;

        currentError = inTestVoltage - voltage;

        // calculating the "polarity", slope dependent 
        polarity = (currentError > 0) ? true : false; 
        if (potSlope)
            polarity = !polarity;

        // adjust by half pot previous value.
        potInc /= 2;

        if (polarity)
            potValue -= potInc;
        else
            potValue += potInc;
    }

    // The divide-and-conquer algorithm, while simple, does not always give
    // the best result by +/-1. So the simple patch is just to check the final 
    // point +/- 1 and use the best result. 
    // There are probably better ways to do this but this is a safe way to 
    // "bolt-on" an independent piece of code to do the job.
    const int FINAL_SIZE = 3;
    int finalPotValue[FINAL_SIZE];

    // Clamp potential bad pot values to min/max.
    finalPotValue[0] = ((potValue - 1) < CAL_POT_MIN) ? 
                       CAL_POT_MIN : (potValue - 1);
    finalPotValue[1] = potValue;
    finalPotValue[2] = ((potValue + 1) > CAL_POT_MAX) ? 
                       CAL_POT_MAX : (potValue + 1);

    float absCurrentError;
    float bestError = DBL_MAX;

    // Set each pot value and read a buffer. Calculate error.
    for (i = 0; i < FINAL_SIZE; i++)
    {
        status = WriteCalWiper(g_ain_file, inChannel, inTestPot, finalPotValue[i]);
        if (!status)
            return false;

        status = GetBuffer(NUM_SAMPLES_AVG, &voltage, inGain);
        if (!status)
            return false;

        currentError = voltage - inTestVoltage;
        absCurrentError = (currentError < 0) ? -currentError : currentError;	
        if (absCurrentError < bestError)
        {
            potValue = finalPotValue[i];
            bestError = absCurrentError;
        }
    }

    // Sanity range check
    if ((potValue < CAL_POT_MIN) || (potValue > CAL_POT_MAX))
        return false;

    // finalize value to registers
    status = WriteCalWiper(g_ain_file, inChannel, inTestPot, potValue);
    if (!status)
        return false;

    status = WriteCalEeprom(g_ain_file, inChannel, inTestPot, 
                            USER_CAL_REG, inSlot, potValue);
    if (!status)
        return false;

    return true;
}


// Calibration function for a single pot for each of the four channels.
// This function handles one pot at a time (either offset or gain).
// Calibration ends with the best possible pot value (for minimum error).
// There is no pass/fail; no error margin to calibrate to.
bool AinCalibrateFourPot(int inTestPot,   // 0 (offset) or 1 (gain)
                         int inSlot,      // 0-3
                         float inGain,    // 1 or 10
                         float inTestVoltage)
{
    bool status;
    float voltage[4];
    bool polarity;
    float currentError = 0;       
    int potValue[] = {CAL_STARTING_VAL, CAL_STARTING_VAL,
                      CAL_STARTING_VAL, CAL_STARTING_VAL}; 
    int potInc = CAL_STARTING_VAL;   // increment to pot value for each pass
    int c, l, p; 
    bool potSlope;

    // Do sanity check - check both ends of the pot's range. If the target voltage
    // does not lie to between the two ends, it's impossible to calibrate this pot.
    float min_voltage[] = {0.0, 0.0, 0.0, 0.0};
    float max_voltage[] = {0.0, 0.0, 0.0, 0.0};

    for (c = 0; c < NUM_AIN; c++)
    {
        status = WriteCalWiper(g_ain_file, c, inTestPot, CAL_POT_MIN);
        if (!status)
            return false;
    }
                
    status = GetFourBuffer(NUM_SAMPLES_AVG, min_voltage, inGain);
    if (!status)
        return false;

    for (c = 0; c < NUM_AIN; c++)
    {
        status = WriteCalWiper(g_ain_file, c, inTestPot, CAL_POT_MAX);
        if (!status)
            return false;
    }
                
    status = GetFourBuffer(NUM_SAMPLES_AVG, max_voltage, inGain);
    if (!status)
        return false;

    bool bUnreachable = false;
    for (c = 0; c < NUM_AIN; c++)
    {
        if (((inTestVoltage < min_voltage[c]) && (inTestVoltage < max_voltage[c])) ||
            ((inTestVoltage > min_voltage[c]) && (inTestVoltage > max_voltage[c])))
        {
            fprintf(stdout, "*** ERROR %s calibration is unreachable for channel %d\n", 
                    (inTestPot == 0) ? "offset" : "gain", c);
            fprintf(stdout, "   min possible V=%f, max possible V=%f, target=%f\n", 
                    min_voltage[c], max_voltage[c], inTestVoltage);
            bUnreachable = true;
        }
    }
    if (bUnreachable)
        return false;

    // On this board, the slope is different between offset and gain pot
    potSlope = (inTestPot == OFFSET_POT) ? true : false;

    // There are different ways to do the cal. Here we simply start from the middle pot
    // value and divide and conquer.
    for (p = 0; p < EEPOT_RES; p++)
    {
        for (c = 0; c < NUM_AIN; c++)
        {
            status = WriteCalWiper(g_ain_file, c, inTestPot, potValue[c]);
            if (!status)
                return false;
        }
                
        status = GetFourBuffer(NUM_SAMPLES_AVG, voltage, inGain);
        if (!status)
            return false;

        // adjust by half pot previous value.
        potInc /= 2;

        for (c = 0; c < NUM_AIN; c++)
        {
            currentError = inTestVoltage - voltage[c];

            // calculating the "polarity", slope dependent 
            polarity = (currentError > 0) ? true : false; 
            if (potSlope)
                polarity = !polarity;

            if (polarity)
                potValue[c] -= potInc;
            else
                potValue[c] += potInc;
        }
    }

    // The divide-and-conquer algorithm, while simple, does not always give
    // the best result by +/-1. So the simple patch is just to check the final 
    // point +/- 1 and use the best result. 
    // There are probably better ways to do this but this is a safe way to 
    // "bolt-on" an independent piece of code to do the job.
    const int FINAL_SIZE = 3;
    int finalPotValue[NUM_AIN][FINAL_SIZE];

    for (c = 0; c < NUM_AIN; c++)
    {
        // Clamp potential bad pot values to min/max.
        finalPotValue[c][0] = ((potValue[c] - 1) < CAL_POT_MIN) ? 
                              CAL_POT_MIN : (potValue[c] - 1);
        finalPotValue[c][1] = potValue[c];
        finalPotValue[c][2] = ((potValue[c] + 1) > CAL_POT_MAX) ? 
                              CAL_POT_MAX : (potValue[c] + 1);
    }
    
    float absCurrentError;
    float bestError[] = {DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX};

    // Set each pot value and read a buffer. Calculate error.
    for (l = 0; l < FINAL_SIZE; l++)
    {
        for (c = 0; c < NUM_AIN; c++)
        {
            status = WriteCalWiper(g_ain_file, c, inTestPot, finalPotValue[c][l]);
            if (!status)
                return false;
        }

        status = GetFourBuffer(NUM_SAMPLES_AVG, voltage, inGain);
        if (!status)
            return false;

        for (c = 0; c < NUM_AIN; c++)
        {
            currentError = voltage[c] - inTestVoltage;
            absCurrentError = (currentError < 0) ? -currentError : currentError;	
            if (absCurrentError < bestError[c])
            {
                potValue[c] = finalPotValue[c][l];
                bestError[c] = absCurrentError;
            }
        }
    }

    // Sanity range check
    for (c = 0; c < NUM_AIN; c++)
    {
        if ((potValue[c] < CAL_POT_MIN) || (potValue[c] > CAL_POT_MAX))
            return false;
    }

    // finalize value to registers
    for (c = 0; c < NUM_AIN; c++)
    {
        status = WriteCalWiper(g_ain_file, c, inTestPot, potValue[c]);
        if (!status)
            return false;

        status = WriteCalEeprom(g_ain_file, c, inTestPot, 
                                USER_CAL_REG, inSlot, potValue[c]);
        if (!status)
            return false;

        status = WriteCalEeprom(g_ain_file, c, inTestPot, 
                                FACTORY_CAL_REG, inSlot, potValue[c]);
        if (!status)
            return false;
    }

    return true;
}


char main_ui()
{
    int offset1 = 0;
    int gain1 = 0;
    int offset2 = 0;
    int gain2 = 0;
    int offset3 = 0;
    int gain3 = 0;
    bool s1, s2, s3, s4, s5, s6;
    int i, g;
    int slot;

    // display current pot values for Ain 
    fprintf(stdout, "\n");
    if (g_factory)
    {
        fprintf(stdout, "\t\t*** FACTORY CALIBRATION MODE ***\n\n");
        fprintf(stdout, "\tOnly use this mode to change factory calibration value \n\n");
    }
    fprintf(stdout, "\t\t*** Analog Input Pots ***\n");
    fprintf(stdout, "\tsampling rate:\t -- low --\t -- high --\n");
    fprintf(stdout, "\t\t\tOffset  Gain\tOffset  Gain\n");

    for (i = 0; i < NUM_AIN; i++)
    {
        for (g = 0; g < NUM_INPUT_GAINS; g++)
        {
            // low frequency
            slot = GetAinPotSlot(INPUT_GAIN_VALUES[g], true);
            s1 = ReadCalEeprom(g_ain_file, i, OFFSET_POT, USER_CAL_REG, slot, &offset1);
            s2 = ReadCalEeprom(g_ain_file, i, GAIN_POT, USER_CAL_REG, slot, &gain1);

            // high frequency
            slot = GetAinPotSlot(INPUT_GAIN_VALUES[g], false);
            s3 = ReadCalEeprom(g_ain_file, i, OFFSET_POT, USER_CAL_REG, slot, &offset2);
            s4 = ReadCalEeprom(g_ain_file, i, GAIN_POT, USER_CAL_REG, slot, &gain2);

            if (!s1 || !s2)
                fprintf(stdout, "\tCh %d: Gain=%2d:\t  ???    ??? ", 
                        i, INPUT_GAIN_VALUES[g]);
            else
                fprintf(stdout, "\tCh %d: Gain=%2d:\t  %3d    %3d ", 
                        i, INPUT_GAIN_VALUES[g], offset1, gain1);
            if (!s3 || !s4)
                fprintf(stdout, "\t  ???    ??? \n");
            else
                fprintf(stdout, "\t  %3d    %3d \n", offset2, gain2);
        }
    }

    // display current pot values for Aout 
    fprintf(stdout, "\t\t*** Analog Output Pots ***\n");
    fprintf(stdout, "\trate:\t -- low --\t -- mid --\t -- high --\n");
    fprintf(stdout, "\t\tOffset  Gain\tOffset  Gain\tOffset  Gain\n");
    for (i = 0; i < NUM_AOUT; i++)
    {	
        // low frequency
        s1 = ReadCalEeprom(g_aout_file, i, OFFSET_POT, USER_CAL_REG, 
                           CAL_AOUT_SLOT_LOW, &offset1);
        s2 = ReadCalEeprom(g_aout_file, i, GAIN_POT, USER_CAL_REG, 
                           CAL_AOUT_SLOT_LOW, &gain1);

        // mid frequency
        s3 = ReadCalEeprom(g_aout_file, i, OFFSET_POT, USER_CAL_REG, 
                           CAL_AOUT_SLOT_MID, &offset2);
        s4 = ReadCalEeprom(g_aout_file, i, GAIN_POT, USER_CAL_REG, 
                           CAL_AOUT_SLOT_MID, &gain2);

        // freq frequency
        s5 = ReadCalEeprom(g_aout_file, i, OFFSET_POT, USER_CAL_REG, 
                           CAL_AOUT_SLOT_HIGH, &offset3);
        s6 = ReadCalEeprom(g_aout_file, i, GAIN_POT, USER_CAL_REG, 
                           CAL_AOUT_SLOT_HIGH, &gain3);

        if (!s1 || !s2)
            fprintf(stdout, "\tCh %d:\t  ???    ??? ", i);
        else
            fprintf(stdout, "\tCh %d:\t  %3d    %3d ", i, offset1, gain1);
        if (!s3 || !s4)
            fprintf(stdout, "\t  ???    ??? ");
        else
            fprintf(stdout, "\t  %3d    %3d ", offset2, gain2);
        if (!s5 || !s6)
            fprintf(stdout, "\t  ???    ??? \n");
        else
            fprintf(stdout, "\t  %3d    %3d \n", offset3, gain3);
    }

    // display user menu
    fprintf(stdout, "\n");
    fprintf(stdout, "Select one of the following:\n");
    if (g_factory)
        fprintf(stdout, " 0: Factory calibration for all channels\n");
    fprintf(stdout, " 1: Manually calibrate an analog input channel\n");
    fprintf(stdout, " 2: Manually calibrate an analog output channel\n");
    fprintf(stdout, " 3: Automatically calibrate an analog input channel\n");
    fprintf(stdout, " 4: Restore all analog input factory calibration settings\n");
    fprintf(stdout, " 5: Restore all analog output factory calibration settings\n");
    if (g_factory)
    {
        fprintf(stdout, " I: Reset all analog input calibration values to 255\n");
        fprintf(stdout, " O: Reset all analog output calibration values to 255\n");
    }
    fprintf(stdout, " X: Exit\n");
    fprintf(stdout, "-->");

    // get user selection. Return only the character
    char c = getchar(); 
    while(getchar() != '\n')
        ;
    return c;
}


// return true if the user inputs are good
// return false if the user wants to bail from performing this task
bool manual_ain_ui(int *outChannel, int *outGain, int *outPot, bool *lowFreq)
{
    int chan;
    int gain;
    int pot;
    int rate;
    bool done = false;

    while (!done)
    {
        while (true)
        {
            fprintf(stdout, "Enter Analog Input channel number (0 to 3): ");
            fscanf(stdin, "%d", &chan);
            while(getchar() != '\n')
                ;
            if ((chan < 0) || (chan > 3))
            {
                fprintf(stdout, "Invalid channel. ");
                continue;
            }
            break;
        }

        while (true)
        {
            fprintf(stdout, "Enter Analog Input gain (1 or 10): ");
            fscanf(stdin, "%d", &gain);
            while(getchar() != '\n')
                ;
            if ((gain != 1) && (gain != 10))
            {
                fprintf(stdout, "Invalid gain. ");
            	continue;
            }
            break;
        }

        while (true)
        {
            fprintf(stdout, "Enter '0' for offset, '1' for gain pot: ");
            fscanf(stdin, "%d", &pot);
            while(getchar() != '\n')
                ;
            if ((pot != 0) && (pot != 1))
            {
                fprintf(stdout, "Invalid pot. ");
                continue;
            }
            break;
        }

        while (true)
        {
            fprintf(stdout, "Enter '0' for <= 52734 Hz, '1' for > 52734 Hz: ");
            fscanf(stdin, "%d", &rate);
            while(getchar() != '\n')
                ;
            if ((rate != 0) && (rate != 1))
            {
                fprintf(stdout, "Invalid rate. ");
                continue;
            }
            break;
        }

        fprintf(stdout, "Channel = %d, Gain = %d, Pot = %d, Rate = %d. ",
                chan, gain, pot, rate);
        fprintf(stdout, "Enter Y (ok), N (do-over), X (exit): ");
        char c = getchar();
        while (getchar() != '\n')
            ;
        switch(c)
        {
            case 'x':
            case 'X':
                return false;   // bail out of test
            case 'y':
            case 'Y':
                *outChannel = chan;
                *outGain = gain;
                *outPot = pot;
                *lowFreq = (rate == 0) ? 1 : 0;
                done = true;
                break;
            case 'n':
            case 'N':
            default:   // treat this as a 'n'
                continue;
        }
    }
    return true;
}


// return true if the user inputs are good
// return false if the user wants to bail from performing this task
bool manual_aout_ui(int *outChannel, int *outPot, float *outFrequency)
{
    int chan;
    int pot;
    float frequency;
    bool done = false;

    while (!done)
    {
        // The DT7837 only has one analog output channel so there's no 
        // need for user channel selection
        chan = 0;

        while (true)
        {
            fprintf(stdout, "Enter '0' for offset, '1' for gain pot: ");
            fscanf(stdin, "%d", &pot);
            while(getchar() != '\n')
                ;
            if ((pot != 0) && (pot != 1))
            {
                fprintf(stdout, "Invalid pot. ");
                continue;
            }
            break;
        }

        while (true)
        {
            fprintf(stdout, "Enter sampling frequency between %dHz and %dHz: ",
                             CAL_AOUT_FREQ_MIN, CAL_AOUT_FREQ_MAX);
            fscanf(stdin, "%f", &frequency);
            while(getchar() != '\n')
                ;
            if ((frequency < CAL_AOUT_FREQ_MIN) ||
                (frequency > CAL_AOUT_FREQ_MAX))
            {
                fprintf(stdout, "Invalid frequency. ");
                continue;
            }
            break;
        }

        fprintf(stdout, "Channel = %d, Pot = %d, Rate = %6.0f. ",
                chan, pot, frequency);
        fprintf(stdout, "Enter Y (ok), N (do-over), X (exit): ");
        char c = getchar();
        while (getchar() != '\n')
            ;
        switch(c)
        {
            case 'x':
            case 'X':
                return false;   // bail out of test
            case 'y':
            case 'Y':
                *outChannel = chan;
                *outPot = pot;
                *outFrequency = frequency;
                done = true;
                break;
            case 'n':
            case 'N':
            default:   // treat this as a 'n'
                continue;
        }
    }
    return true;
}


// return true if the user inputs are good
// return false if the user wants to bail from performing this task
bool auto_ain_ui(int *outChannel)
{
    int chan;
    bool done = false;

    while (!done)
    {
        while (true)
        {
            fprintf(stdout, "Enter Analog Input channel number (0 to 3): ");
            fscanf(stdin, "%d", &chan);
            while(getchar() != '\n')
                ;
            if ((chan < 0) || (chan > 3))
            {
                fprintf(stdout, "Invalid channel. ");
                continue;
            }
            break;
        }

        fprintf(stdout, "Channel = %d. Enter Y (ok), N (do-over), X (exit): ", 
                chan);
        char c = getchar();
        while (getchar() != '\n')
            ;
        switch(c)
        {
            case 'x':
            case 'X':
                return false;	// bail out of test
            case 'y':
            case 'Y':
                *outChannel = chan;
                done = true;
                break;
            case 'n':
            case 'N':
            default:	// treat this as a 'n'
                continue;
        }
    }
    return true;
}


// manually calibrate a given channel's pot. Input parameters are
// channel number (0-3), gain (1, 10), pot (0=offset, 1=gain), frequency (low, high)
bool manual_ain_cal(int chan, int gain, int pot, bool lowFreq)
{
    bool done = false;
    bool status;
    float voltage;
    float tvolt;   // target voltage
    int potvalue;   // the one the user is changing manually
    int v;
    int slot = GetAinPotSlot(gain, lowFreq);

    status = InSetHardware(chan, gain,
                         lowFreq ? CAL_AIN_FREQ_LOW : CAL_AIN_FREQ_HIGH);
    if (!status)
        return false;

    // have user set the input voltage
    if (pot == OFFSET_POT)
    {
        tvolt = TEST_V_OFFSET;
        fprintf(stdout, "Set input voltage on channel %d to %1.4fV (short). 'C' to continue: ",
                chan, tvolt);
    }
    else
    {   // gain pot
        tvolt = TEST_V_FULLSCALE_1 / gain;
        fprintf(stdout, "Set input voltage on channel %d to %1.4fV. 'C' to continue: ",
                chan, tvolt); 
    }
    WaitForC();

    // get the current pot value from user register
    status = ReadCalEeprom(g_ain_file, chan, pot, USER_CAL_REG, slot, &potvalue);
    if (!status)
        return false;

    fprintf(stdout, "\n");
    fprintf(stdout, "Enter '+', '-', or 0-255 to adjust pot; 'x' to exit\n");
    while (!done)
    {
        // write wiper and get a buffer. Scale voltage reading by gain
        status = WriteCalWiper(g_ain_file, chan, pot, potvalue);
        if (!status)
       	    return false;
        GetBuffer(NUM_SAMPLES_AVG, &voltage, gain);
        fprintf(stdout, "Ch %d: gain %d: %s pot = %d: target = %1.4fV: reading = %1.4fV\n",
                chan, (int)gain, (pot == 0) ? "offset" : "gain", potvalue, tvolt, voltage);

        // Get user input 
        char s[100];
        fscanf(stdin, "%s", s);
        char c = s[0];
        while (getchar() != '\n')
			;
        switch (c)
        {   // check first character for simple up/down
            case '-':
                // decrement if possible
                if (potvalue > CAL_POT_MIN)
                    --potvalue;
                break;
            case '+':
                // increment if possible
                if (potvalue < CAL_POT_MAX)
                    potvalue++;
                break;
            case 'x':
            case 'X':
                done = true;
                break;
                // check input string for number
            default:
                // treat this as a pot number. Clamp to pot range
                sscanf(s, "%d", &v); 
                potvalue = v;
                if (potvalue < CAL_POT_MIN)
                    potvalue = CAL_POT_MIN;
                else if (potvalue > CAL_POT_MAX)
                    potvalue = CAL_POT_MAX;
                break;   // ignore input
        }
    }

    // update user value and close up shop. The wiper already has the correct
    // value set.
    status = WriteCalEeprom(g_ain_file, chan, pot, USER_CAL_REG, slot, potvalue);
    if (!status)
        return false;
    return true;
}


bool manual_aout_cal_user_adjust(float tvolt, int chan, int pot, int slot, 
                                 int *outpotvalue)
{
    bool done = false;
    bool status;
    int v;
    int potvalue = 0;

    // Set the output voltage 
    status = SetValue(tvolt);
    if (!status)
        return false;

    // get the current pot value from user register
    status = ReadCalEeprom(g_aout_file, chan, pot, USER_CAL_REG, slot, &potvalue);
    if (!status)
        return false;

    fprintf(stdout, "\n");
    fprintf(stdout, "Enter '+', '-', or 0-255 to adjust pot; 'x' to exit\n");
    while (!done)
    {
        // write wiper and write a value to the DAC. 
        status = WriteCalWiper(g_aout_file, chan, pot, potvalue);
        if (!status)
       	    return false;

        fprintf(stdout, "Ch %d: target = %1.4fV: %s pot = %d \n",
                chan, tvolt, (pot == 0) ? "offset" : "gain", potvalue);

        // Get user input 
        char s[100];
        fscanf(stdin, "%s", s);
        char c = s[0];
        while (getchar() != '\n')
			;
        switch (c)
        {   // check first character for simple up/down
            case '-':
                // decrement if possible
                if (potvalue > CAL_POT_MIN)
                    --potvalue;
                break;
            case '+':
                // increment if possible
                if (potvalue < CAL_POT_MAX)
                    potvalue++;
                break;
            case 'x':
            case 'X':
                done = true;
                break;
                // check input string for number
            default:
                // treat this as a pot number. Clamp to pot range
                sscanf(s, "%d", &v); 
                potvalue = v;
                if (potvalue < CAL_POT_MIN)
                    potvalue = CAL_POT_MIN;
                else if (potvalue > CAL_POT_MAX)
                    potvalue = CAL_POT_MAX;
                break;   // ignore input
        }
    }
    // update user value and close up shop. The wiper already has the correct
    // value set.
    status = WriteCalEeprom(g_aout_file, chan, pot, USER_CAL_REG, slot, potvalue);
    if (!status)
        return false;

    // return final pot value
    *outpotvalue = potvalue;
    return true;
}


// Mannually calibrate an analog output channel. There is no automatic
// calibration for DACs. The DT7837 only has one output channel but
// we still pass a channel number for future versions of this code.
// channel number (0), pot (0=offset, 1=gain), frequency (30-216KHz)
bool manual_aout_cal(int chan, int pot, float frequency)
{
    bool status;
    float tvolt;   // target voltage
    int potvalue;   // the one the user is changing manually

    int slot = GetAoutPotSlot(frequency);

    status = OutSetHardware(chan, frequency);
    if (!status)
        return false;

    // tell user what voltage to look for 
    if (pot == OFFSET_POT)
        tvolt = TEST_V_OFFSET;
    else
        tvolt = TEST_V_FULLSCALE_1;
    fprintf(stdout, "Connect DMM to output. The target voltage is %1.4fV. 'C' to continue: ", 
            tvolt);
    WaitForC();

    status = manual_aout_cal_user_adjust(tvolt, chan, pot, slot, &potvalue);
    if (!status)
        return false;

    return true;
}


// Auto calibrate one AD channel. There are 8 pots to calibrate - one offset
// and one gain pot for each of the two gain settings (1, 10) and two
// frequency bands (low, high).  The calibration frequencies are in the 
// middle of each band. 
// The offset pot calibration is made with 0V on the input. The gain pot 
// calibration is made with 9.375V and 0.9375V on the input (channel
// gain of 1 and 10 respectively). 
// The user is responsible for providing an accurate input voltage reference.
bool auto_ain_cal(int inChannel)
{
    int status;
    int i, f;
    int slot;

    status = InSetHardware(inChannel, INPUT_GAIN_VALUES[0], 100000); // dummy frequency 
    if (!status)
        return false;

    // User sets input to 0V for Offset calibration
    fprintf(stdout, "Set input voltage on channel %d to %1.4fV (short). 'C' to continue: ",
            inChannel, TEST_V_OFFSET);
    WaitForC();

    for (i = 0; i < NUM_INPUT_GAINS; i++)
    {
        // Setup the gain
        status =  InSetGain(inChannel, INPUT_GAIN_VALUES[i]);
        if (!status)
            return false;

        for (f = 0; f < NUM_AIN_FREQ; f++)
        {
            status = SetFreq(g_stream_in_file, AIN_FREQS[f]);
            if (!status)
                return false;

            slot = GetAinPotSlot(INPUT_GAIN_VALUES[i], LOW_FREQ_BOOL[f]);
            status = AinCalibrateOnePot(inChannel, 
                                        OFFSET_POT, 
                                        slot, 
                                        INPUT_GAIN_VALUES[i],
                                        0);
            if (!status)
                return false;
        }
    }

    for (i = 0; i < NUM_INPUT_GAINS; i++)
    {
        // User sets input for full-scale calibration. The voltage depends 
        // on the gain.
        fprintf(stdout, "Set input voltage on channel %d to %1.4fV. 'C' to continue: ",
                inChannel, GAIN_FS_VOLTAGE[i]);
        WaitForC();

        status = InSetGain(inChannel, INPUT_GAIN_VALUES[i]);
        if (!status)
            return false;

        for (f = 0; f < NUM_AIN_FREQ; f++)
        {
            status = SetFreq(g_stream_in_file, AIN_FREQS[f]);
            if (!status)
                return false;

            slot = GetAinPotSlot(INPUT_GAIN_VALUES[i], LOW_FREQ_BOOL[f]);
            status = AinCalibrateOnePot(inChannel, 
                                        GAIN_POT, 
                                        slot, 
                                        INPUT_GAIN_VALUES[i],
                                        GAIN_FS_VOLTAGE[i]);
            if (!status)
                return false;
        }
    }
    return true;
}


// Auto calibrate all (4) analog input channels at once.
// There are 8 pots to calibrate - one offset and one gain pot for each
// of the two gain settings (1, 10) and two frequency bands (low, high).
// The calibration frequencies are in the middle of each band.
// The offset pot calibration is made with 0V on the input. The gain pot 
// calibration is made with 9.375V and 0.9375V on the input (channel
// gain of 1 and 10 respectively). 
bool factory_ain_cal()
{
    int status;
    int c, g, f;   // channel, gain and frequency
    int slot;

    status = SetFreq(g_stream_in_file, 100000); //dummy frequency
    if (!status)
        return false;

    // configure for software trigger
    dt78xx_trig_config_t trig_cfg;
    trig_cfg.src = trig_src_sw;
    if (ioctl(g_stream_in_file, IOCTL_START_TRIG_CFG_SET, &trig_cfg))
    {
        fprintf(stdout, "*** ERROR failed to set software trigger \n");
        return false;
    }

    // write channel mask
    chan_mask_t chan_mask = 0;
    for (c = 0; c < NUM_AIN; c++)
        chan_mask |= 1 << c;
    if (ioctl(g_stream_in_file, IOCTL_CHAN_MASK_SET, &chan_mask))
    {
        fprintf(stdout, "*** ERROR failed to set channel mask \n");
        return false;
    }

    // Offset cal
    fprintf(stdout, "Connect all inputs together and to the voltage source\n");
    fprintf(stdout, "Set input voltage to %1.4fV (short). 'C' to continue: ",
            TEST_V_OFFSET);
    WaitForC();

    for (g = 0; g < NUM_INPUT_GAINS; g++)
    {
        // set gain, coupling and current source. 
        for (c = 0; c < NUM_AIN; c++)
        {
            status = InSetGain(c, INPUT_GAIN_VALUES[g]);
            if (!status)
                return false;
        }

        for (f = 0; f < NUM_AIN_FREQ; f++)
        {
            status = SetFreq(g_stream_in_file, AIN_FREQS[f]);
            if (!status)
                return false;

            slot = GetAinPotSlot(INPUT_GAIN_VALUES[g], LOW_FREQ_BOOL[f]);
            status = AinCalibrateFourPot(OFFSET_POT, 
                                         slot, 
                                         INPUT_GAIN_VALUES[g],
                                         0);
            if (!status)
                return false;
        }
    }

    // Gain cal
    for (g = 0; g < NUM_INPUT_GAINS; g++)
    {
        // User sets input for full-scale calibration. The voltage depends 
        // on the gain.
        fprintf(stdout, "Set input voltage to %1.4fV. 'C' to continue: ",
                GAIN_FS_VOLTAGE[g]);
        WaitForC();

        // set gain, coupling and current source. 
        for (c = 0; c < NUM_AIN; c++)
        {
            status = InSetGain(c, INPUT_GAIN_VALUES[g]);
            if (!status)
                return false;
        }

        for (f = 0; f < NUM_AIN_FREQ; f++)
        {
            status = SetFreq(g_stream_in_file, AIN_FREQS[f]);
            if (!status)
                return false;

            slot = GetAinPotSlot(INPUT_GAIN_VALUES[g], LOW_FREQ_BOOL[f]);
            status = AinCalibrateFourPot(GAIN_POT, 
                                         slot, 
                                         INPUT_GAIN_VALUES[g],
                                         GAIN_FS_VOLTAGE[g]);
            if (!status)
                return false;
        }
    }
    return true;
}


// Auto calibrate all (1) analog output channels.
// There are 6 pots to calibrate - one offset and one gain pot for each
// of the three frequency ranges (low, mid, high).
// The calibration frequencies are in the middle of each band.
// The offset pot calibration is made with 0V on the output. The gain pot 
// calibration is made with 9.375V on the output
// This calibration is not automatic - it requires the user to adjust
// the pot value until the correct output voltage is reached.
bool factory_aout_cal()
{
    int status;
    int chan, f;   // channel and frequency
    int slot;
    int pot;
    int potvalue;

    // only one channel on DT7837
    chan = 0;

    // Offset cal
    fprintf(stdout, "Connect the output to the DMM to measure its voltage \n");
    fprintf(stdout, "For offset pots, the target voltage is %1.4fV. 'C' to continue: ", 
            TEST_V_OFFSET);
    WaitForC();

    pot = OFFSET_POT;
    for (f = 0; f < NUM_AOUT_FREQ; f++)
    {
        fprintf(stdout, "(calibrating for frequency %6.0f, pass %d of %d)", 
                AOUT_FREQS[f], f+1, NUM_AOUT_FREQ);
        status = SetFreq(g_stream_out_file, AOUT_FREQS[f]);
        if (!status)
            return false;

        slot = GetAoutPotSlot(AOUT_FREQS[f]);
        status = manual_aout_cal_user_adjust(TEST_V_OFFSET, chan, pot, slot, &potvalue);
        if (!status)
            return false;

        // The user value is already set. Write the factory value.
        status = WriteCalEeprom(g_aout_file, chan, pot, FACTORY_CAL_REG, slot, potvalue);
        if (!status)
            return false;
    }

    // Gain cal
    fprintf(stdout, "For gain pots, the target voltage is %1.4fV. 'C' to continue: ",
            TEST_V_FULLSCALE_1);
    WaitForC();

    pot = GAIN_POT;
    for (f = 0; f < NUM_AOUT_FREQ; f++)
    {
        fprintf(stdout, "(calibrating for frequency %6.0f, pass %d of %d)", 
                AOUT_FREQS[f], f+1, NUM_AOUT_FREQ);
        status = SetFreq(g_stream_out_file, AOUT_FREQS[f]);
        if (!status)
            return false;

        slot = GetAoutPotSlot(AOUT_FREQS[f]);
        status = manual_aout_cal_user_adjust(TEST_V_FULLSCALE_1, chan, pot, slot, &potvalue);
        if (!status)
            return false;

        // The user value is already set. Write the factory value.
        status = WriteCalEeprom(g_aout_file, chan, pot, FACTORY_CAL_REG, slot, potvalue);
        if (!status)
            return false;
    }

    return true;
}


bool restore_ain_cal()
{
    int status;
    int c, g, p, f, v;
    int slot;

    // loop through each channel
    for (c = 0; c < NUM_AIN; c++)
    {
        // loop through each gain
        for (g = 0; g < NUM_INPUT_GAINS; g++)
        {
            for (f = 0; f < NUM_AIN_FREQ; f++)
            {
                slot = GetAinPotSlot(INPUT_GAIN_VALUES[g], LOW_FREQ_BOOL[f]);
                for (p = 0; p < NUM_POTS; p++)
                {
                    // read pot from factory register and write to user register
                    status = ReadCalEeprom(g_ain_file, c, POT_VALUES[p], 
                                           FACTORY_CAL_REG, slot, &v);
                    if (!status)
                        return false;
                    status = WriteCalEeprom(g_ain_file, c, POT_VALUES[p], 
                                            USER_CAL_REG, slot, v);
                    if (!status)
                        return false;
                }
            }
        }
    }

    // No need to update the wipers with the latest data. That will
    // happen when the next time the gain or frequency is set.
    return true;
}


bool restore_aout_cal()
{
    int status;
    int c, p, v;
    int slot;

    // loop through each channel
    for (c = 0; c < NUM_AOUT; c++)
    {
        for (slot = 0; slot < NUM_AOUT_FREQ; slot++)
        {
            for (p = 0; p < NUM_POTS; p++)
            {
                // read pot from factory register and write to user and wiper registers
                status = ReadCalEeprom(g_aout_file, c, POT_VALUES[p], 
                                       FACTORY_CAL_REG, slot, &v);
                if (!status)
                    return false;
                status = WriteCalEeprom(g_aout_file, c, POT_VALUES[p], 
                                        USER_CAL_REG, slot, v);
                if (!status)
               	    return false;
            }
        }
    }
    return true;
}


// This is primarily a tool for diagnostics and testing use.
// restore all cal pots in AIN subsystem to 255
bool reset_ain_cal()
{
    int status;
    int c, g, p, f;
    int slot;

    // loop through each channel
    for (c = 0; c < NUM_AIN; c++)
    {
        // loop through each gain
        for (g = 0; g < NUM_INPUT_GAINS; g++)
        {
            for (f = 0; f < NUM_AIN_FREQ; f++)
            {
                slot = GetAinPotSlot(INPUT_GAIN_VALUES[g], LOW_FREQ_BOOL[f]);
                for (p = 0; p < NUM_POTS; p++)
                {
                    // write to the factory register
                    status = WriteCalEeprom(g_ain_file, c, POT_VALUES[p], 
                                            FACTORY_CAL_REG, slot, 
                                            CAL_POT_RESET);
                    if (!status)
                        return false;

                    // write to the user register
                    status = WriteCalEeprom(g_ain_file, c, POT_VALUES[p], 
                                            USER_CAL_REG, slot, 
                                            CAL_POT_RESET);
                    if (!status)
                        return false;

                    // write to the wiper
                    status = WriteCalWiper(g_ain_file, c, POT_VALUES[p],
                                           CAL_POT_RESET);
                }
            }
        }
    }

    // No need to update the wipers with the latest data. That will
    // happen when the next time the gain or frequency is set.
    return true;
}


// This is primarily a tool for diagnostics and testing use.
// restore all cal pots in AOUT subsystem to 255
bool reset_aout_cal()
{
    int status;
    int c, p;
    int slot;

    // loop through each channel
    for (c = 0; c < NUM_AOUT; c++)
    {
        for (slot = 0; slot < NUM_AOUT_FREQ; slot++)
        {    
            for (p = 0; p < NUM_POTS; p++)
            {
                // write to the factory register
                status = WriteCalEeprom(g_aout_file, c, POT_VALUES[p], 
                                        FACTORY_CAL_REG, slot, 
                                        CAL_POT_RESET);
                if (!status)
                    return false;

                // write to the user register
                status = WriteCalEeprom(g_aout_file, c, POT_VALUES[p], 
                                        USER_CAL_REG, slot, 
                                        CAL_POT_RESET);
                if (!status)
                    return false;

                // write to the wiper
                status = WriteCalWiper(g_aout_file, c, POT_VALUES[p],
                                       CAL_POT_RESET);
            }
        }
    }

    // No need to update the wipers with the latest data. That will
    // happen when the next time the gain or frequency is set.
    return true;
}


int main(int argc, char ** argv)
{
    char sel;   // user selection
    int chan;
    int gain;
    int pot;
    bool lowFreq;
    bool status;
    bool done = false;
    float frequency;

    g_ain_file = 0;
    g_stream_in_file = 0;
    g_aout_file = 0;
    g_stream_out_file = 0;

    // Set up ctrl-C handler to terminate infinite wait in io_getevents()
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);

    // Open the hardware device and then initialize the hardware 
    status = OpenFiles();
    if (!status)
        return false;

    // parse input options
    int opt;
    while ((opt = getopt(argc, argv, "F")) != -1)
    {
        switch(opt)
        {
            case 'F':
                g_factory = true;
                break;
            default:
                break;
        }
    }

    while (! done)
    {
        // display UI, get user selection
        sel = main_ui();

        // perform user selection
        switch(sel)
        {
            case '0':
                if (g_factory)
                {
                    fprintf(stdout, "Factory calibration for analog input channels\n");
                    factory_ain_cal();
                    fprintf(stdout, "Factory calibration for analog output channels\n");
                    factory_aout_cal();
                    break;
                }
            case '1':
                fprintf(stdout, "Manual Analog Input Calibration\n");
                status = manual_ain_ui(&chan, &gain, &pot, &lowFreq);
                if (!status)
                    break;
                manual_ain_cal(chan, gain, pot, lowFreq);
                break;
            case '2':
                fprintf(stdout, "Manual Analog Output Calibration\n");
                status = manual_aout_ui(&chan, &pot, &frequency);
                if (!status)
                    break;
                manual_aout_cal(chan, pot, frequency); 
                break;
            case '3':
                fprintf(stdout, "Automatic Analog Input Calibration\n");
                status = auto_ain_ui(&chan);
                if (!status)
                    break;
                auto_ain_cal(chan);
                break;
            case '4':
                fprintf(stdout, "Restore Factory Analog Input Calibration Values...");
                restore_ain_cal();
                fprintf(stdout, "done\n");
                break;
            case '5':
                fprintf(stdout, "Restore Factory Analog Output Calibration Values...");
                restore_aout_cal();
                fprintf(stdout, "done\n");
                break;
            case 'I':
                fprintf(stdout, "Reset all analog input calibration values to 255...\n");
                reset_ain_cal();
                fprintf(stdout, "done\n");
                break;
            case 'O':
                fprintf(stdout, "Reset all analog output calibration values to 255...\n");
                reset_aout_cal();
                fprintf(stdout, "done\n");
                break;
            case 'x':
            case 'X':
                fprintf(stdout, "Calibration done. Have nice day\n");
                done = true;
                break;
            default:
                // do nothing
                break;
        }
    }

    // if there are file handles open, close them
    CloseFiles();
    return 0;
}

