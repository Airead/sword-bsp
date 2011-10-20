/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 20 12:07:26 CST			*
 ********************************************************
 *		after studying C 94 days		*
 *		after studying APUE 59 days		*
 *		after studying ARM 12 days		*
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

#include "sw_xmodem.h"
#include "sw_stdio.h"
#include "swstd.h"

/*
 * Before call this funtion, you SHOULD have initialize uartdbg.
 *
 * Receive data from host
 *   @return: bytes of receive data
 */
unsigned int sw_xmodem_rec(unsigned int addr)
{
	int c;
	int i;
	int count;
	char *xbuf;
	
	xbuf = (char *)addr;

	count = 0;

	sw_printf("Countdown to receive data, you have 10 seconds...");
	for(i = 9; i >= 0; i--)
	{
		sw_usleep(1000 * 1000);
		sw_printf("%u ", i);
	}

	sw_putchar(XMODEM_NAK); //start transfer

	for(;;){
		c = sw_getchar();

		if(c == XMODEM_EOT){
			break;
		}
		if(c != XMODEM_SOH){
			continue;
		}

		sw_getchar();	/* eat package number */
		sw_getchar();	/* eat package ~number */

		for(i = 0; i < 128; i++){
			*xbuf++ = sw_getchar();
		}
		
		sw_getchar();	/* eat check byte */

		sw_putchar(XMODEM_ACK);
	}
	sw_putchar(XMODEM_ACK);

	return count;
}
