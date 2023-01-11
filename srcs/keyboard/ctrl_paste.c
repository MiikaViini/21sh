/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:14:23 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/11 20:32:18 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	paste_into_array(t_term *t)
{
	int	i;

	i = -1;
	while (t->bytes < (BUFF_SIZE - 1) && t->clipboard.buff[++i])
	{
		t->c_col++;
		ft_putc(t->clipboard.buff[i]);
		ft_shift_nl_addr(t, 1);
		if (t->inp[t->index])
			ft_shift_insert(t);
		t->inp[t->index++] = t->clipboard.buff[i];
		t->bytes++;
		trigger_nl(t);
		if (t->c_col == t->ws_col)
			t->c_row++;
	}
}

void	ft_paste(t_term *t)
{
	if (t->clipboard.buff)
	{
		run_capability("vi");
		paste_into_array(t);
		if (t->inp[t->index])
			ft_print_trail(t);
		if (t->clipboard.type == CUT)
			ft_strdel(&t->clipboard.buff);
		ft_quote_flag_reset(t);
		run_capability("ve");
	}
}
