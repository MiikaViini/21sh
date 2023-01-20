/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:19:44 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/20 10:17:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_term	*g_t;

static void	sig_handler(int num)
{
	if (num == SIGWINCH)
		get_window_size(g_t);
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		restart_cycle(g_t);
		add_nl_last_row(g_t, g_t->inp, 0);
		write(1, SHELL_PROMPT, 7);
		g_t->sigint = 1;
	}
}

void	init_signals(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);
}
