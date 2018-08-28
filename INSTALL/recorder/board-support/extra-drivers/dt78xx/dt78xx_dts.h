/*
 *  Device Tree common definitions
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
#ifndef _DT78XX_DTS_H_
#define _DT78XX_DTS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/*
 * MODE0 - Mux Mode 0
 * MODE1 - Mux Mode 1
 * MODE2 - Mux Mode 2
 * MODE3 - Mux Mode 3
 * MODE4 - Mux Mode 4
 * MODE5 - Mux Mode 5
 * MODE6 - Mux Mode 6
 * MODE7 - Mux Mode 7
 * IDIS - Receiver disabled
 * IEN - Receiver enabled
 * PD - Internal pull-down
 * PU - Internal pull-up
 * OFF - Internal pull disabled
 */

#define MODE0   0
#define MODE1   1
#define MODE2   2
#define MODE3   3
#define MODE4   4
#define MODE5   5
#define MODE6   6
#define MODE7   7
#define IDIS    (0 << 5)
#define IEN     (1 << 5)
#define PD      (0 << 3)
#define PU      (2 << 3)
#define OFF     (1 << 3)

/*
 * To get the physical address the offset has
 * to be added to AM335X_CTRL_BASE
 */

#define PINCTRL_GPMC_AD0             0x00
#define PINCTRL_GPMC_AD1             0x04
#define PINCTRL_GPMC_AD2             0x08
#define PINCTRL_GPMC_AD3             0x0C
#define PINCTRL_GPMC_AD4             0x10
#define PINCTRL_GPMC_AD5             0x14
#define PINCTRL_GPMC_AD6             0x18
#define PINCTRL_GPMC_AD7             0x1C
#define PINCTRL_GPMC_AD8             0x20
#define PINCTRL_GPMC_AD9             0x24
#define PINCTRL_GPMC_AD10            0x28
#define PINCTRL_GPMC_AD11            0x2C
#define PINCTRL_GPMC_AD12            0x30
#define PINCTRL_GPMC_AD13            0x34
#define PINCTRL_GPMC_AD14            0x38
#define PINCTRL_GPMC_AD15            0x3C
#define PINCTRL_GPMC_A0              0x40
#define PINCTRL_GPMC_A1              0x44
#define PINCTRL_GPMC_A2              0x48
#define PINCTRL_GPMC_A3              0x4C
#define PINCTRL_GPMC_A4              0x50
#define PINCTRL_GPMC_A5              0x54
#define PINCTRL_GPMC_A6              0x58
#define PINCTRL_GPMC_A7              0x5C
#define PINCTRL_GPMC_A8              0x60
#define PINCTRL_GPMC_A9              0x64
#define PINCTRL_GPMC_A10             0x68
#define PINCTRL_GPMC_A11             0x6C
#define PINCTRL_GPMC_WAIT0           0x70
#define PINCTRL_GPMC_WPN             0x74
#define PINCTRL_GPMC_BEN1            0x78
#define PINCTRL_GPMC_CSN0            0x7C
#define PINCTRL_GPMC_CSN1            0x80
#define PINCTRL_GPMC_CSN2            0x84
#define PINCTRL_GPMC_CSN3            0x88
#define PINCTRL_GPMC_CLK             0x8C
#define PINCTRL_GPMC_ADVN_ALE        0x90
#define PINCTRL_GPMC_OEN_REN         0x94
#define PINCTRL_GPMC_WEN             0x98
#define PINCTRL_GPMC_BEN0_CLE        0x9C
#define PINCTRL_LCD_DATA0            0xA0
#define PINCTRL_LCD_DATA1            0xA4
#define PINCTRL_LCD_DATA2            0xA8
#define PINCTRL_LCD_DATA3            0xAC
#define PINCTRL_LCD_DATA4            0xB0
#define PINCTRL_LCD_DATA5            0xB4
#define PINCTRL_LCD_DATA6            0xB8
#define PINCTRL_LCD_DATA7            0xBC
#define PINCTRL_LCD_DATA8            0xC0
#define PINCTRL_LCD_DATA9            0xC4
#define PINCTRL_LCD_DATA10           0xC8
#define PINCTRL_LCD_DATA11           0xCC
#define PINCTRL_LCD_DATA12           0xD0
#define PINCTRL_LCD_DATA13           0xD4
#define PINCTRL_LCD_DATA14           0xD8
#define PINCTRL_LCD_DATA15           0xDC
#define PINCTRL_LCD_VSYNC            0xE0
#define PINCTRL_LCD_HSYNC            0xE4
#define PINCTRL_LCD_PCLK             0xE8
#define PINCTRL_LCD_AC_BIAS_EN       0xEC
#define PINCTRL_MMC0_DAT3            0xF0
#define PINCTRL_MMC0_DAT2            0xF4
#define PINCTRL_MMC0_DAT1            0xF8
#define PINCTRL_MMC0_DAT0            0xFC
#define PINCTRL_MMC0_CLK                  0x100
#define PINCTRL_MMC0_CMD                  0x104
#define PINCTRL_MII1_COL                  0x108
#define PINCTRL_MII1_CRS                  0x10C
#define PINCTRL_MII1_RX_ER                0x110
#define PINCTRL_MII1_TX_EN                0x114
#define PINCTRL_MII1_RX_DV                0x118
#define PINCTRL_MII1_TXD3                 0x11C
#define PINCTRL_MII1_TXD2                 0x120
#define PINCTRL_MII1_TXD1                 0x124
#define PINCTRL_MII1_TXD0                 0x128
#define PINCTRL_MII1_TX_CLK               0x12C
#define PINCTRL_MII1_RX_CLK               0x130
#define PINCTRL_MII1_RXD3                 0x134
#define PINCTRL_MII1_RXD2                 0x138
#define PINCTRL_MII1_RXD1                 0x13C
#define PINCTRL_MII1_RXD0                 0x140
#define PINCTRL_RMII1_REF_CLK             0x144
#define PINCTRL_MDIO                      0x148
#define PINCTRL_MDC                       0x14C
#define PINCTRL_SPI0_SCLK                 0x150
#define PINCTRL_SPI0_D0                   0x154
#define PINCTRL_SPI0_D1                   0x158
#define PINCTRL_SPI0_CS0                  0x15C
#define PINCTRL_SPI0_CS1                  0x160
#define PINCTRL_ECAP0_IN_PWM0_OUT         0x164
#define PINCTRL_UART0_CTSN                0x168
#define PINCTRL_UART0_RTSN                0x16C
#define PINCTRL_UART0_RXD                 0x170
#define PINCTRL_UART0_TXD                 0x174
#define PINCTRL_UART1_CTSN                0x178
#define PINCTRL_UART1_RTSN                0x17C
#define PINCTRL_UART1_RXD                 0x180
#define PINCTRL_UART1_TXD                 0x184
#define PINCTRL_I2C0_SDA                  0x188
#define PINCTRL_I2C0_SCL                  0x18C
#define PINCTRL_MCASP0_ACLKX              0x190
#define PINCTRL_MCASP0_FSX                0x194
#define PINCTRL_MCASP0_AXR0               0x198
#define PINCTRL_MCASP0_AHCLKR             0x19C
#define PINCTRL_MCASP0_ACLKR              0x1A0
#define PINCTRL_MCASP0_FSR                0x1A4
#define PINCTRL_MCASP0_AXR1               0x1A8
#define PINCTRL_MCASP0_AHCLKX             0x1AC
#define PINCTRL_XDMA_EVENT_INTR0          0x1B0
#define PINCTRL_XDMA_EVENT_INTR1          0x1B4
#define PINCTRL_WARMRSTN                  0x1B8
#define PINCTRL_EXTINTN                   0x1C0
#define PINCTRL_TMS                       0x1D0
#define PINCTRL_TDI                       0x1D4
#define PINCTRL_TDO                       0x1D8
#define PINCTRL_TCK                       0x1DC
#define PINCTRL_TRSTN                     0x1E0
#define PINCTRL_EMU0                      0x1E4
#define PINCTRL_EMU1                      0x1E8
#define PINCTRL_RTC_PWRONRSTN             0x1F8
#define PINCTRL_PMIC_POWER_EN             0x1FC
#define PINCTRL_EXT_WAKEUP                0xA00
#define PINCTRL_RTC_KALDO_ENN             0xA04
#define PINCTRL_USB0_DRVVBUS              0xA1C
#define PINCTRL_USB1_DRVVBUS              0xA34

/**
 * EDMA channels
 * See section 11.3.20 EDMA Events, Table 11-24 Crossbar 
 * Mapped, section 9.2.3 EDMA Event Multiplexing and sections 9.3.1.55 to
 * 9.3.1.70 in the AM335x TRM (SPRUH73J).
 * Event 30 = xdma_event_intr2 -> EDMA_CHAN2 crossbar mapped
 * Event 29 = xdma_event_intr1 -> EDMA_CHAN1 crossbar mapped
 * Event 28 = xdma_event_intr0 -> EDMA_CHAN0 crossbar mapped
 * Event 23 = gpioevt1 -> EDMA_CHAN3 direct mapped
 */
#define EDMA_CHAN0  (13)
#define EDMA_CHAN1  (21)
#define EDMA_CHAN2  (20)
#define EDMA_CHAN3  (23)
    
#ifdef  __cplusplus
}
#endif

#endif //_DT78XX_DTS_H_