/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:14:16 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/02 15:30:28 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It parses the escape sequence and calls the appropriate function
 *
 * @param t the term structure
 */

void	ft_line_mv(t_term *t)
{
	t->ch = get_input();
	if (t->ch == ';')
	{
		t->ch = get_input();
		if (t->ch == '3')
		{
			t->ch = get_input();
			if (t->ch == ARROW_UP && t->c_row && get_linenbr())
				ft_line_up(t);
			if (t->ch == ARROW_DOWN && t->c_row < t->total_row)
				ft_line_down(t);
			t->ch = 0;
		}
	}
}

/*
 * It moves the cursor to the left
 *
 * @param t the term structure
 *
 * @return the number of lines that the input string
 * 		occupies.
 */
static void	ft_left(t_term *t)
{
	ssize_t	row;

	if (&t->inp[t->index] == t->nl_addr[t->c_row] \
		&& ft_is_prompt_line(t, t->c_row))
		return ;
	row = (ssize_t)get_linenbr();
	if (&t->inp[t->index] == t->nl_addr[t->c_row])
	{
		t->c_col = 0;
		if (t->c_row == 1)
			t->c_col = t->prompt_len;
		else if (ft_is_prompt_line(t, t->c_row - 1))
			t->c_col = t->m_prompt_len;
		t->c_col += t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1];
		row--;
	}
	t->index--;
	set_cursor(--t->c_col, row);
}

static void	ft_right(t_term *t)
{
	ssize_t	row;

	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1] \
		&& ft_is_prompt_line(t, t->c_row + 1))
		return ;
	row = (ssize_t)get_linenbr();
	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1])
	{
		t->c_col = -1;
		t->c_row++;
		row++;
	}
	t->index++;
	set_cursor(++t->c_col, row);
}

void	ft_arrow_input(t_term *t)
{
	if (t->ch == ARROW_RGHT && t->index)
		ft_left(t);
	else if (t->ch == ARROW_LFT && t->index < t->bytes)
		ft_right(t);
	// else if (t->ch == ARROW_UP && (size_t)t->his < t->v_history.len)
	// 	ft_history_trigger(t, ++t->his);
	// else if (t->ch == ARROW_DOWN && t->his > 0)
	// 	ft_history_trigger(t, --t->his);
}

void	ft_alt_mv(t_term *t)
{
	if (t->ch == ALT_LFT || t->ch == ALT_RGHT)
		ft_word_mv(t);
	else if (t->ch == LINE_MV)
		ft_line_mv(t);
}

static void	ft_cursor_beginning(t_term *t)
{
	if (!t->c_row)
	{
		t->c_col = t->prompt_len;
		t->index = 0;
	}
	else
	{
		if (ft_is_prompt_line(t, t->c_row))
			t->c_col = t->m_prompt_len;
		else
			t->c_col = 0;
		t->index = t->nl_addr[t->c_row] - t->nl_addr[0];
	}
	set_cursor(t->c_col, get_linenbr());
}

static void	ft_cursor_end(t_term *t)
{
	ssize_t	len;

	t->c_col = 0;
	len = t->index;
	if (!t->c_row || ft_is_prompt_line(t, t->c_row))
	{
		if (!t->c_row)
			t->c_col = t->prompt_len;
		else
			t->c_col = t->m_prompt_len;
	}
	if (t->nl_addr[t->c_row + 1])
		t->index = (t->nl_addr[t->c_row + 1] - t->nl_addr[0]) - 1;
	else
		t->index = t->bytes;
	len = t->index - len;
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	set_cursor(t->c_col, get_linenbr());
}

static void	shift_arrow(t_term *t)
{
	if (t->ch == ARROW_RGHT && t->bytes)
		ft_cursor_beginning(t);
	if (t->ch == ARROW_LFT)
		ft_cursor_end(t);
}

void	ft_esc_parse(t_term *t)
{
	t->ch = get_input();
	if (t->ch == '[')
	{
		t->ch = get_input();
		if (t->ch >= ARROW_UP && t->ch <= ARROW_RGHT)
			ft_arrow_input(t);
		if (t->ch == LINE_MV)
			ft_alt_mv(t);
		if (t->ch == CURS_BIGIN && t->bytes)
			ft_cursor_beginning(t);
		if (t->ch == CURS_END)
			ft_cursor_end(t);
		if (t->ch == KEY_SHIFT)
		{
			t->ch = get_input();
			shift_arrow(t);
		}
	}
	if (t->ch == ALT_LFT || t->ch == ALT_RGHT)
		ft_alt_mv(t);
	t->ch = 0;
}
