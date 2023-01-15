/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:12:47 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 17:09:51 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	remove_nl_addr(t_term *t, ssize_t row)
{
	ssize_t	i;
	ssize_t	j;
	char	**new_array;

	i = -1;
	j = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) \
		* (size_t)(t->total_row + 1));
	while (t->nl_addr[++i])
	{
		if (i != row)
			new_array[++j] = t->nl_addr[i];
	}
	new_array[++j] = NULL;
	ft_memdel((void **)&t->nl_addr);
	t->nl_addr = new_array;
}

void	shift_nl_addr(t_term *t, int num)
{
	ssize_t	row;

	row = t->c_row + 1;
	while (t->nl_addr[row] && !is_prompt_line(t, row))
		row++;
	while (t->nl_addr[row++])
		t->nl_addr[row - 1] = &t->nl_addr[row - 1][num];
}

void	update_nl_addr_del(t_term *t)
{
	ssize_t	row;

	row = t->c_row + 1;
	while (t->nl_addr[row])
	{
		if (is_prompt_line(t, row))
			t->nl_addr[row] = &t->nl_addr[row][-1];
		row++;
	}
}

void	reset_nl_addr(t_term *t)
{
	ssize_t	i;
	ssize_t	len;

	i = -1;
	len = 0;
	t->total_row = 0;
	if (t->nl_addr)
		ft_memdel((void **)&t->nl_addr);
	add_nl_last_row(t, t->inp, 0);
	while (t->inp[++i])
	{
		len++;
		if (((len + get_prompt_len(t, t->total_row))) == t->ws_col \
			|| t->inp[i] == '\n')
		{
			t->total_row++;
			add_nl_last_row(t, t->inp, i + 1);
			len = 0;
		}
	}
	quote_flag_reset(t);
}

void	trigger_nl(t_term *t)
{
	ssize_t	len;
	ssize_t	row;

	row = row_lowest_line(t);
	len = len_lowest_line(t, row);
	if (len == t->ws_col)
	{
		t->total_row++;
		if ((t->start_row + t->total_row) >= t->ws_row)
		{
			t->start_row--;
			scroll_down();
		}
		if (t->nl_addr[t->c_row + 1])
			reset_nl_addr(t);
		else
			add_nl_last_row(t, t->inp, t->bytes);
	}
	if (t->c_col == t->ws_col)
	{
		t->c_col = 0;
		t->c_row++;
	}
}
