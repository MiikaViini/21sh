/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:23:16 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/17 18:11:15 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_add_nl_last_row(t_term *t, char *array, ssize_t pos)
{
	int		index;
	char	**n_arr;

	index = -1;
	n_arr = NULL;
	if (!t->nl_addr)
	{
		t->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		t->nl_addr[++index] = array + pos;
		t->nl_addr[++index] = NULL;
	}
	else
	{
		n_arr = (char **)ft_memalloc(sizeof(char *) \
			* (size_t)(t->total_row + 2));
		while (t->nl_addr[++index])
			n_arr[index] = t->nl_addr[index];
		n_arr[index++] = array + pos;
		n_arr[index] = NULL;
		ft_memdel((void **)&t->nl_addr);
		t->nl_addr = n_arr;
	}
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
