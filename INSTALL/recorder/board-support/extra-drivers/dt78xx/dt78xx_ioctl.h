/*
 *  IOCTLs used to communicate from user application to DT78xx KLM
 *  
 *  (C) Copyright (c) 2014 Data Translation Inc
 *                    www.datatranslation.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed WITHOUT ANY WARRANTY; without the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 */
#ifndef _DT78XX_IOCTL_H_
#define _DT78XX_IOCTL_H_

#ifdef __KERNEL__
#include <linux/ioctl.h>
#include <linux/bug.h>
#else
#include <sys/ioctl.h>
#endif

#ifdef  __cplusplus
/* Must use either -std=c++0x or -std=gnu++0x as compiler flag to enable
 * the g++ static_assert keyword */
#define _ASSERT static_assert
#else
#define _ASSERT _Static_assert
#endif

#ifdef  __cplusplus
extern "C"
{
#endif  
/*****************************************************************************
 *                      IOCTL definitions
 ****************************************************************************/
#define DT78XX_IOCTL            (0xf3)
    
#define AIN_CFG_GET             (2)
#define AIN_CFG_SET             (3)
#define START_TRIG_CFG_GET      (4)
#define START_TRIG_CFG_SET      (5)
#define ARM_SUBSYS              (6)
#define STOP_SUBSYS             (7)
#define START_SUBSYS            (8)
#define CHAN_MASK_GET           (9)
#define CHAN_MASK_SET           (10)
#define SAMPLE_CLK_GET          (11)
#define SAMPLE_CLK_SET          (12)
#define CT_CFG_GET              (13)
#define CT_CFG_SET              (14)
#define GAIN_POT_GET            (15)
#define GAIN_POT_SET            (16)
#define OFFSET_POT_GET          (17)
#define OFFSET_POT_SET          (18)
#define GAIN_POT_WIPER_GET      (19)
#define GAIN_POT_WIPER_SET      (20)
#define OFFSET_POT_WIPER_GET    (21)
#define OFFSET_POT_WIPER_SET    (22)
#define MCTR_CFG_GET            (23)
#define MCTR_CFG_SET            (24) 
#define TACH_CFG_GET            (25)
#define TACH_CFG_SET            (26) 
#define ACQ_STATUS_GET          (27)
#define LED_GET                 (28)
#define LED_SET                 (29)

/*****************************************************************************
 *                      IOCTL data types
 ****************************************************************************/
    
/*****************************************************************************
 Trigger sources specified in dt78xx_trig_config_t
 */
typedef enum
{
    trig_src_sw,            /* software trigger */
    trig_src_ext,           /* Digital input 7:0 */
    trig_src_threshold      /* Analog input threshold */
}trig_src_t;

/*****************************************************************************
 * Trigger configuration for specific trigger sources
 * Used in IOCTL_START_TRIG_CFG_SET, IOCTL_START_TRIG_CFG_GET
 * Note :
 * 1) When analog input is specified as trigger, the threshold for triggering
 * is specified in member 'level' below. This is a two's complement value that
 * must be within the +/- full scale range corresponding to the gain of the
 * selected analog input. Therefore, analog threshold must be configured
 * after configuring the specific analog input channel; IOCTL_START_TRIG_CFG_SET
 * must follow IOCTL_AIN_CFG_SET
 * 2) In the DT7837, the AD is 24-bits. Therefore, the threshold 'level' must
 * be between 0x007fffff to 0x0 and 0xffffffff to 0xff800000 
 * 3) In the DT7816, the AD is 16-bits. Therefore, the threshold 'level' must
 * be between 0x00007fff to 0x0 and 0xffffffff to 0xffff8000 
 */
typedef struct __attribute__ ((__packed__))
{
    trig_src_t  src;
    union
    {
        struct __attribute__ ((__packed__))
        {
            uint16_t    edge_rising; /* 1=rising edge, 0=falling edge */
            uint16_t    din;         /* 0=DIN0,1=DIN1,...,7=DIN7 */
        }ext;
        struct __attribute__ ((__packed__))
        {
            uint16_t    edge_rising; /* 1=rising edge, 0=falling edge */
            uint16_t    ain;         /* 0=AI0,1=AIN1,... */
            int32_t     level;       /* threshold level on ain.  */
        }threshold;
     } src_cfg;
} dt78xx_trig_config_t;

_ASSERT ((sizeof(dt78xx_trig_config_t) == 12), \
                "dt78xx_trig_config_t size bad"); 
    
/*****************************************************************************
 * Configuration for a specific analog input channel.
 * Used in IOCTL_AIN_CFG_SET, IOCTL_AIN_CFG_GET
 */
typedef struct __attribute__ ((__packed__))
{
    uint16_t    ain;    /* 0=AI0,1=AIN1,... */
    uint16_t    gain;   /* 1,10,... */
    uint16_t    ac_coupling; /*Coupling 0=dc, 1=ac */
    uint16_t    current_on;  /*current source 0=off 1=on */ 
    uint16_t    differential;  /* 1= differential input, 0=single ended */
    uint16_t    unused;
} dt78xx_ain_config_t;

_ASSERT ((sizeof(dt78xx_ain_config_t) == 12), \
                "dt78xx_ain_config_t size bad"); 

/*****************************************************************************
 * Channel mask used to enable channels to be sampled and determine channels
 * that are currently enabled in either input or output stream. Each bit in this
 * mask corresponds to a channel as enumerated below.
 * Used in IOCTL_CHAN_MASK_GET, IOCTL_CHAN_MASK_SET
 */
typedef enum
{
    chan_mask_dout7      = (1<<31),     /* output stream */
    chan_mask_dout6      = (1<<30),     /* output stream */
    chan_mask_dout5      = (1<<29),     /* output stream */
    chan_mask_dout4      = (1<<28),     /* output stream */
    chan_mask_dout3      = (1<<27),     /* output stream */
    chan_mask_dout2      = (1<<26),     /* output stream */
    chan_mask_dout1      = (1<<25),     /* output stream */
    chan_mask_dout0      = (1<<24),     /* output stream */
    chan_mask_aout3      = (1<<19),     /* output stream */
    chan_mask_aout2      = (1<<18),     /* output stream */
    chan_mask_aout1      = (1<<17),     /* output stream */
    chan_mask_aout0      = (1<<16),     /* output stream */
                                        /* bit 15:12 reserved */
    chan_mask_din        = (1<<11),     /* input stream */
    chan_mask_meas_ctr   = (1<<10),     /* input stream */
                                        /* bit 9 reserved */
    chan_mask_tach       = (1<<8),      /* input stream */
    chan_mask_ain7       = (1<<7),      /* input stream */
    chan_mask_ain6       = (1<<6),      /* input stream */     
    chan_mask_ain5       = (1<<5),      /* input stream */
    chan_mask_ain4       = (1<<4),      /* input stream */
    chan_mask_ain3       = (1<<3),      /* input stream */
    chan_mask_ain2       = (1<<2),      /* input stream */
    chan_mask_ain1       = (1<<1),      /* input stream */
    chan_mask_ain0       = (1<<0)       /* input stream */
}chan_mask_t;

_ASSERT ((sizeof(chan_mask_t) == 4), \
                "chan_mask_t size bad"); 

/*****************************************************************************
 * Counter timer modes and configuration. These are used in IOCTL_CT_CFG_GET,
 * IOCTL_CT_CFG_SET 
 * 
 * ct_mode_divider : This mode uses the divider struct in dt78xx_ct_config_t.
 * Divides either internal or external clock by the specified
 * number of counts to generate an output clock. The duty cycle of the generated 
 * clock can also be specified. The gate is either none or external (either high
 * or low). External gate and/or external clock uses a user specified DIN bit, 
 * the divided clock is output on a user specified DOUT bit. 
 * 
 * ct_mode_counter : Counts rising edge on the external clock input. The counter
 * can be disabled by software or external gate (either high or low). 
 * External gate uses a user specified DIN bit, 
 * 
 * ct_mode_1shot : This mode uses the one_shot struct in dt78xx_ct_config_t.
 * Divides either internal or external clock by the specified
 * number of counts to generate a one-shot pulse. The duty cycle of the generated 
 * pulse can also be specified. The gate is either none or external (either high
 * or low). External gate and/or external clock uses a user specified DIN bit, 
 * the one-shot pulse is output on a user specified DOUT bit. If the on-shot is
 * retriggerable, it will be re-triggered *after* the pulse period expires in
 * response to a previous trigger. If the one-shot is non-retriggerable, it
 * will generate a single pulse in response to a trigger and ignore all
 * subsequent triggers. 
 * 
 * ct_mode_measure : This mode uses the measure struct in dt78xx_ct_config_t.
 * Measure Mode uses the internal clock to measure the time interval between
 * the selected measure start edge and the selected measure stop edge. Either
 * edge of the external gate or external clock can be independently chosen as 
 * the measure start edge or measure stop edge, providing the ability to measure
 * signal pulse width high, signal pulse width low, signal period and time 
 * interval between 2 signals.
 * Note that the 'gate' and 'ext_clk' are ignored and configured for external
 * inputs on digital inputs specified by 'ext_gate_din' and 'ext_clk_din'
 */
typedef enum
{
    ct_mode_idle,
    ct_mode_1shot, 
    ct_mode_divider, 
    ct_mode_counter,
    ct_mode_measure,
}ct_mode_t;

typedef enum
{
    ct_gate_none,
    ct_gate_ext_hi,    
    ct_gate_ext_lo 
}ct_gate_t;

typedef struct __attribute__ ((__packed__))
{
    ct_mode_t   mode;       /* Counter timer mode */
    ct_gate_t   gate;       /*gate type */
    uint8_t     ext_gate_din; /*DIN bit 7:0 used as ext. gate*/
    uint8_t     ext_clk;      /*0=internal clock, 1=external clock */
    uint8_t     ext_clk_din;  /* DIN bit 7:0 used as external clock input */
    uint8_t     unused;
    union
    {
        //used for ct_mode_divider
        struct __attribute__ ((__packed__))
        {
            uint32_t    period;       /*Number of input clock cycles in one
                                       period of output clock*/
            uint32_t    pulse;        /*Number of input clock cycles when
                                        output clock is active; must be less 
                                        than period*/
            uint8_t     out;          /*DOUT bit 7:0 used as output clock */
            uint8_t     out_hi;       /*1=out high active, 0=out low active*/
        }divider;  
        //used for ct_mode_1shot
        struct __attribute__ ((__packed__))
        {
            uint32_t    period;       /*Number of input clock cycles in one
                                        period of output pulse*/
            uint32_t    pulse;        /*Number of input clock cycles when
                                        output pulse is active; must be less 
                                        than period*/
            uint8_t     out;           /*Output generated on DOUT bit 7:0 */
            uint8_t     out_hi;        /*1=out high active, 0=out low active*/
            uint8_t     retriggerable; /*0=not retriggerable, 1=retriggerable*/
        }one_shot;   
    };
}dt78xx_ct_config_t;

/*****************************************************************************
 * Registers and data structures used to read and write the calibration
 * potentiometers using IOCTL_GAIN_POT_GET/SET, IOCTL_OFFSET_POT_GET/SET and
 * IOCTL_GAIN_POT_WIPER_GET/SET, IOCTL_OFFSET_POT_WIPER_GET/SET.
 */

typedef struct __attribute__ ((__packed__))
{
    int         pot; /* channel number; 0 through max. channels in subsystem */
    uint32_t    value; /* value written or read back */
    /* Factory or user calibration parameters. Not used for wipers */
    struct
    {
        int      factory; /* Calibration type, 1=factory, 0=user*/
        uint32_t reg;     /* Calibration register */
    }cal;
}dt78xx_cal_pot_t;

/*****************************************************************************
 * Measure counter configuration. These are used in 
 * IOCTL_MCTR_CFG_GET, IOCTL_MCTR_CFG_SET
 *
 * mctr_sel_t : these are the different selections that can be 
 * used to start and stop the counter. "falling" and "rising" refers
 * to the edges of those signals.
 *
 * stale_flg : this is the MSB of the count. When enabled for use, the 
 * stale bit is set to '1' when the reading is stale. When disabled, the
 * MSB is always 0. The measure counter is 31 bits wide.
 */
typedef enum
{
    mctr_sel_adc_complete = 0x00,
    mctr_sel_tach_falling = 0x10,
    mctr_sel_tach_rising = 0x11,
    mctr_sel_din0_falling = 0x20,
    mctr_sel_din0_rising = 0x21,
    mctr_sel_din1_falling = 0x22,
    mctr_sel_din1_rising = 0x23,
    mctr_sel_din2_falling = 0x24,
    mctr_sel_din2_rising = 0x25,
    mctr_sel_din3_falling = 0x26,
    mctr_sel_din3_rising = 0x27,
    mctr_sel_din4_falling = 0x28,
    mctr_sel_din4_rising = 0x29,
    mctr_sel_din5_falling = 0x2a,
    mctr_sel_din5_rising = 0x2b,
    mctr_sel_din6_falling = 0x2c,
    mctr_sel_din6_rising = 0x2d,
    mctr_sel_din7_falling = 0x2e,
    mctr_sel_din7_rising = 0x2f,
} mctr_sel_t;

typedef struct __attribute__ ((__packed__))
{
    mctr_sel_t   start_sel;    /* what starts measurement */
    mctr_sel_t   stop_sel;     /* what stops measurement */
    uint8_t      stale_flag;   /* 0=not used, 1=used */
} dt78xx_mctr_config_t;

/*****************************************************************************
 * Tachometer configuration. These are used in 
 * IOCTL_TACH_CFG_GET, IOCTL_TACH_CFG_SET
 *
 * edge_rising : select either the rising or falling edge to make measurements.
 *
 * stale_flg : this is the MSB of the count. When enabled for use, the 
 * stale bit is set to '1' when the reading is stale. When disabled, the
 * MSB is always 0. The measure counter is 31 bits wide.
 */
typedef struct __attribute__ ((__packed__))
{
    uint8_t   edge_rising;  /* 0=falling, 1=rising edge */
    uint8_t   stale_flag;   /* 0=not used, 1=used */
} dt78xx_tach_config_t;

/*****************************************************************************
 * Acquisition status. This is a bit mask returned by IOCTL_ACQ_STATUS_GET.
 * A bit is set when the corresponding status condition is true.
 */
typedef enum
{
    acq_status_armed     = 0x1, /* armed */
    acq_status_triggered = 0x2, /* triggered and active */ 
    acq_status_fifo_empty = 0x04,/* FIFO empty */
    acq_status_fifo_full = 0x08,/* FIFO full */
}acq_status_t;

/*****************************************************************************
 * LED state. These are used in 
 * IOCTL_LED_GET, IOCTL_LED_SET
 *
 */
typedef struct __attribute__ ((__packed__))
{
    uint8_t   mask;    /* 0=keep as-is, 1=modify. Used in SET only */
    uint8_t   state;   /* 0=LED off, 1=LED on */
} dt78xx_led_t;

/*****************************************************************************
 * Structure used in IOCTL_SAMPLE_CLK_SET/GET to set/get the sampling clock
 * of either AD or DA subsystem.
 * Notes : 
 *  (a) The rangle for clk_freq is board dependent
 *  (b) For boards that don't support external clock source, ext_clk and 
 *      ext_clk_din are ignored
 *  (c) If ext_clk is 0 (i.e internal clock source), ext_clk_din is ignored
 *  (d) clk_freq is used to set internal clock frequency
 */
typedef struct __attribute__ ((__packed__))
{
    uint8_t     ext_clk;      /* 0=internal clock, 1=external clock 
                                 2= external clock inverted */
    uint8_t     ext_clk_din;  /* DIN bit 7:0 used as external clock input */
    uint8_t     unused[2];
    float       clk_freq;     /* Clock frequency in Hz*/
} dt78xx_clk_config_t;

/*****************************************************************************
 *                      List of IOCTLs
 ****************************************************************************/

/*****************************************************************************
 *  IOCTL command to arm a subsystem
 *  Input :
 *      Reserved for future use
 *  Return :
 *      0 = success; subsytem was armed
 *     <0 = failure
 */
#define IOCTL_ARM_SUBSYS  \
            _IOW(DT78XX_IOCTL, ARM_SUBSYS, int)
    
/*****************************************************************************
 *  IOCTL command to stop a subsystem
 *  Input :
 *      Reserved for future use
 *  Return :
 *      0 = success; subsytem has been stopped
 *     <0 = failure
 */
#define IOCTL_STOP_SUBSYS   \
            _IOW(DT78XX_IOCTL, STOP_SUBSYS, int)
    
/*****************************************************************************
 *  IOCTL command to set start trigger configuration
 *  Input :
 *      Pointer to ioctl_trig_config_t with members initialized
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_START_TRIG_CFG_SET   \
            _IOW(DT78XX_IOCTL, START_TRIG_CFG_SET, dt78xx_trig_config_t)
    
/*****************************************************************************
 *  IOCTL command to get start trigger configuration
 *  Input :
 *      Pointer to ioctl_trig_config_t 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_START_TRIG_CFG_GET   \
            _IOR(DT78XX_IOCTL, START_TRIG_CFG_GET, dt78xx_trig_config_t)
    
/*****************************************************************************
 *  IOCTL command to start a subsystem, specifically if it uses software
 *  trigger or gate
 *  Input :
 *      Default is NULL. If not-null, pointer to uint32_t. Value dependent upon 
 *      subsystem as listed below.
 *      Input stream : Non-zero value will trigger this and output stream
 *      Output stream : Non-zero value will trigger this and input stream
 *      Counter-Timer : not used
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_START_SUBSYS   \
            _IOW(DT78XX_IOCTL, START_SUBSYS, uint32_t)
    
/*****************************************************************************
 *  IOCTL command to get AIN configuration
 *  Input :
 *      Pointer to dt78xx_ain_config_t with member ain initialized
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_AIN_CFG_GET   \
            _IOWR(DT78XX_IOCTL, AIN_CFG_GET, dt78xx_ain_config_t)
    
/*****************************************************************************
 *  IOCTL command to set AIN configuration
 *  Input :
 *      Pointer to dt78xx_ain_config_t with all members initialized
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_AIN_CFG_SET   \
            _IOW(DT78XX_IOCTL, AIN_CFG_SET, dt78xx_ain_config_t)
           
/*****************************************************************************
 *  IOCTL command to get stream channel mask 
 *  Input :
 *      Pointer to chan_mask_t 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_CHAN_MASK_GET   \
            _IOR(DT78XX_IOCTL, CHAN_MASK_GET, chan_mask_t)
    
/*****************************************************************************
 *  IOCTL command to Set stream channel mask 
 *  Input :
 *      Pointer to chan_mask_t 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_CHAN_MASK_SET   \
            _IOW(DT78XX_IOCTL, CHAN_MASK_SET, chan_mask_t)

/*****************************************************************************
 *  IOCTL command to get the sampling clock configuration
 *  Input :
 *      Pointer to dt78xx_clk_config_t
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_SAMPLE_CLK_GET   \
            _IOR(DT78XX_IOCTL, SAMPLE_CLK_GET, dt78xx_clk_config_t)

/*****************************************************************************
 *  IOCTL command to set the sampling clock configuration
 *  Input :
 *      Pointer to dt78xx_clk_config_t. On success, the actual configuration is
 *       returned here
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_SAMPLE_CLK_SET   \
            _IOWR(DT78XX_IOCTL, SAMPLE_CLK_SET, dt78xx_clk_config_t)

/*****************************************************************************
 *  IOCTL command to get the counter timer configuration
 *  Input :
 *      Pointer to dt78xx_ct_config_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_CT_CFG_GET   \
            _IOR(DT78XX_IOCTL, CT_CFG_GET, dt78xx_ct_config_t)

/*****************************************************************************
 *  IOCTL command to set the counter timer configuration
 *  Input :
 *      Pointer to dt78xx_ct_config_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_CT_CFG_SET   \
            _IOW(DT78XX_IOCTL, CT_CFG_SET, dt78xx_ct_config_t)

/*****************************************************************************
 *  IOCTL command to get the measure counter configuration
 *  Input :
 *      Pointer to dt78xx_mctr_config_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_MCTR_CFG_GET   \
            _IOR(DT78XX_IOCTL, MCTR_CFG_GET, dt78xx_mctr_config_t)

/*****************************************************************************
 *  IOCTL command to set the measure counter configuration
 *  Input :
 *      Pointer to dt78xx_mctr_config_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_MCTR_CFG_SET   \
            _IOW(DT78XX_IOCTL, MCTR_CFG_SET, dt78xx_mctr_config_t)

/*****************************************************************************
 *  IOCTL command to get the value in a specific potentiometer used for
 *  offset calibration
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot and reg initialized. The
 *      value of the specified potentiometer's register will be returned in the
 *      structure's value member.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_OFFSET_POT_GET   \
            _IOWR(DT78XX_IOCTL, OFFSET_POT_GET, dt78xx_cal_pot_t)

/*****************************************************************************
 *  IOCTL command to set the value in a specific potentiometer used for
 *  offset calibration
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot, reg and value initialized.
 *      The specified potentiometer's register will be written with the
 *      structure's value member.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_OFFSET_POT_SET   \
            _IOW(DT78XX_IOCTL, OFFSET_POT_SET, dt78xx_cal_pot_t)

/*****************************************************************************
 *  IOCTL command to get the value in a specific potentiometer used for
 *  gain calibration
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot and reg initialized. The
 *      value of the specified potentiometer's register will be returned in the
 *      structure's value member.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_GAIN_POT_GET   \
            _IOWR(DT78XX_IOCTL, GAIN_POT_GET, dt78xx_cal_pot_t)


/*****************************************************************************
 *  IOCTL command to set the value in a specific potentiometer used for
 *  gain calibration
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot, reg and value initialized.
 *      The specified potentiometer's register will be written with the
 *      structure's value member. NOTE : This operation will block for at least
 *      5ms.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_GAIN_POT_SET   \
            _IOW(DT78XX_IOCTL, GAIN_POT_SET, dt78xx_cal_pot_t)

/*****************************************************************************
 * IOCTL command to read the wiper for a channel in a specific gain calibration
 * potentiometer
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot initialized.
 *      The specified potentiometer's wiper value will be returned in the
 *      structure's value member.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_GAIN_POT_WIPER_GET   \
            _IOWR(DT78XX_IOCTL, GAIN_POT_WIPER_GET, dt78xx_cal_pot_t)

/*****************************************************************************
 * IOCTL command to set the wiper for a channel in a specific gain calibration
 * potentiometer
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot, and value initialized.
 *      The specified potentiometer's wiper will be written with the
 *      structure's value member.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_GAIN_POT_WIPER_SET   \
            _IOW(DT78XX_IOCTL, GAIN_POT_WIPER_SET, dt78xx_cal_pot_t)

/*****************************************************************************
 * IOCTL command to read the wiper for a channel in a specific offset calibration
 * potentiometer
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot initialized.
 *      The specified potentiometer's wiper value will be returned in the
 *      structure's value member.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_OFFSET_POT_WIPER_GET   \
            _IOWR(DT78XX_IOCTL, OFFSET_POT_WIPER_GET, dt78xx_cal_pot_t)

/*****************************************************************************
 * IOCTL command to set the wiper for a channel in a specific offset calibration
 * potentiometer
 *  Input :
 *      Pointer to dt78xx_cal_pot_t with members pot, and value initialized.
 *      The specified potentiometer's wiper will be written with the
 *      structure's value member.
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_OFFSET_POT_WIPER_SET   \
            _IOW(DT78XX_IOCTL, OFFSET_POT_WIPER_SET, dt78xx_cal_pot_t)

/*****************************************************************************
 *  IOCTL command to get the tachometer configuration
 *  Input :
 *      Pointer to dt78xx_tach_config_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_TACH_CFG_GET   \
            _IOR(DT78XX_IOCTL, TACH_CFG_GET, dt78xx_tach_config_t)

/*****************************************************************************
 *  IOCTL command to set the tachometer configuration
 *  Input :
 *      Pointer to dt78xx_tach_config_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_TACH_CFG_SET   \
            _IOW(DT78XX_IOCTL, TACH_CFG_SET, dt78xx_tach_config_t)

/*****************************************************************************
 *  IOCTL command to get the acquisition status
 *  Input :
 *      Pointer to acq_status_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_ACQ_STATUS_GET   \
            _IOR(DT78XX_IOCTL, ACQ_STATUS_GET, acq_status_t)

/*****************************************************************************
 *  IOCTL command to get the state of the board's LEDs 
 *  Input :
 *      Pointer to dt78xx_led_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_LED_GET   \
            _IOR(DT78XX_IOCTL, LED_GET, dt78xx_led_t)

/*****************************************************************************
 *  IOCTL command to set the state of the board's LEDs
 *  Input :
 *      Pointer to dt78xx_led_t. 
 *  Return :
 *      0 = success
 *     <0 = failure
 */
#define IOCTL_LED_SET   \
            _IOW(DT78XX_IOCTL, LED_SET, dt78xx_led_t)

#ifdef  __cplusplus
}
#endif

#endif //_DT78XX_IOCTL_H_
