// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2024 Iscle <albertiscle9@gmail.com>
 */

#include <linux/clk-provider.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>

#include "ccu_common.h"
#include "ccu_reset.h"

#include "ccu_gate.h"
#include "ccu_mp.h"

#include "ccu-sun8i-v853-r.h"

static const char *const ahb_apb0_parents[] = {
	"hosc",
	"losc",
	"iosc",
	"pll-periph",
};
static SUNXI_CCU_MP_WITH_MUX(r_ahb_clk, "r-ahb", ahb_apb0_parents, 0x000,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  0);

static SUNXI_CCU_MP_WITH_MUX(r_apb0_clk, "r-apb0", ahb_apb0_parents, 0x00c,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  0);

static SUNXI_CCU_GATE_HW(r_ppu_clk, "r-ppu", &r_apb0_clk.common.hw, 0x01ac, BIT(16), 0);
static SUNXI_CCU_GATE_HW(r_rtc_clk, "r-rtc", &r_ahb_clk.common.hw, 0x020c, BIT(16), 0);
static SUNXI_CCU_GATE_HW(r_cpucfg_clk, "r-cpucfg", &r_apb0_clk.common.hw,
			 0x022c, BIT(16), 0);

static struct ccu_reset_map sun8i_v853_r_ccu_resets[] = {
	[RST_BUS_R_TWD]		= { 0x012c, BIT(0) },
	[RST_BUS_R_PPU]		= { 0x01ac, BIT(0) },
	[RST_BUS_R_RTC]		= { 0x020c, BIT(0) },
	[RST_BUS_R_CPUCFG]	= { 0x022c, BIT(0) },
};

static struct clk_hw_onecell_data sun8i_v853_r_hw_clks = {
	.hws    = {
		[CLK_R_AHB]		= &r_ahb_clk.common.hw,
		[CLK_R_APB0]		= &r_apb0_clk.common.hw,
		[CLK_BUS_R_PPU]		= &r_ppu_clk.common.hw,
		[CLK_BUS_R_RTC]		= &r_rtc_clk.common.hw,
		[CLK_BUS_R_CPUCFG]	= &r_cpucfg_clk.common.hw,
	},
	.num = CLK_NUMBER,
};

static struct ccu_common *sun8i_v853_r_ccu_clks[] = {
	&r_ahb_clk.common,
	&r_apb0_clk.common,
	&r_ppu_clk.common,
	&r_rtc_clk.common,
	&r_cpucfg_clk.common,
};


static const struct sunxi_ccu_desc sun8i_v853_r_ccu_desc = {
	.ccu_clks	= sun8i_v853_r_ccu_clks,
	.num_ccu_clks	= ARRAY_SIZE(sun8i_v853_r_ccu_clks),

	.hw_clks	= &sun8i_v853_r_hw_clks,

	.resets		= sun8i_v853_r_ccu_resets,
	.num_resets	= ARRAY_SIZE(sun8i_v853_r_ccu_resets),
};

static int sun8i_v853_r_ccu_probe(struct platform_device *pdev)
{
	void __iomem *reg;

	reg = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(reg))
		return PTR_ERR(reg);

	return devm_sunxi_ccu_probe(&pdev->dev, reg, &sun8i_v853_r_ccu_desc);
}

static const struct of_device_id sun8i_v853_r_ccu_ids[] = {
	{ .compatible = "allwinner,sun8i-v853-r-ccu" },
	{ }
};

static struct platform_driver sun8i_v853_r_ccu_driver = {
	.probe	= sun8i_v853_r_ccu_probe,
	.driver	= {
		.name			= "sun8i-v853-r-ccu",
		.suppress_bind_attrs	= true,
		.of_match_table		= sun8i_v853_r_ccu_ids,
	},
};
module_platform_driver(sun8i_v853_r_ccu_driver);

MODULE_IMPORT_NS(SUNXI_CCU);
MODULE_LICENSE("GPL");
