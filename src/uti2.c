/*
** EPITECH PROJECT, 2018
** uti2.c
** File description:
** uti2.c
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"

int strlen_tab_cmp(char **tab, char *str, int i)
{
	for (; tab && str && tab[i]; ++i)
		if (my_strcmp(tab[i], str, 0) == 0)
			return (i);
	return (i);
}

void tab_path_paste(var_t *var, char *str)
{
	int n = 0;

	for (int i = 5, k = 0; var->path && str[i]; ++i) {
		if (str[i] != ':') {
			var->path[n][k] = str[i];
			k++;
		}
		if (str[i + 1] == '\0' || str[i] == ':') {
			n++;
			k = 0;
		}
	}
	free(str);
	if (var->path)
		var->path[n] = NULL;
}

void tab_path(var_t *var, char *str)
{
	int n = 0;

	for (int i = 0; str[i]; ++i) {
		if (str[i + 1] == '\0' || str[i] == ':')
			n++;
	}
	var->path = malloc_char_tab(n + 1);
	for (int i = 5, n = 0, k = 0; var->path && str[i]; ++i, ++k) {
		if (str[i] == ':') {
			var->path[n] = malloc_char_str(k);
			n++;
			k = 0;
		}
		if (str[i + 1] == '\0')
			var->path[n] = malloc_char_str(k + 1);
	}
	tab_path_paste(var, str);
}

void get_path(var_t *var)
{
	var->path = NULL;
	for (int i = 0; var->env && var->env[i]; ++i) {
		if (my_strcmp("PATH", var->env[i], 2) == 0)
			tab_path(var, strdup(var->env[i]));
	}
}
