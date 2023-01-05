/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:11:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/20 11:31:34 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokens.h"

typedef struct s_ast
{
	int				type;			
	char			**cmd;
	char			*file;
	int				redir_type;
	int				to_fd;
	int				from_fd;
	int				err_fd;
	int				fd_close;
	struct s_tlist	*redirs;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

void	build_all_asts(t_ast **tree, t_tlist *tokens);
t_ast	*simple_command(t_ast *node, t_tlist ***tokens);
t_tlist	*new_redir(char *content, char *file, int from, int redir_type);
int		set_aggr_values(t_tlist **redirs, t_tlist **tokens);

#endif
