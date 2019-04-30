/*
** EPITECH PROJECT, 2018
** unset.c
** File description:
** unset.c
*/

#include <stdlib.h>
#include "mysh.h"

void unset_line(var_t *var, int i)
{
	char *tmp = NULL;

	free(var->env[i]);
	for (; var->env[i]; i++) {
		tmp = var->env[i + 1];
		var->env[i] = tmp;
	}
}

void unset_loop(var_t *var, int j)
{
	int i = 0;
	int n = 0;

	for (; var->env && var->env[i]; i++) {
		if ((n = my_strcmp(var->tab[j], var->env[i], 2)) == 0) {
			unset_line(var, i);
		}
	}
}

void unset(var_t *var)
{
	for (int j = 1; var->tab && var->tab[j]; j++)
		unset_loop(var, j);
}
