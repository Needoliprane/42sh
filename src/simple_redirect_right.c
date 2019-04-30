/*
** EPITECH PROJECT, 2018
** simple_redirect_right.c
** File description:
** simple_redirect_right
*/

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "mysh.h"

void set_cur_pos(var_t *var)
{
	if (var->val != 0) {
		for (int i = var->cur_pos; var->mid_tab[i]; ++i)
			var->cur_pos++;
		var->cur_pos -= 1;
	}
	else
		var->cur_pos += 2;
}

void redirect_in_file(var_t *var, int fd)
{
	pid_t pid = 0;
	int status = 0;

	if ((pid = fork()) == -1)
		exit_process(var);
	if (pid == 0) {
		if (dup2(fd, 1) != 1)
			exit_process(var);
		if (var->mid_tab[var->cur_pos + 3] != NULL)
			chained_in_operator(var);
		else
			builtins_n_exe(var);
		exit(var->val);
	}
	wait(&status);
	last_child_status(status, var);
	set_cur_pos(var);
	close(fd);
}

void simple_redirect_right(var_t *var)
{
	int fd = 0;
	char **arg = my_str_to_word_array(var->mid_tab[var->cur_pos + 2]);
	char **next_tab = my_str_to_word_array(var->mid_tab[var->cur_pos]);

	if (arg == NULL || next_tab == NULL)
		exit_process(var);
	if ((fd = open(arg[0], O_CREAT | O_WRONLY | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1) {
		set_error_value(arg, next_tab, var);
		return;
	}
	if ((next_tab = append_option(next_tab, arg)) == NULL)
		exit_process(var);
	var->tab = next_tab;
	redirect_in_file(var, fd);
	freeing(next_tab);
}
