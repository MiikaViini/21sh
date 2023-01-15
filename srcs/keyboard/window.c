/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:53:41 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 16:53:16 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	set_new_cur_pos(t_term *t)
{
	t->c_row = 0;
	while (t->nl_addr[t->c_row] \
		&& &t->inp[t->index] >= t->nl_addr[t->c_row])
		t->c_row++;
	t->c_row--;
	t->c_col = get_prompt_len(t, t->c_row);
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
		reset_nl_addr(t);
		print_input(t, 0, 0);
		set_new_cur_pos(t);
	}
	run_capability("ve");
}
