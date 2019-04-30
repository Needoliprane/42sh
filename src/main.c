/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main.c
*/

#include "mysh.h"

int main(int ac, char **av, char **envp)
{
	int val = 0;

	if (av[ac] == NULL)
		val = prompt(envp);
	return (val);
}
