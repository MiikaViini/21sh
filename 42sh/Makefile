# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2023/01/09 21:00:25 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = gcc 

INCLUDE_DIR = ./include

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/
LIB_INCLUDE_DIR = ./libft/include

FLAGS = -Wall -Wextra -Werror -g -pedantic

UNAME :=$(shell uname)

AST_DIR = ast
AST_FILES = build_all_asts.c \
			new_redir.c \
			create_cmd_node.c \
			set_aggr_values.c \
			new_variable.c

BUILT_INS_DIR = builtins
BUILT_INS_FILES = do_cd.c \
				do_echo.c \
				do_exit.c \
				do_export.c \
				do_unset.c \
				do_set.c

EXECUTION_DIR = execution
EXECUTION_FILES = check_builtins.c \
				check_command.c \
				check_redirs.c \
				exec_tree.c \
				exec_single_command.c \
				expand_and_remove_quotes.c \
				get_path.c \
				redirection.c \
				redir_aggr.c \
				execute_all.c \
				expand_remove_quotes_redirs.c \
				execute_redir_out.c
				
				
EXPANSIONS_DIR = expansions
EXPANSIONS_FILES = dollar_expansion.c \
				handle_expansions.c \
				is_expansion.c \
				passwd_user.c \
				tilde_expansion.c \
				user_expansion.c \

INITIALISING_DIR = initialising
INITIALISING_FILES = initialize_and_set_builtins.c \
					set_pars_struct.c \
					set_start_values.c \
					initialise_structs.c \
					init_tree.c
					

PARSING_DIR = parsing
PARSING_FILES = parse_input.c \
			new_token.c \
			redir_token.c \
			token_to_last.c \
			check_syntax.c \
			set_values_aggr_io.c \
			set_redirections.c \
			is_redirect.c \
			tokens_del.c \
			token_to_last_var.c

SIGNALS_DIR = signals
SIGNALS_FILES = set_signal_handling.c 

UTILS_DIR = utils
UTILS_FILES = check_quotes.c \
			error_print.c \
			fork_wrapper.c \
			is_operator.c \
			get_env.c \
			update_env.c \
			utils.c \
			utils2.c \
			see_quote.c \
			remove_quotes.c

SRC_FILES = main.c \
			$(patsubst %, $(AST_DIR)/%, $(AST_FILES)) \
			$(patsubst %, $(BUILT_INS_DIR)/%, $(BUILT_INS_FILES)) \
			$(patsubst %, $(EXECUTION_DIR)/%, $(EXECUTION_FILES)) \
			$(patsubst %, $(EXPANSIONS_DIR)/%, $(EXPANSIONS_FILES)) \
			$(patsubst %, $(INITIALISING_DIR)/%, $(INITIALISING_FILES)) \
			$(patsubst %, $(SIGNALS_DIR)/%, $(SIGNALS_FILES)) \
			$(patsubst %, $(PARSING_DIR)/%, $(PARSING_FILES)) \
			$(patsubst %, $(UTILS_DIR)/%, $(UTILS_FILES))

DIR_O = ./objs
DIR_S = ./srcs

SRCS := $(patsubst %, $(DIR_S)/%, $(SRC_FILES))
OBJS := $(patsubst %, $(DIR_O)/%, $(SRC_FILES:.c=.o))



##COLOURS##
ifeq ($(UNAME), Linux)
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[33m
RESET = \033[0m
else 
RED = \x1b[31;01m
GREEN = \x1b[32;01m
YELLOW = \x1b[33;01m
RESET = \x1b[32;00m
endif

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)
	@chmod 755 42sh
	@echo "$(GREEN)$(NAME) compiled$(RESET)"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c include/ft_21sh.h
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
