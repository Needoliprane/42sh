/*
** EPITECH PROJECT, 2018
** bootstrap.c
** File description:
** bootstrap
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

int how_many_pipes(var_t *var)
{
	int i = var->cur_pos + 1;
	int len = 0;

	while (var->mid_tab && var->mid_tab[i]) {
		if (strcmp(var->mid_tab[i], "|") != 0)
			return (len + 1);
		i += 2;
		len++;
	}
	return (len + 1);
}

void last_child_status(int wstatus, var_t *var)
{
	var->val = wstatus / 256;
	if (WIFSIGNALED(wstatus)) {
		if (WTERMSIG(wstatus) == 11) {
			var->val = 139;
		}
		if (WTERMSIG(wstatus) == 8 && WCOREDUMP(wstatus)) {
			var->val = 136;
		}
		else if (WTERMSIG(wstatus) == 8) {
			var->val = 136;
		}
	}
}

void closing_pipes(int *pipefd, int n)
{
	(n % 2 == 0) ? close(pipefd[1]) : close(pipefd[3]);
	(n % 2 == 1) ? close(pipefd[0]) : 0;
	(n % 2 == 0 && n != 0) ? close(pipefd[2]) : 0;
}

void making_a_pipe(var_t *var)
{
	int pipefd[4];
	pid_t pid = 0;
	int status = 0;

	for (int i = var->cur_pos, n = 0, len = how_many_pipes(var);
	n < len; i += 2, n++, var->cur_pos += 2) {
		call_pipe2(pipefd, n);
		pid = fork();
		if (pid == 0 && n == 0)
			making_a_first_pipe(var, pipefd, n, i);
		if (pid == 0 && n != 0 && n == len - 1)
			making_a_last_pipe(var, pipefd, n, i);
		else if (pid == 0 && n != 0 && n != len - 1)
			making_a_mid_pipe(var, pipefd, n, i);
		wait(&status);
		closing_pipes(pipefd, n);
	}
	close(pipefd[0]);
	close(pipefd[2]);
	var->cur_pos -= 2;
	last_child_status(status, var);
}
