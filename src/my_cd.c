/*
** EPITECH PROJECT, 2018
** my_cd.c
** File description:
** my_cd.c
*/

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

void get_home(var_t *var)
{
	var->home = NULL;
	for (int i = 0; var->env && var->env[i]; i++) {
		if (my_strcmp("HOME", var->env[i], 2) == 0) {
			var->home = strdup_int(var->env[i], 5);
		}
	}
}

void cd_home(var_t *var)
{
	int err = 0;

	free(var->oldpwd);
	var->oldpwd = NULL;
	var->oldpwd = getcwd(var->oldpwd, 0);
	if (var->home)
		err = chdir(var->home);
	else {
		err_putstr("cd: Bad address.\n");
		var->val = 1;
	}
	if (err == -1 && var->home != NULL) {
		errq_putstr(var->tab[0], ": ", strerror(errno), ".\n");
		var->val = 1;
	}
	free(var->home);
}

void print_err(var_t *var, int i)
{
	errq_putstr(var->tab[i], ": ", strerror(errno), ".\n");
	var->val = 1;
}

void my_cd(var_t *var)
{
	char *tmppwd = NULL;
	int err = 0;

	if (var->tab[1] != NULL && var->oldpwd != NULL
	&& my_strcmp("-", var->tab[1], 0) == 0) {
		tmppwd = getcwd(tmppwd, 0);
		err = chdir(var->oldpwd);
		free(var->oldpwd);
		var->oldpwd = tmppwd;
	}
	else if (var->tab[1] == NULL) {
		get_home(var);
		cd_home(var);
	} else {
		free(var->oldpwd);
		var->oldpwd = NULL;
		var->oldpwd = getcwd(var->oldpwd, 0);
		err = chdir(var->tab[1]);
	}
	if (err == -1)
		print_err(var, 1);
}
