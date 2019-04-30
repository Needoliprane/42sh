/*
** EPITECH PROJECT, 2018
** my_exe.c
** File description:
** my_exe.c
*/

#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

const char *WRONG_AR = "Exec format error. Wrong Architecture";

int check_path(var_t *var)
{
	char *pat = NULL;

	for (int i = 0, n = 0, y = 0; var->path && var->path[i]; i++) {
		pat = my_strcat(var->path[i], var->tab[0], '/');
		n = access(pat, X_OK);
		if (n == 0) {
			y = execve(pat, var->tab, var->env);
			free(pat);
			return (y);
		}
		free(pat);
	}
	err_putstr(var->tab[0]);
	var->val = 1;
	err_putstr(": Command not found.\n\0");
	return (0);
}

void child_status(int wstatus, var_t *var)
{
	var->val = wstatus / 256;
	if (WIFSIGNALED(wstatus)) {
		if (WTERMSIG(wstatus) == 11) {
			err_putstr("Segmentation fault\n\0");
			var->val = 139;
		}
		else if (WTERMSIG(wstatus) == 8 && WCOREDUMP(wstatus)) {
			var->val = 136;
			err_putstr("Floating exception\n\0");
		}
		else if (WTERMSIG(wstatus) == 8) {
			var->val = 136;
			err_putstr("Floating exception\n\0");
		}
	}
}

void cmd_not_found(var_t *var)
{
	if (access(var->tab[0], F_OK) != 0)
		errq_putstr(var->tab[0], ": \0", "Command not found", ".\n\0");
	else if (access(var->tab[0], X_OK) != 0)
		print_err(var, 0);
	var->val = 1;
}

void wrong_exec(var_t *var, int y)
{
	if (y < 0 && errno == 8) {
		errq_putstr(var->tab[0], ": \0", WRONG_AR, ".\n\0");
		var->val = 1;
	}
	else if (y < 0) {
		print_err(var, 0);
		var->val = 1;
	}
}

void my_exe(var_t *var)
{
	pid_t pid = 0;
	int wstatus;
	int i = 0;
	int y = 0;

	pid = fork();
	if (pid == 0) {
		if ((i = access(var->tab[0], X_OK)) == 0)
			y = execve(var->tab[0], var->tab, var->env);
		else if ((var->tab[0][0] != '.' && var->tab[0][0] != '/'))
			y = check_path(var);
		wrong_exec(var, y);
		if ((var->tab[0][0] == '.' || var->tab[0][0] == '/'))
			cmd_not_found(var);
		exit_process(var);
	} else
		wait(&wstatus);
	child_status(wstatus, var);
}
