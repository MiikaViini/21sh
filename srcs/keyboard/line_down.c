/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:38:43 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/01 23:39:34 by spuustin         ###   ########.fr       */
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

ssize_t	ft_mv_prompt_lend(t_term *t, int num)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (t->c_row == 1 && (num < 0))
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, t->c_row + num))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
}

static void	ft_move_down_end_line(t_term *t, ssize_t len, ssize_t prompt_len)
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
static void	ft_move_down(t_term *t, ssize_t prompt_len)
{
	if (t->c_col < prompt_len)
	{
		t->c_col = prompt_len;
		t->index = t->nl_addr[t->c_row + 1] - t->nl_addr[0];
	}
	t->index = &t->nl_addr[t->c_row + 1][t->c_col - prompt_len] \
		- t->nl_addr[0];
}

/*
 * It moves the cursor down one line
 *
 * @param t the term structure
 */
void	ft_line_down(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;

	prompt_len = ft_mv_prompt_lend(t, 1);
	if (t->c_row < (t->total_row - 1))
		len = (t->nl_addr[t->c_row + 2] - t->nl_addr[t->c_row + 1]);
	else
		len = &t->inp[t->bytes] - t->nl_addr[t->c_row + 1];
	if (t->c_col < (len + prompt_len))
		ft_move_down(t, prompt_len);
	else
		ft_move_down_end_line(t, len, prompt_len);
	t->c_row++;
	set_cursor(t->c_col, (get_linenbr() + 1));
}
