/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:37:49 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/09 20:59:28 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#include "ft_21sh.h"

static void	heredoc_reset(t_term *t)
{
	if (t->delim)
	{
		ft_memcpy(t->history_buff, t->inp, t->bytes);
		ft_nl_removal(t);
		add_command_to_history(t, t->history_buff);
	}
	ft_strdel(&t->delim);
	t->heredoc = 0;
}

void	ft_restart_cycle(t_term *t)
{
	heredoc_reset(t);
	t->ch = 0;
	t->his = 0;
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->c_col = t->prompt_len;
	t->total_row = 0;
	t->bslash = 0;
	t->c_row = 0;
	t->history_row = -1;
	ft_strdel(&t->input_cpy);
	ft_memdel((void **)&t->nl_addr);
	ft_strclr(t->inp);
	ft_strclr(t->history_buff);
	t->start_row = get_linenbr();
}
