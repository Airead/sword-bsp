/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 22 22:46:02 CST			*
 ********************************************************
 *		after studying C 96 days		*
 *		after studying APUE 61 days		*
 *		after studying ARM 14 days		*
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

static CLKCTRL * const clkctrl = (CLKCTRL*) REGS_CLKCTRL_BASE_PHYS;
#define hw_clkctrl (*clkctrl)
static PINCTRL * const pinctrl = (PINCTRL*) REGS_PINCTRL_BASE_PHYS;
#define hw_pinctrl (*pinctrl) 

int sw_gpmi_init(void)
{
	/*set GPMI freq. */
	hw_clkctrl.gpmi &= ~(1<<31); //xtal clk 24Mhz to GPMI

	/*GPMI pin initialized for GPMI-8 and CE0 & CE1*/
	hw_pinctrl.muxsel[0].clr = 0xffff; //open gpmi_d0 - d7
	hw_pinctrl.muxsel[1].clr = 0x000fc3cf;//0x000fc3c3;open r/w wp, ready0,1, ALE, CLE
	hw_pinctrl.muxsel[5].clr = 0x03c00000;// 0x03000000; ////opne ce0/1
	hw_pinctrl.pull[0].set = 0xff;
	
	return 0;
}
