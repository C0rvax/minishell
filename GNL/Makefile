NAME	=	get_next_line.a
SRC		=	get_next_line.c get_next_line_utils.c

CC		=	cc
includes =	get_next_line.h
CFLAGS	=	-Wall -Wextra -Werror
# CPPFLAGS =  -MMD
OBJ		=	$(SRC:%.c=%.o)
DEP 	= 	$(OBJ:.o=.d)

all:	$(NAME)

$(NAME):	 $(OBJ)
		ar rc $(NAME) $(OBJ)

%.o: %.c
		$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

clean:
	rm -f $(OBJ)
	rm -f $(DEP)

fclean: clean
	rm -f $(NAME)
	
re: fclean 
	$(MAKE) all

-include $(DEP)
.PHONY: clean all fclean re all so