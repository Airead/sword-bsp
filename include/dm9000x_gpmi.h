/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 22 22:00:32 CST			*
 ********************************************************
 *		after studying C 96 days		*
 *		after studying APUE 61 days		*
 *		after studying ARM 14 days		*
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

#ifndef SWORD_DM9000X_GPMI_H
#define SWORD_DM9000X_GPMI_H

typedef struct _dma_cmd{
	struct _dma_cmd *next;

	unsigned int command : 	2 ;
	unsigned int chain :	1 ;
	unsigned int irq_complete : 1 ;
	unsigned int nandlock : 1 ;
	unsigned int nandwait4ready : 1 ;
	unsigned int decrement_semaphore : 1 ;
	unsigned int wait4endcmd : 1 ;
	unsigned int un_used : 4 ;
	unsigned int piowords_cnt : 4 ;
	unsigned int xfer_cnt : 16 ;

	unsigned int *dma_buf;
	unsigned int piowords[1];	//size depends on piowords_cnt
}DMA_CMD;

unsigned int gpmi_dm9000_read_reg(unsigned int regno);
void gpmi_dm9000_write_reg(unsigned int regno, unsigned int regval);
void gpmi_dm9000_read_data_bulk(unsigned char* buf, int count);
void gpmi_dm9000_write_data_bulk(unsigned char* buf, int count);
void gpmi_dm9000_write_reg_index(unsigned int index);

#endif
