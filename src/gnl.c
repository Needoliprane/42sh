/*
** EPITECH PROJECT, 2018
** gnl.c
** File description:
** get next line
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

char *fill_g(char *str, char add)
{
	char *dest = NULL;
	int i = 0;
	int j = 0;

	for (; str && str[i]; i++);
	if ((dest = malloc_char_str(i + 2)) == NULL)
		return (NULL);
	for (; str && j < i; j++)
		dest[j] = str[j];
	dest[j] = add;
	if (str != NULL)
		free(str);
	return (dest);
}

char *get_next_line(int fd)
{
	char buff[1];
	char *str = NULL;

	for (int n = 0; (n = read(fd, buff, 1) > 0);) {
		if (n == -1 && str) {
			free(str);
			return (NULL);
		}
		else if (n == -1)
			return (NULL);
		if (buff[0] == '\n' && str == NULL)
			return (my_malloc(0));
		if (buff[0] == '\n')
			return (str);
		else if (buff == NULL || (str = fill_g(str, buff[0])) == NULL)
			break;
	}
	if (str)
		free(str);
	return (NULL);
}
