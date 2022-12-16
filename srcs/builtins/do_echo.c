/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:00:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 12:15:07 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	do_echo(char **input, t_env *env)
{
	int			i;
	struct stat	buf;

	i = 1;
	(void)env;
	if (fstat(STDOUT_FILENO, &buf) == -1)
	{
		error_print("write error", input[0], E_BFD);
		return (-1);
	}
	while (input[i])
	{
		ft_putstr(input[i++]);
		if (input[i])
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
