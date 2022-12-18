/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aggr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:27:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/17 17:55:19 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static int	is_valid(t_tlist *redirs)
// {
// 	struct stat	buf;
// 	int			ret;
// 	int			status;

// 	ret = 1;
// 	status = stat(redirs->file, &buf);
// 	if (status == 0 && S_ISDIR(buf.st_mode))
// 	{
// 		ret = 0;
// 	}
// 	else if ((status == 0 && access(redirs->file, W_OK) == -1 && redirs->redir_type == REDIR_AGGR_OUT)
// 		|| ((status == 0 && access(redirs->file, R_OK) == -1) && redirs->redir_type == REDIR_AGGR_IN))
// 	{
// 		ret = 0;
// 	}
// 	return (ret);
// }

// static void	file_errors(t_tlist *redirs)
// {
// 	struct stat	buf;
// 	int			status;

// 	status = stat(redirs->file, &buf);
// 	if (status == 0 && S_ISDIR(buf.st_mode))
// 		error_print(NULL, redirs->file, E_ISDIR);
// 	else if ((access(redirs->file, F_OK) == 0 && access(redirs->file, W_OK) == -1 && redirs->redir_type == REDIR_AGGR_OUT)
// 			|| ((status == 0 && access(redirs->file, R_OK) == -1) && redirs->redir_type == REDIR_AGGR_IN))
// 		error_print(NULL, redirs->file, E_NOPERM);
// 	else
// 	{
// 		if (redirs->redir_type == REDIR_AGGR_OUT)
// 		{
// 			close(1);
// 			open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
// 		}
// 		else if (redirs->redir_type == REDIR_AGGR_IN)
// 		{
// 			close(0);
// 			redirs->file_fd = open(redirs->file, O_RDONLY);
// 		}
// 	}
// }

static void	is_error(t_tlist *redirs, int *ret)
{
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
		if (redirs->to_fd == -1)
			error_print("no token", redirs->file, E_SYNERR);
		else if (redirs->to_fd == -2
			|| redirs->to_fd >= SHELL_MAX_FD || redirs->from_fd >= SHELL_MAX_FD)
			error_print(NULL, redirs->file, E_BFD);
		else if (redirs->to_fd == -3 || redirs->from_fd == -1)
			error_print(NULL, redirs->file, E_AMB);
		else
			dup2(redirs->to_fd, redirs->from_fd);
	}
}
