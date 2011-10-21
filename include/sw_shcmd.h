/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>		*
 * @date    201110月 19 16:48:50 CST			*
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

#ifndef SWORD_SHCMD_H
#define SWORD_SHCMD_H

#define CMD_BUF_SIZE 128
#define CMD_ARG_NUM 7

typedef int (*SW_SHELL_CMD)(char *arg_list[], int n);

struct shell_cmd{
	char *name;
	SW_SHELL_CMD cmd;
	char *usage;		/* short help */
	char *help;		/* long help */
};

int cmd_run(char *arg);
int get_arglist(char *arg_list[], char *arg);
int cmd_world(char *args[], int n);
int cmd_xmodem_rec(char *arg_list[], int n);
int cmd_set_env(char *arg_list[], int n);
int cmd_save_env(char *arg_list[], int n);
int cmd_print_env(char *arg_list[], int n);
int cmd_nand_write(char *arg_list[], int n);
int cmd_nand_read(char *arg_list[], int n);
int cmd_mem_write(char *arg_list[], int n);
int cmd_mem_read(char *arg_list[], int n);
int cmd_go(char *arg_list[], int n);
int cmd_tftp(char *arg_list[], int n);
int cmd_reset(char *arg_list[], int n);
int cmd_help(char *arg_list[], int n);

#endif
