/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:00:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/15 20:34:51 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int do_echo(char **input, t_env *env)
{
	int i;

	i = 1;
	(void)env;
	if (!input[i])
		write(1, "\n", 1);
	else
	{
		while (input[i])
		{
			ft_putstr(input[i++]);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (0);
}
