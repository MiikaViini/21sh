/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:38:43 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 18:38:11 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * If the cursor is not at the end of the line, move it to the end of the line
 *
 * @param t the term structure
 * @param len the length of the current line
 * @param prompt_len The length of the prompt.
 */

static void	move_down_end_line(t_term *t, ssize_t len, ssize_t prompt_len)
{
	t->c_col = len + prompt_len;
	if (t->c_row < (t->total_row - 1))
	{
		t->c_col--;
		t->index = &t->nl_addr[t->c_row + 2][-1]
			- t->nl_addr[0];
	}
	else
		t->index = (&t->inp[t->bytes] - t->nl_addr[0]);
}

/*
 * It moves the cursor down one line
 *
 * @param t the term structure
 * @param prompt_len the length of the prompt
 */
static void	move_down(t_term *t, ssize_t prompt_len)
{
	if (t->c_col < prompt_len)
	{
		t->c_col = prompt_len;
		t->index = t->nl_addr[t->c_row + 1] - t->nl_addr[0];
	}
	t->index = &t->nl_addr[t->c_row + 1][t->c_col - prompt_len] \
		- t->nl_addr[0];
}

static ssize_t	col_diff(t_term *t, ssize_t len)
{
	int	len_cur_row;

	len_cur_row = &t->inp[t->index] - t->nl_addr[t->c_row];
	if (len_cur_row > len)
		return (len_cur_row - len);
	else
		return (t->c_row);
}

/*
 * It moves the cursor down one line
 *
 * @param t the term structure
 */
void	line_down(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;
	ssize_t	col;

	if (t->c_row < (t->total_row - 1))
		len = (t->nl_addr[t->c_row + 2] - t->nl_addr[t->c_row + 1]);
	else
		len = &t->inp[t->bytes] - t->nl_addr[t->c_row + 1];
	col = col_diff(t, len);
	if (col < t->c_col)
		col = t->c_col - col;
	else
		col = col - t->c_col;
	prompt_len = get_prompt_len(t, t->c_row + 1);
	if (t->c_col < (len + prompt_len))
		move_down(t, prompt_len);
	else
		move_down_end_line(t, len, prompt_len);
	set_cursor(t->c_col, t->start_row + ++t->c_row);
}
