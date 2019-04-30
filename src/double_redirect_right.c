/*
** EPITECH PROJECT, 2018
** double_redirect_right.c
** File description:
** double_redirect_right
*/

#include <fcntl.h>
#include <unistd.h>
#include "mysh.h"

void double_redirect_right(var_t *var)
{
	int fd = 0;
	char **arg = my_str_to_word_array(var->mid_tab[var->cur_pos + 2]);
	char **next_tab = my_str_to_word_array(var->mid_tab[var->cur_pos]);

	if (arg == NULL || next_tab == NULL)
		exit_process(var);
	if ((fd = open(arg[0], O_CREAT | O_WRONLY | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1) {
		set_error_value(arg, next_tab, var);
		return;
	}
	if ((next_tab = append_option(next_tab, arg)) == NULL)
		exit_process(var);
	var->tab = next_tab;
	redirect_in_file(var, fd);
	freeing(next_tab);
}
