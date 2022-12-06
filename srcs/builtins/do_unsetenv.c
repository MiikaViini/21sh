/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:30:06 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/06 13:00:25 by mviinika         ###   ########.fr       */
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

int do_unsetenv(char **input, t_env *env, int fd)
{
	int i;
	int k;
	int len;

	i = 0;
	len = 0;
	(void)fd;
	while (input[++i])
	{
		k = -1;
		while (env->env[++k])
		{
			len = (int)ft_strlen(input[i]);
			if (ft_strnequ(env->env[k], input[i], len) && env->env[k][len] == '=')
				delete_var(env, &k);
		}
	}
	return (0);
}
