/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:11:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/24 13:59:57 by mviinika         ###   ########.fr       */
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
	int				redir_fd;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

t_ast	*create_pipe_node(int type);
void	insert_right(t_ast *root, char *pars, int type, int size);
void	insert_left(t_ast *root, char *pars, int type, int size);



#endif
