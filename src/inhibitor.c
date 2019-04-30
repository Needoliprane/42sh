/*
** EPITECH PROJECT, 2018
** inhibitors
** File description:
** inhibitors.c
*/

#include <unistd.h>
#include "mysh.h"

char *open_new_gnl(void)
{
	char *command = NULL;

	write(1, "? ", 2);
	command = get_next_line(0);
	return (command);
}

char *master_check_inhibitors(char *command)
{
	char *command_return = NULL;

	for (int i = 0; command[i]; ++i) {
		if (command[i] == '\\' && command[i + 1] == '\0') {
			command_return = open_new_gnl();
			return (command_return);
		}/*si command_return == NULL ignorer*/
	}/*Sinon exectuer la commande*/
	if (command[0] == '\\')
		return (command + 1);
	return (command);
}
