/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 14 18:09:25 CST			*
 ********************************************************
 *		after studying C 88 days		*
 *		after studying APUE 53 days		*
 *		after studying ARM 6 days		*
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

#include "sw_beep.h"
#include "swstd.h"

/*
 * test beep
 */
int beeptest(int argc, char *argv[])
{
	sw_beep_init();
	while(1){
		sw_beep_off();
		sw_usleep(1000*500);
		sw_beep_on();
		sw_usleep(1000*50);
	}
	
	return 0;
}
