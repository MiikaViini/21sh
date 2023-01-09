/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:30:06 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/09 20:59:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	delete_var(char **env, int *k)
{
	ft_strdel(&env[*k]);
	env[*k] = env[*k + 1];
	while (env[*k + 1])
	{
		env[*k] = env[*k + 1];
		*k += 1;
	}
	env[*k] = NULL;
}

int	do_unset(char **input, t_env *env)
{
	int		i;
	int		k;
	int		len;

	i = 0;
	len = 0;
	while (input[++i])
	{
		k = -1;
		while (env->env[++k])
		{
			len = (int)ft_strlen(input[i]);
			if (ft_strnequ(env->env[k], input[i], len)
				&& env->env[k][len] == '=')
				delete_var(env->env, &k);
		}
		k = -1;
		while (env->intr->env[++k])
		{
			len = (int)ft_strlen(input[i]);
			if (ft_strnequ(env->intr->env[k], input[i], len)
				&& env->intr->env[k][len] == '=')
				delete_var(env->intr->env, &k);
		}
	}
	return (0);
}
