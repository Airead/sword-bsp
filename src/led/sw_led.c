/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 15 20:10:52 CST			*
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
#include "sw_led.h"

/* regsiter define */
static struct HW_PINCTRL * const pinctrl = 
	(struct HW_PINCTRL *) REGS_PINCTRL_BASE_PHYS;

/*
 * Initialize the environment of led
 */
int sw_led_init()
{
	/*
	 * 1. find bank and pin
	 *     GPIO1 --> (14)LCD_RS/LCD_CCIRCLK --> bank1 pin19
	 */
	
	/*
	 * Wirte to HW_PINCTRL_DRIVE6 register bit to select desired
	 * pin voltage;
	 * | 17:16 | BANK1_PIN19_MA | RW | 0x0 | 
	 * 00= 4 mA;
	 * 01= 8 mA;
	 * 10= 12 mA;
	 * 11= reserved.
	 */
	pinctrl->drive[6].clr = 3 << 16; /* set 4mA */
	
	/*
	 * Write to HW_PINCTRL_MUXSEL3 register bit to select pin as GPIO;
	 * 7:6 bit
	 * 00= lcd_rs;
	 * 01= etm_tclk;
	 * 10= reserved;
	 * 11= GPIO.
	 */
	pinctrl->muxsel[3].set = 3 << 6; /* set GPIO */

	/*
	 * Write zero to HW_PINCTRL_DOE1 register bit to ensure pin
	 * is selected as an input;
	 * Each bit in this register corresponds to one of the 31
	 * pins in bank 1. Setting a bit in this register to one
	 * allows the chip to drive the corresponding pin in GPIO
	 * mode.
	 */
	pinctrl->doe[1].set = 1 << 19; /* enable bank1 pin19 to GPIO */

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

int sw_led_close()
{
	/*
	 * Write zero to HW_PINCTRL_DOE1 register bit to ensure pin
	 * is selected as an input;
	 * Each bit in this register corresponds to one of the 31
	 * pins in bank 1. Setting a bit in this register to one
	 * allows the chip to drive the corresponding pin in GPIO
	 * mode.
	 */
	pinctrl->doe[1].clr = 1 << 19; /* disable bank1 pin19 to GPIO */
	
	return 0;

}

int sw_led_on()
{
	/*
	 * turn on led;
	 * set bank1 pin28 to 0
	 */
	pinctrl->dout[1].clr = 1 << 19;
	
	return 0;
}

int sw_led_off()
{
	/*
	 * turn off led;
	 * set bank1 pin28 to 1
	 */
	pinctrl->dout[1].set = 1 << 19;
	
	return 0;
}
