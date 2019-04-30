/*
** EPITECH PROJECT, 2018
** uti.c
** File description:
** uti.c
*/

#include <string.h>
#include "mysh.h"

int my_strlen_tab(char **tab)
{
	int i = 0;

	for (; tab && tab[i]; ++i);
	return (i);
}

int my_strlen(char *str)
{
	int i = 0;

	for (; str && str[i]; ++i);
	return (i);
}

char *my_strcat(char *dest, char *src, char c)
{
	int i = 0;
	int len = my_strlen(dest) + my_strlen(src) + 1;
	char *dest2 = NULL;

	if (dest != NULL)
		dest2 = malloc_char_str(len);
	if (dest && !dest2)
		return (NULL);
	if (dest == NULL) {
		dest2 = strdup(src);
		return (dest2);
	}
	for (; dest[i]; ++i)
		dest2[i] = dest[i];
	dest2[i] = c;
	i += 1;
	for (int n = 0; src[n]; ++i, ++n)
		dest2[i] = src[n];
	return (dest2);
}

char *strdup_int(char *src, int st)
{
	char *str = NULL;
	int i = 0;
	int n = 0;

	for (;src[i]; ++i);
	str = malloc_char_str(i - st);
	if (!str)
		return (NULL);
	for (i = st; src[i]; ++i, ++n)
		str[n] = src[i];
	return (str);
}

int my_strcmp(char const *s1, char const *s2, int cond)
{
	int i = 0;

	if (cond == 0 && strlen(s1) != strlen(s2))
		return (-1);
	if (cond == 1 && strlen(s1) > strlen(s2))
		return (-1);
	for (int n = 0; s1[i] && s2[i]; ++i) {
		if (s1[i] != s2[i]) {
			n = (s1[i] - s2[i]);
			return (n);
		}
	}
	if (cond == 2 && s2[i] != '=')
		return (-1);
	return (0);
}
