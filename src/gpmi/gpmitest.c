/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 22 22:52:30 CST			*
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
#include "sw_gpmi.h"

static POWER * const power = (POWER*) REGS_POWER_BASE_PHYS;
#define hw_power (*power)

int gpmitest(int argc, char *argv[])
{
	hw_power.ctrl.clr = 0x40000000; //gate on power-ctrl domain
	
	sw_gpmi_init();

	return 0;
}
