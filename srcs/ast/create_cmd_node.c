/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:00:27 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/07 15:00:59 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ast *simple_command(t_ast *node, t_tlist ***tokens)
{
	int i;
	t_tlist *redirs;
	// int aggrs;

	// aggrs = 0;
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
			node->redirs = new_redir((**tokens)->str, NULL, 0, (**tokens)->redir_type);
			if (node->redir_type == REDIR_TRUNC || node->redir_type == REDIR_IN || node->redir_type == REDIR_APPEND )
			{
				(**tokens) = (**tokens)->next;
				if (node->redir_type == REDIR_APPEND)
					(**tokens) = (**tokens)->next;
				node->redirs->file = ft_strdup((**tokens)->str);
			}
			else if (node->redir_type == REDIR_AGGR_IN || node->redir_type == REDIR_AGGR_OUT)
			{
				
				if(set_aggr_values(&node->redirs->from_fd, &node->redirs->to_fd, *tokens) == 0)
				{
					printf("%d\n", (**tokens)->redir_type);
					node->redirs->redir_type = (**tokens)->redir_type;
				}
				node->redirs->file = ft_strdup((**tokens)->file);
				node->redirs->fd_close = (**tokens)->fd_close;
			}
			token_to_last(&redirs, node->redirs);
			(**tokens) = (**tokens)->next;
		}
		else
			break;
	}
	node->redirs = redirs;
	node->cmd[i] = NULL;
	return (node);
}
