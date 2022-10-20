# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/30 09:25:07 by mviinika          #+#    #+#              #
#    Updated: 2022/10/18 13:19:08 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putchar.c \
	ft_putendl_fd.c ft_putendl.c ft_putnbr.c \
	ft_putnbr_fd.c ft_putstr_fd.c \
	ft_putstr.c ft_strcat.c ft_strchr.c ft_strclr.c \
	ft_strcmp.c ft_strcpy.c \
	ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
	ft_striteri.c ft_strjoin.c \
	ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
	ft_strncmp.c ft_strncpy.c \
	ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
	ft_strsplit.c ft_strstr.c \
	ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
	ft_strlcat.c \
	ft_lstadd.c ft_lstnew.c ft_lstiter.c ft_lstmap.c \
	ft_lstdelone.c ft_lstdel.c ft_strrev.c ft_lstrev.c \
	ft_lstaddlast.c ft_isspace.c ft_swap.c ft_strndup.c \
	ft_pow.c ft_dectobin.c ft_bintodec.c ft_abs.c ft_intlen.c \
	ft_itoabase.c ft_ftoa.c ft_ltoa.c ft_utoa.c ft_putstrlen.c \
	get_next_line.c ft_strsplitws.c ft_strarrcpy.c \
	ft_strarrndup.c ft_linecount.c ft_wordcount_ws.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SRC_FILES))

OBJS = $(addprefix $(DIR_O)/,$(SRC_FILES:.c=.o))

FLAGS = -Wall -Wextra -Werror -g -pedantic

FT_PRINTF = ft_printf/libftprintf.a

FT_PRINTF_DIR = ./ft_printf

##COLOURS##
RED = \x1b[31;01m
GREEN = \x1b[32;01m
YELLOW = \x1b[33;01m
RESET = \x1b[32;00m

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@make -C ./ft_printf/
	@cp $(FT_PRINTF) $(NAME)
	@ar rcs $(NAME) ${OBJS}
	@echo "$(GREEN)Libft compiled$(RESET)"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c include/libft.h
	@mkdir -p $(DIR_O)
	gcc $(FLAGS) -c -I include -o $@ $<

clean:
	@echo "$(YELLOW)Deleting libft objs$(RESET)"
	@rm -Rf $(DIR_O)
	@make clean -C $(FT_PRINTF_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME) $(RESET)"
	@rm -f $(NAME)
	@rm -f $(NAME:.a=.so)
	@make fclean -C $(FT_PRINTF_DIR)

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJ)
