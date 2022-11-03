/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:11:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/03 13:27:15 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

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

#endif
