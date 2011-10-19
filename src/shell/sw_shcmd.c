/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 19 16:51:07 CST			*
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

#include "sw_shcmd.h"
#include "sw_stdio.h"
#include "sw_str.h"

/* Shell command collector */
static struct shell_cmd shell_cmds[] = {
	{"hello", cmd_world}
};

/*
 * Run command comes from sw_shell.c
 */
int cmd_run(char *arg)
{
	int i;
	int cmd_num;
	int ret;
	char *arg_list[CMD_ARG_NUM + 1];
	
	cmd_num = get_arglist(arg_list, arg);

	for(i = 0; i < sizeof(shell_cmds) / sizeof(struct shell_cmd); i++){
		if(sw_strcmp(arg_list[0], shell_cmds[i].name) == 0){
			shell_cmds[i].cmd(arg_list, cmd_num);
			break;
		}else if(sw_strcmp(arg_list[0], "") == 0){
			break;
		}

		sw_puts("command not found\n\r");
	}

	return ret;
}

/*
 * get arg_list from arg, with space
 */
int get_arglist(char *arg_list[], char *arg)
{
	int count;
	char *p;

	p = arg;
	count = 0;
	arg_list[count++] = p;
	while((p = sw_strchr(p, ' ')) != NULL && count < CMD_ARG_NUM){
		*p++ = '\0';
		arg_list[count++] = p;
	}
	*p = '\0';
	arg_list[count] = NULL;

	return count;
}

int cmd_world(char *arg_list[], int n)
{
	unsigned int i;

	sw_puts("world\n\r");
	
	for(i = 0; arg_list[i] != NULL; i++){
		sw_printf("arg_list[%u]: %s\n\r", i, arg_list[i]);
	}

	return 0;
}
