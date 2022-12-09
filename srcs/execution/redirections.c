/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:12:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/09 15:01:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	redirection(t_tlist *redirs)
{
	int			fd;
	static int	ret_val;

	fd = 0;
	if (!redirs)
		return ret_val;
	if (redirs->redir_type == REDIR_TRUNC)
	{
		close(1);
		open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
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
		if(fd == -1)
		{
			error_print(redirs->file, NULL, E_NOEX);
			ret_val = -1;
		}
	}
	else if (redirs->redir_type == REDIR_AGGR_IN || redirs->redir_type == REDIR_AGGR_OUT)
	{
		ft_printf("to %d from %d\n", redirs->to_fd, redirs->from_fd);
		if (redirs->fd_close)
			close(redirs->from_fd);
		else
		{
			if (redirs->to_fd == -1)
			{
				error_print("no token", redirs->file, E_SYNERR);
				ret_val = -1;
			}
			else if (redirs->from_fd == -1)
			{
				DB
				error_print(NULL, redirs->file, E_AMB);
				ret_val = -1;
			}
			else if (redirs->to_fd == -2)
			{
				error_print(NULL, redirs->file, E_BFD);
				ret_val = -1;
			}
			else if (redirs->to_fd == -3)
			{
				error_print(NULL, redirs->file, E_AMB);
				ret_val = -1;
			}
			else
				dup2(redirs->to_fd, redirs->from_fd);
		}
	}
	redirection(redirs->next);
	return (ret_val);
}
