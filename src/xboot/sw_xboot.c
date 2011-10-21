/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 21 16:23:46 CST			*
 ********************************************************
 *		after studying C 95 days		*
 *		after studying APUE 60 days		*
 *		after studying ARM 13 days		*
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
#include "sw_xboot.h"
#include "sw_shell.h"
#include "swstd.h"

int sw_xboot_main(void)
{
	int i;
	int waitsec;
	char *promt = "input any key to enter x-boot: ";

	waitsec = 3;

	sw_printf("\n\n\n\r");
	sw_printf("%s: %u\r", promt, waitsec);
	for(i = waitsec; i > 0; i--){
		sw_usleep(1000 * 1000);
		waitsec--;
		if(sw_trygetchar(NULL) == 1){
			sw_printf("\n\n\rstart x-boot, please wait...\n\n\r");
			sw_shell_main();
		}
		sw_printf("%s: %u\r", promt, waitsec);
	}

	sw_printf("\n\n\rstart Linux kernel, please wait...\n\r");
	for(;;){
		sw_printf(".");
		sw_usleep(888 * 1000);
	}

	return 0;
}
