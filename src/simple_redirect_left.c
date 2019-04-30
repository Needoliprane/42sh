/*
** EPITECH PROJECT, 2018
** simple_redirect.c
** File description:
** simple_redirect
*/

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysh.h"

char **append_option(char **next_tab, char **arg)
{
	for (int i = 1; arg[i]; ++i) {
		if ((next_tab = str_cat_tab(next_tab, arg[i])) == NULL)
			return (NULL);
	}
	freeing(arg);
	return (next_tab);
}

void set_error_value(char **arg, char **next_tab, var_t *var)
{
	errq_putstr(arg[0], ": ", strerror(errno), ".\n");
	freeing(arg);
	freeing(next_tab);
	var->val = 1;
	set_cur_pos(var);
}

void redirect_file_in(var_t *var, int fd)
{
	pid_t pid = 0;
	int status = 0;

	if ((pid = fork()) == -1)
		exit_process(var);
	if (pid == 0) {
		if (dup2(fd, 0) != 0)
			exit_process(var);
		if (var->mid_tab[var->cur_pos + 3] != NULL)
			chained_out_operator(var);
		else
			builtins_n_exe(var);
		exit(var->val);
	}
	wait(&status);
	last_child_status(status, var);
	set_cur_pos(var);
	close(fd);
}

void simple_redirect_left(var_t *var)
{
	int fd = 0;
	char **arg = my_str_to_word_array(var->mid_tab[var->cur_pos + 2]);
	char **next_tab = my_str_to_word_array(var->mid_tab[var->cur_pos]);

	if (arg == NULL || next_tab == NULL)
		exit_process(var);
	if ((fd = open(arg[0], O_RDONLY)) == -1) {
		set_error_value(arg, next_tab, var);
		return;
	}
	if ((next_tab = append_option(next_tab, arg)) == NULL)
		exit_process(var);
	var->tab = next_tab;
	redirect_file_in(var, fd);
	freeing(next_tab);
}
