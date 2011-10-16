/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 16 13:45:15 CST			*
 ********************************************************
 *		after studying C 90 days		*
 *		after studying APUE 55 days		*
 *		after studying ARM 8 days		*
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

#include "sw_uartdbg.h"
#include "swstd.h"
#include "sw_beep.h"

/*
 * test output
 */
int uartdbgtest_output()
{
	for(;;){
		sw_uartdbg_tc('A');
		sw_usleep(100 * 1000);
	}
	return 0;
}

/*
 * test input
 */
int uartdbgtest_input()
{
	int c;

	for(;;){
		c = sw_uartdbg_rc();
		sw_beep_on();
		sw_usleep(40 * 1000);
		sw_beep_off();
		sw_uartdbg_tc(c);
	}

	return 0;
}

int uartdbgtest(int argc, char *argv[])
{
	sw_beep_init();
	sw_uartdbg_nofifo_init();
	
	/* test output */
//	uartdbgtest_output();

	/* test input */
	uartdbgtest_input();

	return 0;
}
