/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:00:27 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/09 14:04:07 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	apply_redir_attrs(t_ast *node, t_tlist ***tokens)
{
	struct stat	buf;

	if (ft_isdigit((**tokens)->str[0]))
	{
		node->redirs->from_fd = ft_atoi((**tokens)->str);
		if (fstat(node->redirs->from_fd, &buf) == -1)
			node->redirs->from_fd = -1;
	}
	else
		node->redirs->from_fd = 1;
	(**tokens) = (**tokens)->next;
	node->redirs->file = ft_strdup((**tokens)->str);
}

static void	create_redirs(t_ast *node, t_tlist ***tokens)
{
	node->redir_type = (**tokens)->redir_type;
	node->type = NODE_REDIR;
	node->redirs = new_redir((**tokens)->str, NULL, 0, (**tokens)->redir_type);
	if (node->redir_type == REDIR_TRUNC
		|| node->redir_type == REDIR_IN || node->redir_type == REDIR_APPEND)
		apply_redir_attrs(node, tokens);
	else if (node->redir_type == REDIR_AGGR_IN
		|| node->redir_type == REDIR_AGGR_OUT)
	{
		if (set_aggr_values(&node->redirs, *tokens) == 0)
			node->redirs->redir_type = (**tokens)->redir_type;
		if ((**tokens)->fd_close == 0 && (**tokens)->str != NULL)
			node->redirs->file = ft_strdup((**tokens)->str);
		node->redirs->fd_close = (**tokens)->fd_close;
	}
	else if (node->redir_type == REDIR_AGGR_STERR_STOUT)
	{
		node->redirs->from_fd = 2;
		node->redirs->to_fd = 1;
		(**tokens) = (**tokens)->next;
		node->redirs->file = ft_strdup((**tokens)->str);
	}
}

static void	create_words(t_ast *node, t_tlist ***tokens, int *i)
{
	ft_printf("node fd%d\n", node->type);
	node->cmd[(*i)] = ft_strdup((**tokens)->str);
	(*i)++;
	if (node->type != NODE_REDIR && node->type != NODE_INTR_VAR)
		node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	(**tokens) = (**tokens)->next;
}

static void create_intr_var(t_ast *node, t_tlist ***tokens)
{
	node->type = NODE_INTR_VAR;
	node->variables = new_variable((**tokens)->str);
}

/* Creates simple command node, which can include redirections and aggregations.
** Redirections and aggregations are linked list inside simple command node.
** Those are executed in order they appear in input
*/
t_ast	*simple_command(t_ast *node, t_tlist ***tokens)
{
	int		i;
	t_tlist	*redirs;
	t_vars	*vars;

	i = 0;
	node = (t_ast *)ft_memalloc(sizeof(t_ast));
	node->cmd = (char **)ft_memalloc(sizeof(char *) * 100);
	node->file = NULL;
	redirs = NULL;
	vars = NULL;
	while (**tokens)
	{
		ft_printf("node %d\n", node->type);
		if ((**tokens)->type == TOKEN_WORD)
			create_words(node, tokens, &i);
		else if ((**tokens)->type == TOKEN_INTR_VAR)
		{
			create_intr_var(node, tokens);
			token_to_last_var(&vars, node->variables);
			(**tokens) = (**tokens)->next;
		}
		else if ((**tokens)->type == TOKEN_REDIRECT)
		{
			create_redirs(node, tokens);
			token_to_last(&redirs, node->redirs);
			(**tokens) = (**tokens)->next;
		}
		else
			break ;
	}
	node->redirs = redirs;
	node->variables = vars;
	node->cmd[i] = NULL;
	ft_printf("node %d\n", node->type);
	return (node);
}
