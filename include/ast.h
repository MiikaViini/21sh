/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:11:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/07 15:15:57 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ft_21sh.h"

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

t_ast	*create_pipe_node(int type);
//t_ast *simple_command(t_ast *node, t_tlist ***tokens);

#endif
