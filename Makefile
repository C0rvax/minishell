#------------ NAME -------------#
CC			= cc

NAME		= minishell

#------------ SOURCE -------------#
LEX			= $(addprefix ./lexer/, lexer.c list.c lex_utils.c parse_read.c	\
			  replace_argument.c delete_quotes.c create_cmd_list.c			\
			  search_errors.c create_parsarray.c)

BUILTINS	= $(addprefix ./builtins/, builtins.c)
ENV_PARSING	= $(addprefix ./env_parsing/, env_parsing.c utils_lists.c utils.c)
# EXEC		= 
# SIGNALS		=
ERRORS		= $(addprefix ./error_checks/, error_checks.c)

MAIN		= $(addprefix ./src/, main.c list_cmd.c list_redirect.c)

# SRC			= $(LEX) $(MAIN)	
SRC			= $(LEX) $(MAIN) $(ERRORS)

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
