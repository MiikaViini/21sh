/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/07 15:11:27 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


static int	peek_for_last_pipe(t_tlist *tokens)
{
	t_tlist	*temp;
	
	temp = tokens;
	while (temp)
	{
		if (temp->type == TOKEN_PIPE)
			return 0;
		if (temp->type == TOKEN_SEMICOLON)
			break;
		temp = temp->next;
	}
	return 1;
}

t_ast	*create_pipe_node(int type)
{
	t_ast	*root;

	root = (t_ast *)ft_memalloc(sizeof(t_ast));
	root->type = type;
	root->cmd = NULL;
	root->file = NULL;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

t_ast	*build_ast(t_tlist **tokens)
{
	t_ast *tree;

	tree = create_pipe_node(NODE_PIPE);
	tree->left = simple_command(tree, &(tokens));
	if (!(*tokens) || (*tokens)->type == TOKEN_SEMICOLON)
		return tree;
	if (peek_for_last_pipe((*tokens)->next))
	{
		(*tokens) = (*tokens)->next;
		tree->right = simple_command(tree, &(tokens));
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		(*tokens) = (*tokens)->next;
		tree->right = build_ast(tokens);
	}
	return (tree);
}
