/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:44:38 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/14 18:52:26 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_left(t_term *t)
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

void	ft_right(t_term *t)
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

void	ft_cursor_beginning(t_term *t)
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

void	ft_cursor_end(t_term *t)
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
