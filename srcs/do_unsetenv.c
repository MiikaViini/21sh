/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:30:06 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/20 09:04:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void delete_var(t_env *env, int *k)
{
	ft_strdel(&env->env[*k]);
	env->env[*k] = env->env[*k + 1];
	while (env->env[*k + 1])
	{
		env->env[*k] = env->env[*k + 1];
		*k += 1;
	}
	env->env[*k] = NULL;
}

int do_unsetenv(char **input, t_env *env)
{
	int i;
	int k;
	int len;

	i = 0;
	len = 0;
	while (input[++i])
	{
		k = -1;
		while (env->env[++k])
		{
			len = (int)ft_strlen(input[i]);
			if (ft_strnequ(env->env[k], input[i], len) && env->env[k][len] == '=')
			{
				delete_var(env, &k);
			}
		}
	}
	return (0);
}
