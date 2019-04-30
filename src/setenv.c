/*
** EPITECH PROJECT, 2018
** setenv.c
** File description:
** setenv.c
*/

#include <string.h>
#include <stdlib.h>
#include "mysh.h"

char *my_strcat_r(char *dest, char *src)
{
	int i = 0;
	int len = strlen(dest) + strlen(src) + 1;
	char *dest2 = malloc_char_str(len);

	if (!dest2)
		return (NULL);
	if (dest == NULL) {
		dest2 = strdup(src);
		return (dest2);
	}
	for (; dest[i]; i++)
		dest2[i] = dest[i];
	for (int n = 0; src[n]; ++i, ++n)
		dest2[i] = src[n];
	return (dest2);
}

char **str_cat_tab(char **tab, char *src)
{
	int i = 0;
	int len = my_strlen_tab(tab) + 1;
	char **dest2 = malloc_char_tab(len);

	if (!dest2)
		return (NULL);
	if (tab == NULL) {
		dest2[0] = strdup(src);
		return (dest2);
	}
	for (; tab[i]; ++i)
		dest2[i] = strdup(tab[i]);
	dest2[i] = strdup(src);
	freeing(tab);
	return (dest2);
}

void setenv_cpy(var_t *var)
{
	char *tmp = NULL;

	if (var->tab[1] == NULL)
		envi(var);
	if (var->tab[1] != NULL && var->tab[2] == NULL) {
		tmp = my_strcat_r(var->tab[1], "=\0");
		free(var->tab[1]);
		var->tab[1] = tmp;
		var->env = str_cat_tab(var->env, var->tab[1]);
	}
	if (var->tab[1] != NULL && var->tab[2] != NULL) {
		if (var->tab[2][0] != '=')
			tmp = my_strcat(var->tab[1], var->tab[2], '=');
		else
			tmp = my_strcat_r(var->tab[1], var->tab[2]);
		var->env = str_cat_tab(var->env, tmp);
	}
}

void setenv_occur(var_t *var, int i, int n)
{
	char *tmp = NULL;

	if (n == 0 && var->env) {
		if (var->tab[1] == NULL)
			envi(var);
		if (var->tab[1] != NULL && var->tab[2] == NULL) {
			tmp = my_strcat_r(var->tab[1], "=\0");
			free(var->env[i]);
			var->env[i] = tmp;
		}
		if (var->tab[1] != NULL && var->tab[2] != NULL) {
			tmp = my_strcat(var->tab[1], var->tab[2], '=');
			free(var->env[i]);
			var->env[i] = tmp;
		}
	} else
		setenv_cpy(var);
}

void setienv(var_t *var)
{
	int n = 0;
	int i = 0;

	for (; var->tab[1] && var->env && var->env[i]; ++i) {
		if ((n = my_strcmp(var->tab[1], var->env[i], 2)) == 0)
			break;
	}
	for (int j = 0; var->tab[1] && var->tab[1][j];) {
		if ((var->tab[1][j] >= 47 && var->tab[1][j] <= 57)
		|| (var->tab[1][j] >= 65 && var->tab[1][j] <= 90)
		|| (var->tab[1][j] >= 97 && var->tab[1][j] <= 122))
			j++;
		else {
			var->val = 1;
			err_putstr("setenv: Variable name must contain\0");
			err_putstr(" alphanumeric characters.\n\0");
			return;
		}
	}
	setenv_occur(var, i, n);
}
