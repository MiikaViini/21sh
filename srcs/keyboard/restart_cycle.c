/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:37:49 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/02 19:34:34 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_restart_cycle(t_term *t)
{
	ft_strclr(t->inp);
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->heredoc = 0;
	t->c_col = 0;
	t->start_row = get_linenbr();
	t->total_row = 0;
	t->his = 0;
	t->c_row = t->total_row;
	ft_strdel(&t->delim);
	set_cursor(t->c_col, t->c_row + t->start_row);
}
