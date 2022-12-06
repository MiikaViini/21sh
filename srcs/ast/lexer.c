/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/06 14:09:06 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

int set_aggr_values(int *from, int *to, t_tlist **tokens)
{
	char *num;
	struct stat buf;
	int i;

	i = 0;
	(*tokens)->fd_close = 0;
	num = ft_strdup((*tokens)->str);
	*from = ft_atoi(num);
	if (((*tokens)->redir_type == REDIR_TRUNC && *from == 0)
		|| ((*tokens)->redir_type == REDIR_AGGR_OUT && *from == 0))
		*from = 1;
	ft_strdel(&num);
	(*tokens) = (*tokens)->next;
	if ((*tokens) == NULL)
	{
		error_print("no token", NULL, E_SYNERR);
		return -1;
	}
	else
	{
		while (ft_isdigit((*tokens)->str[i]))
			i++;
		if ((*tokens)->str[i] != '\0')
		{
			if (*from > 1 && (*tokens)->str[0] != '-')
			{
				error_print(NULL, (*tokens)->str, E_AMB);
				return (-1);
			}
			else if ((*tokens)->str[0] == '-')
			{
				(*tokens)->fd_close = 1;
				return 1;
			}
			else
			{
				(*tokens)->file = ft_strdup((*tokens)->str);
				(*tokens)->redir_type = REDIR_TRUNC;
			}
			
			return 0;
		}
		num = ft_strdup((*tokens)->str);
		*to = ft_atoi(num);
		ft_strdel(&num);
		
	}
	if (fstat(*from, &buf) == -1 || fstat(*to, &buf))
	{
		num = ft_itoa(*to);
		error_print(NULL, num, E_BFD);
		ft_strdel(&num);
		return -1;
	}
	return 1;
}

static void	lstaddlast(t_tlist **alst, t_tlist *new)
{
	t_tlist	*temp;

	temp = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			temp->next = new;
			break ;
		}
		temp = temp->next;
	}
}

static t_tlist	*newlst(char *content, char *file, int from, int redir_type)
{
	t_tlist	*fresh;

	fresh = (t_tlist *)ft_memalloc(sizeof(t_tlist));
	if (content == NULL)
	{
		fresh->str = NULL;
		fresh->type = 0;
		fresh->next = NULL;
		return (fresh);
	}
	fresh->str = ft_strdup(content);
	fresh->redir_type = redir_type;
	fresh->file = file;
	fresh->from_fd = from;
	fresh->next = NULL;
	return (fresh);
}

void free_token(t_tlist *token)
{
	ft_strdel(&token->file);
	ft_strdel(&token->file);
	free(token);
}
static t_ast *simple_command(t_ast *node, t_tlist ***tokens)
{
	int i;
	t_tlist *redirs;
	int aggrs;

	aggrs = 0;
	i = 0;
	node = (t_ast *)ft_memalloc(sizeof(t_ast));
	node->cmd = (char **)ft_memalloc(sizeof(char *) * 100);
	node->file = NULL;
	redirs = NULL;
	while(**tokens)
	{
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
			node->redir_type = (**tokens)->redir_type;
			node->type = NODE_REDIR;
			node->redirs = newlst((**tokens)->str, NULL, 0, (**tokens)->redir_type);
			if (node->redir_type == REDIR_TRUNC || node->redir_type == REDIR_IN || node->redir_type == REDIR_APPEND )
			{
				(**tokens) = (**tokens)->next;
				if (node->redir_type == REDIR_APPEND)
					(**tokens) = (**tokens)->next;
				node->redirs->file = ft_strdup((**tokens)->str);
			}
			else if (node->redir_type == REDIR_AGGR_IN || node->redir_type == REDIR_AGGR_OUT)
			{
				aggrs = set_aggr_values(&node->redirs->from_fd, &node->redirs->to_fd, *tokens);
				if( aggrs == -1)
				{
					node->type = NODE_CMD;
					//tokens_del(node);
					delete_node(node);
					return ((NULL));
					
				}
				else if (aggrs == 0)
				{
					printf("%d\n", (**tokens)->redir_type);
					node->redirs->redir_type = (**tokens)->redir_type;
					node->redirs->file = ft_strdup((**tokens)->file);
				}
				node->redirs->fd_close = (**tokens)->fd_close;
			}
			lstaddlast(&redirs, node->redirs);
			(**tokens) = (**tokens)->next;
		}
		else
			break;
	}
	node->redirs = redirs;
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
	if (!tree->left)
	{
		free(tree);
		return (NULL);
	}
		
	if (!(*tokens))
		return tree;
	if ((*tokens)->type == TOKEN_SEMICOLON)
		return tree;
	if (peek_for_last_pipe((*tokens)->next))
	{
		(*tokens) = (*tokens)->next;
		tree->right = simple_command(tree, &(tokens));
		if (!tree->right)
		return (NULL);
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		(*tokens) = (*tokens)->next;
		tree->right = make_ast(tokens);
	}
	return (tree);
}
