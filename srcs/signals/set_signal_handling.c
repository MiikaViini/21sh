/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:28:37 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/04 13:23:36 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_myputchar(int c)
{
	write(1, &c, 1);
	return (c);
}

void	set_signal_int(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		ft_putstr("21sh$ ");
	}
}

void	set_signal_handling(void)
{
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
}
