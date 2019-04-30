/*
** EPITECH PROJECT, 2018
** my_malloc.c
** File description:
** my_malloc.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "mysh.h"

void *my_memset(void *str, int c, size_t n)
{
	unsigned char *s = (unsigned char *)str;
	size_t i = 0;

	for (; i < n; i++)
		s[i] = (unsigned char)c;
	return (str);
}

void *my_malloc(unsigned int size)
{
	void *tmp = malloc(size + 1);

	if (tmp == NULL)
		exit (84);
	for (unsigned int i = 0; i < size + 1; i++)
		(*((char *)tmp + i)) = 0;
	return (tmp);
}

char *malloc_char_str(int i)
{
	char *str = malloc(sizeof(char) * (i + 1));

	if (str == NULL) {
		perror("malloc");
		exit (84);
	}
	str = my_memset(str, '\0', (i + 1) * sizeof(char));
	return (str);
}

char **malloc_char_tab(int i)
{
	char **tab = malloc(sizeof(char *) * (i + 1));

	if (tab == NULL) {
		perror("malloc");
		exit (84);
	}
	for (int n = 0; n < (i + 1); n++)
		tab[n] = NULL;
	return (tab);
}
