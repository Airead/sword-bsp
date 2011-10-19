/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 19 17:00:34 CST			*
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

#include "sw_stdio.h"		/* for NULL */
/*
 * Compare string
 *   @return:
 *       if return 1, str1 > str2;
 *       if return 0, str1 = str2;
 *       if return -1, str1 < str2;
 */
int sw_strcmp(const char *str1, const char * str2)
{
	const char *p, *q;

	p = str1;
	q = str2;
	
	while(*p != '\0' && *q != '\0'){ /* first compare */
		if(*p > *q){
			return 1;
		}else if(*p < *q){
			return -1;
		}
		p++;
		q++;
	}

	if(*p == '\0' && *q == '\0'){	/* equal */
		return 0;
	}else if(*p == 0){	/* str1 < str2 */
		return -1;
	}else{
		return 1;	/* str1 > str2 */
	}
}

/*
 * Returns a pointer to the first occurrence of the character c in the string str.
 * if not found, return NULL
 */
char *sw_strchr(const char *str, int c)
{
	const char *p;

	p = str;
	while(*p != '\0'){
		if(*p == c){
			return (char *)p;
		}else{
			p++;
		}
	}

	return NULL;
}
