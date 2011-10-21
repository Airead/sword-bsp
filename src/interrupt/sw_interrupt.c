/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 18 09:20:18 CST			*
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

#include "imx233.h"
#include "sw_interrupt.h"
#include "swstd.h"

extern void int_init(void);		
extern void irq_enable(void);
extern void irq_disable(void);

/* regsiter define */
static struct HW_PINCTRL * const pinctrl = 
	(struct HW_PINCTRL *) REGS_PINCTRL_BASE_PHYS;

static struct HW_ICOLL * const icoll = 
	(struct HW_ICOLL *) REGS_ICOLL_BASE_PHYS;


typedef void (*INTERRUPT_HANDLER)(void);
/* FIXME: Is the low 2 bits of vector_table's address(1:0) 0? */
INTERRUPT_HANDLER vector_table[128];

/*
 * Initialize Interrupt Collector
 */
int sw_int_init_icoll0()
{
	/*
	 * clear soft reset, regs = HW_ICOLL_CTRL
	 *     31 | soft reset | 1 = turn on, 0 = turn off
	 *     30 | gate | 1 = gate off, 0 = gate on
	 *     23:21 | step pitch | 2 = 2 word, 1 = 1 word, 0 = 1 word
	 *     20 | bypass FSM | 1 = bypass, 0 = normal
	 *     19 | nesting | 1 = no nesting, 0 = normal
	 *     18 | ARM_RSE_MODE | 1 = enable, 0 = disable
	 *     17 | FIQ_FINAL_ENABLE | 1 = enable, 0 = disable
	 *     16 | IRQ_FINAL_ENABLE | 1 = enable, 0 = disable
	 */
	icoll->ctrl.clr = 1 << 31; /* turn off soft reset */
	icoll->ctrl.clr = 1 << 30; /* gate on */
	icoll->ctrl.clr = 7 << 21; /* 1 word */
	icoll->ctrl.clr = 1 << 20; /* no bypass FSM */
	icoll->ctrl.set = 1 << 19; /* no nesting*/
	icoll->ctrl.clr = 1 << 18; /* ARM_RSE_MODE disable */
	icoll->ctrl.clr = 1 << 17; /* FIQ disable */
	icoll->ctrl.set = 1 << 16; /* IRQ enable */

	sw_usleep(100); 	/* Stable clock */
	
	/* set Interrupt Collector Interrupt Vector Base Address Register */
	icoll->vbase.dat = (int)vector_table; 

	/* change to irq mode, and set irq stack */
	int_init();

	/* clear cpsr I bit, arm can handle interrupt */
	irq_enable();

	return 0;
}

/*
 * Initialize Pin Contrl
 */
int sw_int_init_pinctrl(int bankn, int pinn, int irqlevel, int irqpol,
			int irqsrc, int priority, void irq_handle(void))
{
	int mux_num;
	int mux_bit_num;

	/* get mux_num */
	if(pinn < 16){
		mux_num = bankn * 2;
	}else{
		mux_num = bankn * 2 + 1;
	}

	/* get mux_bit_num */
	if(pinn < 16){
		mux_bit_num = pinn * 2;
	}else{
		mux_bit_num = (pinn - 16) * 2;
	}
	
	/*
	 * Set interrupt Level/Edge detection, regs = HW_PINCTRL_IRQLEVELn
	 *     1 = level, 0 = edge
	 */
	if(irqlevel == IRQ_LEVEL){
		pinctrl->irqlevel[bankn].set = 1 << mux_bit_num;
	}else if(irqlevel == IRQ_EDGE){
		pinctrl->irqlevel[bankn].clr = 1 << mux_bit_num;
	}else{
		return -1;
	}

	/*
	 * Set Interrupt Polarity low/high, regs = HW_PINCTRL_IRQPOLn
	 *     0 = Low or falling edge,
	 *     1 = High or rising edge
	 */
	if(irqpol == IRQ_LOW){
		pinctrl->irqpol[bankn].clr = 1 << pinn;
	}else if(irqpol == IRQ_HIGH){
		pinctrl->irqpol[bankn].set = 1 << pinn;
	}else{
		return -1;
	}

	/*
	 * Clear Interrupt Status, regs = HW_PINCTRL_IRQSTAT0
	 *     0= No interrupt pending;
	 *     1= Interrupt pending.
	 */
	pinctrl->irqstat[bankn].clr = 1 << pinn;
	
	/*
	 * Set Interrupt Select, regs = HW_PINCTRL_PIN2IRQn
	 *     0= Deselect the pin's interrupt functionality.
	 *     1= Select the pin to be used as an interrupt source.
	 */
	pinctrl->pin2irq[bankn].set = 1 << pinn;

	/*
	 * Set Interrupt Mask, regs = HW_PINCTRL_IRQENn
	 *     1= Enable interrupts corresponding bit 
	 *     0= Disable interrupts corresponding bit 
	 */
	pinctrl->irqen[bankn].set = 1 << pinn;

	/*
	 * Register interrupt function
	 */
	vector_table[irqsrc] = irq_handle;

	/*
	 * Set Interrupt Collector Interrupt, regs = HW_ICOLL_INTERRUPTn 
	 *     4 | ENFIQ | 1 = enable, 0 = disable
	 *     3 | SOFTIRQ | 1 = force a soft interrupt, 0 = turn off
	 *     2 | ENABLE | 1 = enable, 0 = disable
	 *    1:0 | PRIORITY | 3 = 11, 2 = 10, 1 = 01; 0 = 00
	 */
	icoll->interrupt[irqsrc].clr = 1 << 4; /* disable FIQ */
	icoll->interrupt[irqsrc].clr = 1 << 3; /* clear softirq */
	icoll->interrupt[irqsrc].set = 1 << 2; /* enable IRQ */
	icoll->interrupt[irqsrc].set = priority & 0x3; /* set priority */
	
	return 0;
}

void irq_dist0(void)
{
	icoll->vector.dat = icoll->vector.dat; /* FIXME: what's meaning? */
	(*((INTERRUPT_HANDLER *)icoll->vector.dat))();
}

int irq_clear_pending(int bankn, int pinn, int priority)
{
	/*
	 * Set Level Acknowledge, regs = HW_ICOLL_LEVELACK
	 *   3:0 | IRQLEVELACK | level0 = 0x1, 1 = 0x2, 2 = 0x4, 3 0x8 
	 */
	icoll->levelack.dat = 1 << priority; /* only fit level0, and no nest */
	
	pinctrl->irqstat[bankn].clr = 1 << pinn;
	
	return 0;
}
