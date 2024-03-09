#------------ NAME -------------#
CC			= cc

NAME		= minishell

#------------ SOURCE -------------#
LEX			= $(addprefix ./lexer/, lexer.c list.c lex_utils.c parse_read.c	\
			  replace_argument.c)

MAIN		= $(addprefix ./src/, main.c)					\

SRC			= $(LEX) $(MAIN)	

#------------ FLAGS + INCLUDE -------------#
CFLAGS		= -Wextra -Wall -Werror -g

HEADERS		= -I./include

LIBRARIES	= -L./printf -lftprintf -L./libft -lft -lreadline

#------------ COMPILING -------------#
OBJ			:= $(SRC:.c=.o)

all			: $(NAME)

$(NAME)		: $(OBJ)
		make -C printf
		make -C libft
		$(CC) $(CFLAGS) $^ $(LIBRARIES) -o $@

%.o			: %.c
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean		:
		rm -f $(OBJ)
		make clean -C printf
		make clean -C libft

fclean		: clean
		rm -f $(NAME)
		make fclean -C printf
		make fclean -C libft

re			: fclean all

.PHONY		: all clean fclean re
