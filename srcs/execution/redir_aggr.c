/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aggr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:27:39 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 14:33:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	is_error(t_tlist *redirs, int *ret)
{
	struct stat	buf;
	char		*num;

	if (fstat(redirs->to_fd, &buf) == -1)
	{
		num = ft_itoa(redirs->to_fd);
		error_print(NULL, num, E_BFD);
		ft_strdel(&num);
		*ret = -1;
	}
	if (redirs->to_fd < 0 || redirs->from_fd < 0
		|| redirs->to_fd >= SHELL_MAX_FD
		|| redirs->from_fd >= SHELL_MAX_FD)
		*ret = -1;
}

void	redir_aggr(t_tlist *redirs, int *ret)
{
	if (redirs->fd_close || ft_strcmp("-", redirs->file) == 0)
		close(redirs->from_fd);
	else
	{
		is_error(redirs, ret);
		if (redirs->to_fd == -2
			|| redirs->to_fd >= SHELL_MAX_FD
			|| redirs->from_fd >= SHELL_MAX_FD)
			error_print(NULL, redirs->file, E_BFD);
		else if (redirs->to_fd == -3 || redirs->from_fd == -1)
			error_print(NULL, redirs->file, E_AMB);
		else
			dup2(redirs->to_fd, redirs->from_fd);
	}
}
