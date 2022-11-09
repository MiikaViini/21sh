/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/09 13:01:50 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	insert_left(t_ast *root, char *pars, int type, int size)
{
	root->left = create_ast_node(pars, type, size);
}

void	insert_right(t_ast *root, char *pars, int type, int size)
{
	ft_printf("insert right");
	root->right = create_ast_node(pars, type, size);
}

t_ast	*create_ast_node(char *pars, int type, int size)
{
	t_ast	*root;

	root = ft_memalloc(sizeof(t_ast));
	(void)size;
	if (pars && *pars)
	{
		ft_printf("pars\n");
		root->cmd = pars;
	}
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
	if (tree->cmd)
		ft_printf("%s -> ", tree->cmd);
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

t_ast *simple_command(t_ast *node, t_tlist **tokens)
{
	if ((*tokens)->type == TOKEN_WORD)
	{
		node = ft_memalloc(sizeof(node));
		//insert_left(node, tokens->str, TOKEN_WORD, 0);
		//insert_left(node, (*tokens)->str, TOKEN_WORD, 0);
		node->cmd = (*tokens)->str;
		node->type = TOKEN_WORD;
		node->left = NULL;
		node->right = NULL;
		(*tokens) = (*tokens)->next;
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
			return 0;
		temp = temp->next;
	}
	return 1;
}

t_ast	*make_ast(t_tlist *tokens)
{
	t_ast *tree;

	tree = create_ast_node(NULL, TOKEN_PIPE, 0);
	tree->left= simple_command(tree, &tokens);
	if (!tokens)
		return tree;
	if (no_pipe(tokens->next))
	{
		insert_right(tree, tokens->next->str, TOKEN_WORD, 0);
		return(tree);
	}
	else if (tokens->type == TOKEN_PIPE)
		tree->right = make_ast(tokens->next);
	return (tree);
}
