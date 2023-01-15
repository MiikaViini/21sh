/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_trail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:15:38 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 18:44:40 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	print_line(t_term *t, ssize_t row)
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
		if (is_prompt_line(t, row))
			print_prompt(row);
		if (t->nl_addr[row + 1])
			write(1, t->nl_addr[row], \
				(size_t)(t->nl_addr[row + 1] - t->nl_addr[row]));
		else
			write(1, t->nl_addr[row], \
				(size_t)((&t->inp[t->bytes] - t->nl_addr[row]) + 1));
	}
}

static void	print_line_trail(t_term *t)
{
	ssize_t	row;
	ssize_t	dis_row;

	row = t->c_row;
	dis_row = t->start_row + t->c_row;
	while (row <= t->total_row)
	{
		run_capability("ce");
		print_line(t, row++);
		set_cursor(0, ++dis_row);
	}
}

void	print_trail(t_term *t)
{
	run_capability("vi");
	run_capability("sc");
	print_line_trail(t);
	run_capability("rc");
	run_capability("ve");
}
