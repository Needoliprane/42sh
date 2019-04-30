/*
** EPITECH PROJECT, 2018
** env.c
** File description:
** env.c
*/

#include <string.h>
#include "mysh.h"

void cpy_env(var_t *var, char **envp)
{
	int i = 0;

	for (; envp[i]; i++);
	var->env = malloc_char_tab(i);
	for (i = 0; var->env && envp[i]; i++)
		var->env[i] = strdup(envp[i]);
	var->env[i] = NULL;
}

void envi(var_t *var)
{
	for (int i = 0; var->env && var->env[i]; i++) {
		my_putstr(var->env[i]);
		my_putstr("\n");
	}
}
