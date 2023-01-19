/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:26:56 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/19 15:44:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	scroll_up(t_term *t)
{
	run_capability("ho");
	run_capability("sr");
	set_cursor(t->c_col, (t->start_row + t->c_row));
}

static void	backpace_continue(t_term *t, ssize_t row, ssize_t len)
{
	if (!t->c_col)
	{
		t->c_row--;
		t->c_col = t->ws_col - 1;
		set_cursor(t->c_col, (t->start_row + t->c_row));
	}
	else
	{
		t->c_col--;
		run_capability("le");
	}
	if (!len)
	{
		remove_nl_addr(t, row);
		t->total_row--;
		if (((t->start_row + t->c_row) + 1) >= t->ws_row)
			scroll_up(t);
	}
	run_capability("ce");
	shift_nl_addr(t, -1);
	deletion_shift(t, --t->index);
}

void	backspace(t_term *t)
{
	ssize_t	row;
	ssize_t	len;

	if (&t->inp[t->index] == t->nl_addr[t->c_row] && \
		is_prompt_line(t, t->c_row))
		return ;
	row = row_lowest_line(t);
	len = len_lowest_line(t, row);
	backpace_continue(t, row, len);
	if (t->inp[t->index])
		print_trail(t);
}
