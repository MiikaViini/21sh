/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:44:28 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 18:32:38 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	is_separator(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	delim_fetch_error(t_term *t, char *ptr)
{
	if (*ptr && is_separator(*ptr))
	{
		ft_putstr_fd("\n21sh: syntax error near unexpected token `", 2);
		write(2, ptr, 1);
		ft_putstr_fd("'", 2);
	}
	else
		ft_putstr_fd("\n21sh: syntax error near unexpected token `newline'", 2);
	ft_strclr(t->inp);
	t->heredoc = 0;
}

static char	*strdelim(t_term *t)
{
	char	*ptr;
	int		delim_qty;

	ptr = t->inp;
	delim_qty = 0;
	while (*ptr)
	{
		if (*ptr == '<')
			delim_qty++;
		if (delim_qty == 2)
			return (ptr + 1);
		ptr++;
	}
	return (ptr);
}

int	delim_fetch(t_term *t)
{
	char	*ptr;
	char	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = strdelim(t);
		while (*ptr && is_space(ptr))
			ptr++;
		if (*ptr && !is_separator(*ptr))
		{
			end_q = ptr;
			while (*end_q && !is_space(end_q))
				end_q++;
			t->delim = ft_strsub(ptr, 0, end_q - ptr);
		}
		else
		{
			delim_fetch_error(t, ptr);
			return (1);
		}
	}
	return (0);
}
