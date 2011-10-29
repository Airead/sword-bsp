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
#include "swstd.h"
#include "sw_xmodem.h"

/* Shell command collector */
static struct shell_cmd shell_cmds[] = {
	{"hello", cmd_world, "usage: hello [args...]", /* hello */
	"just test shell command frame"},
	
	{"xmr", cmd_xmodem_rec, "usage: xmr <memaddr>", /* xmr */
	 "copy file from disk to memory at `memaddr'"},

	{"setenv", cmd_set_env, "usage: setenv <key> <value>", /* setenv */
	 "set environment value"},

	{"saveenv", cmd_save_env, "usage: saveenv", /* save env */
	 "save current environment to nand flash"},

	{"printenv", cmd_print_env, "usage: print", /* printenv */
	 "print current environment"},

	{"nandw", cmd_nand_write, /* nandw */
	 "usage: nandw <start memaddr> <start nandaddr> <write size>",
	 "write data to nand flash"},

	{"nandr", cmd_nand_read, /* nandr */
	 "usage: nandr <start memaddr> <start nandaddr> <read size>",
	 "read data from nand flash"},

	{"memw", cmd_mem_write,	/* memw */
	 "usage: memw <memaddr> <data> <data type>",
	 "write data to memory"},

	{"memr", cmd_mem_read,	/* memr */
	 "usage: memr <memaddr> <data> <data type>",
	 "read data from memory"},

	{"go", cmd_go, 		/* go */
	 "usage: go <memaddr>",
	 "run cpu at memaddr"},

	{"tftp", cmd_tftp,	/* tftp */
	 "usage: tftp <ip> <memaddr> <filename>",
	 "store file at memaddr form ip with tftp protocol"},

	{"reset", cmd_reset,	/* reset */
	 "usage: reset",
	 "reset system"},

	{"help", cmd_help,	/* help */
	 "usage: help [command]",
	 "if command is NULL, show all command help information, \n\r"
	 "else show help information according to command."}

};

/*
 * Run command comes from sw_shell.c
 */
int cmd_run(char *arg)
{
	unsigned int i;
	int cmd_num;
	int ret;		/* 0 success, 1 can't found, -1 run error*/
	char *arg_list[CMD_ARG_NUM + 1];
	
	cmd_num = get_arglist(arg_list, arg);

	for(i = 0; i < sizeof(shell_cmds) / sizeof(struct shell_cmd); i++){
		if(sw_strcmp(arg_list[0], shell_cmds[i].name) == 0){
			ret = shell_cmds[i].cmd(arg_list, cmd_num);
			break;
		}else if(sw_strcmp(arg_list[0], "") == 0){
			break;
		}
		ret = 1;
	}
	
	if(ret == 1){
		sw_printf("`%s' not found as command\n\r", arg_list[0]);
	}else if(ret == -1){
		sw_printf("`%s run error\n\r", arg_list[0]);
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

/*
 * test shell command frame
 */
int cmd_world(char *arg_list[], int n)
{
	unsigned int i;

	sw_puts("world\n\r");
	
	for(i = 0; arg_list[i] != NULL; i++){
		sw_printf("arg_list[%u]: %s\n\r", i, arg_list[i]);
	}

	return 0;
}

/*
 * receive data from host with x-modem protocol
 */
int cmd_xmodem_rec(char *arg_list[], int n)
{
	unsigned int ret;
	
	if(n < 2){
		sw_printf("%s","sfsadf");
		return -1;
	}

	//unsigned int sw_xmodem_rec(unsigned int addr);
	ret = sw_xmodem_rec(sw_strtoul(arg_list[1], NULL, 16));

	return ret;
}

int cmd_set_env(char *arg_list[], int n)
{
	sw_printf("\nstart run %s...\n\n\r",__func__);
	return 0;
}

int cmd_save_env(char *arg_list[], int n)
{
	sw_printf("\nstart run %s...\n\n\r",__func__);
	return 0;
}

int cmd_print_env(char *arg_list[], int n)
{
	sw_printf("\nstart run %s...\n\n\r",__func__);
	return 0;
}

int cmd_nand_write(char *arg_list[], int n)
{
	sw_printf("\nstart run %s...\n\n\r",__func__);
	return 0;
}

int cmd_nand_read(char *arg_list[], int n)
{
	sw_printf("\nstart run %s...\n\n\r",__func__);
	return 0;
}

int cmd_mem_write(char *arg_list[], int n)
{
	volatile int *addr;

	if (n < 3) {
		sw_printf("usage: %s <memaddr> <data>\n\r", arg_list[0]);
		return -1;
	}

	addr = (int *)sw_strtoul(arg_list[1], NULL, 16);
	*addr = (int)sw_strtoul(arg_list[2], NULL, 16);

	return 0;
}

int cmd_mem_read(char *arg_list[], int n)
{
	volatile int *addr;

	if (n < 2) {
		sw_printf("usage: %s <memaddr>\n\r", arg_list[0]);
		return -1;
	}

	addr = (int *)sw_strtoul(arg_list[1], NULL, 16);

	sw_printf("addr[%x]: %x\n\r", addr, *addr);

	return 0;
}

int cmd_go(char *arg_list[], int n)
{
	unsigned int addr;

	addr = sw_strtoul(arg_list[1], NULL, 16); 
	sw_printf("cpu will run at %x, after 1 seconds...\n\r", addr);
	sw_usleep(1000 * 1000);

	goto *addr;

	return 0;
}

int cmd_tftp(char *arg_list[], int n)
{
	sw_printf("\nstart run %s...\n\n\r",__func__);
	return 0;
}

int cmd_reset(char *arg_list[], int n)
{
	sw_printf("\nstart run %s...\n\n\r",__func__);
	return 0;
}

int cmd_help(char *arg_list[], int n)
{
	int i;

	if(n < 2){
		for(i = 0; i < sizeof(shell_cmds) / sizeof(struct shell_cmd); i++){
			sw_printf("------%s------\n\r", shell_cmds[i].name);
			sw_printf("%s\n\r", shell_cmds[i].usage);
			sw_printf("%s\n\n\r", shell_cmds[i].help);
		}
	}else{
		for(i = 0; i < sizeof(shell_cmds) / sizeof(struct shell_cmd); i++){
			if(sw_strcmp(arg_list[1], shell_cmds[i].name) == 0){
				sw_printf("------%s------\n\r", shell_cmds[i].name);
				sw_printf("%s\n\r", shell_cmds[i].usage);
				sw_printf("%s\n\n\r", shell_cmds[i].help);
			}
		}
	}

	return 0;
}
