/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:53:41 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/17 18:05:09 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	set_new_cur_pos(t_term *t)
{
	while (t->nl_addr[t->c_row] \
	&& &t->inp[t->index] >= t->nl_addr[t->c_row])
		t->c_row++;
	t->c_row--;
	t->c_col = 0;
	if (ft_is_prompt_line(t, t->c_row))
	{
		if (!t->c_row)
			t->c_col = t->prompt_len;
		else
			t->c_col = t->m_prompt_len;
	}
	t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row];
	set_cursor(t->c_col, t->c_row + t->start_row);
}

static void	ft_print_line(t_term *t, ssize_t row)
{
	if (row == t->c_row)
	{
		if (t->nl_addr[row + 1])
			write(1, &t->inp[t->index], \
				(size_t)(t->nl_addr[row + 1] - &t->inp[t->index]));
		else
			write(1, &t->inp[t->index], \
				(size_t)((&t->inp[t->bytes] - &t->inp[t->index]) + 1));
	}
	else
	{
		if (ft_is_prompt_line(t, row))
			print_prompt(row);
		if (t->nl_addr[row + 1])
			write(1, t->nl_addr[row], \
				(size_t)(t->nl_addr[row + 1] - t->nl_addr[row]));
		else
			write(1, t->nl_addr[row], \
				(size_t)((&t->inp[t->bytes] - t->nl_addr[row]) + 1));
	}
}

static void	ft_print_line_trail(t_term *t)
{
	ssize_t	row;
	ssize_t	dis_row;

	row = t->c_row;
	dis_row = get_linenbr();
	while (row <= t->total_row)
	{
		run_capability("ce");
		ft_print_line(t, row++);
		set_cursor(0, ++dis_row);
	}
}

void	ft_print_trail_two(t_term *t)
{
	run_capability("vi");
	run_capability("sc");
	run_capability("vi");
	ft_print_line_trail(t);
	run_capability("rc");
	run_capability("ve");
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
		run_capability("cl");
		ft_reset_nl_addr(t);
		ft_print_input(t, 0, 0);
		set_new_cur_pos(t);
	}
	run_capability("ve");
}
