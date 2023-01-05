/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/22 11:37:00 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# ifdef __linux__
#  define LIN 1
#  define SHELL_MAX_FD 1024
#  include <sys/wait.h>
# endif

# ifdef __APPLE__
#  define LIN 0
#  define SHELL_MAX_FD 256
# endif

# include "../libft/include/libft.h"
# include "ast.h"
# include "tokens.h"
# include "error.h"
# include "builtins.h"
# include "execution.h"
# include "expansions.h"
# include "initialising.h"
# include "parsing.h"
# include "signals.h"
# include "utils.h"

# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>

# define MAX_PATH 1024
# define MAX_LINE 4096
# define SHELL "42sh"

void		free_parsed_input(char **p_input);

/***********\
** utils.c **
\***********/
size_t		ft_linecount(char **arr);
void		free_strarr(char **strarr);
int			is_single_quote(char c);
int			is_double_quote(char c);
int			is_quote(char c);

/************\
** utils2.c **
\************/
int			check_equalsign(char *input);
int			is_valid_char(char c);
void		add_letter(char *word, char c, t_word *values);
int			can_be_added(char c, t_quotes *quots);
int			is_end_of_word(char c, t_quotes *quots, int index);

#endif
