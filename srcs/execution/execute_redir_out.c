/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:07:42 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 20:42:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void execute_trunc(t_tlist *redirs)
{
	int	fd;

	close(redirs->from_fd);
	fd = open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	dup2(fd, redirs->from_fd);
}

static void execute_append(t_tlist *redirs)
{
	int	fd;

	close(redirs->from_fd);
	fd = open(redirs->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	dup2(fd, redirs->from_fd);
}

static void execute_sterr_stout(t_tlist *redirs)
{
	int	fd;

	close(1);
	fd = open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	dup2(fd, 2);
}

void	execute_redir_out(t_tlist *redirs)
{
	if (ft_strcmp(redirs->file, "/dev/fd/1")
		&& ft_strcmp(redirs->file, "/dev/stdout"))
	{
		if (redirs->redir_type == REDIR_TRUNC)
			execute_trunc(redirs);
		else if (redirs->redir_type == REDIR_APPEND)
			execute_append(redirs);
		else if (redirs->redir_type == REDIR_AGGR_STERR_STOUT)
			execute_sterr_stout(redirs);
		else
			error_print(NULL, ft_itoa(redirs->from_fd), E_BFD);
	}	
}
