#------------ NAME -------------#
CC			= cc

NAME		= minishell

#------------ SOURCE -------------#
GNL			= $(addprefix ./GNL/, get_next_line.c get_next_line_utils.c		\
			  Prompted_gnl.c)

LEX			= $(addprefix ./lexer/, lexer.c list.c lex_utils.c parse_read.c	\
			  replace_argument.c delete_quotes.c create_cmd_list.c			\
			  search_errors.c create_parsarray.c append.c replace_home.c)

BUILTINS	= $(addprefix ./builtins/, builtins.c clearing.c echo.c			\
			  env_exit.c pwd.c export.c unset.c cd.c utils.c unset_exp.c	\
			  joinexp.c joinarr.c print_export.c)

EXEC		= $(addprefix ./exec/, exec.c exec_multiple_cmd.c manage_fds.c	\
				clean.c utils_exec.c)

ERRORS		= $(addprefix ./file_checks/, checker.c infile_checks.c 		\
			  outfile_checks.c cmd_checks.c cmd_checks2.c here_doc.c		\
			  utils_checks.c)

MAIN		= $(addprefix ./src/, main.c list_cmd.c list_redirect.c			\
			  list_read.c prompt.c utils.c signals.c signals2.c init_env.c)

SRC			= $(LEX) $(MAIN) $(ERRORS) $(EXEC) $(BUILTINS) $(GNL)

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
