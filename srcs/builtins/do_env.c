/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/26 09:39:39 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	try_execute(char **input, int *i, t_env *temp, t_env *env)
{
	char	*exec;

	exec = input[*i];
	input[*i] = NULL;
	if (!do_setenv(input, temp))
		;
	else
	{
		input[*i] = exec;
		return ;
	}
	input[*i] = exec;
	check_command(&input[*i], env->path, temp->env, 0);
}

static void	exec_w_env(char **input, t_env *env, int i, int k)
{
	t_env	temp;

	temp.env = ft_strarrndup(temp.env, env->env, ft_linecount(input));
	update_env(temp.env, input[0], "_");
	if (input[i])
		try_execute(input, &i, &temp, env);
	else
	{
		if (do_setenv(input, &temp))
			;
		else
			while (temp.env[++k])
				ft_putendl(temp.env[k]);
	}
	free_strarr(temp.env);
}

int	do_env(char **input, t_env *env)
{
	int			i;
	int			k;
	struct stat	buf;

	i = 0;
	k = -1;
	if (fstat(STDOUT_FILENO, &buf) == -1)
	{
		error_print("write error", input[0], E_BFD);
		return (-1);
	}
	if (!input[1])
		while (env->env[++k])
			ft_putendl(env->env[k]);
	else
	{
		while (input[++i])
			if (check_equalsign(input[i]))
				break ;
		k = -1;
		exec_w_env(input, env, i, k);
	}
	update_env(env->env, input[ft_linecount(input) - 1], "_");
	return (0);
}
