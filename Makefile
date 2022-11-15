# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/11/15 10:42:34 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC_FILES = main.c \
			do_echo.c \
			check_quotes.c \
			handle_expansions.c \
			parse_input.c \
			do_unsetenv.c \
			do_setenv.c \
			do_env.c \
			do_cd.c \
			utils.c \
			check_exec.c \
			error_print.c \
			dollar_expansion.c \
			check_command.c \
			tilde_expansion.c \
			utils2.c \
			user_expansion.c \
			update_env.c \
			is_expansion.c \
			get_env.c \
			passwd_user.c \
			redirect.c \
			lexer.c \
			do_exit.c \
			check_command_tree.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SRC_FILES))

OBJS = $(addprefix $(DIR_O)/,$(SRC_FILES:.c=.o))

#FLAGS = -Wall -Wextra -Werror -g -pedantic

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft/

##COLOURS##
RED = \x1b[31;01m
GREEN = \x1b[32;01m
YELLOW = \x1b[33;01m
RESET = \x1b[32;00m

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)
	@echo "$(GREEN)$(NAME) compiled$(RESET)"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c include/ft_21sh.h
	@mkdir -p $(DIR_O)
	gcc $(FLAGS) -c -I include -o $@ $<

clean:
	@echo "$(YELLOW)Deleting $(NAME) objs$(RESET)"
	@rm -Rf $(DIR_O)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME) $(RESET)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

