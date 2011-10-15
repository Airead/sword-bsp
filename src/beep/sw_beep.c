/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 13 22:25:53 CST			*
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

#include "imx233.h"
#include "sw_beep.h"

/* regsiter define */
struct HW_PINCTRL * const pinctrl = 
	(struct HW_PINCTRL *) REGS_PINCTRL_BASE_PHYS;

/*
 * Initialize the environment of beep
 */
int sw_beep_init()
{
	/*
	 * 1. find bank and pin
	 *     CONTROL --> (91)PWM2/GPMI_RDY3 --> bank1 pin28
	 */
	
	/*
	 * Wirte to HW_PINCTRL_DRIVEx register bit to select desired
	 * pin voltage;
	 * | 17:16 | BANK1_PIN28_MA | RW | 0x0 | 
	 * Pin 129, PWM2 pin output drive strength selection:
	 * 00= 4 mA;
	 * 01= 8 mA;
	 * 10= 12 mA;
	 * 11= reserved.
	 */
	pinctrl->drive[7].clr = 3 << 16; /* set 4mA */
	
	/*
	 * Write to HW_PINCTRL_MUXSEL3 register bit to select pin as GPIO;
	 * 00= pwm2;\
	 * 01= gpmi_ready3;
	 * 10= reserved;
	 * 11= GPIO.
	 */
	pinctrl->muxsel[3].set = 3 << 24; /* set GPIO */

	/*
	 * Write zero to HW_PINCTRL_DOE1 register bit to ensure pin
	 * is selected as an input;
	 * Each bit in this register corresponds to one of the 31
	 * pins in bank 1. Setting a bit in this register to one
	 * allows the chip to drive the corresponding pin in GPIO
	 * mode.
	 */
	pinctrl->doe[1].set = 1 << 28; /* enable bank1 pin28 to GPIO */

	/* if applicable, set bits in HW_PINCTRL_PULL */
	/* here do nothing */

	/*
	 * Read HW_PINCTRL_DIN1 register bit to get the value on the pin;
	 * Each bit in this read-only register corresponds to one
	 * of the 31 pins in bank 1. The current state of each pin
	 * in bank 1, synchronized to HCLK, may be read here.
	 */
	/* here do nothing */

	return 0;
}

int sw_beep_close()
{
	/*
	 * Write zero to HW_PINCTRL_DOE1 register bit to ensure pin
	 * is selected as an input;
	 * Each bit in this register corresponds to one of the 31
	 * pins in bank 1. Setting a bit in this register to one
	 * allows the chip to drive the corresponding pin in GPIO
	 * mode.
	 */
	pinctrl->doe[1].clr = 1 << 28; /* disable bank1 pin28 to GPIO */
	
	return 0;
}

int sw_beep_on()
{
	/*
	 * turn on beep;
	 * set bank1 pin28 to 0
	 */
	pinctrl->dout[1].clr = 1 << 28;
	
	return 0;
}

int sw_beep_off()
{
	/*
	 * turn off beep;
	 * set bank1 pin28 to 1
	 */
	pinctrl->dout[1].set = 1 << 28;
	
	return 0;
}
