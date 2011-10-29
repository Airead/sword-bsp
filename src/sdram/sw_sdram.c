/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 27 22:54:13 CST			*
 ********************************************************
 *		after studying C 101 days		*
 *		after studying APUE 66 days		*
 *		after studying ARM 19 days		*
 ********************************************************/

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
#include "sw_sdram.h"
#include "swstd.h" 

static CLKCTRL * const clkctrl = (CLKCTRL*) REGS_CLKCTRL_BASE_PHYS;
#define hw_clkctrl (*clkctrl)
static PINCTRL * const pinctrl = (PINCTRL*) REGS_PINCTRL_BASE_PHYS;
#define hw_pinctrl (*pinctrl) 
static POWER * const power = (POWER*) REGS_POWER_BASE_PHYS;
#define hw_power (*power)
static EMI * const emi = (EMI*) REGS_EMI_BASE_PHYS;
#define hw_emi (*emi)
static DRAM * const dram = (DRAM*) REGS_DRAM_BASE_PHYS;
#define hw_dram (*dram)

int sw_sdram_init()
{
	sw_sdram_power_init();
	sw_sdram_clock_init();
	sw_sdram_pins_init();

	
	return 0;
}

int sw_sdram_pins_init()
{
	int i;

	/*EMI DDR SDRAM init for EMI pins*/
	//hw_pinctrl.drive[9-14]: no need to set this time, we use default value, 2.5V/4ma
	//seems not work, change to 2.5V/12ma
	for(i=9;i<=14;i++)
		hw_pinctrl.drive[i].dat = 0x33333333;//0;//0x77777777;

	hw_pinctrl.muxsel[4].clr = 0xfffc0000; //open A0-A6
	hw_pinctrl.muxsel[5].clr = 0xfc3fffff; //open cas,ras,we,ce0/1,a7-a12,ba0/1
	hw_pinctrl.muxsel[6].clr = 0xffffffff; //open d0-d15
	hw_pinctrl.muxsel[7].clr = 0x00000fff; //open clk,clkn, dqs,dqm

	//hw_pinctrl.pull[3].clr = 0x0003ffff;	//disable padkeeper on EMI pins

	/* set register of emi */
	hw_emi.ctrl.clr = 0xc0000000; //clr soft-rest and gate

	hw_dram.ctl[0] = 0x01010001;
	hw_dram.ctl[1] = 0x00010000;
	hw_dram.ctl[2] = 0x01000000;
	hw_dram.ctl[3] = 0x00000001;
	hw_dram.ctl[4] = 0x00000101;
	hw_dram.ctl[5] = 0x00000000;
	hw_dram.ctl[6] = 0x00010000;
	hw_dram.ctl[7] = 0x01000001;
	hw_dram.ctl[9] = 0x00000001;

	hw_dram.ctl[10] = 0x07000200;
	hw_dram.ctl[11] = 0x00070202; //64MB, col-line: 10
	hw_dram.ctl[12] = 0x02020000;
	hw_dram.ctl[13] = 0x04040a01;
	hw_dram.ctl[14] = 0x00000201;
	hw_dram.ctl[15] = 0x02040000;
	hw_dram.ctl[16] = 0x02000000;
	hw_dram.ctl[17] = 0x25001506;
	hw_dram.ctl[18] = 0x1f1f0000;
	hw_dram.ctl[19] = 0x027f1a1a;

	hw_dram.ctl[20] = 0x02041c22;//ras-min: 5->4 
	hw_dram.ctl[21] = 0x00000006;//trfc: 7->6
	hw_dram.ctl[22] = 0x00080008;
	hw_dram.ctl[23] = 0x00200020;
	hw_dram.ctl[24] = 0x00200020;
	hw_dram.ctl[25] = 0x00200020;
	hw_dram.ctl[26] = 0x00000269;//tref:0x2e6->269
	hw_dram.ctl[29] = 0x00000000;//lowpower_external_cnt:20->00
	hw_dram.ctl[30] = 0x00000000;//lowpower_external_cnt:20->00
	hw_dram.ctl[31] = 0x00c80000;
	hw_dram.ctl[32] = 0x000615d6;//0x00081a3b;
	hw_dram.ctl[33] = 0x000000c8;
	hw_dram.ctl[34] = 0x00003e80;//4b0d;
	hw_dram.ctl[36] = 0x00000101;
	hw_dram.ctl[37] = 0x00040001;
	hw_dram.ctl[38] = 0x00000000;
	hw_dram.ctl[39] = 0x00000000;
	hw_dram.ctl[40] = 0x00010000;
	hw_dram.ctl[8] = 0x01000000; //start sdram controller (0x40000000~0x44000000)
	sw_usleep(10000);
	hw_dram.ctl[8] |= 0x00010000;

	return 0;
}

int sw_sdram_power_init()
{
	unsigned int val;
	hw_power.ctrl.clr = 0x40000000; //gate on power-ctrl domain

	val = hw_power.vdddctrl;
	val &= ~0x1f;	//bit0-4, vddd output voltage triger 
	val |= ((1550-800)/25)&0x1f;	//set to 1.55v, default 1.2v
	hw_power.vdddctrl = val; //for higher cpu freq.: 454MHz

	/*Vdd-Mem output voltage*/
	hw_power.vddmemctrl = 0xf00 | (((2500-1700)/50)&0x1f); //2.5v output, and enable current limit in case of damage 
	sw_usleep(1000); //wait 1ms for capacitor charging
	hw_power.vddmemctrl &= ~0x600;	//clear current limit and pull down

	return 0;
}

int sw_sdram_clock_init()
{
	/*enable PLL and set dividor fraction*/
	hw_clkctrl.pllctrl[0].set = 0x10000; //power on pll
	sw_usleep(150); //wait pll lock

	/*set cpu freq. to 454Mhz CLK_P*/
	hw_clkctrl.frac.clr = 0x3f;//6bit int. divider
	hw_clkctrl.frac.set = 19; //480Mhz * (18/19) = 454Mhz :ref_cpu
	hw_clkctrl.frac.clr = 0x80; //enable clock gate of cpu
	
	/*set AHB bus freq. CLK_H*/
	hw_clkctrl.hbus.set = 0x1f; //mask div fraction
	hw_clkctrl.hbus.clr = 0x1b; //454Mhz/4=113.5Mhz
	//hw_clkctrl.hbus.clr = 0x19;

	hw_clkctrl.clkseq.clr = 0x80; //switch cpu clock to pll (clear bypassing)
	// well, we got cpu running at 454Mhz now! 

	/*set EMI clock to 80Mhz */

	hw_clkctrl.frac.set = 0x3f00; 
	//hw_clkctrl.frac.clr = 0x400; //~27 ; //480Mhz * (18/27) = 320Mhz :ref_emi
	hw_clkctrl.frac.clr = 0x2100;  //480Mhz * (18/30) = 288Mhz :ref_emi
	hw_clkctrl.frac.clr = 0x8000; //enable clock gate of emi
	sw_usleep(100);	
	//hw_clkctrl.emi &= ~0x1f; //clear emi dividor
	hw_clkctrl.emi |= 0x3f;
	//hw_clkctrl.emi |= 0x4; //320Mhz/4 =80Mhz , the final emi freq.
	//hw_clkctrl.emi &= ~0x17;//1b; //320M/4=80M
	hw_clkctrl.emi &= ~0x3c; //288M/3=96M
	//zhai comment @class
	hw_clkctrl.emi &= ~0xc0000000; //clr gate, syc disble

	hw_clkctrl.clkseq.clr = 0x40; //enable emi clock to pll (clear bypassing)

	return 0;
}
