#ifndef _DT7837_FPGA_
#define _DT7837_FPGA_
/*
 * FPGA register definition for DT7837. 
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
#define AD_RES_BITS         (24)
#define DA_RES_BITS         (24)
#define NUM_DIN             (8)     //Number of digital inputs
#define NUM_DOUT            (8)     //Number of digital outputs         
#define NUM_AIN             (4)     //Number of analog inputs         
    
#ifndef _BIT_DEFINED_
#define _BIT_DEFINED_
#define BIT0    (1<<0)
#define BIT1    (1<<1)
#define BIT2    (1<<2)
#define BIT3    (1<<3)
#define BIT4    (1<<4)
#define BIT5    (1<<5)
#define BIT6    (1<<6)
#define BIT7    (1<<7)
#define BIT8    (1<<8)
#define BIT9    (1<<9)
#define BIT10   (1<<10)
#define BIT11   (1<<11)
#define BIT12   (1<<12)
#define BIT13   (1<<13)
#define BIT14   (1<<14)
#define BIT15   (1<<15)
#endif    
    
#define FPGA_REG_TAB \
    FPGA_REG(IN_CTRL,       0x0000) \
    FPGA_REG(IN_SETUP0,     0x0004) \
    FPGA_REG(IN_SETUP1,     0x0006) \
    FPGA_REG(IN_SETUP2,     0x0008) \
    FPGA_REG(IN_MASK,       0x000c) \
    FPGA_REG(THOLD_TRIG_LVL,0x0010) \
    FPGA_REG(THOLD_TRIG_SEL,0x0014) \
    FPGA_REG(REC_LEN_LO,    0x0018) \
    FPGA_REG(REC_LEN_HI,    0x001A) \
    FPGA_REG(REC_COUNT,     0x001C) \
    FPGA_REG(TRIG_COUNT_LO, 0x0020) \
    FPGA_REG(TRIG_COUNT_HI, 0x0022) \
    FPGA_REG(TRIG_DLY_LO,   0x0024) \
    FPGA_REG(TRIG_DLY_HI,   0x0026) \
    FPGA_REG(RETRIG_DLY_LO, 0x0028) \
    FPGA_REG(RETRIG_DLY_HI, 0x002A) \
    FPGA_REG(IN_STAT,       0x0034) \
    FPGA_REG(IN_FIFO_STAT,  0x0040) \
    FPGA_REG(IN_FIFO_MASK,  0x0042) \
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
    FPGA_REG(CT_IO_CTRL,    0x0240) \
    FPGA_REG(OUT_CTRL0,     0x0400) \
    FPGA_REG(OUT_CTRL1,     0x0402) \
    FPGA_REG(DAC0_LO,       0x0480) \
    FPGA_REG(DAC0_HI,       0x0482) \
    FPGA_REG(DAC1_LO,       0x0484) \
    FPGA_REG(DAC1_HI,       0x0486) \
    FPGA_REG(OUT_MASK,      0x0500) \
    FPGA_REG(DAC_CTRL,      0x0520) \
    FPGA_REG(OUT_FIFO_STAT, 0x0524) \
    FPGA_REG(IO_CTRL,       0x0600) \
    FPGA_REG(TRIG_CTRL,     0x0602) \
    FPGA_REG(INTR_MASK,     0x0620) \
    FPGA_REG(INTR_STAT,     0x0622) \
    FPGA_REG(DMA_STAT,      0x0626) \
    FPGA_REG(DIN,           0x0800) \
    FPGA_REG(DOUT,          0x0a00) \
    FPGA_REG(EVNT_OUT_CTRL, 0x0C00) \
    FPGA_REG(I2C0_CTRL,     0x0E00) \
    FPGA_REG(I2C0_WR,       0x0E02) \
    FPGA_REG(I2C0_RD,       0x0E04) \
    FPGA_REG(I2C1_CTRL,     0x0E08) \
    FPGA_REG(I2C1_WR,       0x0E0A) \
    FPGA_REG(I2C1_RD,       0x0E0C) \
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
 FPGA_REG_IN_CTRL      0x000
 */
#define MASK_IN_CTRL_DIN_TRIG   (BIT14 | BIT13 | BIT12)
#define SHIFT_IN_CTRL_DIN_TRIG  (12)
#define MASK_IN_CTRL_PCG_CLK_SEL (BIT9)
#define MASK_IN_CTRL_EXT_CLK_SRC (BIT7)
#define MASK_IN_CTRL_AD_SYNC    (BIT4)
#define MASK_IN_CTRL_CLK_DIV    (BIT3 | BIT2)
#define SHIFT_IN_CTRL_CLK_DIV   (2)
#define MASK_IN_CTRL_MODE       (BIT1 | BIT0)
#define SHIFT_IN_CTRL_MODE      (0)
#define MASK_IN_CTRL_MODE_HS    (0x0)
#define MASK_IN_CTRL_MODE_HRES  (BIT0)

