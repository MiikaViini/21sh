/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:42:47 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 18:50:06 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	quote_flag_reset(t_term *t)
{
	ssize_t	i;

	i = -1;
	t->q_qty = 0;
	t->quote = 0;
	t->heredoc = 0;
	while (t->inp[++i])
	{
		if ((t->inp[i] == D_QUO || t->inp[i] == S_QUO) && !t->heredoc)
		{
			if (!backslash_escape_check(t, i))
				quote_handling(t, t->inp[i]);
		}
		if (t->inp[i] == '<' && !t->quote)
		{
			heredoc_handling(t);
			if (!t->heredoc && t->delim)
				ft_strdel(&t->delim);
		}
	}
}

void	quote_flag_check(t_term *t, ssize_t index)
{
	ssize_t	i;

	i = index;
	while (t->inp[i] && t->inp[i] == '\\')
		i++;
	if (t->inp[i] == S_QUO || t->inp[i] == D_QUO)
		quote_flag_reset(t);
}
