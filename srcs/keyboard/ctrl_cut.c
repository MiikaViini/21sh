/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_cut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:47:32 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 17:15:58 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*cut_to_clipboard(t_term *t)
{
	ssize_t	i;
	ssize_t	start;

	i = t->index - 1;
	while (i && is_space(&t->inp[i]))
		i--;
	while (i && !is_space(&t->inp[i]))
		i--;
	if (!i)
		start = 0;
	else
		start = 1;
	return (ft_strsub(&t->inp[i], start, (size_t)((t->index - i) + 1)));
}

void	ctrl_cut(t_term *t)
{
	int	i;

	if (t->bytes)
	{
		i = -1;
		run_capability("vi");
		if (t->clipboard.buff)
			ft_strdel(&t->clipboard.buff);
		t->clipboard.buff = cut_to_clipboard(t);
		while (t->clipboard.buff[++i])
			backspace(t);
		if (t->inp[t->index])
			print_trail(t);
		t->clipboard.type = CUT;
		run_capability("ve");
	}
}
