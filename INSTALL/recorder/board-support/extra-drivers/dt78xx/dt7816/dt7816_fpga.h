#ifndef _DT7816_FPGA_
#define _DT7816_FPGA_
/*
 * FPGA register definition for DT7816. 
 * 
 *  (C) Copyright (c) 2015 Data Translation Inc
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
#ifdef  __cplusplus
extern "C"
{
#endif
#include "dt78xx.h"

#ifndef U8_MAX
#define U8_MAX      ((u8)(~0U))
#endif
#ifndef U16_MAX
#define U16_MAX     ((u16)(~0U))
#endif
#ifndef U32_MAX
#define U32_MAX     ((u32)(~0U))    
#endif
    
#define FPGA_REG_LEN_BITS   (16)    //FPGA register width
#define NUM_DIN             (8)     //Number of digital inputs
#define NUM_DOUT            (8)     //Number of digital outputs         
#define NUM_AIN             (8)     //Number of analog inputs         
#define NUM_AOUT            (2)     //Number of analog outputs    
#define AD_CLK_HZ_MIN       (100.0f)    
#define AD_CLK_HZ_MAX       (400000.0f)    
#define DA_CLK_HZ_MIN       (1.0f)    
#define DA_CLK_HZ_MAX       (400000.0f)    
    
#ifndef _BIT_DEFINED_
#define _BIT_DEFINED_
#define BIT0    (u16)(1<<0)
#define BIT1    (u16)(1<<1)
#define BIT2    (u16)(1<<2)
#define BIT3    (u16)(1<<3)
#define BIT4    (u16)(1<<4)
#define BIT5    (u16)(1<<5)
#define BIT6    (u16)(1<<6)
#define BIT7    (u16)(1<<7)
#define BIT8    (u16)(1<<8)
#define BIT9    (u16)(1<<9)
#define BIT10   (u16)(1<<10)
#define BIT11   (u16)(1<<11)
#define BIT12   (u16)(1<<12)
#define BIT13   (u16)(1<<13)
#define BIT14   (u16)(1<<14)
#define BIT15   (u16)(1<<15)
#endif    
    
#define FPGA_REG_TAB \
    FPGA_REG(IN_CTRL,       0x0000) \
    FPGA_REG(IN_CLK_LO,     0x0006) \
    FPGA_REG(IN_CLK_HI,     0x0008) \
    FPGA_REG(IN_MASK,       0x000c) \
    FPGA_REG(THOLD1_TRIG,   0x0010) \
    FPGA_REG(IN_STAT,       0x0034) \
    FPGA_REG(IN_FIFO_CTRL1, 0x0040) \
    FPGA_REG(IN_FIFO_CTRL2, 0x0042) \
    FPGA_REG(TACH_CTR_CTRL, 0x0200) \
    FPGA_REG(MSR_CTR_CTRL,  0x0204) \
    FPGA_REG(CT_PERIOD_LO,  0x0220) \
    FPGA_REG(CT_PERIOD_HI,  0x0222) \
    FPGA_REG(CT_PULSE_LO,   0x0224) \
    FPGA_REG(CT_PULSE_HI,   0x0226) \
    FPGA_REG(CT_CTRL,       0x0228) \
    FPGA_REG(CT_COUNT_LO,   0x022C) \
    FPGA_REG(CT_COUNT_HI,   0x022E) \
    FPGA_REG(CT_INTR_STAT,  0x0230) \
    FPGA_REG(CT_INTR_MASK,  0x0232) \
    FPGA_REG(OUT_CTRL,      0x0400) \
    FPGA_REG(OUT_CLK_LO,    0x0406) \
    FPGA_REG(OUT_CLK_HI,    0x0408) \
    FPGA_REG(DA_CFG_LO,     0x0480) \
    FPGA_REG(DA_CFG_HI,     0x0482) \
    FPGA_REG(OUT_MASK,      0x0500) \
    FPGA_REG(OUT_STAT,      0x0514) \
    FPGA_REG(OUT_FIFO_CTRL, 0x0520) \
    FPGA_REG(IO_CTRL,       0x0600) \
    FPGA_REG(TRIG_CTRL,     0x0602) \
    FPGA_REG(INTR_MASK,     0x0620) \
    FPGA_REG(INTR_STAT,     0x0622) \
    FPGA_REG(DMA_STAT,      0x0626) \
    FPGA_REG(DIN,           0x0800) \
    FPGA_REG(DIN_GPIO1,     0x0900) \
    FPGA_REG(DIN_GPIO2,     0x0902) \
    FPGA_REG(DIN_GPIO3,     0x0904) \
    FPGA_REG(DOUT,          0x0a00) \
    FPGA_REG(DOUT_GPIO1,    0x0b00) \
    FPGA_REG(DOUT_GPIO2,    0x0b02) \
    FPGA_REG(EVNT_OUT_CTRL, 0x0C00) \
    FPGA_REG(DEBUG,         0x8000) \
    FPGA_REG(LED,           0x8002) \
    FPGA_REG(VERSION,       0xA000) 
    
//FPGA register offset enumeration

#define FPGA_REG(a,b)   FPGA_REG_##a=b,
typedef enum
{
    FPGA_REG_TAB
}fpga_reg_t;

#undef FPGA_REG

/*****************************************************************************
 * Input Subsystem Control Register
 * FPGA_REG_IN_CTRL      0x000
 */
