/*
** EPITECH PROJECT, 2018
** my_free.c
** File description:
** my_free.c
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

void kill_process(var_t *var)
{
	for (int i = 0; var->path && var->path[i] != NULL; i++)
		my_free(var->path[i]);
	for (int i = 0; var->tab && var->tab[i] != NULL; i++)
		my_free(var->tab[i]);
	my_free(var->path);
	my_free(var->tab);
	my_free(var);
	kill(getpid(), SIGKILL);
}

void exit_process(var_t *var)
{
	int val = var->val;

	for (int i = 0; var->path && var->path[i] != NULL; i++)
		my_free(var->path[i]);
	for (int i = 0; var->tab && var->tab[i] != NULL; i++)
		my_free(var->tab[i]);
	for (int i = 0; var->mid_tab && var->mid_tab[i] != NULL; i++)
		my_free(var->mid_tab[i]);
	for (int i = 0; var->all_tab && var->all_tab[i] != NULL; i++)
		my_free(var->all_tab[i]);
	for (int i = 0; var->env && var->env[i] != NULL; i++)
		my_free(var->env[i]);
	my_free(var->env);
	my_free(var->path);
	my_free(var->mid_tab);
	my_free(var->tab);
	my_free(var->all_tab);
	my_free(var->oldpwd);
	my_free(var->s);
	my_free(var);
	exit(val);
}

void exit_destroy(var_t *var)
{
	int val = var->val;

	for (int i = 0; var->env && var->env[i] != NULL; i++)
		free(var->env[i]);
	my_free(var->env);
	my_free(var->oldpwd);
	my_free(var);
	exit(val);
}

void freeing(char **tab)
{
	for (int i = 0; tab && tab[i] != NULL; i++)
		my_free(tab[i]);
	my_free(tab);
}

void my_free(void *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
}
