/*
** EPITECH PROJECT, 2018
** or_n_and.c
** File description:
** or_n_and
*/

#include "mysh.h"

int and_n_or(var_t *var)
{
	if (var->cur_pos == 0
	|| (var->cur_pos > 0
		&& index_operand(var->mid_tab[var->cur_pos - 1]) == -1)) {
		var->tab = my_str_to_word_array(var->mid_tab[var->cur_pos]);
		builtins_n_exe(var);
		freeing(var->tab);
		var->cur_pos += 2;
	}
	return (0);
}
