/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:49:29 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/09 23:13:20 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_copy(t_term *t)
{
	ssize_t	i;
	ssize_t	j;

	i = t->index - 1;
	while (i && ft_sspace(&t->inp[i]))
		i--;
	j = i;
	while (j && !ft_sspace(&t->inp[j]))
		j--;
	if (ft_sspace(&t->inp[j]))
		j++;
	if (t->clipboard.buff)
		ft_strdel(&t->clipboard.buff);
	t->clipboard.buff = ft_strsub(&t->inp[j], 0, (size_t)((i - j) + 1));
	t->clipboard.type = COPY;
}