#define MASK_IN_CTRL_RESET      (BIT15)
#define MASK_IN_CTRL_RANGE_WR   (BIT12)
#define MASK_IN_CTRL_CLK_EN     (BIT3)
#define MASK_IN_CTRL_EXT_CLK_INV (BIT2)
#define MASK_IN_CTRL_EXT_CLK    (BIT0)

/*****************************************************************************
 * InputChannelMask
 * FPGA_REG_IN_MASK  0x000C
 */
#define MASK_IN_MASK_DIN     (BIT11)
#define MASK_IN_MASK_MSR_CTR (BIT10)
#define MASK_IN_MASK_CT      (BIT9)
#define MASK_IN_MASK_TACH    (BIT8)
#define MASK_IN_MASK_AIN7    (BIT7)
#define MASK_IN_MASK_AIN6    (BIT6)
#define MASK_IN_MASK_AIN5    (BIT5)
#define MASK_IN_MASK_AIN4    (BIT4)
#define MASK_IN_MASK_AIN3    (BIT3)
#define MASK_IN_MASK_AIN2    (BIT2)
#define MASK_IN_MASK_AIN1    (BIT1)
#define MASK_IN_MASK_AIN0    (BIT0)

/*****************************************************************************
 * Threshold1Control
 * FPGA_REG_THOLD1_TRIG  0x0010
 */
#define MASK_THOLD1_TRIG_SRC     (BIT14 | BIT13 | BIT12)
#define SHIFT_THOLD1_TRIG_SRC    (12)
#define MASK_THOLD1_TRIG_LVL     ((BIT10)-1)
#define SHIFT_THOLD1_TRIG_LVL    (0)

static inline int32_t threshold_2_twos_comp(uint16_t offbin)
{
    offbin <<=6; //shift bits 9:0 t most significant 10-bits
    return (offbin ^ SHRT_MIN);
}
static inline int16_t twos_comp_2_threshold(int32_t twoscomp)
{
    twoscomp ^= 0xffff8000;
    return ((twoscomp & USHRT_MAX)>>6); //shift ms 10-bits to bits 9:0
}
/*****************************************************************************
 * InputStatus
 * FPGA_REG_IN_STAT       0x0034
 */
#define MASK_IN_STAT_FIFO_FULL  (BIT2)
#define MASK_IN_STAT_FIFO_EMPTY (BIT1)
#define MASK_IN_STAT_ACTIVE     (BIT0)

/*****************************************************************************
 * InputFifoCtrl1
 * FPGA_REG_IN_FIFO_CTRL1  0x0040
 */
#define MASK_IN_FIFO_CTRL1_RESET     (BIT0)

/*****************************************************************************
 * InputFifoCtrl2
 * FPGA_REG_IN_FIFO_CTRL2  0x0042
 */
