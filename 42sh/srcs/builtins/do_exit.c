/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:08:24 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/22 11:59:26 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_exit_code(char *exit_status)
{
	int	i;

	i = 0;
	while (exit_status[i])
	{
		if (!ft_isdigit(exit_status[i]))
			return (0);
		i++;
	}
	return (1);
}

int	do_exit(char **input, t_env *env)
{
	int	exit_status;

	exit_status = 0;
	ft_putendl("exit");
	if (input && input[1])
	{
		if (check_exit_code(input[1]))
			exit_status = ft_atoi(input[1]);
		else
		{
			error_print(input[1], input[0], E_NODIGIT);
			exit_status = 2;
		}
	}
	if (input)
	{
		free_strarr(input);
		free_strarr(env->env);
		free_strarr(env->path);
		free_strarr(env->intr->env);
		free(env->intr);
	}
	exit(exit_status);
}
