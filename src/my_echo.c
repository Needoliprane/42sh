/*
** EPITECH PROJECT, 2018
** my_echo.c
** File description:
** Elie
*/

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "mysh.h"

static void print_no_quote(char const *str)
{
	char c;

	for (int i = 0; str[i]; i++) {
		c = str[i];
		if (c != '\"')
			write(1, &c, 1);
	}
}

static int check_error(var_t *var)
{
	int quote_count = 0;
	char **tab = var->tab;

	if (var->tab[1] == NULL) {
		my_putstr("\n");
		return (0);
	}
	for (int i = 0; tab[i]; i++) {
		for (int j = 0; tab[i][j]; j++)
			quote_count += (tab[i][j] == '\"') ? 1 : 0;
	}
	if (quote_count % 2 == 1) {
		my_putstr("Unmatched '\"'.\n");
		return (0);
	}
	return (1);
}

void my_echo(var_t *var)
{
	int i = 1;
	int opt_n = 0;

	if (check_error(var) == 0)
		return;
	if (strcmp(var->tab[i], "-n") == 0) {
		opt_n = 1;
		i++;
	}
	if (var->tab[i]) {
		print_no_quote(var->tab[i]);
		i++;
	}
	for (; var->tab[i]; i++) {
		my_putstr(" ");
		print_no_quote(var->tab[i]);
	}
	if (opt_n == 0)
		my_putstr("\n");
}
