/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:26:56 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/09 22:39:30 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It scrolls the terminal up one line
 *
 * @param t the term structure
 */
static void	ft_scroll_up(t_term *t)
{
	ssize_t	row;

	row = get_linenbr() + 1;
	run_capability("ho");
	run_capability("sr");
	set_cursor(t->c_col, row);
}

/*
 * It handles the backspace key
 * when the cursor is not at the beginning of the line
 *
 * @param t the term structure
 * @param row the row of the cursor
 * @param len the length of the line that is being deleted
 */
static void	backpace_continue(t_term *t, ssize_t row, ssize_t len)
{
	if (!t->c_col)
	{
		t->c_col = t->ws_col - 1;
		t->c_row--;
		set_cursor(t->c_col, get_linenbr() - 1);
	}
	else
	{
		run_capability("le");
		t->c_col--;
	}
	if (!len)
	{
		if (((t->start_row + t->c_row) + 1) >= t->ws_row)
			ft_scroll_up(t);
		ft_remove_nl_addr(t, row);
		t->total_row--;
	}
	run_capability("ce");
	ft_shift_nl_addr(t, -1);
	ft_deletion_shift(t, BCK);
}

/*
 * It deletes the character
 * before the cursor
 *
 * @param t the term structure
 */
void	ft_backspace(t_term *t)
{
	ssize_t	row;
	ssize_t	len;

	if (&t->inp[t->index] == t->nl_addr[t->c_row] && \
		ft_is_prompt_line(t, t->c_row))
		return ;
	row = ft_row_lowest_line(t);
	if (t->nl_addr[row + 1])
		len = (t->nl_addr[row + 1] - t->nl_addr[row]) - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	if (t->index && (t->inp[t->index - 1] == D_QUO || \
		t->inp[t->index - 1] == S_QUO))
		ft_quote_decrement(t, 1);
	backpace_continue(t, row, len);
	if (t->inp[t->index])
		ft_print_trail(t);
}
