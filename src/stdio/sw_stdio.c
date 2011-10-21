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
#include "stdarg.h"

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
		if(ch == '\b' && count != 0){
			p--;
			*p = ' ';
			sw_printf("\b \b");
			count--;
		}else if(ch != '\b'){
			count++;
			*p++ = ch;
			sw_putchar(ch);
		}
		ch = sw_getchar();
	}
	*p = '\0';

	sw_printf("\n\r");

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

/*
 * family produce output according to a format
 *   1. %u for Decimal unsigned int
 *   2. %s for string
 *   3. %x for hex unsigned int
 *   4. %% output '%'
 */
int sw_printf(const char *format, ...)
{
	int i;
	va_list ap;

	va_start(ap, format);
	
	for(i = 0; format[i] != '\0'; i++){
		if(format[i] == '%'){
			i++;
			switch(format[i]){
			case 's':
				sw_puts(va_arg(ap, char *));
				continue;
			case 'x':
				sw_put_hex(va_arg(ap, unsigned int));
				continue;
			case 'u':
				sw_put_uint(va_arg(ap, unsigned int));
				continue;
			case '%':
				sw_putchar('%');
				continue;
			}
		}
		sw_putchar(format[i]);
	}

	return i;
}

/*
 * output unsigned int with Decimal string
 */
int sw_put_uint(unsigned int num)
{
	int i;
	char num_buf[15];

	i = 0;
	while((num / 10) != 0){
		num_buf[i++] = (num % 10) | 0x30;
		num /= 10;
	}
	sw_putchar(num | 0x30);

	for(i = i - 1; i >= 0; i--){
		sw_putchar(num_buf[i]);
	}

	return num;
}

/*
 * output unsigned int with hex string
 */
int sw_put_hex(unsigned int num)
{
	int i;
	char tmp;
	char hex_flag[] = "0123456789ABCDEF";

	for(i = 28; i >= 0; i -= 4){
		tmp = (num >> i) & 0xf;
		sw_putchar(hex_flag[(int)tmp]);
	}

	return num;
}

/*
 * Try to get one char from serial port with uartdbg
 *   @retrun: 1 is received, 0 is not
 */
int sw_trygetchar(char *ch)
{
	if(sw_uartdbg_isrc() == 1){
		*ch = sw_uartdbg_rc() & 0xff;
		return 1;
	}else{
		return 0;
	}
}
