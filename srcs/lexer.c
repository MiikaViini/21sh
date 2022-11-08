/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/08 16:01:22 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	insert_left(t_ast *root, char *pars, int type, int size)
{
	root->left = create_ast_node(pars, type, size);
	root = root->left;
}

void	insert_right(t_ast *root, char *pars, int type, int size)
{
	ft_printf("insert right");
	root->right = create_ast_node(pars, type, size);
	
	root = root->right;
}

t_ast	*create_ast_node(char *pars, int type, int size)
{
	t_ast	*root;

	root = (t_ast *)malloc(sizeof(t_ast));
	(void)size;
	if (*pars)
	{
		ft_printf("insert right\n");
		root->cmd = pars;
		ft_printf("insertdddd right\n");
	}
	root->type = type;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

void ast_travers(t_ast *tree)
{
	if (tree == NULL)
	{
		return ;
	}
	ast_travers(tree->left);
	ft_printf("%d -> ", tree->type);
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
	node->cmd = (*tokens)->str;
	*tokens = (*tokens)->next;
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

	tree = ft_memalloc(sizeof(tree));
	tree->type = TOKEN_PIPE;
	// if (tokens == NULL)
	// 	return tree;
	ft_printf("token %s\n", tokens->str);
	tree->left = simple_command(tree, &tokens);
	ft_printf("token %s\n", tokens->str);

	if (tokens->type == TOKEN_WORD || no_pipe(tokens))
	{
		ft_printf("word a%s\n", tokens->str);
		insert_left(tree, tokens->str, TOKEN_WORD, 0);
		
	}
	
	else if (!no_pipe(tokens))
	{
		ft_printf("word d%s\n", tokens->str);
		insert_right(tree, tokens->str, TOKEN_WORD, 0);
		ft_printf("word d%s\n", tokens->str);
		return(tree);
	}
	else if (tokens->type == TOKEN_PIPE && tokens->next)
	{
		ft_printf("word  s%s\n", tokens->str);
		make_ast(tokens->next);
	}
	
	return (tree);
}
