// SPDX-License-Identifier: GPL-2.0
/*
 * MUSB OTG driver - support for Allwinner (sunxi) DMA controller
 *
 * Copyright (C) 2024 Iscle <albertiscle9@gmail.com>
 * 
 * Based on musbhsdma.c, which is:
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2007 by Texas Instruments
 */

#include <linux/device.h>
#include <linux/dmaengine.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include "musb_core.h"
#include "musb_dma.h"

#define SUNXI_MUSB_DMA_MAX_CHANNELS	5

struct sunxi_musb_dma_controller;

struct sunxi_musb_dma_channel {
	struct dma_channel			channel;
	struct sunxi_musb_dma_controller	*controller;
	struct dma_chan				*chan;
	dma_cookie_t				dma_cookie;
	u8					epnum;
	u8					is_tx;
	u32					len;
	u16					packet_sz;
};

struct sunxi_musb_dma_controller {
	struct dma_controller		controller;
	void __iomem			*base;
	dma_addr_t			phy_base;
	struct sunxi_musb_dma_channel	tx_channels[SUNXI_MUSB_DMA_MAX_CHANNELS];
	struct sunxi_musb_dma_channel	rx_channels[SUNXI_MUSB_DMA_MAX_CHANNELS];
};

static void sunxi_musb_dma_channel_release(struct dma_channel *channel)
{
	channel->status = MUSB_DMA_STATUS_UNKNOWN;
}

static struct dma_channel *sunxi_musb_dma_channel_allocate(
	struct dma_controller *c, struct musb_hw_ep *hw_ep, u8 is_tx)
{
	struct sunxi_musb_dma_controller *controller = container_of(c,
		struct sunxi_musb_dma_controller, controller);
	u8 chnum = hw_ep->epnum - 1;

	struct sunxi_musb_dma_channel *musb_channel = NULL;
	struct dma_channel *channel = NULL;

	if (chnum >= SUNXI_MUSB_DMA_MAX_CHANNELS)
		return NULL;

	if (is_tx)
		musb_channel = &controller->tx_channels[chnum];
	else
		musb_channel = &controller->rx_channels[chnum];

	channel = &musb_channel->channel;

	if (channel->status != MUSB_DMA_STATUS_UNKNOWN)
		return NULL;

	channel->status = MUSB_DMA_STATUS_FREE;

	return channel;
}

static void sunxi_musb_dma_callback(void *dma_async_param)
{
	unsigned long flags;
	struct dma_channel *channel = dma_async_param;
	struct sunxi_musb_dma_channel *musb_channel = channel->private_data;
	struct sunxi_musb_dma_controller *controller = musb_channel->controller;
	struct musb *musb = controller->controller.musb;

	spin_lock_irqsave(&musb->lock, flags);

	channel->actual_len = musb_channel->len;
	channel->status = MUSB_DMA_STATUS_FREE;

	if (musb_channel->is_tx) {
		struct musb_hw_ep *ep = &musb->endpoints[musb_channel->epnum];
		bool autoset;

		if (is_host_active(musb)) {
			struct musb_qh *qh = ep->out_qh;
			autoset = qh->hb_mult == 1 || (qh->hb_mult > 1 &&
				can_bulk_split(musb, qh->type));
		} else {
			struct musb_ep *musb_ep = &ep->ep_out;
			autoset = !musb_ep->hb_mult ||
				can_bulk_split(musb, musb_ep->type);
		}

		if (!autoset || channel->actual_len % musb_channel->packet_sz) {
			u16 csr;

			musb_ep_select(musb->mregs, musb_channel->epnum);
			csr = musb_readw(ep->regs, MUSB_TXCSR);
			csr |= MUSB_TXCSR_TXPKTRDY;
			musb_writew(ep->regs, MUSB_TXCSR, csr);
		}
	}

	musb_dma_completion(musb, musb_channel->epnum, musb_channel->is_tx);

	spin_unlock_irqrestore(&musb->lock, flags);
}

static int sunxi_musb_dma_channel_program(struct dma_channel *channel,
					  u16 packet_sz, u8 mode,
					  dma_addr_t dma_addr, u32 len)
{
	struct sunxi_musb_dma_channel *musb_channel = channel->private_data;
	struct sunxi_musb_dma_controller *controller = musb_channel->controller;
	struct musb *musb = controller->controller.musb;
	
	int ret;
	struct dma_slave_config slave_cfg;
	struct dma_async_tx_descriptor *tx_desc;

	musb_dbg(musb, "ep%d-%s pkt_sz %d, dma_addr %p, length %d, mode %d",
		musb_channel->epnum,
		musb_channel->is_tx ? "Tx" : "Rx",
		packet_sz, &dma_addr, len, mode);

	BUG_ON(channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY);

	channel->actual_len = 0;
	channel->status = MUSB_DMA_STATUS_BUSY;

	musb_channel->len = len;
	musb_channel->packet_sz = packet_sz;

	dma_addr_t fifo_addr = controller->phy_base +
		musb->io.fifo_offset(musb_channel->epnum);
	enum dma_transfer_direction direction = musb_channel->is_tx ?
		DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;

	memset(&slave_cfg, 0, sizeof(slave_cfg));
	slave_cfg.direction = direction;
	slave_cfg.src_addr = fifo_addr;
	slave_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	slave_cfg.src_maxburst = 16;
	slave_cfg.dst_addr = fifo_addr;
	slave_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	slave_cfg.dst_maxburst = 16;
	
	ret = dmaengine_slave_config(musb_channel->chan, &slave_cfg);
	if (ret)
		return 0;

	tx_desc = dmaengine_prep_slave_single(musb_channel->chan,
		dma_addr, len, direction, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!tx_desc) {
		dev_err(musb->controller, "DMA channel %d: prep failed\n",
			musb_channel->epnum - 1);
		return 0;
	}

	tx_desc->callback = sunxi_musb_dma_callback;
	tx_desc->callback_param = channel;
	musb_channel->dma_cookie = tx_desc->tx_submit(tx_desc);

	dma_async_issue_pending(musb_channel->chan);

	return 1;
}

