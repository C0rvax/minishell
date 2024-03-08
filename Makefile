CC			= cc

NAME		= minishell

SRC			= $(addprefix ./src/, main.c)					\
			  $(addprefix ./lexer/, lexer.c)

OBJ			:= $(SRC:.c=.o)

CFLAGS		= -Wextra -Wall -Werror -g

HEADERS		= -I./include

LIBRARIES	= -L./printf -lftprintf -L./libft -lft -lreadline

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
