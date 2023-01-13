/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:53:41 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/13 19:24:47 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	set_new_cur_pos(t_term *t)
{
// 	while (t->nl_addr[t->c_row] \
// 	&& &t->inp[t->index] >= t->nl_addr[t->c_row])
// 		t->c_row++;
// 	t->c_row--;
// 	t->c_col = 0;
// 	if (ft_is_prompt_line(t, t->c_row))
// 	{
// 		if (!t->c_row)
// 			t->c_col = t->prompt_len;
// 		else
// 			t->c_col = t->m_prompt_len;
// 	}
// 	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
// 	set_cursor(t->c_col, t->c_row + t->start_row);
	t->c_row = 0;
	while (t->nl_addr[t->c_row] \
		&& &t->inp[t->index] >= t->nl_addr[t->c_row])
		t->c_row++;
	t->c_row--;
	t->c_col = ft_get_prompt_len(t, t->c_row);
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	set_cursor(t->c_col, t->c_row);
}

void	get_window_size(t_term *t)
{
	struct winsize	window;

	run_capability("vi");
	if (ioctl(0, TIOCGWINSZ, (char *)&window) < 0)
		perror("TIOCGWINSZ");
	t->ws_col = window.ws_col;
	t->ws_row = window.ws_row;
	if (*t->inp)
	{
		t->start_row = 0;
		run_capability("cl");
		ft_reset_nl_addr(t);
		ft_print_input(t, 0, 0);
		set_new_cur_pos(t);
	}
	run_capability("ve");
}
