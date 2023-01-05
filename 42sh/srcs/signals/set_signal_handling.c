/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:28:37 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/03 13:57:02 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int g_signal;

void	set_signal_int(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal;
		ft_putchar('\n');
		ft_putstr("42sh$ ");
		
	}
	
}

void	set_signal_handling(void)
{
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
}
