/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:11:50 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/04 15:20:29 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	check_builtins(char **input, char **builtins, t_env *env)
{
	int		k;

	k = -1;
	if (*input == NULL)
		return (-1);
	if (ft_strequ(input[0], "history") == 1)
		return (1);
	while (builtins[++k])
	{
		if (ft_strequ(builtins[k], input[0]))
		{
			g_builtins[k](input, env);
			return (1);
		}
	}
	return (0);
}
