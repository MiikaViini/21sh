/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:12:47 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/14 19:49:27 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// is pos even needed, for now always set to 0
// check values this is called with

void	ft_remove_nl_addr(t_term *t, ssize_t row)
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
	ft_memdel((void **)&t->nl_addr); //free_array
	t->nl_addr = new_array;
}

void	ft_shift_nl_addr(t_term *t, int num)
{
	int	row;

	row = t->c_row + 1;
	while (t->nl_addr[row] && !ft_is_prompt_line(t, row))
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
		if (ft_is_prompt_line(t, row))
			t->nl_addr[row] = &t->nl_addr[row][-1];
		row++;
	}
}

void	ft_reset_nl_addr(t_term *t)
{
	ssize_t	i;
	ssize_t	len;

	i = 0;
	len = 0;
	t->total_row = 0;
	if (t->nl_addr)
		ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, i);
	while (t->inp[++i])
	{
		len++;
		if (((len + ft_get_prompt_len(t, t->total_row)) + 1) == \
			(t->ws_col) || t->inp[i] == '\n')
		{
			ft_add_nl_last_row(t, i + 1);
			t->total_row++;
			len = -1;
		}
		if (t->inp[i] == D_QUO || t->inp[i] == S_QUO)
			ft_quote_handling(t, t->inp[i]);
	}
}

void	trigger_nl(t_term *t)
{
	ssize_t	len;
	ssize_t	row;

	row = ft_row_lowest_line(t);
	len = ft_len_lowest_line(t, row);
	if (len == t->ws_col)
	{
		t->total_row++;
		if (t->start_row + t->total_row >= t->ws_row)
			ft_scroll_down();
		ft_add_nl_last_row(t, t->bytes);
	}
	if (len == t->ws_col + 1)
		if (t->nl_addr[row + 1])
			ft_add_nl_mid_row(t, row + 1, (ssize_t)(&t->nl_addr[row + 1][-1] \
			- t->nl_addr[0]));
	if (t->c_col == t->ws_col)
	{
		t->c_row++;
		t->c_col = 0;
		set_cursor(t->c_col, get_linenbr() + 1);
	}
}
