/*
** EPITECH PROJECT, 2018
** tab_parsing.c
** File description:
** tab_parsing.c
*/

#include <string.h>
#include <stdlib.h>
#include "mysh.h"

void add_space_parsing_end(char *str, char *tmp, int i, int n)
{
	if ((str[i] == '&' && str[i + 1] == '&')) {
		tmp[n++] = ' ';
		tmp[n++] = str[i++];
		tmp[n++] = str[i];
		tmp[n] = ' ';
	} else if ((str[i] == '<' && str[i + 1] == '<') ||
	(str[i] == '|' && str[i + 1] == '|') ||
	(str[i] == '>' && str[i + 1] == '>')) {
		tmp[n++] = ' ';
		tmp[n++] = str[i++];
		tmp[n++] = str[i];
		tmp[n] = ' ';
	} else
		tmp[n] = str[i];
}

void add_space_parsing(char *str, char *tmp)
{
	for (int i = 0, n = 0; str[i]; ++i, ++n) {
		if (str[i] == ';' || (str[i] == '|' && str[i + 1] != '|')) {
			tmp[n++] = ' ';
			tmp[n++] = str[i];
			tmp[n] = ' ';
		} else if ((str[i] == '<' && str[i + 1] != '<')
		|| (str[i] == '>' && str[i + 1] != '>')) {
			tmp[n++] = ' ';
			tmp[n++] = str[i];
			tmp[n] = ' ';
		} else
			add_space_parsing_end(str, tmp, i, n);
	}
}

void check_op_parsing_end(char *str, int *nbr, int *i_tmp)
{
	int i = *i_tmp;

	if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '|'
	&& str[i + 1] == '|') || (str[i] == '>' && str[i + 1] == '>')
	|| (str[i] == '&' && str[i + 1] == '&')) {
		nbr += 2;
		*i_tmp += 1;
	}
}

char *check_op_parsing(char *str)
{
	int nbr = 0;
	char *tmp = NULL;

	for (int i = 0; str[i]; ++i) {
		if (str[i] == ';' || (str[i] == '|' && str[i + 1] != '|'))
			nbr += 2;
		else if ((str[i] == '<' && str[i + 1] != '<')
		|| (str[i] == '>' && str[i + 1] != '>'))
			nbr += 2;
		else
			check_op_parsing_end(str, &nbr, &i);
	}
	if (nbr == 0)
		return (str);
	tmp = my_malloc(strlen(str) + nbr);
	add_space_parsing(str, tmp);
	free(str);
	return (tmp);
}

void clean_tab(char **tab, char *op)
{
	for (int i = 0; tab && tab[i]; ++i)
		while (tab[i] && ((my_strcmp(tab[i], op, 0) == 0 && i == 0)
		|| (my_strcmp(tab[i], op, 0) == 0 && tab[i + 1] != NULL
		&& (my_strcmp(tab[i + 1], op, 0) == 0
		|| my_strcmp(tab[i - 1], op, 0) == 0))))
			unset_a_line(tab, i);
}
