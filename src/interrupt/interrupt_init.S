/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 13 22:20:26 CST			*
 ********************************************************
 *		after studying C 87 days		*
 *		after studying APUE 52 days		*
 *		after studying ARM 5 days		*
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

@This is an `testbeep` entry routine

	.arm

	.section ".init", "ax"
	.global irq_enable
irq_enable:
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c , r0
	mov pc, lr

	.global irq_disable
irq_disable:
	mrs r0, cpsr
	orr r0, r0, #0x80
	msr cpsr_c , r0
	mov pc, lr

	.end