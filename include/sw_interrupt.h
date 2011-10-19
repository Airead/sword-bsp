/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 18 09:20:32 CST			*
 ********************************************************
 *		after studying C 92 days		*
 *		after studying APUE 57 days		*
 *		after studying ARM 10 days		*
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

#ifndef SWORD_KEYBOARD_H
#define SWORD_KEYBOARD_H

#define IRQ_LEVEL 1
#define IRQ_EDGE 0
#define IRQ_LOW 0
#define IRQ_HIGH 1

int sw_int_init_icoll();
int sw_int_init_pinctrl(int bankn, int pinn, int irqlevel, int irqpol,
			int irqsrc, int priority, void irq_handle(void));

#endif
