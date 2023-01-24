/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:59:22 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/24 20:31:19 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	set_signal_fork(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
	}
	signal = 0;
}

int	fork_wrapper(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_print(NULL, NULL, E_NOFORK);
	if (pid)
		signal(SIGINT, set_signal_fork);
	return (pid);
}
