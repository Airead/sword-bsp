/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 15 21:29:00 CST			*
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

#include "imx233.h"
#include "sw_uartdbg.h"

/* regsiter define */
static struct HW_PINCTRL * const pinctrl = 
	(struct HW_PINCTRL *) REGS_PINCTRL_BASE_PHYS;

static struct HW_DBGUART * const dbguart = 
	(struct HW_DBGUART *) REGS_DBGDUART_BASE_PHYS;

/*
 * Initialize the environment of uartdbg
 */
int sw_uartdbg_nofifo_init()
{
	unsigned int divisor;

	/*
	 * 1. find bank and pin
	 *     URATDBG_RX --> (125)PWM0/ROTARYA/UARTDBG_RX --> bink1 pin26
	 *     URATDBG_TX --> (126)PWM1/ROTARYB/UARTDBG_TX --> bink1 pin27
	 */

	/*
	 * Set bank1 pin26/27 to dbguart mode
	 * | 21:20 | bank1 pin26 | 10 = duart_rx |
	 * | 23:22 | bank1 pin27 | 10 = duart_tx |
	 */
	pinctrl->muxsel[3].set |= 2 << 20;	/* set pin26 to dbguart mode */
	pinctrl->muxsel[3].set |= 2 << 22;	/* set pin27 to dbguart mode */

	/*
	 * Set dbguart transmission parameters, reg-->HW_UARTDBGLCR_H
	 *     Word length | 6:5 | 11 = 8 bits, 10 = 7 bits, 01 = 6 bits, 00 = 5 bits
	 *     FIFO mode | 4 | 1 = enable FIFO, 0 = disable FIFO
	 *     Stop Bits | 3 | 1 = two stop bits, 0 = one stop bit
	 *     Receive Parity Select | 2 | 1 = enable, 0 = disable
	 *     Send Parity Select | 1 | 1 = enable, 0 = disable
	 *     Send Break | 0 | For normal use, this bit must be cleared to 0.
	 */
	/*
	 * 8bits, disable FIFO, one stop bit, all parity disable, break at high
	 * set 6:0 | ?110 0000 --> 0x60; clear with ~(0x7f)
	 */
	dbguart->lcr_h &= ~(0x7f);
	dbguart->lcr_h |= 0x60;
	
	/*
	 * Set baud rate at HW_UARTDBGIBRD, HW_UARTDBGFBRD
	 * 
	 *    divisor = (UARTCLK * 4) / baud rate, rounded to the nearest integer
	 *    
	 *    The divisor must be between 0x00000040 and 0x003FFFC0, inclusive.
	 *    Program the lowest 6 bits of the divisor into BAUD_DIVFRAC,
	 *    and the next 16 bits of the divisor into BAUD_DIVINT.
	 */
	divisor = (SW_UART_CLK * 4) / SW_UART_BAUDRATE;
	dbguart->fbrd = divisor & 0x3f;
	dbguart->ibrd = (divisor >> 6) & 0xffff;

	/*
	 * Set dbguart Control Register, reg-->HW_UARTDBGCR
	 *     Receive Enable | 9 | 1 = enable | 0 = disable
	 *     Transmit Enable | 8 | 1 = enbale | 0 = disable
	 *     Loop Back Enable | 7 | I don't konw how to work?
	 *     UART Enable | 0 | 1 = enable, 0 = disable
	 */
	/*
	 * Receive Enable, Transmit Enable, Look Bakck ?(here set 0), UART enable
	 * set 9:7, 0 | ??11 ???? ???1 --> 0x301; 
	 */
	dbguart->cr |= 0x301;
	
	return 0;
}

/*
 * disable UART
 */
int sw_uartdbg_close()
{
	/*
	 * Set dbguart Control Register, reg-->HW_UARTDBGCR
	 *     UART Enable | 0 | 1 = enable, 0 = disable
	 */
	/*
	 * UART disable
	 * set 0 | 0 --> ~(0x1); 
	 */
	dbguart->cr &= ~(0x1);
	
	return 0;
}

/*
 * Transmit 8 bits to serial ports
 */
int sw_uartdbg_tc(unsigned char c)
{
	/*
	 * Read HW_UARTDBGFR, a UART flag register
	 * | Receive FIFO Full | 6 | 1 == full
	 * | Transmit FIFO Full | 5 | 1 == full
	 */
	while(dbguart->fr & (1 << 5))	/* if full, not output */
		;
	dbguart->dr = c;
	
	return c;
}

/*
 * Receive 8 bits from serial ports
 */
int sw_uartdbg_rc()
{
	/*
	 * Read HW_UARTDBGFR, a UART flag register
	 * | Receive FIFO Full | 6 | 1 == full
	 * | Transmit FIFO Full | 5 | 1 == full
	 */
	while(!(dbguart->fr & (1 << 6)))
		;

	return (dbguart->dr & 0xff);
}

/*
 * Check data is exist from serial port
 *   @return 1 for received, 0 for not received
 */
int sw_uartdbg_isrc()
{
	/*
	 * Read HW_UARTDBGFR, a UART flag register
	 * | Receive FIFO Full | 6 | 1 == full
	 * | Transmit FIFO Full | 5 | 1 == full
	 */
	if(dbguart->fr & (1 << 6)){
		return 1;
	}else{
		return 0;
	}
}
