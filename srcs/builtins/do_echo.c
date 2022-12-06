/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:00:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/18 10:08:40 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int do_echo(char **input, t_env *env, int fd)
{
	int i;

	i = 1;
	(void)env;
	if (!input[i])
		write(fd, "\n", 1);
	else
	{
		while (input[i])
		{
			ft_putstr_fd(input[i++], fd);
			write(fd, " ", 1);
		}
		write(fd, "\n", 1);
	}
	return (0);
}
