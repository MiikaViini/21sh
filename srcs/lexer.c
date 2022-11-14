/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/14 16:01:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// void	insert_left(t_ast *root, char *pars, int type, int size)
// {
// 	root->left = create_ast_node(pars, type, size);
// }

// void	insert_right(t_ast *root, char *pars, int type, int size)
// {
// 	ft_printf("insert right");
// 	root->right = create_ast_node(pars, type, size);
// }

t_ast	*create_pipe_node(int type)
{
	t_ast	*root;

	root = ft_memalloc(sizeof(t_ast));
	root->type = type;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

void ast_travers(t_ast *tree)
{
	if (tree == NULL)
		return ;
	ast_travers(tree->left);
	// if (tree->cmd)
	// 	ft_printf("%s -> ", tree->cmd[0]);
	ft_printf("here %d\n", tree->type);
	ast_travers(tree->right);
}

// void initialize_ast(t_ast *ast)
// {
// 	ast->args = NULL;
// 	ast->cmd = NULL;
// 	ast->type = -1;
// 	ast->in_file = -1;
// 	ast->right = NULL;
// }

static t_ast *simple_command(t_ast *node, t_tlist ***tokens)
{
	int i;

	i = 0;
	static int k;
	k++;
	
	if ((**tokens)->type == TOKEN_WORD || (**tokens)->type == TOKEN_DOLLAR)
	{
		node = ft_memalloc(sizeof(node));
		node->cmd = (char **)ft_memalloc(sizeof(char *) * 2);
		while((**tokens))
		{
			if ((**tokens)->type != TOKEN_WORD || (**tokens)->type != TOKEN_DOLLAR)
				break;
			node->cmd[i++] = ft_strdup((**tokens)->str);
			node->type = TOKEN_WORD;
			node->left = NULL;
			node->right = NULL;
			(**tokens) = (**tokens)->next;
		}
		node->cmd[i] = NULL;
	}
	return (node);
}

int	no_pipe(t_tlist *tokens)
{
	t_tlist	*temp;
	
	temp = tokens;
	while (temp)
	{
		if (temp->type == TOKEN_PIPE)
		{
			return 0;
		}
		if (temp->type == TOKEN_SEMICOLON)
		{
			break;
		}
		temp = temp->next;
	}
	return 1;
}

t_ast	*make_ast(t_tlist **tokens)
{
	t_ast *tree;

	tree = create_pipe_node(TOKEN_PIPE);
	tree->left = simple_command(tree, &(tokens));
	if (!(*tokens))
		return tree;
	if ((*tokens)->type == TOKEN_SEMICOLON)
		return tree;
	if (no_pipe((*tokens)->next))
	{
		(*tokens) = (*tokens)->next;
		tree->right = simple_command(tree, &(tokens));
		return(tree);
	}
	else if ((*tokens) && (*tokens)->type == TOKEN_PIPE)
	{
		(*tokens) = (*tokens)->next;
		tree->right = make_ast(tokens);
	}
	return (tree);
}
