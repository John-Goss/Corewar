# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vijacque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/12 13:42:35 by vijacque          #+#    #+#              #
#    Updated: 2016/11/30 12:50:26 by jle-quer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME	=	libcorewar.a
CC		=	gcc
FLAG	=	-Wall -Werror -Wextra
INCLUDE =	-I includes

CFILE	=	ft_putendl.c \
			ft_strlen.c \
			ft_strsub.c \
			ft_putchar.c \
			ft_putnbr.c \
			ft_putstr.c \
			is_slash.c \
			ft_puttab.c \
			ft_strjoin.c \
			ft_strchr.c \
			ft_strcpy.c \
			ft_strclr.c \
			ft_bzero.c \
			ft_strdup.c \
			gnl.c \
			ft_atoi.c \
			ft_malloc.c \
			ft_trim.c \
			ft_strsplit.c \
			ft_strncmp.c \
			ft_strcmp.c \
			ft_tablen.c \
			ft_isdigit_str.c \
			ft_isdigit.c \
			ft_linelen.c

HFILE	=	libcorewar.h

HDIR	=	includes/
HDR		=	$(patsubst %.h, $(HDIR)%.h, $(HFILE))
SDIR	=	src/
SRC		=	$(patsubst %.c, $(SDIR)%.c, $(CFILE))
ODIR	=	obj/
OBJ		=	$(patsubst %.c, $(ODIR)%.o, $(CFILE))

all: compile

$(NAME): $(SRC) $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(ODIR)%.o: $(SDIR)%.c $(HDR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

compile:
	@mkdir -p obj/
	$(MAKE) $(NAME)

norm:
	norminette $(SRC) $(HDR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all, clean, fclean, re
