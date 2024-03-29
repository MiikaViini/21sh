/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:29:47 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 17:10:13 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	history_cpy(t_term *t, char *dst, char *src)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(t->inp);
	while (src[++i] && (len + i) < (BUFF_SIZE - 1))
		dst[i] = src[i];
}

static void	history_inp_update(t_term *t, char *history)
{
	ft_strclr(t->nl_addr[t->c_row]);
	if (history)
		history_cpy(t, t->nl_addr[t->c_row], history);
	else if (t->input_cpy)
		history_cpy(t, t->nl_addr[t->c_row], t->input_cpy);
}

static void	history_clear_line(t_term *t, ssize_t row)
{
	set_cursor(0, (t->start_row + t->history_row));
	while (row > t->history_row)
	{
		remove_nl_addr(t, row);
		t->total_row--;
		row--;
	}
	run_capability("cd");
}

static void	history_push(t_term *t)
{
	if (t->history_row == -1)
	{
		t->input_cpy = ft_strsub(t->nl_addr[t->c_row], 0, \
		ft_strlen(t->nl_addr[t->c_row]));
		if (*t->history_buff)
		{
			nl_removal(t);
			add_command_to_history(t, t->history_buff);
			ft_memset((void *)t->history_buff, '\0', \
			ft_strlen(t->history_buff));
		}
		t->history_row = t->c_row;
	}
	t->c_row = t->history_row;
}

void	history_trigger(t_term *t, ssize_t pos)
{
	ssize_t	row;
	char	*history;

	history = NULL;
	if (t->c_row != t->total_row)
		return ;
	row = t->c_row;
	history_push(t);
	run_capability("vi");
	if (t->history[t->history_size - pos])
		history = t->history[t->history_size - (size_t)pos];
	history_clear_line(t, row);
	history_inp_update(t, history);
	history_reset_nl(t, t->nl_addr[t->history_row]);
	quote_flag_reset(t);
	if (t->start_row + t->total_row >= t->ws_row)
		t->start_row = t->ws_row - (t->total_row + 1);
	print_input(t, t->c_row, 1);
	if (!history)
	{
		ft_strdel(&t->input_cpy);
		t->history_row = -1;
	}
	run_capability("ve");
}
