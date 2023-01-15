# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2023/01/15 12:47:40 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

INCLUDE_DIR = ./include

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/
LIB_INCLUDE_DIR = ./libft/include

FLAGS = -Wall -Wextra -Werror -pedantic -g -fsanitize=address

UNAME :=$(shell uname)

AST_DIR = ast
AST_FILES = build_all_asts.c \
			new_redir.c \
			create_cmd_node.c \
			set_aggr_values.c \

BUILT_INS_DIR = builtins
BUILT_INS_FILES = do_cd.c \
				do_echo.c \
				do_env.c \
				do_exit.c \
				do_setenv.c \
				do_unsetenv.c

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

KEYBOARD_DIR = keyboard
KEYBOARD_FILES = tcaps.c \
				inits.c \
				window.c \
				input_circle.c \
				new_line.c \
				nl_utils.c \
				signals.c \
				restart_cycle.c \
				esc_parse.c \
				move_word.c \
				line_up.c \
				line_down.c \
				get_input.c \
				insertion.c \
				space.c \
				backspace.c \
				kb_ctrl.c \
				ctrl_cut.c \
				ctrl_copy.c \
				ctrl_paste.c \
				trigger_nl.c \
				history.c \
				get_history.c \
				kb_utils.c \
				cursor_control.c \
				quote_management.c \
				print_trail.c \
				prompt_control.c \
				get_line_len.c \
				print_input.c \
				nl_removal.c \
				history_new_line.c \
				backslash.c \
				quote_utils.c \
				delim_utils.c \
				ctrl_d.c

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

SIGNALS_DIR = signals
SIGNALS_FILES = set_signal_handling.c \
				set_signal_fork.c

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
			heredocs.c \
			$(patsubst %, $(AST_DIR)/%, $(AST_FILES)) \
			$(patsubst %, $(BUILT_INS_DIR)/%, $(BUILT_INS_FILES)) \
			$(patsubst %, $(EXECUTION_DIR)/%, $(EXECUTION_FILES)) \
			$(patsubst %, $(EXPANSIONS_DIR)/%, $(EXPANSIONS_FILES)) \
			$(patsubst %, $(INITIALISING_DIR)/%, $(INITIALISING_FILES)) \
			$(patsubst %, $(SIGNALS_DIR)/%, $(SIGNALS_FILES)) \
			$(patsubst %, $(PARSING_DIR)/%, $(PARSING_FILES)) \
			$(patsubst %, $(UTILS_DIR)/%, $(UTILS_FILES)) \
			$(patsubst %, $(KEYBOARD_DIR)/%, $(KEYBOARD_FILES))

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
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) -ltermcap $(LIBFT)
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
