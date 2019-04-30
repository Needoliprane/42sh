/*
** EPITECH PROJECT, 2018
** chained_operator.c
** File description:
** chained_operator
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"

static int operator_out(var_t *var)
{
	char *ope_out[] = {"|", ">", ">>", NULL};

	for (int i = 0; ope_out[i]; ++i)
		if (strcmp(var->mid_tab[var->cur_pos + 3], ope_out[i]) == 0)
			return (i);
	return (-1);
}

void chained_out_operator(var_t *var)
{
	void (*call_operator[])(var_t *) = {making_a_pipe,
					simple_redirect_right,
					double_redirect_right,
					NULL};
	int index = 0;

	index = operator_out(var);
	if (index != -1) {
		var->mid_tab[var->cur_pos + 2] =
			double_array_cat(var->tab, ' ');
		var->cur_pos += 2;
		call_operator[index](var);
	}
	exit(var->val);
}

static int operator_in(var_t *var)
{
	char *ope_out[] = {"<", "<<", NULL};

	for (int i = 0; ope_out[i]; ++i)
		if (strcmp(var->mid_tab[var->cur_pos + 3], ope_out[i]) == 0)
			return (i);
	return (-1);
}

void chained_in_operator(var_t *var)
{
	void (*call_operator[])(var_t *) = {simple_redirect_left,
					double_redirect_left,
					NULL};
	int index = 0;

	index = operator_in(var);
	if (index != -1) {
		var->mid_tab[var->cur_pos + 2] =
			double_array_cat(var->tab, ' ');
		var->cur_pos += 2;
		call_operator[index](var);
	}
	exit(var->val);
}