#define MASK_IN_FIFO_CTRL2_AEPONT     ((BIT14)-1)

/*****************************************************************************
 FPGA_REG_TACH_CTR_CTRL     0x0200
 */
#define MASK_TACH_CTR_CTRL_EDGE_SEL  (BIT3)
#define SHIFT_TACH_CTR_CTRL_EDGE_SEL (3)
#define MASK_TACH_CTR_CTRL_SCLR      (BIT1)
#define SHIFT_TACH_CTR_CTRL_SCLR     (1)
#define MASK_TACH_CTR_CTRL_STALE     (BIT0)
#define SHIFT_TACH_CTR_CTRL_STALE    (0)

/*****************************************************************************
 FPGA_REG_MSR_CTR_CTRL     0x0204
 */
#define MASK_MSR_CTR_CTRL_STOP_SEL  (BIT11|BIT10|BIT9|BIT8)
#define SHIFT_MSR_CTR_CTRL_STOP_SEL (8)
#define MASK_MSR_CTR_CTRL_START_SEL  (BIT7|BIT6|BIT5|BIT4)
#define SHIFT_MSR_CTR_CTRL_START_SEL (4)
#define MASK_MSR_CTR_CTRL_SCLR   (BIT1)
#define MASK_MSR_CTR_CTRL_STALE  (BIT0)

/* Definition of the 4-bits in MASK_MSR_CTR_CTRL_STOP_SEL, 
 * MASK_MSR_CTR_CTRL_START_SEL, F=falling edge, R=rising edge */
#define MSR_CTR_CTRL_TACH_F     (0)
#define MSR_CTR_CTRL_TACH_R     (BIT0)
#define MSR_CTR_CTRL_DIN_F      (BIT1)
#define MSR_CTR_CTRL_DIN_R      (BIT1 | BIT0)
#define MSR_CTR_CTRL_ADC_DONE   (BIT3)

/*****************************************************************************
 FPGA_REG_CT_CTRL    0x0228
 */
#define MASK_CT_CTRL_MCLR        (BIT15)
#define MASK_CT_CTRL_MTRIG       (BIT14)
#define MASK_CT_CTRL_MSTOP       (BIT13 | BIT12)
#define SHIFT_CT_CTRL_MSTOP      (12)
#define MASK_CT_CTRL_MSTART      (BIT11 | BIT10)
#define SHIFT_CT_CTRL_MSTART     (10)
#define MASK_CT_CTRL_POL         (BIT8)
#define MASK_CT_CTRL_MODE        (BIT6 | BIT5 | BIT4)
#define MASK_CT_CTRL_GATE        (BIT3 | BIT2)
#define MASK_CT_CTRL_CLK         (BIT1 | BIT0)

#define CT_CTRL_MODE_IDLE        (0)
#define CT_CTRL_MODE_1SHOT       (BIT4)
#define CT_CTRL_MODE_DIVIDER     (BIT6 | BIT5)
#define CT_CTRL_MODE_COUNTER     (BIT5)

#define CT_CTRL_MODE_GATE_OFF       (0)
#define CT_CTRL_MODE_GATE_SW        (BIT2)
#define CT_CTRL_MODE_GATE_EXT       (BIT3)
#define CT_CTRL_MODE_GATE_EXT_INV   (BIT3 | BIT2)

#define CT_CTRL_MODE_CLK_EXT        (BIT0)
#define CT_CTRL_MODE_CLK_INT        (0)

#define CT_CTRL_MODE_OUT_POL_HI     (BIT8)

/*****************************************************************************
FPGA_REG_CT_INTR_STAT   0x0230
 */
#define MASK_CT_INTR_STAT_OVRFLO         (BIT0)
#define MASK_CT_INTR_STAT_COMPLT         (BIT1)

/*****************************************************************************
 * OutputControl  
 * FPGA_REG_OUT_CTRL  0x400
 */
