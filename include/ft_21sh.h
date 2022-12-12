/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/12 11:27:16 by mviinika         ###   ########.fr       */
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
# define SHELL "21sh"

# define DB ft_putendl("tassa\n");
# define DB1 ft_putendl("there\n");

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
	char	*last_token_str;
}			t_pars;

typedef struct s_word
{
	int		len;
	int		expan;
	int		k;
	int		type;
	int		redir;
	int		redir_way;
	char	*file;
}			t_word;

// typedef struct s_word_attr
// {
// 	int		len;
// 	int		expan;
// 	int		k;
// 	int		redir;
// }			t_word_attr;

int		check_command(char **input, char **path, char **env, int tree);

int		check_quotes(char *input);
int		check_builtins(char **input, char **builtins, t_env *env, int fd);
int		do_cd(char **input, t_env *env, int fd);
int		do_echo(char **input, t_env *env, int fd);
int		do_env(char **input, t_env *env, int fd);
int		do_exit(char **input, t_env *env, int fd);
int		do_setenv(char **input, t_env *env, int fd);
int		do_unsetenv(char **input, t_env *env, int fd);
char	*dollar_expansion(char *expanded, char *word, char **env, int len);
void	error_print(char *word, char *command, char *e_msg);
int		exec_single_command(t_ast *tree, int rb, char **builtins, t_env *env);
int		exec_tree(t_ast *tree, int rb, char **builtins, t_env *env);
void	expand_and_remove_quotes(t_ast **tree, t_env *env);
void	get_env(t_env *dest, char **environ, int argc, char **argv);
char	**get_path(char **env);
char	*handle_expansions(char *input, char **env);
int		is_expansion(char *str, int i);
t_ast	**parse_input(t_env *env, t_pars *pars);
char	*passwd_user(char *input);
char	*tilde_expansion(char *word, char **env, char *expanded);
void	update_env(char **env, char *input, char *var);
char	*user_expansion(char *input);
void	free_parsed_input(char **p_input);
int 	redirection(t_tlist *redirs, int *ret);
int		check_command_tree(char **input, char **path, char **env);

void	initialise_structs(t_quotes *quotes, t_word *ints, char *input);
void	see_quote(t_quotes *quots, char *input, int i);

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
int		is_end_of_word(char c, t_quotes *quots, int index);
int		is_operator (char c, t_quotes *quots);
void	tokens_del(t_tlist **tokens);

void 	ast_travers(t_ast *tree, t_env *env);
void 	delete_node(t_ast *node);
int		fork1(void);
t_ast	*build_ast(t_tlist **tokens);
t_tlist	*new_token(char *content, t_word *word_attrs);
t_ast	*simple_command(t_ast *node, t_tlist ***tokens);
void	token_to_last(t_tlist **alst, t_tlist *new);
t_tlist	*new_redir(char *content, char *file, int from, int redir_type);
int 	set_aggr_values(int *from, int *to, t_tlist **tokens);
int redir_token(char *trimmed, char *word, t_word *ints, int *total);

typedef int					(*t_builtins)(char **input, t_env *env, int fd);

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
