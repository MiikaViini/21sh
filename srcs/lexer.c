/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/03 13:29:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	insert_left(t_ast *root, t_pars *pars, int type)
{
	root->left = create_ast_node(pars, type);
}

void	insert_right(t_ast *root, t_pars *pars, int type)
{
	root->left = create_ast_node(pars, type);
}

t_ast *create_ast_node(t_pars *pars, int type)
{
	t_ast	*root;

	root = (t_ast *)malloc(sizeof(t_ast));
	root->cmd = pars->parsed[0];
	root->args = pars->parsed;
	root->type = type;
}

t_ast *make_ast(t_env *env, t_pars *pars)
{
	int		i;
	t_ast	*root;

	i = 0;
	root = create_ast_node(pars, 0);
	while (pars->parsed[i])
	{
		if (pars->parsed[i][0] == '|')
			insert_right(root, pars, TOKEN_PIPE);
		else
			insert_left(root, pars, TOKEN_WORD);
	}
}