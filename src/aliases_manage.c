/*
** EPITECH PROJECT, 2018
** aliases_manage.c
** File description:
** aliases_manage
*/

#include <unistd.h>
#include "mysh.h"

int print_all_alias(var_t *var)
{
	if (var->tab_alias == NULL || var->tab_command_alias == NULL)
		return (1);
	for (int i = 0; var->tab_alias[i] && var->tab_command_alias[i]; i++) {
		my_putstr(var->tab_alias[i]);
		write(1, "=", 1);
		my_putstr(var->tab_command_alias[i]);
		write(1, "\n", 1);
	}
	return (0);
}

void fill_alias(char **command, var_t *var)
{
	char *command_for_alias = NULL;

	var->tab_alias = str_cat_tab(var->tab_alias, command[1]);
	for (int i = 2; command[i]; i++)
		command_for_alias = my_strcat_r(command_for_alias, command[i]);
	var->tab_command_alias = str_cat_tab(var->tab_command_alias,
		command_for_alias);
}

void master_alias(char *command, var_t *var)
{
	int i = 0;
	char **tab_command = NULL;

	if (var->tab_alias == NULL || var->tab_command_alias == NULL) {
		var->tab_alias = malloc_char_tab(2);
		var->tab_alias = malloc_char_tab(2);
	}
	tab_command = my_str_to_word_array(command);
	for (; tab_command[i]; i++);
	if (i == 1)
		print_all_alias(var);
	else if (i < 2)
		fill_alias(tab_command, var);
}
