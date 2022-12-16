/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 13:00:45 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>
# include <stdio.h>
# include <error.h>

# ifdef __linux__
#  define LIN 1
#  include <sys/wait.h>
# endif

# ifdef	__APPLE__
#  define LIN 0
#  include <sys/wait.h>
# endif

# include "../libft/include/libft.h"
# include "ast.h"
# include "tokens.h"
# include "error.h"

# define MAX_VAR 1024
# define MAX_PATH 1024
# define MAX_LINE 4096
# define SHELL_MAX_FD 1024
# define SHELL "21sh"

typedef struct s_env
{
	char	**env;
	char	**path;
	char	*terminal;
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
	char	*last_token_str;
}			t_pars;

typedef struct s_word
{
	int		len;
	int		expan;
	int		k;
	int		i;
	int		total;
	int		type;
	int		redir;
	int		redir_way;
	char	*file;
}			t_word;

int		check_command(char **input, char **path, char **env, int tree);
int		check_redirs(t_ast *tree, t_env *env);
int		check_quotes(char *input);
int		check_builtins(char **input, char **builtins, t_env *env);
int		do_cd(char **input, t_env *env);
int		do_echo(char **input, t_env *env);
int		do_env(char **input, t_env *env);
int		do_exit(char **input, t_env *env);
int		do_setenv(char **input, t_env *env);
int		do_unsetenv(char **input, t_env *env);
char	*dollar_expansion(char *expanded, char *word, char **env, int len);
void	error_print(char *word, char *command, char *e_msg);
int		exec_single_command(t_ast *tree, char **builtins, t_env *env);
void	exec_tree(t_ast *tree, char **builtins, t_env *env);
int		expand_and_remove_quotes(t_ast **tree, t_env *env);
void	get_env(t_env *dest, char **environ, int argc, char **argv);
char	**get_path(char **env);
char	*handle_expansions(char *input, char **env);
int		is_expansion(char *str, int i);
void	init_tree(t_ast ***tree, size_t size);
t_ast	**parse_input(t_pars *pars);
char	*passwd_user(char *input);
char	*tilde_expansion(char *word, char **env, char *expanded);
void	update_env(char **env, char *input, char *var);
char	*user_expansion(char *input);
void	free_parsed_input(char **p_input);
int		redirection(t_tlist *redirs, int *ret, t_env *env);
void	initialise_structs(t_quotes *quotes, t_word *ints, char *input);
void	see_quote(t_quotes *quots, char *input, int i);

char	**initialize_and_set_builtins(void);
void	set_pars_struct(t_pars *pars, char *input);
void	set_start_values(t_ast ***tree, char *buf, int *rb);
void	execute_all(t_env *env, char **builtins, t_ast **tree);
int		expand_remove_quotes_redirs(t_tlist **redirs, t_env *env);

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
void	add_letter(char *word, char c, t_word *ints);
int		can_be_added(char c, t_quotes *quots);
int		is_end_of_word(char c, t_quotes *quots, int index);
int		is_operator (char c, t_quotes *quots);
void	tokens_del(t_tlist **tokens);
int		fork_wrapper(void);
t_tlist	*new_token(char *content, t_word *word_attrs);
int		redir_token(char *trimmed, char *word, t_word *ints);
int		is_redirect(char c, t_quotes *quots);
void	redir_aggr(t_tlist *redirs , int *ret);
int		check_syntax(t_pars *pars, t_tlist *tokens);
void	set_values_aggr_io(t_word *ints, char **word, int *total);
int		set_redirections(t_pars *pars, t_word *ints, char *word, t_quotes *quots);
char	*remove_quotes(char *input);

typedef int					(*t_builtins)(char **input, t_env *env);

static const t_builtins		g_builtins[7] = {
	do_echo,
	do_cd,
	do_setenv,
	do_unsetenv,
	do_env,
	do_exit,
	NULL
};
#endif
