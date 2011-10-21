/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 19 13:25:32 CST			*
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

#include "sw_interrupt.h"
#include "sw_beep.h"
#include "swstd.h"
#include "sw_led.h"

int key_pressed;

void key_handle(void)
{
	key_pressed = 1;
	irq_clear_pending(0, 23, 0);
}

int interrupttest(int argc, char *argv[])
{
	sw_beep_init();
	sw_led_init();
	sw_int_init_icoll0();
	
	/* we will set key4 to input interrupt, bank0 pin23 */

	//int sw_int_init_pinctrl(int bankn, int pinn, int irqlevel, int irqpol,
	//             int irqsrc, int priority, void irq_handle(void));
	sw_int_init_pinctrl(0, 23, IRQ_EDGE, IRQ_LOW, 16, 0, key_handle);

	key_pressed = 0;
	for(;;){
		sw_led_on();
		sw_usleep(100 * 1000);
		sw_led_off();
		sw_usleep(100 * 1000);
		if(key_pressed > 0)
		{
			sw_beep_on();
			sw_usleep(100 * 1000);
			sw_beep_off();
			key_pressed = 0;
		}
		else{
			sw_usleep(100 * 1000);
		}
	}

	return 0;
}