#define MASK_OUT_CTRL_CFG_WR        (BIT12)
#define MASK_OUT_CTRL_BUSY          (BIT9)
#define MASK_OUT_CTRL_PRELOAD       (BIT8)
#define MASK_OUT_CTRL_FIFO_PRIME    (BIT7)
#define MASK_OUT_CTRL_CLK_EN        (BIT3)
#define MASK_OUT_CTRL_EXT_CLK_INV   (BIT2)
#define MASK_OUT_CTRL_EXT_CLK       (BIT0)

/*****************************************************************************
 FPGA_REG_OUT_MASK       0x500
 */
#define MASK_OUT_MASK_DOUT      (BIT2)
#define MASK_OUT_MASK_AOUT1     (BIT1)
#define MASK_OUT_MASK_AOUT0     (BIT0)

/*****************************************************************************
 * OutputStatus
 * FPGA_REG_OUT_STAT      0x0514
 */
#define MASK_OUT_STAT_FIFO_FULL  (BIT2)
#define MASK_OUT_STAT_FIFO_EMPTY (BIT1)
#define MASK_OUT_STAT_ACTIVE     (BIT0)

/*****************************************************************************
 * OutputFifoCtrl
 * FPGA_REG_OUT_FIFO_CTRL 0x0520
 */
#define MASK_OUT_FIFO_CTRL_RST     (BIT0)

/*****************************************************************************
 * IOOpControl
 * FPGA_REG_IO_CTRL     0x600
 */
#define MASK_IO_CTRL_REF_CLK_RST (BIT12)
#define MASK_IO_CTRL_OUT_SW_TRIG (BIT3)
#define MASK_IO_CTRL_OUT_ARM     (BIT2)
#define MASK_IO_CTRL_IN_SW_TRIG  (BIT1)
#define MASK_IO_CTRL_IN_ARM      (BIT0)

/*****************************************************************************
 * TriggerControl
 * FPGA_REG_TRIG_CTRL   0x602
 */
#define MASK_TRIG_CTRL_OUT_START    (BIT11 |BIT10 | BIT9 | BIT8)
#define SHIFT_TRIG_CTRL_OUT_START   (8)
#define MASK_TRIG_CTRL_IN_START     (BIT3 | BIT2 | BIT1 | BIT0)
#define SHIFT_TRIG_CTRL_IN_START    (0)
//MASK_TRIG_CTRL_IN_START and MASK_TRIG_CTRL_OUT_START bit definitions after
//being shifted right SHIFT_TRIG_CTRL_IN_START/SHIFT_TRIG_CTRL_OUT_START
#define TRIG_CTRL_SW                (0)
#define TRIG_CTRL_EXT_FALLING       (BIT2)
#define TRIG_CTRL_EXT_RISING        (BIT2 | BIT0)
#define TRIG_CTRL_THOLD_FALLING     (BIT3)
#define TRIG_CTRL_THOLD_RISING      (BIT3 | BIT0)

/*****************************************************************************
 FPGA_REG_INTR_STAT   0x622
 */
#define MASK_INTR_STAT_REF_CLK_OK   (BIT15)
#define MASK_INTR_STAT_OUT_UNDRFL   (BIT6)
#define MASK_INTR_STAT_OUT_DONE     (BIT5)
#define MASK_INTR_STAT_OUT_TRIG     (BIT4)
#define MASK_INTR_STAT_IN_COMPLETE  (BIT2)
#define MASK_INTR_STAT_IN_TRIG      (BIT1)
#define MASK_INTR_STAT_IN_OVRFL     (BIT0)

/*****************************************************************************
 * DMARequestStatus
 * FPGA_REG_DMA_STAT      0x0626
 */
#define MASK_DMA_STAT_CLR2     (BIT2)
#define MASK_DMA_STAT_CLR1     (BIT1)

/*****************************************************************************
 * GPIOInMap1
 * FPGA_REG_DIN_GPIO1   0x0900
 */
#define MASK_DIN_GPIO1_IN_CLK_EN    (BIT11)
#define MASK_DIN_GPIO1_IN_CLK       (BIT10 | BIT9 | BIT8)
#define SHIFT_DIN_GPIO1_IN_CLK      (8)
#define MASK_DIN_GPIO1_IN_TRIG1_EN  (BIT3)
#define MASK_DIN_GPIO1_IN_TRIG1     (BIT2 | BIT1 | BIT0)
#define SHIFT_DIN_GPIO1_IN_TRIG1    (0)

