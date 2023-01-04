/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:39:53 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/02 19:42:03 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_bslash_handling(t_term *t)
{
	ssize_t	i;

	i = t->index - 1;
	if (t->ch == '\\' && t->index == t->bytes && !t->heredoc)
	{
		while (i && t->inp[i] == '\\')
			i--;
		if ((t->index - i) % 2)
			t->bslash = 1;
		else
			t->bslash = 0;
	}
	else
		if (t->ch != D_QUO && t->ch != S_QUO)
			t->bslash = 0;
}

int	ft_bslash_escape_check(t_term *t, ssize_t pos)
{
	ssize_t	start;
	ssize_t	count;

	if (!pos)
		return (0);
	start = pos - 1;
	while (start && t->inp[start] == '\\')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->inp[count] == '\\')
		count++;
	if ((count - start) % 2)
		return (1);
	return (0);
}
