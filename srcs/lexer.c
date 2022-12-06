/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/06 11:53:52 by mviinika         ###   ########.fr       */
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
	printf("%s\n", (*tokens)->str);
	if ((*tokens) == NULL)
	{
		error_print("no token", NULL, E_SYNERR);
		return -1;
	}
	else
	{
		while (ft_isdigit((*tokens)->str[i]))
			i++;
		printf("%c %d %d\n", (*tokens)->str[i], *from, (*tokens)->redir_type);
		if ((*tokens)->str[i] != '\0')
		{
			printf("%c\n", (*tokens)->str[i]);
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
				ft_putendl("adsasdasd");
			}
			
			return 0;
		}
		num = ft_strdup((*tokens)->str);
		*to = ft_atoi(num);
		printf("%d\n", *to);
		ft_strdel(&num);
		
	}
	printf("%d\n", *from);
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
	ft_printf("Good node\n");
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



void create_aggr_node(t_ast **node, t_tlist **tokens)
{

	(*node)->redir_type = REDIR_AGGR_IN;
	(*node)->type = NODE_REDIR;
	(*node)->cmd[0] = NULL;
	set_aggr_values(&(*node)->from_fd, &(*node)->to_fd, tokens);
}

t_ast *aggr_node(t_ast *node, t_tlist ***tokens)
{
	t_tlist	*temp;
	
	temp = **tokens;
	node = ft_memalloc(sizeof(node));
	node->type = NODE_CMD;
	while ((**tokens))
	{
		//ft_printf("tokens left [%s] type [%d]\n",(**tokens)->str, (**tokens)->type);
		if ((**tokens)->type == TOKEN_REDIRECT || (**tokens)->type == TOKEN_SEMICOLON 
			|| (**tokens)->type == TOKEN_PIPE)
			{
				break ;
			}
			
		else if ((**tokens)->type == TOKEN_AGGR)
		{
			create_aggr_node(&node, &(**tokens));
			ft_strdel(&(**tokens)->next->str);
			free((**tokens)->next);
			(**tokens) = (**tokens)->next;
			break ;
		}
		**tokens = (**tokens)->next;
	}
	
	// ft_printf("token 3[%s]\n", (*tokens)->next->next->str);
	
	(**tokens) = temp;
	//ft_printf("token 2[%s]\n", (**tokens)->str);
	//ft_printf("redir 1[%d]\n", node->redir_type);
	return (node);
}


t_ast	*make_ast(t_tlist **tokens)
{
	t_ast *tree;

	tree = create_pipe_node(NODE_PIPE);
	tree->left = simple_command(tree, &(tokens));
	if (!tree->left)
		return (NULL);
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
