/*
** EPITECH PROJECT, 2018
** op_redirect.c
** File description:
** op_redirect
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"

int index_operand(char const *operator)
{
	char *redirect_operator[] = {"<<", ">>", "<", ">", "|", NULL};
	int i = 0;

	while (redirect_operator[i]) {
		if (strcmp(operator, redirect_operator[i]) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

int true_false(var_t *var, int *i)
{
	if (strcmp(var->mid_tab[*i], "||") == 0) {
		and_n_or(var);
		*i = var->cur_pos;
		if (var->val == 0)
			return (1);
		else
			return (0);
	}
	else if (strcmp(var->mid_tab[*i], "&&") == 0) {
		and_n_or(var);
		*i = var->cur_pos;
		if (var->val == 0)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

void last_exe(var_t *var)
{
	if (var->mid_tab[var->cur_pos] != NULL
	|| (var->cur_pos > 0
	&& strcmp(var->mid_tab[var->cur_pos - 1], "&&") == 0
	&& var->val != 0)
	|| (var->cur_pos > 1
	&& strcmp(var->mid_tab[var->cur_pos - 1], "||") == 0
	&& var->val == 0)) {
		var->tab = my_str_to_word_array(var->mid_tab[var->cur_pos]);
		if (var->tab == NULL)
			exit_process(var);
		builtins_n_exe(var);
		freeing(var->tab);
	}
}

void chained_operator_incrementation(var_t *var)
{
	while (var->mid_tab[var->cur_pos]
	&& strcmp(var->mid_tab[var->cur_pos], "&&") != 0
	&& strcmp(var->mid_tab[var->cur_pos], "||") != 0)
		var->cur_pos++;
	var->cur_pos -= 1;
}

int op_redirect(var_t *var)
{
	void (*manage[])(var_t *) = {double_redirect_left,
				double_redirect_right,
				simple_redirect_left,
				simple_redirect_right,
				making_a_pipe,
				NULL};

	for (int i = 0; var->mid_tab[i]; ++i) {
		if (i % 2 == 1 && true_false(var, &i) == 1)
			return (0);
		if (i % 2 == 1) {
			manage[index_operand(var->mid_tab[i])](var);
			chained_operator_incrementation(var);
			i = var->cur_pos;
			var->cur_pos += 1;
		}
	}
	last_exe(var);
	return (0);
}
