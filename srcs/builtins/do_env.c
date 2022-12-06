/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/18 09:47:02 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	try_execute(char **input, int *i, t_env *temp, t_env *env, int fd)
{
	char	*exec;

	exec = input[*i];
	input[*i] = NULL;
	if (!do_setenv(input, temp, fd))
		;
	else
	{
		input[*i] = exec;
		return ;
	}
	input[*i] = exec;
	check_command(&input[*i], env->path, temp->env, 0);
}

static void	exec_w_env(char **input, t_env *env, int i, int k, int fd)
{
	t_env	temp;

	temp.env = ft_strarrndup(temp.env, env->env, ft_linecount(input));
	update_env(temp.env, input[0], "_");
	if (input[i])
		try_execute(input, &i, &temp, env, fd);
	else
	{
		if (do_setenv(input, &temp, fd))
			;
		else
			while (temp.env[++k])
				ft_putendl_fd(temp.env[k], fd);
	}
	free_strarr(temp.env);
}

int	do_env(char **input, t_env *env, int fd)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	if (!input[1])
		while (env->env[++k])
			ft_putendl_fd(env->env[k], fd);
	else
	{
		while (input[++i])
			if (check_equalsign(input[i]))
				break ;
		k = -1;
		exec_w_env(input, env, i, k, fd);
	}
	update_env(env->env, input[ft_linecount(input) - 1], "_");
	return (0);
}
