/*
** EPITECH PROJECT, 2018
** make_mid_tab.c
** File description:
** make_mid_tab.c
*/

#include <string.h>
#include <stdlib.h>
#include "mysh.h"

char **str_cat_tab_first(char **tab, char *src)
{
	int i = 1;
	int len = my_strlen_tab(tab) + 1;
	char **dest2 = malloc_char_tab(len);

	if (!dest2)
		return (NULL);
	if (tab == NULL) {
		dest2[0] = strdup(src);
		return (dest2);
	}
	dest2[0] = strdup(src);
	for (int n = 0; tab[n]; ++i, ++n)
		dest2[i] = strdup(tab[n]);
	freeing(tab);
	return (dest2);
}

void swap_spe_case(var_t *var, const char **op)
{
	char *tmp = NULL;
	int i = 0;

	if (strcmp(var->mid_tab[0], op[1]) == 0
	|| strcmp(var->mid_tab[0], op[3]) == 0) {
		for (; var->mid_tab[1][i] != ' '; ++i);
		tmp = my_malloc(sizeof(char) * (strlen(var->mid_tab[1]) - (i)));
		for (int n = i + 1, j = i, k = 0; var->mid_tab[1][n];
		++n, ++k, ++j) {
			tmp[k] = var->mid_tab[1][n];
			var->mid_tab[1][j] = '\0';
		}
		var->mid_tab = str_cat_tab_first(var->mid_tab, tmp);
	}
}

void fill_mid_tab(var_t *var, const char **op)
{
	char *tmp = NULL;

	for (int i = 0, n = 0, k = 0; var->tab && var->tab[i]; ++n) {
		if (op[n] != NULL && strcmp(op[n], var->tab[i]) == 0) {
			(i != 0) ? (k += 1) : (0);
			var->mid_tab[k] = strdup(op[n]);
			k++;
			tmp = var->mid_tab[k];
			i++;
			n = 0;
		} else if (op[n] == NULL) {
			var->mid_tab[k] = my_strcat(tmp, var->tab[i], ' ');
			free(tmp);
			tmp = var->mid_tab[k];
		}
		(op[n] == NULL) ? (i += 1) : (i);
		(op[n] == NULL) ? (n = -1) : (n);
	}
	freeing(var->tab);
	var->tab = NULL;
	swap_spe_case(var, op);
}

void make_mid_tab(var_t *var)
{
	const char *op[] = {"|", "<", "<<", ">", ">>", "||", "&&", NULL};
	int line_nbr = 0;

	for (int i = 0, n = 0; var->tab && var->tab[i]; ) {
		if (op[n] != NULL && strcmp(op[n], var->tab[i]) == 0)
			line_nbr++;
		(op[n] != NULL) ? (n += 1) : (n);
		(op[n] == NULL) ? (i += 1) : (i);
		(op[n] == NULL) ? (n = 0) : (n);
	}
	var->mid_tab = malloc_char_tab(((line_nbr * 2) + 1));
	fill_mid_tab(var, op);
	op_redirect(var);
	var->cur_pos = 0;
}
