/*
** EPITECH PROJECT, 2018
** semi_col.c
** File description:
** semi_col.c
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"

void unset_a_line(char **var, int i)
{
	char *tmp = NULL;

	free(var[i]);
	for (; var[i]; ++i) {
		tmp = var[i + 1];
		var[i] = tmp;
	}
}

int check_op_middle(char **tab, char **op, int i, int n)
{
	for (int y = 0; op[y]; ++y) {
		if (my_strcmp(tab[i + 1], op[y], 0) == 0 && n == 0
		&& (y == 1 || y == 2) && tab[i + 2] != NULL) {
			err_putstr("Ambiguous input redirect.\n\0");
			return (1);
		}
		else if (my_strcmp(tab[i + 1], op[y], 0) == 0) {
			err_putstr("Missing name for redirect.\n\0");
			return (1);
		}
	}
	return (0);
}

int check_op_loop(char **tab, char **op, int i)
{
	for (int n = 0; op[n]; n++) {
		if ((i == 0 || (my_strcmp(tab[i], "||\0", 0) == 0 &&
		tab[i + 1] == NULL) || (tab[i + 1] == NULL && n == 0))
		&& n != 1 && n != 3 && (my_strcmp(tab[i], op[n], 0) == 0 ||
		my_strcmp(tab[i], "&&\0", 0) == 0 ||
		my_strcmp(tab[i], "||\0", 0) == 0)) {
			err_putstr("Invalid null command.\n\0");
			return (1);
		}
		else if (tab[i + 1] == NULL
		&& my_strcmp(tab[i], op[n], 0) == 0 && n != 0 ) {
			err_putstr("Missing name for redirect.\n\0");
			return (1);
		}
		else if (my_strcmp(tab[i], op[n], 0) == 0
		&& check_op_middle(tab, op, i, n) == 1) {
			return (1);
		}
	}
	return (0);
}

int check_redirect(char **tab, int i)
{
	if (i > 0 && (strcmp(tab[i], ">\0") == 0 ||
	strcmp(tab[i], ">>\0") == 0) &&	tab[i + 1] != NULL &&
	tab[i + 2] != NULL && (strcmp(tab[i + 2], ">\0") == 0 ||
	strcmp(tab[i + 2], ">>\0") == 0 || strcmp(tab[i + 2], "|\0") == 0)
	&& tab[i + 3] != NULL) {
		err_putstr("Ambiguous output redirect.\n\0");
		return (1);
	}
	if (i > 0 && (strcmp(tab[i], "<\0") == 0 ||
	strcmp(tab[i], "<<\0") == 0 || strcmp(tab[i], "|\0") == 0) &&
	tab[i + 1] != NULL && tab[i + 2] != NULL &&
	(strcmp(tab[i + 2], "<\0") == 0 || strcmp(tab[i + 2], "<<\0") == 0) &&
	tab[i + 3] != NULL) {
		err_putstr("Ambiguous output redirect.\n\0");
		return (1);
	}
	return (0);
}

int check_op(char **tab)
{
	char *op[] = {"|", "<", "<<", ">", ">>", NULL};

	for (int i = 0; tab && tab[i]; ++i) {
		if (tab && tab[i] && (i == 0 || strcmp(tab[i - 1], ";") == 0)
		&& strcmp(tab[i], "&&") == 0)
			unset_a_line(tab, i);
		if (tab[i] != NULL && check_redirect(tab, i) == 1)
			return (1);
		if (tab[i] != NULL && check_op_loop(tab, op, i) == 1)
			return (1);
	}
	return (0);
}
