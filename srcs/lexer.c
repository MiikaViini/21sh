/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/28 17:28:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ast	*create_pipe_node(int type)
{
	t_ast	*root;

	root = ft_memalloc(sizeof(t_ast));
	root->type = type;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

// void change_fd(char *str, int *in, int *out)
// {
	
// }
void dup_fildes(t_ast *tree)
{
	tree->in_fd = dup2(tree->in_fd,STDIN_FILENO);
	tree->out_fd = dup2(tree->out_fd, STDOUT_FILENO);
	tree->err_fd = dup2(tree->err_fd, STDERR_FILENO);
}
static t_ast *simple_command(t_ast *node, t_tlist ***tokens)
{
	int i;
	int k;
	char *num;

	num = NULL;
	i = 0;
	k = 0;
	node = ft_memalloc(sizeof(node));
	node->cmd = (char **)ft_memalloc(sizeof(char *) * 100);
	dup_fildes(node);
	while(**tokens)
	{
		ft_printf("%s\n",(**tokens)->str);
		if ((**tokens)->type == TOKEN_WORD)
		{
			node->cmd[i++] = ft_strdup((**tokens)->str);
			if (node->type != NODE_REDIR)
				node->type = NODE_CMD;
			node->left = NULL;
			node->right = NULL;
			(**tokens) = (**tokens)->next;
		}
		else if ((**tokens)->type == TOKEN_REDIRECT)
		{
			ft_printf("[%s]\n",(**tokens)->str);
			node->redir_type = (**tokens)->redir_type;
			if (node->redir_type == REDIR_AGGR)
			{
				while(ft_isdigit((**tokens)->str[k++]))
					;
				num = ft_strndup((**tokens)->str, k);
				close(STDERR_FILENO);
				if ((**tokens)->redir_way == REDIR_TRUNC || (**tokens)->redir_way == REDIR_APPEND)
					node->out_fd = dup2(node->out_fd, ft_atoi(num));
				else if ((**tokens)->redir_way == REDIR_IN)
					node->in_fd = dup2(node->out_fd, ft_atoi(num));
				ft_strdel(&num);
				k = 0;
				
			}
		
			//ft_printf("[%s]\n",(**tokens)->str);
			
			//node->file = ft_strdup((**tokens)->str);
			if (ft_isdigit((**tokens)->str[k]))
			{
				//close(STDOUT_FILENO);
				while(ft_isdigit((**tokens)->str[k++]))
				{
					;
				}
				
				num = ft_strndup((**tokens)->str, k - 1);
				ft_printf("ju [%s]\n",num);
				close(ft_atoi(num));
				//dup2(ft_atoi(num), node->out_fd);
				//node->out_fd = dup(ft_atoi(num));
				ft_strdel(&num);
			}
			(**tokens) = (**tokens)->next;
			ft_printf("%d\n", node->out_fd);
			//close(node->out_fd);
			node->file = open((**tokens)->str, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			dup2(node->file, node->out_fd);
		//	ft_printf("%s\n",(**tokens)->str);
			node->type = NODE_REDIR;
			
			(**tokens) = (**tokens)->next;
		}
		else
			break;
	}
	node->cmd[i] = NULL;
	return (node);
}

int	peek_for_last_pipe(t_tlist *tokens)
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


t_ast	*make_ast(t_tlist **tokens)
{
	t_ast *tree;

	tree = create_pipe_node(NODE_PIPE);
	tree->left = simple_command(tree, &(tokens));
	if (!(*tokens))
		return tree;
	if ((*tokens)->type == TOKEN_SEMICOLON)
		return tree;
	if (peek_for_last_pipe((*tokens)->next))
	{
		(*tokens) = (*tokens)->next;
		tree->right = simple_command(tree, &(tokens));
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		(*tokens) = (*tokens)->next;
		tree->right = make_ast(tokens);
	}
	return (tree);
}
