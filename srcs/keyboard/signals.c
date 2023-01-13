/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:19:44 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/13 19:34:14 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_term	*g_t;

/*
 * It's a signal handler that
 * handles the window size change and the interrupt signal
 *
 * @param num The signal number.
 */
static void	sig_handler(int num)
{
	if (num == SIGWINCH)
		get_window_size(g_t);
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		ft_restart_cycle(g_t);
    	ft_add_nl_last_row(g_t, g_t->inp, 0);
		write(1, SHELL_PROMPT, 7);
		g_t->sigint = 1;
	}
}

/*
 * It initializes the signal handlers for the program
 */
void	init_signals(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);
}
