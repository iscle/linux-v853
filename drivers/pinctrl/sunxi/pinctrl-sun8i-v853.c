// SPDX-License-Identifier: GPL-2.0
/*
 * Allwinner V853 SoC pinctrl driver.
 *
 * Copyright (c) 2020 wuyan@allwinnertech.com
 * Copyright (c) 2021-2022 Samuel Holland <samuel@sholland.org>
 * Copyright (c) 2024 Iscle <albertiscle9@gmail.com>
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-sunxi.h"

static const struct sunxi_desc_pin v853_pins[] = {
	/* PA */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x4, "i2c1"),		/* SCK */
		SUNXI_FUNCTION(0x5, "pwm0"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x4, "i2c1"),		/* SDA */
		SUNXI_FUNCTION(0x5, "pwm1"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "i2c4"),		/* SCK */
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x5, "pwm2"),
		SUNXI_FUNCTION(0x6, "uart2"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "i2c4"),		/* SDA */
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x5, "pwm3"),
		SUNXI_FUNCTION(0x6, "uart2"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x5, "i2c0"),		/* SCK */
		SUNXI_FUNCTION(0x6, "clk"),			/* FANOUT0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(A, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x5, "i2c0"),		/* SDA */
		SUNXI_FUNCTION(0x6, "clk"),			/* FANOUT1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 0, 11)),
	/* PC */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "mmc2"),		/* CLK */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "mmc2"),		/* CMD */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CS0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "mmc2"),		/* D2 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MOSI */
		SUNXI_FUNCTION(0x5, "boot"),		/* SEL0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "mmc2"),		/* D1 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MISO */
		SUNXI_FUNCTION(0x5, "boot"),		/* SEL1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "mmc2"),		/* D0 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* WP */
		SUNXI_FUNCTION(0x5, "pwm4"),
		SUNXI_FUNCTION(0x6, "i2c1"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(C, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "mmc2"),		/* D3 */
		SUNXI_FUNCTION(0x4, "spi0"),		/* HOLD */
		SUNXI_FUNCTION(0x5, "pwm5"),
		SUNXI_FUNCTION(0x6, "i2c1"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 1, 5)),
	/* PD */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D3 */
		SUNXI_FUNCTION(0x3, "pwm0"),
		SUNXI_FUNCTION(0x4, "emac"),		/* RXD1 */
		SUNXI_FUNCTION(0x5, "dsi"),			/* D0N */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D4 */
		SUNXI_FUNCTION(0x3, "pwm1"),
		SUNXI_FUNCTION(0x4, "emac"),		/* RXD0 */
		SUNXI_FUNCTION(0x5, "dsi"),			/* D0P */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D5 */
		SUNXI_FUNCTION(0x3, "pwm2"),
		SUNXI_FUNCTION(0x4, "emac"),		/* CRS_DV */
		SUNXI_FUNCTION(0x5, "dsi"),			/* D1N */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D6 */
		SUNXI_FUNCTION(0x3, "pwm3"),
		SUNXI_FUNCTION(0x4, "emac"),		/* RXER */
		SUNXI_FUNCTION(0x5, "dsi"),			/* D1P */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D7 */
		SUNXI_FUNCTION(0x3, "pwm4"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXD1 */
		SUNXI_FUNCTION(0x5, "dsi"),			/* CKN */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D10 */
		SUNXI_FUNCTION(0x3, "pwm5"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXD0 */
		SUNXI_FUNCTION(0x5, "dsi"),			/* CKP */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D11 */
		SUNXI_FUNCTION(0x3, "pwm6"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* D12 */
		SUNXI_FUNCTION(0x3, "pwm7"),
		SUNXI_FUNCTION(0x4, "emac"),		/* TXEN */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 18),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* CLK */
		SUNXI_FUNCTION(0x4, "emac"),		/* EPHY_25M */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 18)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 19),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* DE */
		SUNXI_FUNCTION(0x3, "pwm9"),
		SUNXI_FUNCTION(0x4, "tcon"),		/* TRIG */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MOSI */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 19)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 20),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* HSYNC */
		SUNXI_FUNCTION(0x3, "pwm10"),
		SUNXI_FUNCTION(0x4, "emac"),		/* MDC */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MISO */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 20)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(D, 21),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "lcd0"),		/* VSYNC */
		SUNXI_FUNCTION(0x4, "emac"),		/* MDIO */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CS0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 2, 21)),
	/* PE */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* PCLK */
		// SUNXI_FUNCTION(0x3, "uart2"),		/* RTS */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* MCLK */
		SUNXI_FUNCTION(0x5, "pwm0"),
		SUNXI_FUNCTION(0x6, "mmc1"),		/* CLK */
		SUNXI_FUNCTION(0x7, "uart3"),		/* TX */
		SUNXI_FUNCTION(0x8, "i2c3"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* MCLK */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* BCLK */
		SUNXI_FUNCTION(0x5, "pwm1"),
		SUNXI_FUNCTION(0x6, "mmc1"),		/* CMD */
		SUNXI_FUNCTION(0x7, "uart3"),		/* RX */
		SUNXI_FUNCTION(0x8, "i2c3"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* HSYNC */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x4, "i2s1"),		/* LRCK */
		SUNXI_FUNCTION(0x5, "pwm2"),
		SUNXI_FUNCTION(0x6, "mmc1"),		/* D0 */
		SUNXI_FUNCTION(0x7, "uart3"),		/* CTS */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* VSYNC */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x4, "i2s1_din"),	/* DIN0 */
		SUNXI_FUNCTION(0x5, "pwm3"),
		SUNXI_FUNCTION(0x6, "mmc1"),		/* D1 */
		SUNXI_FUNCTION(0x7, "uart3"),		/* RTS */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D0 */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x4, "i2s1_dout"),	/* DOUT0 */
		SUNXI_FUNCTION(0x5, "pwm4"),
		SUNXI_FUNCTION(0x6, "mmc1"),		/* D2 */
		SUNXI_FUNCTION(0x7, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x8, "i2c0"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D1 */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x5, "pwm5"),
		SUNXI_FUNCTION(0x6, "mmc1"),		/* D3 */
		SUNXI_FUNCTION(0x7, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x8, "i2c0"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D2 */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x5, "pwm6"),
		SUNXI_FUNCTION(0x6, "uart1"),		/* TX */
		SUNXI_FUNCTION(0x8, "i2c4"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 6)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 7),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D3 */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x5, "pwm7"),
		SUNXI_FUNCTION(0x6, "uart1"),		/* RX */
		SUNXI_FUNCTION(0x7, "i2s1_dout"),	/* DOUT0 */
		SUNXI_FUNCTION(0x8, "i2c4"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 7)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 8),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D4 */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x5, "pwm8"),
		SUNXI_FUNCTION(0x6, "wiegand"),		/* D0 */
		SUNXI_FUNCTION(0x7, "i2s1_din"),	/* DIN0 */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SCK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 8)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D5 */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x5, "pwm9"),
		SUNXI_FUNCTION(0x6, "wiegand"),		/* D1 */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* LRCK */
		SUNXI_FUNCTION(0x8, "i2c1"),		/* SDA */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D6 */
		// SUNXI_FUNCTION(0x3, "emac"),		/* CTS */
		SUNXI_FUNCTION(0x5, "pwm10"),
		SUNXI_FUNCTION(0x6, "uart2"),		/* RTS */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* BCLK */
		SUNXI_FUNCTION(0x8, "wiegand"),		/* D0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D7 */
		// SUNXI_FUNCTION(0x5, "i2s0_din"),	/* DIN3 */
		SUNXI_FUNCTION(0x6, "uart2"),		/* CTS */
		SUNXI_FUNCTION(0x7, "i2s1"),		/* MCLK */
		SUNXI_FUNCTION(0x8, "wiegand"),		/* D1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 11)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 12),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D8 */
		// SUNXI_FUNCTION(0x3, "ncsi0"),		/* FIELD */
		// SUNXI_FUNCTION(0x5, "i2s0_din"),	/* DIN2 */
		SUNXI_FUNCTION(0x6, "uart2"),		/* TX */
		SUNXI_FUNCTION(0x7, "uart3"),		/* TX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 12)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(E, 13),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "ncsi0"),		/* D9 */
		// SUNXI_FUNCTION(0x5, "i2s0_din"),	/* DIN1 */
		SUNXI_FUNCTION(0x6, "uart2"),		/* RX */
		SUNXI_FUNCTION(0x7, "uart3"),		/* RX */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 3, 13)),
	/* PF */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "mmc0"),		/* D1 */
		SUNXI_FUNCTION(0x3, "jtag"),		/* MS */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CLK */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CLK */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* MS */
		SUNXI_FUNCTION(0x7, "cpu"),			/* BIST0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 1),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "mmc0"),		/* D0 */
		SUNXI_FUNCTION(0x3, "jtag"),		/* DI */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MOSI */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MOSI */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* DI */
		SUNXI_FUNCTION(0x7, "cpu"),			/* BIST1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 1)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 2),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "mmc0"),		/* CLK */
		SUNXI_FUNCTION(0x3, "uart0"),		/* TX */
		SUNXI_FUNCTION(0x4, "spi0"),		/* MISO */
		SUNXI_FUNCTION(0x5, "spi2"),		/* MISO */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 2)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 3),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "mmc0"),		/* CMD */
		SUNXI_FUNCTION(0x3, "jtag"),		/* DO */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CS0 */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CS0 */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* DO */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 3)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 4),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "mmc0"),		/* D3 */
		SUNXI_FUNCTION(0x3, "uart0"),		/* RX */
		SUNXI_FUNCTION(0x4, "spi0"),		/* CS1 */
		SUNXI_FUNCTION(0x5, "spi2"),		/* CS1 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 4)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 5),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "mmc0"),		/* D2 */
		SUNXI_FUNCTION(0x3, "jtag"),		/* CK */
		SUNXI_FUNCTION(0x6, "r_jtag"),		/* CK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 5)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(F, 6),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x3, "dbg"),			/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 4, 6)),
	/* PH */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 0),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm0"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 0)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 9),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm9"),
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x5, "uart0"),		/* TX */
		SUNXI_FUNCTION(0x7, "dmic"),		/* DATA0 */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 9)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 10),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "pwm10"),
		SUNXI_FUNCTION(0x4, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x5, "uart0"),		/* RX */
		SUNXI_FUNCTION(0x7, "dmic"),		/* CLK */
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 10)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 11),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* MS */
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* MS */
		SUNXI_FUNCTION(0x5, "i2c2"),		/* SCK */
		SUNXI_FUNCTION(0x6, "spi3"),		/* CLK */
		SUNXI_FUNCTION(0x7, "clk"),			/* FANOUT0 */
		SUNXI_FUNCTION(0x8, "pwm4"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 11)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 12),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* CK */
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* CK */
		SUNXI_FUNCTION(0x5, "i2c2"),		/* SDA */
		SUNXI_FUNCTION(0x6, "spi3"),		/* MOSI */
		SUNXI_FUNCTION(0x7, "clk"),			/* FANOUT1 */
		SUNXI_FUNCTION(0x8, "pwm5"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 12)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 13),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* DO */
		SUNXI_FUNCTION(0x3, "mdc"),
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* DO */
		SUNXI_FUNCTION(0x5, "i2c3"),		/* SCK */
		SUNXI_FUNCTION(0x6, "spi3"),		/* MISO */
		SUNXI_FUNCTION(0x7, "wiegand"),		/* D0 */
		SUNXI_FUNCTION(0x8, "pwm6"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 13)),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(H, 14),
		SUNXI_FUNCTION(0x0, "gpio_in"),
		SUNXI_FUNCTION(0x1, "gpio_out"),
		SUNXI_FUNCTION(0x2, "jtag"),		/* DI */
		SUNXI_FUNCTION(0x3, "mdio"),
		SUNXI_FUNCTION(0x4, "r_jtag"),		/* DI */
		SUNXI_FUNCTION(0x5, "i2c3"),		/* SDA */
		SUNXI_FUNCTION(0x6, "spi3"),		/* CS0 */
		SUNXI_FUNCTION(0x7, "wiegand"),		/* D1 */
		SUNXI_FUNCTION(0x8, "pwm7"),
		SUNXI_FUNCTION_IRQ_BANK(0xe, 5, 14)),
};

