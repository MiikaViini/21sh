/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:12:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 20:40:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	redir_trunc(t_tlist *redirs, int *ret)
{
	struct stat	buf;

	if (redirs->from_fd == -1)
	{
		error_print(NULL, ft_itoa(redirs->from_fd), E_BFD);
		*ret = -1;
	}
	else
	{
		if (stat(redirs->file, &buf) == 0 && S_ISDIR(buf.st_mode))
		{
			error_print(NULL, redirs->file, E_ISDIR);
			*ret = -1;
			return ;
		}
		else if (access(redirs->file, F_OK) == 0
			&& access(redirs->file, W_OK) == -1)
		{
			error_print(NULL, redirs->file, E_NOPERM);
			*ret = -1;
			return ;
		}
		close(redirs->from_fd);
		open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	}
}

static void	redir_append(t_tlist *redirs, int *ret)
{
	(void)ret;
	close(STDOUT_FILENO);
	redirs->file_fd = \
	open(redirs->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
}

static void	redir_in(t_tlist *redirs, int *ret)
{
	struct stat	buf;
	int			status;

	status = stat(redirs->file, &buf);
	close(STDIN_FILENO);
	redirs->file_fd = open(redirs->file, O_RDONLY);
	if (redirs->file_fd == -1)
	{
		if (status == 0 && access(redirs->file, R_OK) == -1)
			error_print(redirs->file, NULL, E_NOPERM);
		else if (status == -1)
			error_print(redirs->file, NULL, E_NOEX);
		else if (status == 0 && S_ISDIR(buf.st_mode))
			error_print(redirs->file, NULL, E_ISDIR);
		*ret = -1;
	}
}

static void	redir_aggr_io(t_tlist *redirs, int *ret)
{
	(void)ret;
	close(redirs->to_fd);
	open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	dup2(redirs->to_fd, redirs->from_fd);
}

int	redirection(t_tlist *redirs, int *ret, t_env *env)
{
	if (!redirs)
		return (*ret);
	ft_printf("%s %d\n", redirs->file, redirs->redir_type);
	expand_remove_quotes_redirs(&redirs, env);
	if (redirs->redir_type == REDIR_TRUNC)
		redir_trunc(redirs, ret);
	else if (redirs->redir_type == REDIR_APPEND)
		redir_append(redirs, ret);
	else if (redirs->redir_type == REDIR_IN)
		redir_in(redirs, ret);
	else if (redirs->redir_type == REDIR_AGGR_IN
		|| redirs->redir_type == REDIR_AGGR_OUT)
		redir_aggr(redirs, ret);
	else if (redirs->redir_type == REDIR_AGGR_STERR_STOUT)
		redir_aggr_io(redirs, ret);
	if (*ret >= 0)
		redirection(redirs->next, ret, env);
	return (*ret);
}
