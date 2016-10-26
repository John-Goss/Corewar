NAME = corewar

SRC = corewar.c
SRC += init_data.c
SRC += testaff.c
SRC += tools.c
SRC += display_infos_box.c
SRC += turn_by_slowmode.c
SRC += instructions/add_and_sub.c
SRC += instructions/and_or_xor.c
SRC += instructions/direct_value.c
SRC += instructions/fork_lfork_aff.c
SRC += instructions/indirect_value.c
SRC += instructions/instruction.c
SRC += instructions/ld_ldi.c
SRC += instructions/live_zjump.c
SRC += instructions/lld_lldi.c
SRC += instructions/parameters.c
SRC += instructions/st_sti.c

$(OBJ):
	gcc -c $(SRC)

OBJ = $(SRC:.c=.o)

FLAG = -g -fsanitize=address

all: $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAG) -o corewar $(OBJ) Libft/libft.a -lncurses

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f corewar

re : fclean all

.PHONY : all, clean, fclean , re
