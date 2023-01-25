/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aggr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:27:39 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 21:39:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	is_error(t_tlist *redirs, int *ret)
{
	struct stat	buf;
	char		*num;

	
	if (fstat(redirs->to_fd, &buf) == -1 && redirs->to_fd != -3)
	{
		num = ft_itoa(redirs->to_fd);
		error_print(NULL, num, E_BFD);
		ft_strdel(&num);
		*ret = -1;
	}
	else if (redirs->to_fd < 0 || redirs->from_fd < 0
		|| redirs->to_fd >= SHELL_MAX_FD
		|| redirs->from_fd >= SHELL_MAX_FD)
		*ret = -2;
}

void	redir_aggr(t_tlist *redirs, int *ret)
{
	// int	fd;

	// fd = 0;
	if (redirs->fd_close || ft_strcmp("-", redirs->file) == 0)
		close(redirs->from_fd);
	else
	{
		is_error(redirs, ret);
		ft_printf("%d %d\n",redirs->to_fd,redirs->from_fd);
		if ((redirs->to_fd == -2 && redirs->to_fd != -3 )|| (*ret == -2 && redirs->to_fd != -3))
			error_print(NULL, redirs->file, E_BFD);
		else if (redirs->to_fd == -3 || redirs->from_fd == -1)
			error_print(NULL, redirs->file, E_AMB);
		// else if (redirs->file)
		// {
		// 	close(redirs->from_fd);
		// 	fd = open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		// 	dup2(fd, redirs->from_fd);
		// }
		else
			dup2(redirs->to_fd, redirs->from_fd);
	}
}
