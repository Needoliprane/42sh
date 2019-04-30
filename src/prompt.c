/*
** EPITECH PROJECT, 2018
** prompt.c
** File description:
** prompt.c
*/

#include <string.h>
#include <stdlib.h>
#include "mysh.h"

const char *CD = "cd";
const char *SETENV = "setenv";
const char *UNSETENV = "unsetenv";
const char *ENV = "env";
const char *EXIT = "exit";
const char *ECHO = "echo";

void builtins_n_exe(var_t *var)
{
	void (*command[])(var_t *) = {my_cd, exit_process, setienv,
				unset, envi, my_echo, NULL};
	const char *builtins[] = {CD, EXIT, SETENV, UNSETENV, ENV, ECHO, NULL};

	var->val = 0;
	for (int i = 0; builtins[i]; ++i) {
		if (var->tab && my_strcmp(builtins[i], var->tab[0], 0) == 0) {
			command[i](var);
			return;
		}
	}
	my_exe(var);
}

void check_all_tab(var_t *var)
{
	int i = 0;
	int old_len = 0;
	int n = 0;
	int len = my_strlen_tab(var->all_tab);

	clean_tab(var->all_tab, ";");
	if ((var->val = check_op(var->all_tab)) != 0)
		return;
	for (; i < len && var->all_tab && var->all_tab[i]; ++i, ++old_len) {
		i = strlen_tab_cmp(var->all_tab, ";", i);
		var->tab = my_malloc(sizeof(char *) * (i + 1 - old_len));
		for (n = 0; i > 0 && old_len < i; ++n, ++old_len)
			var->tab[n] = strdup(var->all_tab[old_len]);
		if (i > 0 && n > 0 && var->tab) {
			get_path(var);
			make_mid_tab(var);
		}
		freeing(var->mid_tab);
		freeing(var->path);
	}
}

int prompt(char **envp)
{
	var_t *var = my_malloc(sizeof(var_t));
	int value = 0;

	cpy_env(var, envp);
	my_putstr("$> ");
	while ((var->s = get_next_line(0)) != NULL) {
		if (strlen(var->s) > 0) {
			var->s = check_op_parsing(var->s);
			var->all_tab = my_str_to_word_array(var->s);
			check_all_tab(var);
			freeing(var->all_tab);
		}
		my_putstr("$> ");
		free(var->s);
	}
	value = var->val;
	exit_destroy(var);
	return (value);
}
