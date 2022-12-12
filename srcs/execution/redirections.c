/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:12:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/12 23:34:12 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	redirection(t_tlist *redirs , int *ret)
{
	if (!redirs)
		return *ret;
	if (redirs->redir_type == REDIR_TRUNC)
	{
		if (redirs->from_fd == -1)
		{
			error_print(NULL, ft_itoa(redirs->from_fd), E_BFD);
			*ret = -1;
		}
		else
		{
			close(redirs->from_fd);
			open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		}	
	}
	else if (redirs->redir_type == REDIR_APPEND)
	{
		close(1);
		redirs->file_fd = \
		open(redirs->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	}
	else if (redirs->redir_type == REDIR_IN)
	{
		close(0);
		redirs->file_fd = open(redirs->file, O_RDONLY);
		if(redirs->file_fd == -1)
		{
			error_print(redirs->file, NULL, E_NOEX);
			 *ret = -1;
		}
	}
	else if (redirs->redir_type == REDIR_AGGR_IN || redirs->redir_type == REDIR_AGGR_OUT)
	{
		if (redirs->fd_close)
			close(redirs->from_fd);
		else
		{
			if (redirs->to_fd == -1)
			{
				error_print("no token", redirs->file, E_SYNERR);
				 *ret = -1;
			}
			else if (redirs->from_fd == -1)
			{
				
				error_print(NULL, redirs->file, E_AMB);
				 *ret = -1;
			}
			else if (redirs->to_fd == -2)
			{
				error_print(NULL, redirs->file, E_BFD);
				 *ret = -1;
			}
			else if (redirs->to_fd == -3)
			{
				error_print(NULL, redirs->file, E_AMB);
				 *ret = -1;
			}
			else
				dup2(redirs->to_fd, redirs->from_fd);
		}
	}
	else if (redirs->redir_type == REDIR_AGGR_STERR_STOUT)
	{
		close(redirs->to_fd);
		open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		dup2(redirs->to_fd, redirs->from_fd);
	}
	if (*ret >= 0)
		redirection(redirs->next, ret);
	return (*ret);
}
