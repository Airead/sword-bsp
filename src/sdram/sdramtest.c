/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 27 23:16:16 CST			*
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

#include "sw_sdram.h"
#include "swstd.h"
#include "sw_stdio.h"

#define STEP (4 * 4 * 4 * 4 * 4)

int sdramtest(int argc, char *argv[])
{
	int *addr = (int *)0x40008000;
	int *endaddr = (int *)0x44000000;
	int *p;
	

	sw_sdram_init();

	while(1){
		p = addr;
		while(p < endaddr){
			*p = (int)p;
			p += STEP;
		}

		p = addr;
		while(p < endaddr){
			sw_printf("%x: %x\n\r", (int)p, *p);
			p += STEP;
			sw_usleep(1 * 1000);
		}
	}

	return 0;
}
