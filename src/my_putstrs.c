/*
** EPITECH PROJECT, 2018
** my_putstrs.c
** File description:
** my_putstrs.c
*/

#include <string.h>
#include <unistd.h>
#include "mysh.h"

void my_putstr(const char *str)
{
	write(1, str, strlen(str));
}

void my_putstr_jump(const char *str)
{
	my_putstr(str);
	write(1, "\n", 1);
}

void err_putstr(const char *str)
{
	write(2, str, strlen(str));
}

void errq_putstr(char *str1, char *str2, const char *str3, char *str4)
{
	err_putstr(str1);
	err_putstr(str2);
	err_putstr(str3);
	err_putstr(str4);
}

void print_tab(char **tab)
{
	for (int i = 0; tab && tab[i]; i++)
		my_putstr_jump(tab[i]);
}
