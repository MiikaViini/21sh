/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:11:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/08 16:00:50 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ft_21sh.h"

typedef struct s_ast
{
	int				type;
	char			*cmd;
	char			**args;
	int				in_file;
	int				out_file;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

t_ast	*create_ast_node(char *pars, int type, int size);
void	insert_right(t_ast *root, char *pars, int type, int size);
void	insert_left(t_ast *root, char *pars, int type, int size);



#endif
