/****************************************************************************
 * APIs to calculate parameters for the Cypress CY22150 Programmable Clock
 * Generator, and program it using the I2C interface implemented through the
 * FPGA. The FPGA has two independent I2C buses – one for each of the 
 * programmable PLL’s on the board. 
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
 *************************************************************************/

/**
Question: How can I calculate optimal P and Q values for the CY22150 without
using CyberClocks?

Response: If the application requires on-the-fly frequency changes and the
Cypress CyberClocks software is unavailble, use an algorithm to find the best P
and Q values.

Here is a PLL or VCO equation.

VCO = Ref * P / Q. The output frequency is calculated by CLKOUT = VCO / Divider.
Therefore the final equation is CLKOUT = (Ref * P / Q) / Divider. Note: Keep the
VCO running as fast as possible and use a low Q value.

Here is an example of how to find the P and Q values.

1. Multiply the desired CLKOUT value as high as possible before the VCO maximum
frequency is violated. VCO = CLKOUT*Divider. VCO < VCO_MAX. (VCO_MAX is 400MHz for
commercial devices, 333.33MHz for industrial)

2. With the required VCO frequency, start a loop. First loop on the Q value (Q
is between 2 and 129)

Check the phase detector frequency, Ref / Q must be larger than or equal to
250kHz. The second loop on the P value (P is between 8 and 2055). Calculate Ref
* P / Q. Calculate the ppm error between the desired VCO frequency and
Ref * P / Q.
If the ppm error is 0 exit the loop. Otherwise, compare the current ppm error to
previously saved ppm error.
If current ppm is less than saved ppm, save the current ppm value. Note: If
there are no combinations that give an acceptable ppm value, go back to step 1
and change the desired VCO frequency.

3. With the P and Q values established, convert them to the base values used by
the device. P = (2 * (Pbase+4)) + Po (Po can be 0 or 1 and is used for odd
numbers of P). Q = Qbase + 2.

Pbase and Qbase are used in the JEDEC file


4. Use Table 9 in page 6 of the datasheet to use the correct charge pum setting
according to the computed Ptotal value.
**/

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

#include "dt7837_fpga.h"
/******************************************************************************
 MACROS
 *****************************************************************************/
#define MHZ                     (1000000)
#define KHZ                     (1000)
#define REF_CLK_MHZ             (48*MHZ)   
#define MASTER_CLK_MULTIPLIER   (256)
#define PLL_LOCK_WAIT_MS        (3)

#define VCO_MAX                 (float)(400*MHZ)
#define VCO_MIN                 (float)(100*MHZ)

#define DIVIDER_MIN             (4)
#define DIVIDER_MAX             (127)

#define Q_MIN                   (2)
#define Q_MAX                   (129)
#define REF_DIV_Q_MIN           (float)(250*KHZ)

#define P_MIN                   (8)
#define P_MAX                   (2055)

#define PPM_ERR_MAX             (float)50

//CY22150 base address
#define CY22150_I2C_ADDR        0x69
#define CY22150_I2C_ADDR_WR     ((CY22150_I2C_ADDR << 1) & 0xFE)
#define CY22150_I2C_ADDR_RD     ((CY22150_I2C_ADDR << 1) | 0x01)

//CLKOE register bits
#define CLKOE_LCLK1             (BIT0)

//DIV1 register bits
#define DIV1_DIV0               (BIT0)
#define DIV1_DIV6               (BIT6)
#define DIV1_SRC                (BIT7)

//XDRV register bits
#define XDRV_0                  (BIT3)
#define XDRV_1                  (BIT4)

//PBHI register bits
#define PBHI_8                  (BIT0)
#define PBHI_9                  (BIT1)

#define PLL_CONFIG_VALID        (0xc0ffee)
//#define _DBG_THIS_FILE_ (1)

/******************************************************************************
 Data Types
 *****************************************************************************/
//CY22150 registers
typedef enum
{
   CY22150_REG_CLKOE    = 0x09,
   CY22150_REG_DIV1     = 0x0C,
   CY22150_REG_XDRV     = 0x12,
   CY22150_REG_CAPLOAD  = 0x13,
   CY22150_REG_PBHI     = 0x40,
   CY22150_REG_PBLO     = 0x41,
   CY22150_REG_QCNT     = 0x42,
   CY22150_REG_MATRIX1  = 0x44,
   CY22150_REG_MATRIX2  = 0x45,
   CY22150_REG_MATRIX3  = 0x46,
   CY22150_REG_DIV2     = 0x47
} CY22150_REG;

