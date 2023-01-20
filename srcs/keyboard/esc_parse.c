/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:14:16 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/20 12:51:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It parses the escape sequence and calls the appropriate function
 *
 * @param t the term structure
 */

static void	arrow_input(t_term *t)
{
	if (t->ch == ARROW_RGHT && t->index)
		move_cursor_left(t);
	else if (t->ch == ARROW_LFT && t->index < t->bytes)
		move_cursor_right(t);
	else if (t->ch == ARROW_UP && (size_t)t->his < (size_t)t->history_size)
		history_trigger(t, ++t->his);
	else if (t->ch == ARROW_DOWN && t->his > 0)
		history_trigger(t, --t->his);
}

static void	alt_mv(t_term *t)
{
	if (t->ch == ALT_LFT || t->ch == ALT_RGHT)
		word_mv(t);
	else if (t->ch == LINE_MV)
		line_mv(t);
}

static void	shift_arrow(t_term *t)
{
	if (t->ch == ARROW_RGHT && t->bytes)
		cursor_beginning(t);
	if (t->ch == ARROW_LFT)
		cursor_end(t);
}

void	esc_parse(t_term *t)
{
	t->ch = get_input();
	if (t->ch == '[')
	{
		t->ch = get_input();
		if (t->ch >= ARROW_UP && t->ch <= ARROW_RGHT)
			arrow_input(t);
		if (t->ch == LINE_MV)
			alt_mv(t);
		if (t->ch == CURS_BIGIN && t->bytes)
			cursor_beginning(t);
		if (t->ch == CURS_END)
			cursor_end(t);
		if (t->ch == KEY_SHIFT)
		{
			t->ch = get_input();
			shift_arrow(t);
		}
	}
	if (t->ch == ALT_LFT || t->ch == ALT_RGHT)
		alt_mv(t);
	t->ch = 0;
}
