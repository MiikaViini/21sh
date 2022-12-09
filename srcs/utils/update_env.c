/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:35:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/09 09:33:39 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void update_env(char **env, char *input, char *var)
{
	int i;
	char *temp;
	int len;

	i = -1;
	len = ft_strlen(var);
	if (!var)
		return;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
		{
			temp = ft_strndup(env[i], len + 1);
			ft_strdel(&env[i]);
			env[i] = ft_strjoin(temp, input);
			ft_strdel(&temp);
			return ;
		}
	}
	temp = ft_strjoin(var, "=");
	env[i] = ft_strjoin(temp, input);
	ft_strdel(&temp);
}

