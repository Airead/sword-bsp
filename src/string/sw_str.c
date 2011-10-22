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
#include "sw_str.h"

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
 * Compare string
 *   @return:
 *       if return 1, str1 > str2;
 *       if return 0, str1 = str2;
 *       if return -1, str1 < str2;
 */
int sw_strncmp(const char *str1, const char *str2, int n)
{
	int i;
	const char *p, *q;

	p = str1;
	q = str2;
	
	i = 0;
	while(i < n){
		if(*p > *q){
			return 1;
		}else if(*p < *q){
			return -1;
		}
		if(*p != '\0' && *q != '\0'){
			return 0;
		}
	}
	
	return 0;
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

/*
 * converts the initial part of the string in nptr to an
 * unsigned long int value according to the given base
 * 
 * NOW, base can only set to 16
 */
unsigned long int sw_strtoul(char *nptr, char **endptr, int base)
{
	int i;
	unsigned long int ret;
	char *p;

	ret = 0;
	p = nptr;
	i = 0;
	if(base == 16){
		if(sw_strncmp(p, "0x", 2) == 0 || sw_strncmp(p, "0X", 2) == 0){
			p += 2;
		}
		while(i < 32 && sw_ishex(*p) == 1 && *p != '\0'){
			ret <<= 4;
			if('0' <= *p && *p <= '9'){
				ret |= *p - '0';
			}else{
				ret |= (*p | 0x20) - 'a' + 10;
			}
			p++;
			i += 4;
		}

		*endptr = p;
	}else{
		*endptr = NULL;
		return -1;
	}

	return ret;
}

/*
 * test char is hex flag
 */
int sw_ishex(char ch)
{
	if('0' <= ch && ch <= '9'){
		return 1;
	}else if('a' <= ch && ch <= 'f'){
		return 1;
	}else if('A' <= ch && ch <= 'F'){
		return 1;
	}else{
		return 0;
	}
}

/*
 * calculates  the  length  of  the string s, not
 * including the terminating '\0' character.
 */
int sw_strlen(char *s)
{
	int count;

	count = 0;
	while(*s != '\0'){
		count++;
	}

	return count;
}
/*
 * appends the src string to the dest string, overwriting the
 * null byte ('\0') at the end of dest, and then adds a terminating
 * null byte.
 */
char *sw_strncat(char *dest,  char *src, int n)
{
	int dest_len = sw_strlen(dest);
	int i;

	for (i = 0 ; i < n && src[i] != '\0' ; i++){
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';

	return dest;
}

/*
 * copies the string pointed to by src, including
 * the terminating null byte ('\0'), to the buffer  pointed  to  by  dest.
 * The  strings  may  not overlap, and the destination string dest must be
 * large enough to receive the copy.
 */
char *sw_strcpy(char *dest, char *src)
{
	while(*src != '\0'){
		*dest++ = *src++;
	}
	*dest = '\0';

	return dest;
}
