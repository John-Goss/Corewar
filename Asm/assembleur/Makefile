# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vijacque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/12 13:53:35 by vijacque          #+#    #+#              #
#    Updated: 2016/10/12 14:00:20 by vijacque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME	=	asm
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -O3
INCLUDE =	-I includes -I libcorewar/includes

CFILE	=	asm.c \
			read_champ.c \
			checks.c \
			io.c \
			op.c \
			encode.c \
			complete_labels.c \
			complete_octets_list.c \
			arg_type.c \
			write_file.c

HFILE	=	asm.h \
			op.h

HDIR	=	includes/
HDR		=	$(patsubst %.h, $(HDIR)%.h, $(HFILE))
SDIR	=	src/
SRC		=	$(patsubst %.c, $(SDIR)%.c, $(CFILE))
ODIR	=	obj/
OBJ		=	$(patsubst %.c, $(ODIR)%.o, $(CFILE))

all: compile

$(NAME): $(SRC) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L libcorewar/ -lcorewar

$(ODIR)%.o: $(SDIR)%.c $(HDR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

compile:
	@mkdir -p obj/
	$(MAKE) -C libcorewar
	$(MAKE) $(NAME)

norm:
	norminette $(SRC) $(HDR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
