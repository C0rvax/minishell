CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
RM = rm -rf
AR = ar rc
SRC = ft_printf.c ifforest.c print_hex.c print_number.c print_putchar.c		\
	  print_putstr.c print_unsigned.c print_pointer.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	$(AR) $(NAME) $?

%.o: %.c
	$(CC) -I. -c $? -o $@ $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: bonus all clean fclean re