/*****************************************************************************
 FPGA_REG_IN_SETUP1     0x0006 
 */
#define MASK_IN_SETUP1_GAIN  (BIT3 | BIT2 | BIT1 | BIT0)
#define IN_SETUP1_GAIN_10    (1)
#define IN_SETUP1_GAIN_1     (0)

/*****************************************************************************
 FPGA_REG_IN_MASK     0x000C 
 */
#define MASK_IN_MASK_DIN        (BIT7)
#define MASK_IN_MASK_MSR_CTR    (BIT6)
#define MASK_IN_MASK_CT         (BIT5)
#define MASK_IN_MASK_TACH       (BIT4)
#define MASK_IN_MASK_AIN3       (BIT3)
#define MASK_IN_MASK_AIN2       (BIT2)
#define MASK_IN_MASK_AIN1       (BIT1)
#define MASK_IN_MASK_AIN0       (BIT0)

/*****************************************************************************
 FPGA_REG_THOLD_TRIG_LVL  0x0010
 */
#define MASK_THOLD_TRIG_LVL     ((BIT12)-1)

static inline int32_t threshold_2_twos_comp(uint16_t offbin)
{
    int32_t twoscomp;
    //shift bits 11:0 to bits 23:12
    twoscomp = (offbin << (AD_RES_BITS-12));
    twoscomp ^=(1<<(AD_RES_BITS-1)); //flip sign bit 23
    if (twoscomp & (1<<(AD_RES_BITS-1))) //if bit 23 is 1
        twoscomp |= 0xff000000; //sign extend to 31:24
    return (twoscomp);
}
/* Convert 32-bit 2's complement value; least significant 24-bits used with 
 * bit 23 sign extended to bits 31:24. Output is 16-bit offset binary value
 * used to setup the threshold trigger register
 */
static inline uint16_t twos_comp_2_threshold(int32_t twoscomp)
{
    twoscomp ^=(1<<(AD_RES_BITS-1)); //flip sign bit 23
    twoscomp >>= (AD_RES_BITS-12); //shift bits 23:12 to bits 11:0
    return (twoscomp&MASK_THOLD_TRIG_LVL); 
}
/*****************************************************************************
 FPGA_REG_THOLD_TRIG_SEL  0x0014
 */
#define MASK_THOLD_TRIG_SEL     (BIT3 | BIT2 | BIT1 | BIT0)

/*****************************************************************************
 FPGA_REG_IN_STAT       0x0034
 */
#define MASK_IN_STAT_FIFO_FULL  (BIT3)
#define MASK_IN_STAT_FIFO_EMPTY (BIT1)
#define MASK_IN_STAT_ACTIVE     (BIT0)

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
#define MASK_MSR_CTR_CTRL_SCLR   (BIT15)
#define MASK_MSR_CTR_CTRL_STALE  (BIT14)
#define SHIFT_MSR_CTR_CTRL_STALE  (14)
#define MASK_MSR_CTR_CTRL_STOP_SEL  (BIT13|BIT12|BIT11|BIT10|BIT9|BIT8|BIT7)
#define SHIFT_MSR_CTR_CTRL_STOP_SEL (7)
#define MASK_MSR_CTR_CTRL_START_SEL  (BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
#define SHIFT_MSR_CTR_CTRL_START_SEL (0)

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
FPGA_REG_CT_IO_CTRL,    0x0240
 */
#define MASK_CT_IO_CTRL_OEN         (BIT11)
#define MASK_CT_IO_CTRL_OUT         (BIT10 | BIT9 | BIT8)
#define SHIFT_CT_IO_CTRL_OUT        (8)
#define MASK_CT_IO_CTRL_GATE        (BIT6 | BIT5 | BIT4)
#define SHIFT_CT_IO_CTRL_GATE       (4)
#define MASK_CT_IO_CTRL_CLK         (BIT2 | BIT1 | BIT0)
#define SHIFT_CT_IO_CTRL_CLK        (0)

/*****************************************************************************
 FPGA_REG_OUT_CTRL0    0x400
 */
#define MASK_OUT_CTRL0_OUT1_LOAD (BIT12)
#define MASK_OUT_CTRL0_OUT0_LOAD (BIT11)
#define MASK_OUT_CTRL0_ACTIVE    (BIT10)
#define MASK_OUT_CTRL0_BUSY          (BIT9)
#define MASK_OUT_CTRL0_FIFO_PRIME    (BIT7)
#define MASK_OUT_CTRL0_PGC_CLK_SEL   (BIT4)
#define MASK_OUT_CTRL0_CLK_DIV   (BIT3 | BIT2)
#define SHIFT_OUT_CTRL0_CLK_DIV  (2)
#define MASK_OUT_CTRL0_MODE      (BIT1 | BIT0)
#define SHIFT_OUT_CTRL0_MODE     (0)
#define MASK_OUT_CTRL0_MODE_NORMAL  (0x0)
#define MASK_OUT_CTRL0_MODE_DBL     (BIT0)
#define MASK_OUT_CTRL0_MODE_QUAD    (BIT1)

