/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:07:42 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/20 10:29:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	execute_redir_out(t_tlist *redirs)
{
	if (ft_strcmp(redirs->file, "/dev/fd/1")
		&& ft_strcmp(redirs->file, "/dev/stdout"))
	{
		close(redirs->from_fd);
		if (redirs->redir_type == REDIR_TRUNC
			&& open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664) >= 0)
			return ;
		else if (redirs->redir_type == REDIR_APPEND
			&& open(redirs->file, O_CREAT | O_WRONLY | O_APPEND, 0664) >= 0)
			return ;
		else if (redirs->redir_type == REDIR_AGGR_STERR_STOUT)
		{
			close(redirs->to_fd);
			open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			dup2(redirs->to_fd, redirs->from_fd);
			return ;
		}
		else
			error_print(NULL, ft_itoa(redirs->from_fd), E_BFD);
	}	
}
