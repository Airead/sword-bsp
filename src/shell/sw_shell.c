/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 19 14:30:44 CST			*
 ********************************************************
 *		after studying C 93 days		*
 *		after studying APUE 58 days		*
 *		after studying ARM 11 days		*
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

#include "sw_stdio.h"
#include "sw_shell.h"
#include "sw_beep.h"
#include "sw_uartdbg.h"
#include "swstd.h"
#include "sw_shcmd.h"

int sw_shell_main()
{
	int i;
	char cmd_buf[CMD_BUF_SIZE];

	/* Intialize used module */
	sw_beep_init();
	sw_uartdbg_nofifo_init();

	/* Beep 3 times indicates the start of the New World */
	for(i = 0; i < 3; i++){
		sw_beep_on();
		sw_usleep(150 * 1000);
		sw_beep_off();
		sw_usleep(50 * 1000);
	}

	for(;;){
		sw_printf("x-boot# ");
		sw_getn(cmd_buf, CMD_BUF_SIZE);
		cmd_run(cmd_buf);
	}
	return 0;
}
