/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:36:28 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/01 23:41:28 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//melko varmasti duplikaatti
ssize_t	ft_mv_prompt_lens(t_term *t, int num)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (t->c_row == 1 && (num < 0))
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, t->c_row + num))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
}

/*
 * It moves the cursor up to the end of the line
 *
 * @param t the term structure
 * @param len the length of the line
 * @param prompt_len The length of the prompt.
 */
static void	ft_move_up_end_line(t_term *t, ssize_t len, ssize_t prompt_len)
{
	t->c_col = (len + prompt_len) - 1;
	t->index = (t->nl_addr[t->c_row] - t->nl_addr[0]) - 1;
}

/*
 * If the cursor is on the first line, move it to the beginning of the line.
 * Otherwise, move it to the beginning of the previous line.
 *
 * @param t the term structure
 * @param prompt_len the length of the prompt
 */
static void	ft_move_up(t_term *t, ssize_t prompt_len)
{
	if (t->c_col < prompt_len)
	{
		t->c_col = prompt_len;
		if (t->c_row == 1)
			t->index = 0;
		else
			t->index = t->nl_addr[t->c_row - 1] - t->nl_addr[0];
	}
	else
		t->index = (&t->nl_addr[t->c_row - 1]
			[t->c_col - prompt_len] - t->nl_addr[0]);
}

/*
 * It moves the cursor up one line
 *
 * @param t the term structure
 */
void	ft_line_up(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;

	len = t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1];
	prompt_len = ft_mv_prompt_lens(t, -1);
	if (t->c_col < (len + prompt_len))
		ft_move_up(t, prompt_len);
	else
		ft_move_up_end_line(t, len, prompt_len);
	t->c_row--;
	set_cursor(t->c_col, (get_linenbr() - 1));
}
