/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (C) 2020 huangzhenwei@allwinnertech.com
 * Copyright (C) 2021 Samuel Holland <samuel@sholland.org>
 * Copyright (C) 2023 Andras Szemzo <szemzo.andras@gmail.com>
 * Copyright (C) 2024 Iscle <albertiscle9@gmail.com>
 */

#ifndef _DT_BINDINGS_CLK_SUN8I_V853_CCU_H_
#define _DT_BINDINGS_CLK_SUN8I_V853_CCU_H_

#define CLK_PLL_CPU			0
#define CLK_PLL_DDR			1
#define CLK_PLL_PERIPH_4X	2
#define CLK_PLL_PERIPH_2X	3
#define CLK_PLL_PERIPH_800M	4
#define CLK_PLL_PERIPH_480M	5
#define CLK_PLL_PERIPH		6
#define CLK_PLL_PERIPH_400M	7
#define CLK_PLL_PERIPH_300M	8
#define CLK_PLL_PERIPH_200M	9
#define CLK_PLL_PERIPH_160M	10
#define CLK_PLL_PERIPH_150M	11
#define CLK_PLL_VIDEO_4X	12
#define CLK_PLL_VIDEO_2X	13
#define CLK_PLL_VIDEO		14
#define CLK_PLL_CSI_4X		15
#define CLK_PLL_CSI_2X		16
#define CLK_PLL_CSI			17
#define CLK_PLL_AUDIO_BASE	18
#define CLK_PLL_AUDIO_DIV2	19
#define CLK_PLL_AUDIO_DIV5	20
#define CLK_PLL_AUDIO_4X	21
#define CLK_PLL_AUDIO_1X	22
#define CLK_PLL_NPU_4X		23
#define CLK_PLL_NPU_2X		24
#define CLK_PLL_NPU			25
#define CLK_CPU				26
#define CLK_CPU_AXI			27
#define CLK_CPU_APB			28
#define CLK_AHB				29
#define CLK_APB0			30
#define CLK_APB1			31
#define CLK_MBUS			32
#define CLK_DE				33
#define CLK_BUS_DE			34
#define CLK_G2D				35
#define CLK_BUS_G2D			36
#define CLK_CE				37
#define CLK_BUS_CE			38
#define CLK_VE				39
#define CLK_BUS_VE			40
#define CLK_NPU				41
#define CLK_BUS_NPU			42
#define CLK_BUS_DMA			43
#define CLK_BUS_MSGBOX0		44
#define CLK_BUS_MSGBOX1		45
#define CLK_BUS_SPINLOCK	46
#define CLK_BUS_HSTIMER		47
#define CLK_AVS				48
#define CLK_BUS_DBG			49
#define CLK_BUS_PWM			50
#define CLK_BUS_IOMMU		51
#define CLK_DRAM			52
#define CLK_MBUS_DMA		53
#define CLK_MBUS_VE			54
#define CLK_MBUS_CE			55
#define CLK_MBUS_CSI		56
#define CLK_MBUS_ISP		57
#define CLK_MBUS_G2D		58
#define CLK_BUS_DRAM		59
#define CLK_MMC0			60
#define CLK_MMC1			61
#define CLK_MMC2			62
#define CLK_BUS_MMC0		63
#define CLK_BUS_MMC1		64
#define CLK_BUS_MMC2		65
#define CLK_BUS_UART0		66
#define CLK_BUS_UART1		67
#define CLK_BUS_UART2		68
#define CLK_BUS_UART3		69
#define CLK_BUS_I2C0		70
#define CLK_BUS_I2C1		71
#define CLK_BUS_I2C2		72
#define CLK_BUS_I2C3		73
#define CLK_BUS_I2C4		74
#define CLK_SPI0			75
#define CLK_SPI1			76
#define CLK_SPI2			77
#define CLK_SPI3			78
#define CLK_BUS_SPI0		79
#define CLK_BUS_SPI1		80
#define CLK_BUS_SPI2		81
#define CLK_BUS_SPI3		82
#define CLK_EMAC_25M		83
#define CLK_BUS_EMAC		84
#define CLK_BUS_GPADC		85
#define CLK_BUS_THS			86
#define CLK_I2S1			87
#define CLK_BUS_I2S1		88
#define CLK_DMIC			89
#define CLK_BUS_DMIC		90
#define CLK_AUDIO_DAC		91
#define CLK_AUDIO_ADC		92
#define CLK_BUS_AUDIO		93
#define CLK_USB_OHCI		94
#define CLK_BUS_OHCI		95
#define CLK_BUS_EHCI		96
#define CLK_BUS_OTG			97
#define CLK_BUS_DPSS_TOP	98
#define CLK_MIPI_DSI		99
#define CLK_BUS_MIPI_DSI	100
#define CLK_TCON_LCD		101
#define CLK_BUS_TCON_LCD	102
#define CLK_CSI_TOP			103
#define CLK_CSI_MCLK0		104
#define CLK_CSI_MCLK1		105
#define CLK_CSI_MCLK2		106
#define CLK_BUS_CSI			107
#define CLK_BUS_WIEGAND		108
#define CLK_RISCV			109
#define CLK_RISCV_AXI		110
#define CLK_BUS_RISCV_CFG	111
#define CLK_FANOUT_24M		112
#define CLK_FANOUT_12M		113
#define CLK_FANOUT_16M		114
#define CLK_FANOUT_25M		115
#define CLK_FANOUT_27M		116
#define CLK_FANOUT_PCLK		117
#define CLK_FANOUT0			118
#define CLK_FANOUT1			119
#define CLK_FANOUT2			120

#endif /* _DT_BINDINGS_CLK_SUN8I_V853_CCU_H_ */
