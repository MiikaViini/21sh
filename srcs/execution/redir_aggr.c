/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aggr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:27:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 13:29:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	redir_aggr(t_tlist *redirs , int *ret)
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
