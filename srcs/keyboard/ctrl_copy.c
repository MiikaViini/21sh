/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:49:29 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 17:16:06 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ctrl_copy(t_term *t)
{
	ssize_t	i;
	ssize_t	j;

	if (t->bytes)
	{
		i = t->index - 1;
		while (i && is_space(&t->inp[i]))
			i--;
		j = i;
		while (j && !is_space(&t->inp[j]))
			j--;
		if (is_space(&t->inp[j]))
			j++;
		if (t->clipboard.buff)
			ft_strdel(&t->clipboard.buff);
		t->clipboard.buff = ft_strsub(&t->inp[j], 0, (size_t)((i - j) + 1));
		t->clipboard.type = COPY;
	}
}