/* This struct has the offsets of the I2C control, write and read registers in
 * the FPGA
 */
struct fpga_i2c
{
    uint16_t ctrl_reg;
    uint16_t wr_reg;
    uint16_t rd_reg;
};

enum pll_config_type {pll_config_ad, pll_config_da};
struct pll_config
{
    uint32_t valid;
    float    freq;      
    int      ext_div;   
    int      ext_mode;
    int      P_total;
    int      Q_total;
    int      div;
    enum pll_config_type type;
};

struct pll_table
{
    float fmin;             
    float fmax;             
    uint32_t multiplier;    
    uint32_t mode;          
};

/***************************************************************************
functions                                                        
****************************************************************************/

/****************************************************************************/
/* Global variables                                                         */
/****************************************************************************/

//There are two I2C interfaces in the FPGA
static const struct fpga_i2c g_ad_i2c = 
{
  .ctrl_reg = FPGA_REG_I2C0_CTRL, 
  .wr_reg   = FPGA_REG_I2C0_WR, 
  .rd_reg   = FPGA_REG_I2C0_RD,
};
static const struct fpga_i2c g_da_i2c = 
{
  .ctrl_reg = FPGA_REG_I2C1_CTRL, 
  .wr_reg   = FPGA_REG_I2C1_WR, 
  .rd_reg   = FPGA_REG_I2C1_RD,
};

/**
ADC: Max PLL Master clock is 27MHz
Mode                Frequency Range             Multiplier
---------------     ----------------            ----------- 
High Resolution     195.3125 – 52734.375 Hz       512
High Speed          52734.375 – 105468.75 Hz      256

DAC: Max PLL Master clock is 41.472MHz
Normal Speed        30000 – 54000 Hz              512
Double Speed        54000 – 108000 Hz             256
Quad Speed          108000 – 216000 Hz            128
                  +--------+     +------------------+
    Master clk -> | PLL    | ->  | external divider | -> AD clock
                  +--------+     +------------------+
 
  AD clock = (Multiplier * (external divider) * desired sample rate)
 
 In the tables below, the end-of-range maximum is slightly increased from the
 absolute maximum above, so that the latter value will pass validation
**/
static const struct pll_table g_ad_pll_tab[] =
{
    {.fmin=195.3125f,  .fmax=52734.375f, 512, MASK_IN_CTRL_MODE_HRES},
    {.fmin=52734.375f, .fmax=105468.751f, 256, MASK_IN_CTRL_MODE_HS},
    {.fmin=0.0f, .fmax=0.0f, 0, 0} //terminator
};
static const struct pll_table g_da_pll_tab[] =
{
    {.fmin=30000.0f, .fmax=54000.0f, 512, MASK_OUT_CTRL0_MODE_NORMAL},
    {.fmin=54000.0f, .fmax=108000.0f, 256, MASK_OUT_CTRL0_MODE_DBL},
    {.fmin=108000.0f,.fmax=216000.1f, 128, MASK_OUT_CTRL0_MODE_QUAD},
    {.fmin=0.0f, .fmax=0.0f, 0, 0} //terminator
};

/******************************************************************************
 * Math-NEON:  Neon Optimised Math Library based on cmath
 * Contact:    lachlan.ts@gmail.com
 * Copyright (C) 2009  Lachlan Tychsen - Smith aka Adventus
 * 
 * These math API replacements are taken from the above source
 */
static inline float _modf_c(float x, int *i)
{
    int n;
    n = (int)x;
    *i = n;
    x = x - (float)n;
    return x;
}
       
static inline float _fabsf_c(float x)
{
    union {
            int i;
            float f;
    } xx;

    xx.f = x;
    xx.i = xx.i & 0x7FFFFFFF;
    return xx.f;
}

/******************************************************************************
 Calculate generated VCO rate for a specified VCO rate and the PPM
 error between them, and return optimum P, Q and DIV1N

 Returns :
    0 : success
    <0 : failure
 **/
