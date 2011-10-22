/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 22 21:59:48 CST			*
 ********************************************************
 *		after studying C 96 days		*
 *		after studying APUE 61 days		*
 *		after studying ARM 14 days		*
 ********************************************************/

/* this program come from NiuBoot */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "regs_imx233.h"
#include "dm9000x_gpmi.h"
#include "swstd.h"

#define udelay(us) sw_usleep(us)

static GPMI * const gpmi = (GPMI*) REGS_GPMI_BASE_PHYS;
#define hw_gpmi (*gpmi)
static APBH * const apbh = (APBH*) REGS_APBH_BASE_PHYS;
#define hw_apbh (*apbh)

unsigned int gpmi_dm9000_read_reg(unsigned int regno)
{
	//gpmi-1, dm9000 ethernet, 8bit mode
	volatile unsigned int regval = 0;
	DMA_CMD reg_read[2] =
		{
			{
				&reg_read[1],//next command
				2,//command: 
				1,//:chain
				0,//irq_complete
				0,//nandlock
				0,//nandwait4ready
				0,//decrement_semaphore
				1,//wait4endcmd
				0,//un-used
				1, //piowords_cnt
				1, //xffer_cnt
				(unsigned int*)&regno,
				{0x00d00001}
			},
			{
				0,//next command address

				1,//command, 01 for dma write
				0,//chain
				1,//irq_complete
				0,//nandlock
				0,//nandwait4ready
				1,//decrement semaphore
				1,//wait4endcmd
				0,//unused
				1,
				1, //xfer_cnt
				(unsigned int*)&regval,
				{0x01920001}
			}
		
		};

	//reset gpmi
	hw_gpmi.ctrl0.set = 1<<31;
	udelay(0xf);
	hw_gpmi.ctrl0.clr = 0xc0000000;
	//hw_gpmi.timing0 = 0x00200406;

	//reset APBH
	hw_apbh.ctrl[0].set =1<<31; //0x80100000;
	udelay(0xf);
	hw_apbh.ctrl[0].clr = 0xc0000000;
//while(1)
	//start dma transferring
	hw_apbh.ch[5].nxtcmdar = (unsigned int) reg_read; 
	//printf("reg_read=%x\n", reg_read);
	hw_apbh.ch[5].sema = 0x1;
	while(!(hw_apbh.ctrl[1].dat & (1<<5)));
	//udelay(0x1fff);
	//printf("regval add=%x\n",&regval);

	//hw_apbh.ctrl[1].clr = 1<<5;
	//while(1);
	return regval;
}

void gpmi_dm9000_write_reg(unsigned int regno, unsigned int regval)
{
	//gpmi-1, dm9000 ethernet, 8bit mode
	DMA_CMD reg_write[2] =
		{
			{
				&reg_write[1],//next command
				2,//command: 
				1,//:chain
				0,//irq_complete
				0,//nandlock
				0,//nandwait4ready
				0,//decrement_semaphore
				1,//wait4endcmd
				0,//un-used
				1, //piowords_cnt
				1, //xffer_cnt
				(unsigned int*)&regno,
				{0x00d00001}
			},
			{
				0,//next command address

				2,//command, 01 for dma read 
				0,//chain
				1,//irq_complete
				0,//nandlock
				0,//nandwait4ready
				1,//decrement semaphore
				1,//wait4endcmd
				0,//unused
				1,
				1, //xfer_cnt
				(unsigned int*)&regval,
				{0x00920001}
			}
		
		};

	//reset gpmi
	hw_gpmi.ctrl0.set = 1<<31;
	udelay(0xf);
	hw_gpmi.ctrl0.clr = 0xc0000000;
	//hw_gpmi.timing0 = 0x00200406;

	//reset APBH
	hw_apbh.ctrl[0].set =1<<31; //0x80100000;
	udelay(0xf);
	hw_apbh.ctrl[0].clr = 0xc0000000;

	//start dma transferring
	hw_apbh.ch[5].nxtcmdar = (unsigned int) reg_write; 
	hw_apbh.ch[5].sema = 0x1;
	//udelay(0x1fff);

	while(!(hw_apbh.ctrl[1].dat & (1<<5)));
	//hw_apbh.ctrl[1].clr = 1<<5;
}
void gpmi_dm9000_read_data_bulk(unsigned char* buf, int count)
{
	//gpmi-1, dm9000 ethernet, 8bit mode
	DMA_CMD data_read =
		{
			0,//next command address
			1,//command, 01 for dma write
			0,//chain
			1,//irq_complete
			0,//nandlock
			0,//nandwait4ready
			1,//decrement semaphore
			1,//wait4endcmd
			0,//unused
			1,
			count, //xfer_cnt
			(unsigned int*)buf,
			{0x01d30000 | (count&0xffff)}
		};
	//reset gpmi
	hw_gpmi.ctrl0.set = 1<<31;
	udelay(0xf);
	hw_gpmi.ctrl0.clr = 0xc0000000;
	//reset APBH
	hw_apbh.ctrl[0].set =1<<31; //0x80100000;
	udelay(0xf);
	hw_apbh.ctrl[0].clr = 0xc0000000;
	//start dma transferring
	hw_apbh.ch[5].nxtcmdar = (unsigned int) &data_read; 
	hw_apbh.ch[5].sema = 0x1;
	while(!(hw_apbh.ctrl[1].dat & (1<<5)));
}
void gpmi_dm9000_write_data_bulk(unsigned char* buf, int count)
{
	//gpmi-1, dm9000 ethernet, 8bit mode
	DMA_CMD data_write =
		{
			0,//next command address
			2,//command, 01 for dma read 
			0,//chain
			1,//irq_complete
			0,//nandlock
			0,//nandwait4ready
			1,//decrement semaphore
			1,//wait4endcmd
			0,//unused
			1,
			count, //xfer_cnt
			(unsigned int*)buf,
			{0x00d30000 | (count&0xffff)}
		};
	//reset gpmi
	hw_gpmi.ctrl0.set = 1<<31;
	udelay(0xf);
	hw_gpmi.ctrl0.clr = 0xc0000000;
	//reset APBH
	hw_apbh.ctrl[0].set =1<<31; 
	udelay(0xf);
	hw_apbh.ctrl[0].clr = 0xc0000000;
	//start dma transferring
	hw_apbh.ch[5].nxtcmdar = (unsigned int) &data_write; 
	hw_apbh.ch[5].sema = 0x1;
	while(!(hw_apbh.ctrl[1].dat & (1<<5)));
}
void gpmi_dm9000_write_reg_index(unsigned int index)
{
	//gpmi-1, dm9000 ethernet, 8bit mode
	DMA_CMD reg_write =
		{
			0,//next command
			2,//command: 
			0,//:chain
			1,//irq_complete
			0,//nandlock
			0,//nandwait4ready
			0,//decrement_semaphore
			1,//wait4endcmd
			0,//un-used
			1, //piowords_cnt
			1, //xffer_cnt
			(unsigned int*)&index,
			{0x00d00001}
		};

	//reset gpmi
	hw_gpmi.ctrl0.set = 1<<31;
	udelay(0xf);
	hw_gpmi.ctrl0.clr = 0xc0000000;
	//reset APBH
	hw_apbh.ctrl[0].set =1<<31; //0x80100000;
	udelay(0xf);
	hw_apbh.ctrl[0].clr = 0xc0000000;
	//start dma transferring
	hw_apbh.ch[5].nxtcmdar = (unsigned int) &reg_write; 
	hw_apbh.ch[5].sema = 0x1;
	while(!(hw_apbh.ctrl[1].dat & (1<<5)));
}
