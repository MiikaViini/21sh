/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/09 13:42:52 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>

# include "../libft/include/libft.h"
# include "ast.h"
# include "tokens.h"
# include "error.h"

# define MAX_VAR 1024
# define MAX_PATH 1024
# define MAX_LINE 4096

# define SHELL "21sh"

typedef struct s_env
{
	char	**env;
	char	**path;
}			t_env;

typedef struct s_quotes
{
	int	s_quote;
	int	d_quote;
	int	closed;
}			t_quotes;

typedef struct s_pars
{
	int		len;
	char	**parsed;
	char	*trimmed;
	int		redir;
	int		fd;
	int		std_out;
}			t_pars;

typedef struct s_word
{
	int		len;
	int		expan;
	int		k;
	int		redir;
}			t_word;

int		check_command(char **input, char **path, char **env);
int		check_exec(t_ast *tree, int rb, char **builtins, t_env *env);
int		check_quotes(char *input);
int		do_cd(char **input, t_env *env);
int		do_echo(char **input, t_env *env);
int		do_env(char **input, t_env *env);
int		do_setenv(char **input, t_env *env);
int		do_unsetenv(char **input, t_env *env);
char	*dollar_expansion(char *expanded, char *word, char **env, int len);
void	error_print(char *word, char *command, char *e_msg);
void	get_env(t_env *dest, char **environ, int argc, char **argv);
char	*handle_expansions(char *input, char **env, int *total, int *i);
int		is_expansion(char *str, int i);
t_ast	*parse_input(t_env *env, t_pars *pars);
char	*passwd_user(char *input);
char	*tilde_expansion(char *word, char **env, char *expanded);
void	update_env(char **env, char *input, char *var);
char	*user_expansion(char *input);
void	free_parsed_input(char **p_input);
int		redirect(t_pars *pars, t_env *env);

/***********\
** utils.c **
\***********/
size_t	ft_linecount(char **arr);
void	free_strarr(char **strarr);
int		is_single_quote(char c);
int		is_double_quote(char c);
int		is_quote(char c);

/***********\
** utils2.c **
\***********/
int		check_equalsign(char *input);
int		is_valid_char(char c);
void	add_letter(char *word, char c, int *total, int *k);
int		can_be_added(char c, t_quotes *quots);
int		is_end_of_word(char c, t_quotes *quots);
int 	is_operator (char c, t_quotes *quots);

t_ast	*make_ast(t_tlist *tokens);
void 	ast_travers(t_ast *tree);

typedef int					(*t_builtins)(char **input, t_env *env);

static const t_builtins		g_builtins[6] = {
	do_echo,
	do_cd,
	do_setenv,
	do_unsetenv,
	do_env,
	NULL
};
#endif
