/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:12:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 12:41:26 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void redir_trunc(t_tlist *redirs , int *ret)
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

static void redir_append(t_tlist *redirs , int *ret)
{
	(void)ret;
	close(STDOUT_FILENO);
	redirs->file_fd = \
	open(redirs->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
}

static void redir_in(t_tlist *redirs , int *ret)
{
	close(STDIN_FILENO);
	redirs->file_fd = open(redirs->file, O_RDONLY);
	if(redirs->file_fd == -1)
	{
		error_print(redirs->file, NULL, E_NOEX);
			*ret = -1;
	}
}

static void redir_aggr(t_tlist *redirs , int *ret)
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
		else if (redirs->to_fd == -2 || redirs->to_fd >= SHELL_MAX_FD || redirs->from_fd >= SHELL_MAX_FD)
		{
			error_print(NULL, redirs->file, E_BFD);
			*ret = -1;
		}
		else if (redirs->to_fd == -3 || redirs->from_fd == -1)
		{
			error_print(NULL, redirs->file, E_AMB);
			*ret = -1;
		}
		else
			dup2(redirs->to_fd, redirs->from_fd);
	}
}

static void redir_aggr_io(t_tlist *redirs , int *ret)
{
	(void)ret;
	close(redirs->to_fd);
	open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	dup2(redirs->to_fd, redirs->from_fd);
}

int	redirection(t_tlist *redirs , int *ret) // Maybe jumptable here for readability
{
	if (!redirs)
		return *ret;
	if (redirs->redir_type == REDIR_TRUNC)
		redir_trunc(redirs, ret);
	else if (redirs->redir_type == REDIR_APPEND)
		redir_append(redirs, ret);
	else if (redirs->redir_type == REDIR_IN)
		redir_in(redirs, ret);
	else if (redirs->redir_type == REDIR_AGGR_IN || redirs->redir_type == REDIR_AGGR_OUT)
		redir_aggr(redirs, ret);
	else if (redirs->redir_type == REDIR_AGGR_STERR_STOUT)
		redir_aggr_io(redirs, ret);
	if (*ret >= 0)
		redirection(redirs->next, ret);
	return (*ret);
}
