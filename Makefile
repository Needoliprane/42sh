##
## EPITECH PROJECT, 2017
## makefile
## File description:
## just a simple makefile
##

NAME	=	42sh

SRCPATH	=	src/

SRC	=	$(SRCPATH)env.c				\
		$(SRCPATH)gnl.c				\
		$(SRCPATH)main.c			\
		$(SRCPATH)my_cd.c			\
		$(SRCPATH)my_exe.c			\
		$(SRCPATH)my_free.c			\
		$(SRCPATH)my_malloc.c			\
		$(SRCPATH)my_putstrs.c			\
		$(SRCPATH)my_str_to_word_array.c	\
		$(SRCPATH)prompt.c			\
		$(SRCPATH)make_mid_tab.c		\
		$(SRCPATH)semi_col.c			\
		$(SRCPATH)setenv.c			\
		$(SRCPATH)tab_parsing.c			\
		$(SRCPATH)unset.c			\
		$(SRCPATH)bootstrap.c			\
		$(SRCPATH)make_pip_step.c		\
		$(SRCPATH)uti.c				\
		$(SRCPATH)uti2.c			\
		$(SRCPATH)my_echo.c			\
		$(SRCPATH)op_redirect.c			\
		$(SRCPATH)simple_redirect_left.c	\
		$(SRCPATH)double_redirect_right.c	\
		$(SRCPATH)double_redirect_left.c	\
		$(SRCPATH)simple_redirect_right.c	\
		$(SRCPATH)or_n_and.c			\
		$(SRCPATH)double_array_cat.c		\
		$(SRCPATH)chained_operator.c		\

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra

CPPFLAGS=	-I ./include

LDFLAGS	=	-l ncurses

RM	=	rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
