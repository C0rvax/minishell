#------------ NAME -------------#
CC			= cc

NAME		= minishell

#------------ SOURCE -------------#
LEX			= $(addprefix ./lexer/, lexer.c list.c lex_utils.c parse_read.c	\
			  replace_argument.c delete_quotes.c create_cmd_list.c			\
			  search_errors.c create_parsarray.c)

BUILTINS	= $(addprefix ./builtins/, builtins.c clearing.c)

ENV_PARSING	= $(addprefix ./env_parsing/, env_parsing.c utils.c)
EXEC		= $(addprefix ./exec/, exec.c exec2.c)
# SIGNALS	=
ERRORS		= $(addprefix ./file_checks/, infile_checks.c outfile_checks.c	\
			  cmd_checks.c here_doc.c utils_in_lists.c)

MAIN		= $(addprefix ./src/, main.c list_cmd.c list_redirect.c			\
			  history.c list_read.c prompt.c)

# SRC			= $(LEX) $(MAIN)	
SRC			= $(LEX) $(MAIN) $(ERRORS) $(ENV_PARSING) $(EXEC) $(BUILTINS)

#------------ FLAGS + INCLUDE -------------#
CFLAGS		= -Wextra -Wall -Werror -g

HEADERS		= -I./include

LIBRARIES	= -L./printf -lftprintf -L./libft -lft -lreadline -L./GNL		\
			  -l:get_next_line.a

#------------ COMPILING -------------#
OBJ			:= $(SRC:.c=.o)

all			: $(NAME)

$(NAME)		: $(OBJ)
		make -C printf
		make -C libft
		make -C GNL
		$(CC) $(CFLAGS) $^ $(LIBRARIES) -o $@

%.o			: %.c
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean		:
		rm -f $(OBJ)
		make clean -C printf
		make clean -C libft
		make clean -C GNL

fclean		: clean
		rm -f $(NAME)
		make fclean -C printf
		make fclean -C libft
		make fclean -C GNL

re			: fclean all

.PHONY		: all clean fclean re
