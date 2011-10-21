/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 15 21:29:22 CST			*
 ********************************************************
 *		after studying C 89 days		*
 *		after studying APUE 54 days		*
 *		after studying ARM 7 days		*
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

#ifndef SWORD_UART_H
#define SWORD_UART_H

#define SW_UART_CLK (24 * 1000 * 1000)
#define SW_UART_BAUDRATE (115200)

int sw_uartdbg_nofifo_init();
int sw_uartdbg_close();
int sw_uartdbg_tc(unsigned char c);
int sw_uartdbg_rc();
int sw_uartdbg_isrc();

#endif