static int _cy22150_optimizePQDiv
(
 float *vco,           //Input  : Desired VCO rate in Hz, 
                       //Return : Actual VCO rate  in Hz
 float *pErrPpm,       //Return : PPM error return if != NULL
 int   *pOptimumP,     //Return : Optimum P total if != NULL
 int   *pOptimumQ,     //Return : Optimum Q total if != NULL
 int   *pOptimumDiv    //Return : Optimum DIV1N if != NULL
)
{
    int Q = Q_MIN;
    int Q_opt = Q;
    int P = P_MIN;
    int P_opt = P; 
    int divider;
    int errInit = 0;
    
    float ppmError = PPM_ERR_MAX;
    float clkOut = *vco;
    float vcoIdeal;
    float refDivQ;
    float vcoActual;
    float fraction;
    float err;

    /**
     Multiply the desired CLKOUT value as high as possible before the VCO
      maximum frequency is violated
     **/
    for (divider = DIVIDER_MAX; divider >= DIVIDER_MIN; --divider)
    {
        vcoIdeal = clkOut * divider;
        if ((vcoIdeal < VCO_MAX) && (vcoIdeal > VCO_MIN))
        {
            break;
        }
    }
    
    //If vcoIdeal is not in range, quit
    if (vcoIdeal >= VCO_MAX)
    {
#ifdef _DBG_THIS_FILE_
        pr_err("[%s] vcoIdeal >= VCO_MAX\n", __func__);
#endif
        return (-EINVAL);       //error
    }
    if (vcoIdeal <= VCO_MIN)
    {
#ifdef _DBG_THIS_FILE_
        pr_err("[%s] vcoIdeal <= VCO_MIN\n", __func__);
#endif
        return (-EINVAL);       //error
    }
    /**
     Check the phase detector frequency, (Ref / Q) must be larger than or
     equal to 250kHz. Q is between 2 and 129 and must be as low as possible
     to make VCO as high as possible
     **/
LOOP_Q:
    for (; Q <= Q_MAX; ++Q)
    {
        refDivQ = (float)REF_CLK_MHZ/Q;
        if (refDivQ >= REF_DIV_Q_MIN)
        {
            break;
        }
    }
    //check Q
    if (Q > Q_MAX)
    {
#ifdef _DBG_THIS_FILE_
        pr_err("[%s] Q > Q_MAX\n", __func__);
#endif
        return (-EINVAL);       //error
    }
    
    /**
     Given Q, find the value of P    
    **/
    fraction = _modf_c(vcoIdeal/refDivQ, &P);
    if (fraction >= 0.5)
    {
        ++P;
    }
    
    //If P is illegal, compute Q again
    if ((P > P_MAX) || (P < P_MIN))
    {
        ++Q;
        if (Q <= Q_MAX)
        {
            goto LOOP_Q;
        }
    }
    /**
     Calculate Ref * P / Q. 
     Calculate the ppm error between the desired VCO frequency and Ref * P / Q.
     If the ppm error is 0 exit the loop. Otherwise, compare the current ppm error to
     previously saved ppm error    
    **/
    vcoActual = refDivQ*P;
    err = vcoActual - vcoIdeal;
    err /= vcoIdeal;
    err *= MHZ;
    if ((errInit==0)||(_fabsf_c(err) < _fabsf_c(ppmError)))
    {
        ppmError = err;
        P_opt = P;
        Q_opt = Q;
        errInit = 1;
    }
    if (_fabsf_c(err) == 0.0)
    {
        goto DONE;
    }
    
    /**
     Check the next Q and the resultant P combination
     **/
    ++Q;
    if (Q <= Q_MAX)
    {
        goto LOOP_Q;
    }

DONE:
    vcoActual = (float)(REF_CLK_MHZ/Q_opt)*P_opt;
    *vco = (vcoActual / divider);
   
    if (pOptimumP)
    {
        *pOptimumP = P_opt;
    }
    if (pOptimumQ)
    {
        *pOptimumQ = Q_opt;
    }
    if (pErrPpm)
    {
        *pErrPpm = ppmError;
    }
    if (pOptimumDiv)
    {
        *pOptimumDiv = divider;
    }
    return 0;
}

/******************************************************************************
 * Write data to the FPGA write register. Wait until an I2C read or write 
 * operation is complete and return the status of ACK
 * @param dev
 * @param i2c : Pointer to FPGA I2C registers connected to a specific CY22150
 * @param data : Data to be written to FPGA i2c write register
 * @return : 0 = success, <0 = failure
 */