static const unsigned int v853_irq_bank_map[] = { 0, 2, 3, 4, 5, 7 };

static const struct sunxi_pinctrl_desc v853_pinctrl_data = {
	.pins			= v853_pins,
	.npins			= ARRAY_SIZE(v853_pins),
	.irq_banks		= ARRAY_SIZE(v853_irq_bank_map),
	.irq_bank_map		= v853_irq_bank_map,
	.io_bias_cfg_variant	= BIAS_VOLTAGE_PIO_POW_MODE_CTL,
};

static int v853_pinctrl_probe(struct platform_device *pdev)
{
	unsigned long variant = (unsigned long)of_device_get_match_data(&pdev->dev);

	return sunxi_pinctrl_init_with_variant(pdev, &v853_pinctrl_data, variant);
}

static const struct of_device_id v853_pinctrl_match[] = {
	{
		.compatible = "allwinner,sun8i-v853-pinctrl",
		.data = (void *)PINCTRL_SUN8I_V853
	},
	{}
};

static struct platform_driver v853_pinctrl_driver = {
	.probe	= v853_pinctrl_probe,
	.driver	= {
		.name		= "sun8i-v853-pinctrl",
		.of_match_table	= v853_pinctrl_match,
	},
};
builtin_platform_driver(v853_pinctrl_driver);
