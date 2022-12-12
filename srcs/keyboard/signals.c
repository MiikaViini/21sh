/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:19:44 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/01 21:37:20 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_term *g_t;


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
	}
}

/*
 * It initializes the signal handlers for the program
 */
void	init_signals()
{
	signal(SIGWINCH, sig_handler);
	signal(SIGINT, sig_handler);
}
