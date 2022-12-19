/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:12:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/19 15:07:29 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int folder_access(t_tlist *redirs)
{
	char	folder[MAX_PATH];
	char	file[255];
	int		len;

	if (ft_strchr(redirs->file, '/') == NULL)
		return 0;
	ft_memset(folder, '\0', MAX_PATH);
	ft_memset(file, '\0', 255);
	ft_strcat(file, ft_strrchr(redirs->file, '/'));
	len = ft_strlen(file) - 1;
	ft_strncat(folder, redirs->file, ft_strlen(redirs->file) - len);
	if (access(folder, F_OK) == 0 && access(redirs->file, F_OK) == -1 
		&& access(folder, W_OK) == -1)
	{
		error_print(NULL, redirs->file, E_NOPERM);
		return 1;
	}
	return 0;
}

static int file_access(t_tlist *redirs)
{
	struct stat	buf;
		
	if (stat(redirs->file, &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		error_print(NULL, redirs->file, E_ISDIR);
		return (0);
	}
	else if (access(redirs->file, F_OK) == 0 && access(redirs->file, W_OK) == -1)
	{
		error_print(NULL, redirs->file, E_NOPERM);
		return (0);
	}
	return (1);
}

static void	redir_out(t_tlist *redirs, int *ret)
{
	if (redirs->from_fd == -1)
	{
		error_print(NULL, ft_itoa(redirs->from_fd), E_BFD);
		*ret = -1;
	}
	else if (!file_access(redirs))
	{
		*ret = -1;
		return ;
	}
	else if (folder_access(redirs))
	{
		*ret = -1;
		return ;
	}
	else
		execute_redir_out(redirs);
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

int	redirection(t_tlist *redirs, int *ret, t_env *env)
{
	if (!redirs)
		return (*ret);
	expand_remove_quotes_redirs(&redirs, env);
	if (redirs->redir_type == REDIR_TRUNC 
		|| redirs->redir_type == REDIR_APPEND
		|| redirs->redir_type == REDIR_AGGR_STERR_STOUT)
		redir_out(redirs, ret);
	else if (redirs->redir_type == REDIR_IN)
		redir_in(redirs, ret);
	else if (redirs->redir_type == REDIR_AGGR_IN
		|| redirs->redir_type == REDIR_AGGR_OUT)
		redir_aggr(redirs, ret);
	if (*ret >= 0)
		redirection(redirs->next, ret, env);
	return (*ret);
}