static int _i2c_write_fpga(struct device *dev, const struct fpga_i2c *i2c, 
                           uint8_t data)
{
    volatile uint16_t tmp;
    uint32_t loop = 10000;
    
    dt78xx_fpga_write(dev, i2c->wr_reg, data);
    //wait for done to be asserted
    tmp = dt78xx_fpga_read(dev, i2c->ctrl_reg);
    while (!(tmp & MASK_I2C_DONE) && --loop) 
        tmp = dt78xx_fpga_read(dev, i2c->ctrl_reg);
    if (!loop) //timed out
    {
        dev_err(dev,"[%s] ERROR i2c busy", __func__);
        return -EBUSY;
    }
#ifdef _DBG_THIS_FILE_
    pr_info("[%s] %#x loop %d ctrl %#x", __func__, data, 10000-loop, tmp);
#endif    
    //clear done
    dt78xx_fpga_write(dev, i2c->ctrl_reg, MASK_I2C_DONE);
    //check I2C ACK bit
    if (tmp & MASK_I2C_ACK)
    {
        dev_err(dev,"[%s] ERROR i2c no ack ctrl=%#x", __func__, tmp);
        return -EIO;
    }
    return  0;
}

/******************************************************************************
 * Issue an I2C stop to the specified I2C interface in the FPGA
 * @param dev
 * @param i2c
 * @return : 0 = success, <0 = failure
 */
static int _i2c_stop_fpga(struct device *dev, const struct fpga_i2c *i2c)
{
    volatile uint16_t tmp;
    uint32_t loop = 10000;
    
    //write the stop
    dt78xx_fpga_write(dev, i2c->ctrl_reg, MASK_I2C_CTRL_STOP);

    //wait for done to be asserted
    tmp = dt78xx_fpga_read(dev, i2c->ctrl_reg);
    while (!(tmp & MASK_I2C_DONE) && --loop) 
        tmp = dt78xx_fpga_read(dev, i2c->ctrl_reg);
    if (!loop) //timed out
    {
        dev_err(dev,"[%s] ERROR i2c busy", __func__);
        return -EBUSY;
    }
#ifdef _DBG_THIS_FILE_
    pr_info("[%s] loop %d", __func__, 10000-loop);
#endif    
    //clear done
    dt78xx_fpga_write(dev, i2c->ctrl_reg, MASK_I2C_DONE);
    return 0;
}

/******************************************************************************
 Write to the specified CY22150 register
 * @param dev
 * @param i2c : Pointer to FPGA I2C registers connected to a specific CY22150
 * @param cy22150_reg   : CY22150 register address
 * @param cy22150_data  : Data to be written to CY22150 register
 Returns :
    0=success, <0=failure 
 **/
static int _i2c_cy22150_reg_wr(struct device *dev, const struct fpga_i2c *i2c, 
                               uint8_t cy22150_reg, uint8_t cy22150_data)
{
    int err=0;

    /**
    Write sequence:

    Start signal, Device Address, R/W bit=0, Slave Ack, Register Address,
    Slave Ack, 8-bit register data, Slave Ack, 8-bit register data,
    Slave Ack, . . . ,Stop signal

    Write example: Enabling LCLK1 to LCLK4 from address 09H

    Start signal,1101001,0,Ack,00001001,Ack,00001111,Ack,Stop signal
    **/
#ifdef _DBG_THIS_FILE_    
    pr_info("[%s] %#x=%#x", __func__, cy22150_reg, cy22150_data);
#endif
    //Start bit
    dt78xx_fpga_write(dev, i2c->ctrl_reg, MASK_I2C_CTRL_START);

    //write device ID R/W=0
    err = _i2c_write_fpga(dev, i2c, CY22150_I2C_ADDR_WR);
    if (err)
        return err;
    
    //write CY22150 register address
    err = _i2c_write_fpga(dev, i2c, cy22150_reg);
    if (err)
        return err;

    //write CY22150 register data
    err = _i2c_write_fpga(dev, i2c, cy22150_data);
    if (err)
        return err;

    //Stop bit
    err = _i2c_stop_fpga(dev, i2c);

    return (err);
}

