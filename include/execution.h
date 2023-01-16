/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:33:09 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/16 19:04:25 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "ft_21sh.h"
# include "tcaps.h"

int			check_builtins(char **input, char **builtins, t_env *env);
int			check_command(char **input, char **path, char **env, int tree);
int			check_redirs(t_ast *tree, t_env *env);
int			exec_single_command(t_ast *tree, char **builtins, t_env *env);
void		exec_tree(t_ast *tree, char **builtins, t_env *env);
void		execute_all(t_env *env, char **builtins, t_ast **tree, t_term *t);
void		execute_redir_out(t_tlist *redirs);
int			expand_and_remove_quotes(t_ast **tree, t_env *env);
int			expand_remove_quotes_redirs(t_tlist **redirs, t_env *env);
char		**get_path(char **env);
void		redir_aggr(t_tlist *redirs, int *ret);
int			redirection(t_tlist *redirs, int *ret, t_env *env);

#endif
