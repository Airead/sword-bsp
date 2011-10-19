/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 19 18:25:01 CST			*
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

#include "sw_str.h"
#include "sw_stdio.h"

int strtest(int argc, char *argv[])
{
	int ret;

	/* test sw_strcmp */
	sw_puts("----------------------");
	sw_puts("\n\r");
	sw_puts("fand compare fan: ");
	ret = sw_strcmp("fand", "fan");
	sw_putchar(ret | 0x30);
	sw_puts("\n\r");

	sw_puts("fan compare li: ");
	ret = sw_strcmp("fan", "li");
	sw_putchar(ret | 0x30);
	sw_puts("\n\r");

	sw_puts("li compare fan: ");
	ret = sw_strcmp("li", "fan");
	sw_putchar(ret | 0x30);
	sw_puts("\n\r");

	return 0;
}
