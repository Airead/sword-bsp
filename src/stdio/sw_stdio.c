/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 16 13:25:30 CST			*
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

#include "sw_stdio.h"
#include "sw_uartdbg.h"

/*
 * Get one char from serial port with uartdbg
 *   @retrun: char
 */
int sw_getchar()
{
	int ch;
	
	//int sw_uartdbg_rc();
	ch = sw_uartdbg_rc() & 0xff;

	return ch;
}

/*
 * Put one char to serial port with uartdbg
 *   @return char
 */
int sw_putchar(char c)
{
	//int sw_uartdbg_tc(unsigned char c);
	sw_uartdbg_tc(c);

	return c;
}

/*
 * get n chars(include '\0'), and store them to str
 *   @retrun start pointer of str
 */
char *sw_getn(char *str, int n)
{
	int count;
	int ch;
	char *p;

	count = 0;
	p = str;
	ch = sw_getchar();
	while(count < n - 1 && ch != '\r'){
		count++;
		*p++ = ch;
		sw_putchar(ch);
		ch = sw_getchar();
	}
	*p = '\0';

	if(count == 0){
		return NULL;
	}else{
		return str;
	}
}

/*
 * puts a string that end of '\0'
 *   @return the number of put chars
 */
int sw_puts(char *str)
{
	int count;
	char *p;
	
	p = str;
	while(*p != '\0'){
		sw_putchar(*p++);
		count++;
	}

	return count;
}
