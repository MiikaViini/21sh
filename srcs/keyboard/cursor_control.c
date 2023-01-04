/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:44:38 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/04 17:11:58 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_left(t_term *t)
{
	if (&t->inp[t->index] == t->nl_addr[t->c_row] \
		&& ft_is_prompt_line(t, t->c_row))
		return ;
	if (&t->inp[t->index] == t->nl_addr[t->c_row])
	{
		t->c_col = 0;
		if (t->c_row == 1)
			t->c_col = t->prompt_len;
		else if (ft_is_prompt_line(t, t->c_row - 1))
			t->c_col = t->m_prompt_len;
		t->c_col += t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1];
		set_cursor(--t->c_col, t->start_row + --t->c_row);
	}
	else
	{
		t->c_col--;
		run_capability("le");
	}
	t->index--;
}

void	ft_right(t_term *t)
{
	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1] \
		&& ft_is_prompt_line(t, t->c_row + 1))
		return ;
	if (&t->inp[t->index] == &t->nl_addr[t->c_row + 1][-1])
	{
		t->c_col = -1;
		set_cursor(++t->c_col, t->start_row + ++t->c_row);
	}
	else
	{
		t->c_col++;
		run_capability("nd");
	}
	t->index++;
}

void	ft_cursor_beginning(t_term *t)
{
	t->c_col = ft_get_prompt_len(t, t->c_row);
	if (!t->c_row)
		t->index = 0;
	else
		t->index = t->nl_addr[t->c_row] - t->nl_addr[0];
	set_cursor(t->c_col, t->start_row + t->c_row);
}

void	ft_cursor_end(t_term *t)
{
	ssize_t	len;

	len = t->index;
	t->c_col = ft_get_prompt_len(t, t->c_row);
	if (t->nl_addr[t->c_row + 1])
		t->index = (t->nl_addr[t->c_row + 1] - t->nl_addr[0]) - 1;
	else
		t->index = t->bytes;
	len = t->index - len;
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	set_cursor(t->c_col, t->start_row + t->c_row);
}
