/*
** EPITECH PROJECT, 2018
** mysh.h
** File description:
** mysh
*/

#ifndef MYSH_H_
#define MYSH_H_

#include <stddef.h>

/*STRUTURE*/

typedef struct var_s {
	char *s;
	char **tab_alias;
	char **tab_command_alias;
	char **tab;
	char **mid_tab;
	char **all_tab;
	char **env;
	char **path;
	char *oldpwd;
	char *home;
	int cur_pos;
	int val;
} var_t;

/*PROTOTYPE*/

void my_exe(var_t *var);
void setienv(var_t *var);
void my_cd(var_t *var);
void exit_process(var_t *var);
void unset(var_t *var);
void envi(var_t *var);

void my_free(void *str);
void freeing(char **tab);
void exit_destroy(var_t *var);

char **str_paste(char **tab, const char *str);
char **my_str_to_word_array(const char *str);
void my_putstr(const char *str);
void print_tab(char **tab);
void my_putstr_jump(const char *str);
void err_putstr(const char *str);
char *my_put_nbr_base(int nbr, int base);
char *get_next_line(int fd);
char *fill_g(char *str, char add);
char *get_next_line_dbg(int fd);
int prompt(char **envp);
void for_the_norm(var_t *var);
int my_strcmp(char const *s1, char const *s2, int cond);
void kill_process(var_t *var);
void get_path(var_t *var);
void tab_path(var_t *var, char *str);
void tab_path_paste(var_t *var, char *str);
void cpy_env(var_t *var, char **envp);
char *strdup_int(char *src, int st);
int check_path(var_t *var);
char *my_strcat(char *dest, char *src, char c);
void setenv_occur(var_t *var, int i, int n);
void setenv_cpy(var_t *var);
char **str_cat_tab(char **tab, char *src);
int my_strlen_tab(char **tab);
char *my_strcat_r(char *dest, char *src);
void unset_line(var_t *var, int i);
void unset_loop(var_t *var, int j);
void signals(int err);
void *my_memset(void *str, int c, size_t n);
char *malloc_char_str(int i);
char **malloc_char_tab(int i);
void child_status(int wstatus, var_t *var);
void errq_putstr(char *str1, char *str2, const char *str3, char *str4);

void *my_malloc(unsigned int size);
void print_err(var_t *var, int i);
void cmd_not_found(var_t *var);
int strlen_tab_cmp(char **tab, char *str, int i);
void clean_tab(char **tab, char *op);
char *check_op_parsing(char *str);
void add_space_parsing(char *str, char *tmp);

int check_op(char **tab);
int check_op_loop(char **tab, char **op, int i);
int check_op_middle(char **tab, char **op, int i, int n);
void unset_a_line(char **var, int i);

void make_mid_tab(var_t *var);
void fill_mid_tab(var_t *var, const char **op);
void swap_spe_case(var_t *var, const char **op);
char **str_cat_tab_first(char **tab, char *src);

int how_many_pipes(var_t *var);
void last_child_status(int wstatus, var_t *var);
void making_a_last_pipe(var_t *var, int *pipefd, int n, int i);
void making_a_mid_pipe(var_t *var, int *pipefd, int n, int i);
void making_a_first_pipe(var_t *var, int *pipefd, int n, int i);
void call_pipe2(int *pipefd, int n);
void making_a_pipe(var_t *var);

void builtins_n_exe(var_t *var);
void my_echo(var_t *var);
int my_strlen(char *str);

void builtins_n_exe(var_t *var);
void simple_redirect_left(var_t *var);
void simple_redirect_right(var_t *var);
void double_redirect_right(var_t *var);
void double_redirect_left(var_t *var);

int op_redirect(var_t *var);

char **append_option(char **next_tab, char **arg);
void set_error_value(char **arg, char **next_tab, var_t *var);
void redirect_in_file(var_t *var, int fd);

void set_cur_pos(var_t *var);
int and_n_or(var_t *var);
int index_operand(char const *operator);

char *double_array_cat(char **src, char c);
void chained_out_operator(var_t *var);
void chained_in_operator(var_t *var);

#endif	/* MYSH_H_ */
