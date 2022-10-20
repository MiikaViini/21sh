# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 12:56:26 by mviinika          #+#    #+#              #
#    Updated: 2022/10/18 13:26:00 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c length.c \
	flags.c treat_with_mods.c \
	treat_width.c width.c \
	wildcard.c init_struct.c \
	check_edges.c precision.c\
	treat_precision.c \
	d_specifier.c c_specifier.c \
	p_specifier.c x_specifier.c \
	f_specifier.c o_specifier.c \
	s_specifier.c u_specifier.c \
	b_specifier.c \
	per_specifier.c other_mods.c


OBJS = $(SRCS:.c=.o)

LIBFT = ../libft.a

FLAGS = -Wall -Werror -Wextra -pedantic

##COLOURS##
RED = \x1b[31;01m
GREEN = \x1b[32;01m
YELLOW = \x1b[33;01m
RESET = \x1b[32;00m

all: $(NAME)

$(NAME): $(OBJS)
	@cp $(LIBFT) .
	@gcc $(FLAGS) -c $(SRCS)
	@ar rcs $(NAME) $(OBJS) $(LIBFT)
	@rm -f libft.a
	@echo "$(GREEN)Ft_printf compiled$(RESET)"

clean:
	@echo "$(YELLOW)Deleting ft_printf objs$(RESET)"
	@rm -f *.o

fclean: clean
	@echo "$(RED)Removing $(NAME) $(RESET)"
	@rm -f $(NAME)

re: fclean all