/*****************************************************************************
 FPGA_REG_DIN_GPIO2   0x0902
 */
#define MASK_DIN_GPIO2_OUT_CLK_EN   (BIT7)
#define MASK_DIN_GPIO2_OUT_CLK      (BIT6 | BIT5 | BIT4)
#define SHIFT_DIN_GPIO2_OUT_CLK     (4)
#define MASK_DIN_GPIO2_OUT_TRIG_EN  (BIT3)
#define MASK_DIN_GPIO2_OUT_TRIG     (BIT2 | BIT1 | BIT0)
#define SHIFT_DIN_GPIO2_OUT_TRIG    (0)

/*****************************************************************************
 FPGA_REG_DIN_GPIO3   0x0904
 */
#define MASK_DIN_GPIO3_CT_GATE_EN   (BIT15)
#define MASK_DIN_GPIO3_CT_GATE      (BIT14 | BIT13 | BIT12)
#define SHIFT_DIN_GPIO3_CT_GATE     (12)

#define MASK_DIN_GPIO3_CT_CLK_EN    (BIT11)
#define MASK_DIN_GPIO3_CT_CLK       (BIT10 | BIT9 | BIT8)
#define SHIFT_DIN_GPIO3_CT_CLK      (8)

#define MASK_DIN_GPIO3_MSR_CTR_EDGE2_EN (BIT7)
#define MASK_DIN_GPIO3_MSR_CTR_EDGE2    (BIT6 | BIT5 | BIT4)
#define SHIFT_DIN_GPIO3_MSR_CTR_EDGE2   (4)

#define MASK_DIN_GPIO3_MSR_CTR_EDGE1_EN (BIT3)
#define MASK_DIN_GPIO3_MSR_CTR_EDGE1    (BIT2 | BIT1 | BIT0)
#define SHIFT_DIN_GPIO3_MSR_CTR_EDGE1   (0)

/*****************************************************************************
 * DigitalOutput
 * FPGA_REG_DOUT          0x0a00
 */
#define MASK_DOUT_SRC   (BIT8)
#define MASK_DOUT       (BIT8-1)

/*****************************************************************************
 FPGA_REG_DOUT_GPIO1    0x0b00  Configures DOUT3:0 source
 FPGA_REG_DOUT_GPIO2    0x0b02  Configures DOUT7:4 source
 Each DOUT configuration mode requires 4-bit mask
 */
#define DOUT_GPIO_MODE_DOUT     (0x0)
#define DOUT_GPIO_MODE_CT       (0x1)

#define MASK_DOUT_GPIO_MODE(dout, mode)  \
    (u16)(((mode)&0x7) << (((dout) & 0x3)*4))

/*****************************************************************************
 FPGA_REG_LED   0x8002
 */
#define MASK_LED_ENABLE             (BIT8)

/*****************************************************************************/
static inline int __must_check is_input_armed(struct device *dev)
{
    uint16_t reg;
    reg = dt78xx_fpga_read(dev, FPGA_REG_IO_CTRL);
    return ((reg & MASK_IO_CTRL_IN_ARM)?-EBUSY:0);
}

static inline int __must_check is_input_active(struct device *dev)
{
    uint16_t reg;
    reg = dt78xx_fpga_read(dev, FPGA_REG_IN_STAT);
    return ((reg & MASK_IN_STAT_ACTIVE)?-EBUSY:0);
}

static inline int __must_check is_output_armed(struct device *dev)
{
    uint16_t reg;
    reg = dt78xx_fpga_read(dev, FPGA_REG_IO_CTRL);
    return ((reg & MASK_IO_CTRL_OUT_ARM)?-EBUSY:0);
}

static inline int __must_check is_output_active(struct device *dev)
{
    uint16_t reg;
    reg = dt78xx_fpga_read(dev, FPGA_REG_OUT_STAT);
    return ((reg & MASK_OUT_STAT_ACTIVE)?-EBUSY:0);
}

#ifdef  __cplusplus
}
#endif
#endif