static int sunxi_musb_dma_channel_abort(struct dma_channel *channel)
{
	struct sunxi_musb_dma_channel *musb_channel = channel->private_data;
	struct musb *musb = musb_channel->controller->controller.musb;
	struct musb_hw_ep *ep = &musb->endpoints[musb_channel->epnum];

	int ret;
	u16 csr;

	if (channel->status == MUSB_DMA_STATUS_BUSY) {
		if (musb_channel->is_tx) {
			csr = musb_readw(ep->regs, MUSB_TXCSR);
			csr &= ~(MUSB_TXCSR_AUTOSET | MUSB_TXCSR_DMAENAB);
			musb_writew(ep->regs, MUSB_TXCSR, csr);
		} else {
			csr = musb_readw(ep->regs, MUSB_RXCSR);
			csr &= ~(MUSB_RXCSR_AUTOCLEAR | MUSB_RXCSR_DMAENAB);
			musb_writew(ep->regs, MUSB_RXCSR, csr);
		}

		ret = dmaengine_terminate_async(musb_channel->chan);
		if (ret < 0)
			dev_err(musb->controller, 
				"DMA channel %d: terminate failed %d\n",
				musb_channel->epnum - 1, ret);

		channel->status = MUSB_DMA_STATUS_FREE;
	}

	return 0;
}

static void sunxi_musb_dma_controller_stop(
	struct sunxi_musb_dma_controller *controller)
{
	int i;
	struct dma_chan *chan;

	for (i = 0; i < SUNXI_MUSB_DMA_MAX_CHANNELS; i++) {
		chan = controller->tx_channels[i].chan;
		if (chan)
			dma_release_channel(chan);
		chan = controller->rx_channels[i].chan;
		if (chan)
			dma_release_channel(chan);
	}
}

void sunxi_musb_dma_controller_destroy(struct dma_controller *c)
{
	struct sunxi_musb_dma_controller *controller = container_of(c,
			struct sunxi_musb_dma_controller, controller);

	sunxi_musb_dma_controller_stop(controller);

	kfree(controller);
}
EXPORT_SYMBOL_GPL(sunxi_musb_dma_controller_destroy);

struct dma_controller *
sunxi_musb_dma_controller_create(struct musb *musb, void __iomem *base)
{
	struct device *dev = musb->controller;
	struct device_node *np = dev->parent->of_node;
	struct sunxi_musb_dma_controller *controller;
	struct platform_device *pdev = to_platform_device(musb->controller);
	struct resource	*iomem;
	int count;
	int i;
	int ret;
	struct sunxi_musb_dma_channel *musb_channel;
	struct dma_channel *channel;

	controller = kzalloc(sizeof(*controller), GFP_KERNEL);
	if (!controller)
		return NULL;

	controller->controller.musb = musb;
	controller->controller.channel_alloc = sunxi_musb_dma_channel_allocate;
	controller->controller.channel_release = sunxi_musb_dma_channel_release;
	controller->controller.channel_program = sunxi_musb_dma_channel_program;
	controller->controller.channel_abort = sunxi_musb_dma_channel_abort;

	controller->base = base;

	/* Save physical address for DMA controller. */
	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!iomem) {
		dev_err(musb->controller, "no memory resource defined\n");
		goto err;
	}

	controller->phy_base = (dma_addr_t) iomem->start;

	count = of_property_count_strings(np, "dma-names");
	if (count < 0)
		return ERR_PTR(count);

	for (i = 0; i < count; i++) {
		struct dma_chan *chan;
		const char *str;
		unsigned is_tx;
		unsigned int port;

		ret = of_property_read_string_index(np, "dma-names", i, &str);
		if (ret)
			goto err;
		if (strstarts(str, "tx"))
			is_tx = 1;
		else if (strstarts(str, "rx"))
			is_tx = 0;
		else {
			dev_err(dev, "Wrong dma type %s\n", str);
			goto err;
		}
		ret = kstrtouint(str + 2, 0, &port);
		if (ret) {
			dev_err(dev, "Wrong dma port %s\n", str + 2);
			goto err;
		}

		ret = -EINVAL;
		if (port > SUNXI_MUSB_DMA_MAX_CHANNELS || !port) {
			dev_err(dev, "Wrong dma port %d\n", port);
			goto err;
		}
		if (is_tx)
			musb_channel = &controller->tx_channels[port - 1];
		else
			musb_channel = &controller->rx_channels[port - 1];

		musb_channel->controller = controller;
		musb_channel->epnum = port;
		musb_channel->is_tx = is_tx;

		channel = &musb_channel->channel;
		channel->private_data = musb_channel;
		channel->max_len = SZ_32M;
		channel->status = MUSB_DMA_STATUS_UNKNOWN;

		chan = dma_request_chan(dev->parent, str);
		if (IS_ERR(chan)) {
			ret = dev_err_probe(dev, PTR_ERR(chan),
				"Failed to request %s.\n", str);
			goto err;
		}

		musb_channel->chan = chan;
	}

	return &controller->controller;

err:
	sunxi_musb_dma_controller_stop(controller);
	kfree(controller);
	return ERR_PTR(ret);
}
EXPORT_SYMBOL_GPL(sunxi_musb_dma_controller_create);
