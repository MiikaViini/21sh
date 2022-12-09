/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_aggr_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:04:44 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/09 14:59:26 by mviinika         ###   ########.fr       */
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

int set_aggr_values(int *from, int *to, t_tlist **tokens)
{
	char *num;
	struct stat buf;
	int i;
	t_tlist	*temp;

	i = 0;
	temp = (*tokens);
	(*tokens)->fd_close = 0;
	num = ft_strdup((*tokens)->str);
	*from = ft_atoi(num);
	ft_printf("%d %s\n", *from, (*tokens)->str);
	ft_strdel(&num);
	if (is_going_out(temp) && *from == 0)
		*from = 1;
	(*tokens) = (*tokens)->next;
	if ((*tokens) == NULL)
	{
		*to = -1;
		return (-1);
	}
	else
	{
		while (ft_isdigit((*tokens)->str[i]))
			i++;
		if ((*tokens)->str[i] != '\0')
		{
			if (is_going_out(temp) && *from > 1 && (*tokens)->str[0] != '-')
			{
				*from = -1;
				(*tokens)->file = ft_strdup((*tokens)->str);
				return (-1);
			}
			else if ((*tokens)->str[0] == '-')
			{
				//ft_printf("tama");
				(*tokens)->fd_close = 1;
				return 1;
			}
			else if (is_going_in(temp))
			{
				*to = -3;
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
		*to = ft_atoi(num);
		ft_printf("%d %s\n", *to, num);
		ft_strdel(&num);
	}
	if (fstat(*from, &buf) == -1 || fstat(*to, &buf))
	{
		(*tokens)->file = ft_itoa(*to);
		*to = -2;
		return -1;
	}
	return 1;
}
