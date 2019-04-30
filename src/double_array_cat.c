/*
** EPITECH PROJECT, 2018
** double_array_cat.c
** File description:
** double_array_cat.c
*/

#include <stdlib.h>
#include "mysh.h"

char *double_array_cat(char **src, char c)
{
	char *new = NULL;
	char *tmp = NULL;

	for (int i = 0; src[i]; ++i) {
		tmp = new;
		new = my_strcat(tmp, src[i], c);
		free(tmp);
	}
	freeing(src);
	return (new);
}
