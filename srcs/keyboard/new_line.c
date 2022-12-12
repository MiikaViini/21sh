/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:23:16 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/09 23:29:48 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_add_nl_last_row(t_term *t, ssize_t pos)
{
	int		index;
	char	**n_arr;

	index = -1;
	n_arr = NULL;
	if (!t->nl_addr)
	{
		t->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		t->nl_addr[++index] = &t->inp[pos];
		t->nl_addr[++index] = NULL;
	}
	else
	{
		n_arr = (char **)ft_memalloc(sizeof(char *) \
			* (size_t)(t->total_row + 2));
		while (t->nl_addr[++index])
			n_arr[index] = t->nl_addr[index];
		n_arr[index++] = &t->inp[pos];
		n_arr[index] = NULL;
		ft_memdel((void **)&t->nl_addr);
		t->nl_addr = n_arr;
	}
}

ssize_t	ft_get_prompt_len(t_term *t, ssize_t row)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (!row)
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, row))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
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

ssize_t	ft_row_lowest_line(t_term *t)
{
	ssize_t	row;

	row = t->c_row;
	while (t->nl_addr[row + 1] && !ft_is_prompt_line(t, row + 1))
		row++;
	return (row);
}

ssize_t	ft_len_lowest_line(t_term *t, ssize_t row)
{
	ssize_t	len;

	if (t->nl_addr[row + 1])
		len = t->nl_addr[row + 1] - t->nl_addr[row];
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	if (ft_is_prompt_line(t, row))
	{
		if (!row)
			len += t->prompt_len;
		else
			len += t->m_prompt_len;
	}
	return (len);
}

void	ft_add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos)
{
	ssize_t	i;
	ssize_t	j;
	char	**new_arr;

	j = 0;
	i = -1;
	new_arr = (char **)ft_memalloc(sizeof(char *) * (size_t)(t->total_row + 2));
	while (++i <= t->total_row)
	{
		if (i == row)
			new_arr[i] = &t->inp[pos];
		else
			new_arr[i] = t->nl_addr[j++];
	}
	new_arr[i] = NULL;
	ft_memdel((void **)&t->nl_addr);
	t->nl_addr = new_arr;
}



void	ft_scroll_down(void)
{
	run_capability("sc");
	run_capability("sf");
	run_capability("rc");
	run_capability("up");
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
			ft_add_nl_mid_row(t, row + 1, (ssize_t)(&t->nl_addr[row + 1][-1] - t->nl_addr[0]));
	if (t->c_col == t->ws_col)
	{
		t->c_row++;
		t->c_col = 0;
		set_cursor(t->c_col, get_linenbr() + 1);
	}
}

void	add_new_line(t_term *t, int pos)
{
	int		index;
	char	**n_arr;

	index = -1;
	n_arr = NULL;
	if (!t->nl_addr)
	{
		t->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		t->nl_addr[++index] = &t->inp[pos];
		t->nl_addr[++index] = NULL;
	}
	else
	{
		n_arr = (char **)ft_memalloc(sizeof(char *) \
			* (size_t)(t->total_row + 2));
		while (t->nl_addr[++index])
			n_arr[index] = t->nl_addr[index];
		n_arr[index++] = &t->inp[pos];
		n_arr[index] = NULL;
		ft_memdel((void **)&t->nl_addr); //free_array()
		t->nl_addr = n_arr;
	}
}