static void _da_reset(struct device *dev, struct pll_config *cfg)
{
    uint16_t tmp;
   
    /* convert the external divisor to the corresponding 2-bit pattern to set.
     * divisor 16 => bit pattern 0x3, divisor 2/4/8 => 0x0/0x1/0x2 */
    tmp = (cfg->ext_div==16) ? 0x3 : (cfg->ext_div >> 2);
    tmp <<= SHIFT_OUT_CTRL0_CLK_DIV;
    //set external divisor
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL0, MASK_OUT_CTRL0_CLK_DIV, tmp);
    //set the mode
    tmp = cfg->ext_mode;
    tmp <<= SHIFT_OUT_CTRL0_MODE;
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL0, MASK_OUT_CTRL0_MODE, tmp);
    //set output PGC clock source
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL0, 
                    MASK_OUT_CTRL0_PGC_CLK_SEL, MASK_OUT_CTRL0_PGC_CLK_SEL);
    //wait for PLL to lock
    msleep_interruptible(PLL_LOCK_WAIT_MS);
    
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL1, MASK_OUT_CTRL1_RESET, 0);
    //last step, enable output
    dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL1, 
                    MASK_OUT_CTRL1_ENABLE, MASK_OUT_CTRL1_ENABLE);
}

/***************************************************************************
 * This is the terminating step in dt78xx_pll_config_write(). This writes the
 * external divider, mode, Programmable Clock Generator and waits for the PLL
 * to lock. Then it syncs the AD
 */
static void _ad_sync(struct device *dev, struct pll_config *cfg)
{
    uint16_t tmp;
   
    /* convert the external divisor to the corresponding 2-bit pattern to set.
     * divisor 16 => bit pattern 0x3, divisor 2/4/8 => 0x0/0x1/0x2 */
    tmp = (cfg->ext_div==16) ? 0x3 : (cfg->ext_div >> 2);
    tmp <<= SHIFT_IN_CTRL_CLK_DIV;
    
    //set external divisor
    dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, MASK_IN_CTRL_CLK_DIV, tmp);
    
    //set the mode
    tmp = cfg->ext_mode;
    tmp <<= SHIFT_IN_CTRL_MODE;
    dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, MASK_IN_CTRL_MODE, tmp);

    //set input PGC clock source
    dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, 
                    MASK_IN_CTRL_PCG_CLK_SEL, MASK_IN_CTRL_PCG_CLK_SEL);
    
    //wait for PLL to lock
    msleep_interruptible(PLL_LOCK_WAIT_MS);
    
    //sync the AD
    dt78xx_fpga_rmw(dev, FPGA_REG_IN_CTRL, 
                    MASK_IN_CTRL_AD_SYNC,  MASK_IN_CTRL_AD_SYNC);
}

/***************************************************************************
 * Configure the PLL clock rate generator 
 * @param dev   : this device
 * @param cfg   : 0 PLL configuration allocated and initialized by calling
 *                dt78xx_ad_pll_config_init()
 * @return      : 0=success, <1=failure 
 */
int dt7837_pll_config_write(struct dt78xx_device *dt, struct pll_config *cfg)
{
    int PO, PB, Q, pump, err;
    const struct fpga_i2c *i2c;
    struct device *dev;
    
    if (cfg->valid != PLL_CONFIG_VALID)
        return (-ENXIO);
    dev = &dt->pdev->dev;
    i2c = (cfg->type==pll_config_ad) ? &g_ad_i2c : &g_da_i2c;
   
    //PO is a single bit variable, for odd numbers in Ptotal [pg 6 in manual]
    PO = (cfg->P_total & 0x1)?1:0;
    PB = ((cfg->P_total - PO)/2)-4;
    
    //For DA, outputs disabled & dac reset here and enabled at the end
    if (cfg->type==pll_config_da)
    {
        dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL1, MASK_OUT_CTRL1_ENABLE, 0);
        dt78xx_fpga_rmw(dev, FPGA_REG_OUT_CTRL1, 
                        MASK_OUT_CTRL1_RESET, MASK_OUT_CTRL1_RESET);
    }

    //disable all outputs
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_CLKOE, 0x00);
    if (err)
        return err;
    
    //Set Q
    Q = cfg->Q_total-Q_MIN;
    if (PO)
        Q |= 0x80;
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_QCNT, Q);
    if (err)
        return err;
    
    //set PB low
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_PBLO, PB);
    if (err)
        return err;
    
    //calculate charge pump setting based on P_total
    pump=0;
    if (cfg->P_total<45)
        pump = 0;
    else if (cfg->P_total<480)
        pump = 1;
    else if (cfg->P_total<640)
        pump = 2;
    else if (cfg->P_total<800)
        pump = 3;
    else
        pump = 4;

    //set PB high and chrage pump setting
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_PBHI, 
                             0xC0 | (pump<<2) | ((PB>>8)&0x03));
    if (err)
        return err;
    
    //set post divider DIV1N
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_DIV1, 
                             (cfg->div & 0xFF));
    if (err)
        return err;
    
    //set post divider DIV2N to default 8 since it is not used
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_DIV2, 8);
    if (err)
        return err;

    //select LCLK1 source to be from DIV1N
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_MATRIX1, 0x20);
    if (err)
        return err;

    //enable LCLK1
    err = _i2c_cy22150_reg_wr(dev, i2c, CY22150_REG_CLKOE, 0x01);
    if (err)
        return err;

    if (cfg->type==pll_config_ad)
        _ad_sync(dev, cfg);
    else
        _da_reset(dev, cfg);
    
    return err;
}