/*****************************************************************************
 FPGA_REG_OUT_CTRL1    0x402
 */
#define MASK_OUT_CTRL1_DIN_TRIG   (BIT9 | BIT8 | BIT7)
#define SHIFT_OUT_CTRL1_DIN_TRIG  (7)
#define MASK_OUT_CTRL1_RESET      (BIT1)
#define MASK_OUT_CTRL1_ENABLE     (BIT0)

/*****************************************************************************
 FPGA_REG_OUT_MASK       0x500
 */
#define MASK_OUT_MASK_DOUT7     (BIT9)
#define MASK_OUT_MASK_DOUT6     (BIT8)
#define MASK_OUT_MASK_DOUT5     (BIT7)
#define MASK_OUT_MASK_DOUT4     (BIT6)
#define MASK_OUT_MASK_DOUT3     (BIT5)
#define MASK_OUT_MASK_DOUT2     (BIT4)
#define MASK_OUT_MASK_DOUT1     (BIT3)
#define MASK_OUT_MASK_DOUT0     (BIT2)
#define MASK_OUT_MASK_DOUT      (BIT9|BIT8|BIT7|BIT6|BIT5|BIT4|BIT3|BIT2)
#define MASK_OUT_MASK_AOUT1     (BIT1)
#define MASK_OUT_MASK_AOUT0     (BIT0)

/*****************************************************************************
 * OutputFifoCtrl
 * FPGA_REG_OUT_FIFO_STAT 0x0524
 */
#define MASK_OUT_STAT_FIFO_FULL  (BIT3)
#define MASK_OUT_STAT_FIFO_EMPTY (BIT1)
#define MASK_OUT_FIFO_STAT_RST   (BIT0) // !!Reset is active low

/*****************************************************************************
 FPGA_REG_IO_CTRL     0x600
 */
#define MASK_IO_CTRL_OUT_SW_TRIG (BIT3)
#define MASK_IO_CTRL_OUT_ARM     (BIT2)
#define MASK_IO_CTRL_IN_SW_TRIG  (BIT1)
#define MASK_IO_CTRL_IN_ARM      (BIT0)

/*****************************************************************************
 FPGA_REG_INTR_STAT   0x622
 */
#define MASK_INTR_STAT_OUT_UNDRFL (BIT6)
#define MASK_INTR_STAT_OUT_DONE  (BIT5)
#define MASK_INTR_STAT_OUT_TRIG  (BIT4)
#define MASK_INTR_STAT_IN_TRIG   (BIT1)
#define MASK_INTR_STAT_IN_OVRFL  (BIT0)

/*****************************************************************************
 FPGA_REG_TRIG_CTRL   0x602
 */
#define MASK_TRIG_CTRL_IN_START     (BIT2 | BIT1 | BIT0)
#define SHIFT_TRIG_CTRL_IN_START    (0)
#define MASK_TRIG_CTRL_IN_REF       (BIT6 | BIT5 | BIT4)
#define SHIFT_TRIG_CTRL_IN_REF      (4)
#define MASK_TRIG_CTRL_OUT_START    (BIT10 | BIT9 | BIT8)
#define SHIFT_TRIG_CTRL_OUT_START   (8)

#define TRIG_CTRL_SW                (0)
#define TRIG_CTRL_EXT_FALLING       (BIT1)
#define TRIG_CTRL_EXT_RISING        (BIT1 | BIT0)
#define TRIG_CTRL_THOLD_FALLING     (BIT2 | BIT1)
#define TRIG_CTRL_THOLD_RISING      (BIT2 | BIT1| BIT0)

/*****************************************************************************
 FPGA_REG_I2C0_CTRL and FPGA_REG_I2C1_CTRL
 */
#define MASK_I2C_CTRL_SPEED         (BIT8)
#define MASK_I2C_CTRL_START         (BIT7)
#define MASK_I2C_CTRL_STOP          (BIT6)
#define MASK_I2C_LAST_RD            (BIT5)
#define MASK_I2C_ACK                (BIT1)
#define MASK_I2C_DONE               (BIT0)

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
    reg = dt78xx_fpga_read(dev, FPGA_REG_OUT_CTRL0);
    return ((reg & MASK_OUT_CTRL0_ACTIVE)?-EBUSY:0);
}
#ifdef  __cplusplus
}
#endif
#endif
