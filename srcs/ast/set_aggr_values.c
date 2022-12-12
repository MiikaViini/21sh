/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_aggr_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:04:44 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/12 13:47:04 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int is_going_out(t_tlist *tokens)
{
	return ((tokens->redir_type == REDIR_TRUNC)
		||(tokens->redir_type == REDIR_APPEND)  
		|| (tokens->redir_type == REDIR_AGGR_OUT));
}
static int is_going_in(t_tlist *tokens)
{
	return ((tokens->redir_type == REDIR_IN)
		|| (tokens->redir_type == REDIR_AGGR_IN));
}

static int set_fds(t_tlist **redirs, t_tlist **tokens, t_tlist *temp, char *num)
{
	int i;

	i = 0;
	while (ft_isdigit((*tokens)->str[i]))
		i++;
	if ((*tokens)->str[i] != '\0')
	{
		if (is_going_out(temp) && (*redirs)->from_fd > 1 && (*tokens)->str[0] != '-')
		{
			(*redirs)->from_fd = -1;
			(*tokens)->file = ft_strdup((*tokens)->str);
			return (-1);
		}
		else if ((*tokens)->str[0] == '-')
		{
			(*tokens)->fd_close = 1;
			return 1;
		}
		else if (is_going_in(temp))
		{
			(*redirs)->to_fd = -3;
			return (-1);
		}
		else
		{
			(*tokens)->file = ft_strdup((*tokens)->str);
			(*tokens)->redir_type = REDIR_TRUNC;
		}
		return 0;
	}
	num = ft_strdup((*tokens)->str);
	(*redirs)->to_fd = ft_atoi(num);
	ft_strdel(&num);
	return 1;
}

static int check_fd_validity(t_tlist **redirs, t_tlist **tokens, int *ret)
{
	struct stat buf;

	if (fstat((*redirs)->from_fd, &buf) == -1 || fstat((*redirs)->to_fd, &buf))
	{
		(*tokens)->file = ft_itoa((*redirs)->to_fd);
		(*redirs)->to_fd = -2;
		*ret = -1;
	}
	return (*ret);
}

int set_aggr_values(t_tlist **redirs, t_tlist **tokens)
{
	char *num;
	int ret;
	t_tlist	*temp;

	ret = 0;
	temp = (*tokens);
	(*tokens)->fd_close = 0;
	num = ft_strdup((*tokens)->str);
	(*redirs)->from_fd = ft_atoi(num);
	ft_strdel(&num);
	if (is_going_out(temp) && (*redirs)->from_fd == 0)
		(*redirs)->from_fd = 1;
	(*tokens) = (*tokens)->next;
	if ((*tokens) == NULL)
	{
		(*redirs)->to_fd = -1;
		return (-1);
	}
	else
		ret = set_fds(redirs, tokens, temp, num);
	check_fd_validity(redirs, tokens, &ret);
	return ret;
}
