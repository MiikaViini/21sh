/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:20:25 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/14 16:03:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	set_signal_fork(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
	}
	signal = 0;
}
