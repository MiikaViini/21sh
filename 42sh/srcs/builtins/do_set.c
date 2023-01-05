/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:34:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/05 11:52:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	do_set(char **input, t_env *env)
{
	int	k;	

	k = -1;
	if (!input[1])
		while (env->env[++k])
			ft_putendl(env->env[k]);
	k = -1;
	if (!input[1])
		while (env->intr->env[++k])
			ft_putendl(env->intr->env[k]);
	return (1);
}
