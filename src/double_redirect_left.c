/*
** EPITECH PROJECT, 2018
** double_redirect_left.c
** File description:
** double_redirect_left
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "mysh.h"

static void redirect_buffer(var_t *var, int pipefd[])
{
	pid_t pid = 0;
	int status = 0;

	if ((pid = fork()) == -1)
		exit_process(var);
	if (pid == 0) {
		if (dup2(pipefd[0], 0) != 0)
			exit_process(var);
		if (var->mid_tab[var->cur_pos + 3] != NULL)
			chained_out_operator(var);
		else
			builtins_n_exe(var);
		exit(var->val);
	}
	wait(&status);
	last_child_status(status, var);
}

static void getting_the_buffer(char *key_word, int pipefd[])
{
	char *line = NULL;
	size_t n = 0;

	while (1) {
		my_putstr("? ");
		if (getline(&line, &n, stdin) == -1
		|| strcmp(line, key_word) == 0)
			break;
		write(pipefd[1], line, strlen(line));
	}
	close(pipefd[1]);
	free(key_word);
	free(line);
}

void double_redirect_left(var_t *var)
{
	char **arg = my_str_to_word_array(var->mid_tab[var->cur_pos + 2]);
	char **next_tab = my_str_to_word_array(var->mid_tab[var->cur_pos]);
	char *key_word = NULL;
	int pipefd[2];

	if (arg == NULL || next_tab == NULL || pipe2(pipefd, O_NONBLOCK) == -1)
		exit_process(var);
	if ((key_word = my_strcat_r(arg[0], "\n")) == NULL)
		exit_process(var);
	getting_the_buffer(key_word, pipefd);
	if ((next_tab = append_option(next_tab, arg)) == NULL)
		exit_process(var);
	var->tab = next_tab;
	redirect_buffer(var, pipefd);
	freeing(next_tab);
}
