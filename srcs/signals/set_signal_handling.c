/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:28:37 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/20 12:58:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	g_signal;

static void	set_signal_int(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		ft_putchar('\n');
		ft_putstr("21sh$ ");
	}
	else if (signal == SIGWINCH)
		;
}

void	set_signal_handling(void)
{
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
}
