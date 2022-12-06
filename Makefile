# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/12/06 13:02:04 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc 

INCLUDE_DIR = ./include

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/
LIB_INCLUDE_DIR = ./libft/include


DIR_S = ./srcs

AST_DIR = ast
AST_FILES = lexer.c

BUILT_INS_DIR = builtins
BUILT_INS_FILES = do_cd.c \
				do_echo.c \
				do_env.c \
				do_exit.c \
				do_setenv.c \
				do_unsetenv.c \

EXECUTION_DIR = execution
EXECUTION_FILES = check_command.c \
				check_exec.c \

EXPANSIONS_DIR = expansions
EXPANSIONS_FILES = dollar_expansion.c \
				handle_expansions.c \
				is_expansion.c \
				passwd_user.c \
				tilde_expansion.c \
				user_expansion.c \

PARSING_DIR = parsing
PARSING_FILES = parse_input.c

UTILS_DIR = utils
UTILS_FILES = check_quotes.c \
			error_print.c \
			get_env.c \
			update_env.c \
			utils.c \
			utils2.c \

SRC_FILES = main.c \
			$(patsubst %, $(AST_DIR)/%, $(AST_FILES)) \
			$(patsubst %, $(BUILT_INS_DIR)/%, $(BUILT_INS_FILES)) \
			$(patsubst %, $(EXECUTION_DIR)/%, $(EXECUTION_FILES)) \
			$(patsubst %, $(EXPANSIONS_DIR)/%, $(EXPANSIONS_FILES)) \
			$(patsubst %, $(PARSING_DIR)/%, $(PARSING_FILES)) \
			$(patsubst %, $(UTILS_DIR)/%, $(UTILS_FILES))
# 			do_echo.c \
# 			check_quotes.c \
# 			handle_expansions.c \
# 			parse_input.c \
# 			do_unsetenv.c \
# 			do_setenv.c \
# 			do_env.c \
# 			do_cd.c \
# 			utils.c \
# 			check_exec.c \
# 			error_print.c \
# 			dollar_expansion.c \
# 			check_command.c \
# 			tilde_expansion.c \
# 			utils2.c \
# 			user_expansion.c \
# 			update_env.c \
# 			is_expansion.c \
# 			get_env.c \
# 			passwd_user.c \
# 			lexer.c \
# 			do_exit.c \
#			check_command_tree.c

DIR_O = ./objs



SRCS := $(patsubst %, $(DIR_S)/%, $(SRC_FILES))

OBJS := $(patsubst %, $(DIR_O)/%, $(SRC_FILES:.c=.o))

FLAGS = -Wall -Wextra -Werror -g -pedantic



##COLOURS##
RED = \x1b[31;01m
GREEN = \x1b[32;01m
YELLOW = \x1b[33;01m
RESET = \x1b[32;00m



$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)
	@echo "$(GREEN)$(NAME) compiled$(RESET)"

$(DIR_O)/%.o: $(DIR_S)/%.c include/ft_21sh.h
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I $(INCLUDE_DIR) -c $< -o $@
all: $(NAME)

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

