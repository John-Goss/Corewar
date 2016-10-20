NAME = corewar

SRC = corewar.c
SRC += init_data.c
SRC += testaff.c
SRC += tools.c

$(OBJ):
	gcc -c $(SRC)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	gcc -o corewar $(OBJ) Libft/libft.a -lncurses

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f corewar

re : fclean all

.PHONY : all, clean, fclean , re