/***************************************************************************
 * Allocate and initialize the PLL configuration parameters
 * @param rate  : Desired sampling rate
 * @param tab   : Pointer to table of parameter boundaries
 * @return      : <=0 : error, >0 success
 */
static struct pll_config *_pll_config_init(float rate, const struct pll_table *tab)
{
    struct pll_config *config;
    float pll_freq;
    int ext_div;
    float errPpmBest;
    
    //check rate  and get ref-multipler and device mode
    for( ; tab->multiplier; ++tab)
    {
        if ((rate >= tab->fmin) && (rate < tab->fmax))
            break;
        //If this is the last valid entry then fmax is OK
        if ((rate == tab->fmax) && !((tab+1)->multiplier))
            break;
    }
    if (!tab->multiplier)
        return ERR_PTR(-EINVAL);
#ifdef _WARN_
#warning replace kzalloc w/t devm_kzalloc!!   
#endif
    config = kzalloc(sizeof(struct pll_config), GFP_KERNEL);
    if (!config)
        return ERR_PTR(-ENOMEM);
   
    config->ext_mode = tab->mode;
    errPpmBest = 1000000.0f;
    pll_freq = rate * tab->multiplier;
    /*
     * Find the best external divider that generates the least PPM error between
     * desired master clock and generated master clock.
     **/
    for (ext_div = 2, config->ext_div = 2; ext_div <= 16; ext_div *= 2)
    {
        float errPpm;
        float fMasterClk;
        int P, Q, DIV;
        
        fMasterClk = pll_freq * ext_div;
        if (!_cy22150_optimizePQDiv(&fMasterClk, &errPpm, &P, &Q, &DIV))
        {
            if (_fabsf_c(errPpm) < _fabsf_c(errPpmBest))
            {
                errPpmBest = errPpm;
                config->freq = fMasterClk/(ext_div * tab->multiplier);
                config->ext_div = ext_div;
                config->P_total = P;
                config->Q_total = Q;
                config->div = DIV;
            }
        }
    }
    
    if (!config->div || !config->Q_total || !config->P_total)
    {
        kfree(config);
        return ERR_PTR(-ERANGE);
    }
#if 0
    {
        uint32_t *p1, *p2;
        p1 = (uint32_t *)&config->freq;
        p2 = (uint32_t *)&errPpmBest;
        pr_info("[%s] fMasterClkBest %#x errPpmBest %#x ext_div %d div %d mode %d\n",
                __func__, *p1, *p2, config->ext_div, config->div, config->ext_mode);
    }
#endif
    return (config);
}


/*****************************************************************************
 * Returns PLL configuration for the specified sampling rate
 * @param freq : Pointer to desired sampling rate. On success, the actual rate
 *               is returned here
 * @param ad   : 1 for AD PLL, 0 for DA PLL
 * @return : <=0 :failure. 
 *           >0 : success. The returned pll_config must be used in
 *              dt78xx_pll_config_write()
 * NOTES : This API must be called within a kernel_neon_begin()/kernel_neon_end.
 * The allocated structure must be deallocated by the caller 
 */
struct pll_config * __must_check dt7837_pll_config_init(float *freq, int ad)
{
    struct pll_config *cfg;
    cfg = _pll_config_init(*freq, ad ? g_ad_pll_tab : g_da_pll_tab);
    if (!IS_ERR_OR_NULL(cfg))
    {
        cfg->type = ad ? pll_config_ad : pll_config_da;
        cfg->valid = PLL_CONFIG_VALID;
        *freq = cfg->freq;
    }
    return (cfg);    
}
