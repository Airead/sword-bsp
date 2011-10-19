/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 19 15:23:08 CST			*
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

#ifndef SWORD_STDIO_H
#define SWORD_STDIO_H

#define NULL ((void *)0)

int sw_getchar();
int sw_putchar(char c);
char *sw_getn(char *str, int n);
int sw_puts(char *str);

#endif
