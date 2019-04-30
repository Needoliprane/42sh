/*
** EPITECH PROJECT, 2018
** glob.c
** File description:
** Elie
*/

#include <glob.h>
#include <string.h>
#include <stdlib.h>
#include "mysh.h"

static int patterns_len(glob_t *globbuf)
{
	int len = 0;

	for (size_t i = 0; i < globbuf->gl_pathc; i++) {
		len += strlen(globbuf->gl_pathv[i]);
	}
	return (len + globbuf->gl_pathc);
}

static char *append_patterns(glob_t *globbuf)
{
	int len = patterns_len(globbuf);
	char *new_arg = my_malloc(sizeof(char) * len);

	new_arg = memset(new_arg, 0, len);
	for (size_t i = 0; i < globbuf->gl_pathc; i++) {
		new_arg = strcat(new_arg, globbuf->gl_pathv[i]);
		if (i < globbuf->gl_pathc - 1)
			new_arg[strlen(new_arg)] = ' ';
	}
	return (new_arg);
}

static int replace_patern(char **command_tab, int index)
{
	glob_t globbuf;
	int ret = 0;
	char *new_arg = NULL;

	ret = glob(command_tab[index], 0, NULL, &globbuf);
	if (ret == GLOB_NOMATCH
	|| strcmp(command_tab[index], globbuf.gl_pathv[0]) == 0)
		return (0);
	new_arg = append_patterns(&globbuf);
	if (new_arg == NULL)
		return (0);
	free(command_tab[index]);
	command_tab[index] = new_arg;
	return (1);
}

char **globbing(char *command)
{
	char **command_tab = my_str_to_word_array(command);

	for (int i = 0; command_tab[i]; i++) {
		replace_patern(command_tab, i);
	}
	return (command_tab);
}
