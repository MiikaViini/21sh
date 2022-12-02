/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:54:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/02 16:17:34 by mviinika         ###   ########.fr       */
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
// void dup_fildes(t_ast *tree)
// {
// 	tree->in_fd = 0;
// 	tree->out_fd = 1;
// 	tree->err_fd = 2;
// 	tree->in_fd = dup2(tree->in_fd, 0);
// 	tree->out_fd = dup2(tree->out_fd, 1);
// 	tree->err_fd = dup2(tree->err_fd, 2);
// 	perror(NULL);
// 	ft_printf("%d %d %d\n", tree->in_fd, tree->out_fd, tree->err_fd);
// }

// char *check_fildes(char *num)
// {
// 	DIR *dirp;
// 	struct dirent *ent;
// 	int i;
	
// 	i = 0;
// 	dirp = opendir("/dev/fd");
// 	ent = readdir(dirp);
// 	while(entity != NULL)
// 	{
// 		dirname = ft_strjoin()
// 	}
// }

int set_aggr_values(int *from, int *to, t_tlist **tokens)
{
	char *num;
	int	k;

	k = 0;
	//ft_printf("(*tokens)->str %s\n", (*tokens)->str);
	while (ft_isdigit((*tokens)->str[k++]))
		;
	num = ft_strndup((*tokens)->str, k);
	*from = ft_atoi(num);
	k = 0;
	ft_strdel(&num);
	(*tokens) = (*tokens)->next;
	//ft_printf("(*tokens)->str %s\n", (*tokens)->str);
	if ((*tokens) == NULL)
	{
		error_print("no token", NULL, E_SYNERR);
		return -1;
	}
	else
	{
		while (ft_isdigit((*tokens)->str[k]))
				k++;
		if ((*tokens)->str[k] != 0 && !ft_isspace((*tokens)->str[k]) && (*tokens)->str[k] != '-')
		{
			error_print("weird fd", NULL, E_SYNERR);
			// ft_strdel(&(*tokens)->str);
			//ft_strdel(&(*tokens)->str);
			return -1;
		}
		else
		{
			num = ft_strndup((*tokens)->str, k);
			*to = ft_atoi(num);
			ft_strdel(&num);
		}
	}
	return 0;
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

static t_ast *simple_command(t_ast *node, t_tlist ***tokens)
{
	int i;
	int k;
	char *num;
	t_tlist *redirs;
	
	//struct stat buf;

	num = NULL;
	i = 0;
	k = 0;
	node = ft_memalloc(sizeof(node));
	node->cmd = (char **)ft_memalloc(sizeof(char *) * 100);
	//dup_fildes(node);
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
			//create_aggr_node(&node, &(*tokens)->next);
			node->redir_type = (**tokens)->redir_type;
			node->type = NODE_REDIR;
			node->redirs = newlst((**tokens)->str, NULL, 0, (**tokens)->redir_type);
			//node->redirs->next = NULL;
			if (node->redir_type == REDIR_TRUNC || node->redir_type == REDIR_IN || node->redir_type == REDIR_APPEND )
			{
				(**tokens) = (**tokens)->next;
				if (node->redir_type == REDIR_APPEND)
					(**tokens) = (**tokens)->next;
				node->redirs->file = ft_strdup((**tokens)->str);
			}
			else if (node->redir_type == REDIR_AGGR_IN || node->redir_type == REDIR_AGGR_OUT)
			{
				if(set_aggr_values(&node->redirs->from_fd, &node->redirs->to_fd, *tokens) == -1)
				{
					node->type = NODE_CMD;
					//free(*tokens);
					return ((NULL));
					
				}
					
			}
			lstaddlast(&redirs, node->redirs);
			//	ft_printf("(*tokens)->str %s\n", (**	tokens)->str);
			// {
			// 	while(ft_isdigit((**tokens)->str[k++]))
			// 		;
			// 	num = ft_strndup((**tokens)->str, k);
			// 	node->from_fd = ft_atoi(num);
			// 	k = 0;
			// 	ft_strdel(&num);
			// 	(**tokens) = (**tokens)->next;
			// 	if (**tokens == NULL)
			// 	{
			// 		error_print("no token", NULL, E_SYNERR);
			// 		return (NULL);
			// 	}
			// 	else
			// 	{
			// 		while (ft_isdigit((**tokens)->str[k]))
			// 				k++;
			// 		if ((**tokens)->str[k] != 0 && !ft_isspace((**tokens)->str[k]))
			// 		{
			// 			error_print("weird fd", NULL, E_SYNERR);
			// 			return (NULL);
			// 		}
			// 		else
			// 		{
			// 			num = ft_strndup((**tokens)->str, k);
			// 			node->to_fd = ft_atoi(num);
			// 			ft_strdel(&num);
			// 		}
			// 	}
			// }
			// if (ft_isdigit((**tokens)->str[k]))
			// {
			// 	while(ft_isdigit((**tokens)->str[k++]))
			// 		;
			// 	num = ft_strndup((**tokens)->str, k - 1);
			// 	(**tokens) = (**tokens)->next;
			// 	if (**tokens == NULL)
			// 	{
			// 		error_print(NULL, NULL, E_SYNERR);
			// 		return (NULL);
			// 	}
			// 	node->file = ft_strdup((**tokens)->str);
			// }
			// else
			// {
			// 	if ((**tokens)->redir_way == REDIR_TRUNC)
			// 	{
			// 		node->redir_type = REDIR_TRUNC;
			// 		(**tokens) = (**tokens)->next;
			// 		node->file = ft_strdup((**tokens)->str);
			// 	}
			// 	else if ((**tokens)->redir_way == REDIR_IN)
			// 	{
			// 		node->redir_type = REDIR_IN;
			// 		(**tokens) = (**tokens)->next;
			// 		node->file = ft_strdup((**tokens)->str);
			// 	}
			// }
			(**tokens) = (**tokens)->next;
		}
		else
			break;
	}
	node->redirs = redirs;
	// ft_printf("out fd [] [%d]\n", node->type);
	
	// ft_printf("out fd [] [%d]\n", node->redirs->from_fd);
	// ft_printf("out fd [] [%s]\n", node->redirs->next->file);
	// exit(1);
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
	if (!(*tokens))
	{
		return tree;
	}
	if (!tree->left)
	{
		return (NULL);
	}
		
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
