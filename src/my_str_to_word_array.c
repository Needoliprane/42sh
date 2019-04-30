/*
** EPITECH PROJECT, 2018
** my_str_to_word_array.c
** File description:
** my_str_to_word_array.c
*/

#include <string.h>
#include "mysh.h"

char **str_paste(char **tab, const char *str)
{
	int n = 0;

	if (tab == NULL || tab[0] == NULL)
		return (NULL);
	for (int i = 0, k = 0; str[i]; ++i) {
		if (str[i] >= 33) {
			tab[n][k] = str[i];
			k++;
		}
		if (str[i + 1] == '\0'
		|| (k != 0 && str[i] < 33 && str[i + 1] >= 33)) {
			n++;
			k = 0;
		}
	}
	return (tab);
}

char **my_str_to_word_array(const char *str)
{
	char **res = NULL;
	int n = 0;

	for (int i = 0; str[i]; ++i) {
		if (str[i + 1] == '\0'
		|| (i > 2 && str[i] < 33 && str[i + 1] >= 33))
			n++;
	}
	res = malloc_char_tab(n + 1);
	for (int i = 0, n = 0, k = 0; res && str[i]; i++) {
		if (str[i] >= 33)
			k++;
		if (str[i + 1] == '\0'
		|| (k != 0 && str[i] < 33 && str[i + 1] >= 33)) {
			res[n] = malloc_char_str(k);
			n++;
			k = 0;
		}
	}
	return (res = str_paste(res, str));
}
