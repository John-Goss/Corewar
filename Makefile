# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 18:08:17 by jle-quer          #+#    #+#              #
#    Updated: 2016/12/14 18:21:55 by jle-quer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

FLAGS = -Wall -Werror -Wextra

vpath %.c ./src ./src/Instructions/

SRC = corewar.c \
	parsing.c \
	end.c \
	init_data.c \
	create_list.c \
	testaff.c \
	tools.c \
	tools_2.c \
	tools_3.c \
	display_infos_box.c \
	turn_by_slowmode.c \
	add_and_sub.c \
	and_or_xor.c \
	direct_value.c \
	fork_lfork_aff.c \
	indirect_value.c \
	instruction.c \
	instruction_2.c \
	ld_ldi.c \
	live_zjump.c \
	lld_lldi.c \
	parameters.c \
	parameters_2.c \
	st_sti.c

# FILES
OBJS	= $(SRC:.c=.o)
O2		= $(addprefix $(OPATH), $(OBJS))

# DIRECTORIES
LIBFT	= ./Libft/
OPATH	= ./obj/
INC		= ./src/Header/
LINC	= INCLUDES/
LIBINC	= $(LIBFT)$(LINC)
LIB		= $(LIBFT)libft.a

# PROCESS
all: $(NAME)

$(NAME): $(LIB) $(O2)
	@gcc $(FLAGS) $(O2) -L$(LIBFT) -lft -lncurses -I$(INC) -o $@
	@echo "\033[0;32mCorewar compilation done !\033[0;m"

$(LIB):
	@echo "\033[0;32mWaiting, libft is in compilation...\033[0;m"
	@make -C $(LIBFT)

$(OPATH)%.o: %.c
	@gcc $(FLAGS) -I $(INC) -I $(LIBINC) -o $@ -c $<

clean:
	@rm -f $(O2)
	@echo "\033[0;32mObject files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32mExecutable deleted !\033[0;m"
	@make fclean -C $(LIBFT)
	@echo "\033[0;32mLibft cleaned.\033[0;m"

re: fclean all

.PHONY : all, clean, fclean, re
