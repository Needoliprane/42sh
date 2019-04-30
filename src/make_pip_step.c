/*
** EPITECH PROJECT, 2018
** make_pip_step.c
** File description:
** make_pip_step.c
*/

#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysh.h"

void making_a_last_pair_pipe(var_t *var, int *pipefd, int i)
{
	dup2(pipefd[2], 0);
	close(pipefd[3]);
	if (var->mid_tab[i + 1] != NULL
	&& strcmp(var->mid_tab[i + 1], ">") == 0) {
		simple_redirect_right(var);
	} else if (var->mid_tab[i + 1] != NULL
	&& strcmp(var->mid_tab[i + 1], ">>") == 0) {
		double_redirect_right(var);
	} else {
		var->tab = my_str_to_word_array(var->mid_tab[i]);
		builtins_n_exe(var);
	}
	exit(var->val);
}

void making_a_last_pipe(var_t *var, int *pipefd, int n, int i)
{
	if (n % 2 != 0) {
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		if (var->mid_tab[i + 1] != NULL
		&& strcmp(var->mid_tab[i + 1], ">") == 0)
			simple_redirect_right(var);
		else if (var->mid_tab[i + 1] != NULL
		&& strcmp(var->mid_tab[i + 1], ">>") == 0) {
			double_redirect_right(var);
		} else {
			var->tab = my_str_to_word_array(var->mid_tab[i]);
			builtins_n_exe(var);
		}
		exit(var->val);
	} else if (n % 2 == 0)
		making_a_last_pair_pipe(var, pipefd, i);
}

void making_a_mid_pipe(var_t *var, int *pipefd, int n, int i)
{
	if (n % 2 != 0) {
		dup2(pipefd[0], 0);
		dup2(pipefd[3], 1);
		if (var->mid_tab[i + 1] != NULL
		&& strcmp(var->mid_tab[i + 1], ">") == 0
		&& strcmp(var->mid_tab[i + 1], ">>") == 0)
			exit(var->val);
		var->tab = my_str_to_word_array(var->mid_tab[i]);
		builtins_n_exe(var);
		exit(var->val);
	} else if (n % 2 == 0) {
		dup2(pipefd[2], 0);
		dup2(pipefd[1], 1);
		if (var->mid_tab[i + 1] != NULL
		&& strcmp(var->mid_tab[i + 1], ">") == 0
		&& strcmp(var->mid_tab[i + 1], ">>") == 0) 
			exit(var->val);
		var->tab = my_str_to_word_array(var->mid_tab[i]);
		builtins_n_exe(var);
		exit(var->val);
	}
}

void making_a_first_pipe(var_t *var, int *pipefd, int n, int i)
{
	if (n == 0) {
		dup2(pipefd[1], 1);
		var->tab = my_str_to_word_array(var->mid_tab[i]);
		builtins_n_exe(var);
		exit(var->val);
	}
}

void call_pipe2(int *pipefd, int n)
{
	if (n % 2 == 0 && pipe2(pipefd, O_NONBLOCK) == -1)
		exit(84);
	if (n % 2 != 0 && pipe2(pipefd + 2, O_NONBLOCK) == -1)
		exit(84);
}
