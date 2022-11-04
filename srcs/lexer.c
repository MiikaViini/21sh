/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/04 15:44:01 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	insert_left(t_ast *root, char **pars, int type, int size)
{
	root->left = create_ast_node(pars, type, size);
}

void	insert_right(t_ast *root, char **pars, int type, int size)
{
	root->right = create_ast_node(pars, type, size);
}

t_ast	*create_ast_node(char **pars, int type, int size)
{
	t_ast	*root;

	root = (t_ast *)malloc(sizeof(t_ast));
	if (pars)
	{
		root->cmd = pars[size];
		root->args = ft_strarrndup(root->args, &pars[size], size);
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

t_ast	*make_ast(t_env *env, t_pars *pars)
{
	int		i;
	int		pipe;
	t_ast	*root;
	t_ast	*start;

	i = 0;
	pipe = 0;
	(void)env;
	root = create_ast_node(NULL, TOKEN_PIPE, 0);
	start = root;
	while (pars->parsed[i])
	{
		// if (ft_strcmp(pars->parsed[i], "|") == 0)
		// 	insert_right(root, &pars->parsed[i], TOKEN_PIPE, 1);
		if (!root->left)
			insert_left(root, &pars->parsed[i], TOKEN_WORD, 1);
		else if (!root->right)
			insert_right(root, &pars->parsed[i], TOKEN_WORD, 1);
		else
			root = root->right;
		i++;
	}
	root = start;
	return (root);
}
