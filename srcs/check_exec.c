/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/09 13:48:59 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = -1;
	path = (char **)ft_memalloc(sizeof(char *));
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0 && env[i][5])
		{
			free(path);
			path = ft_strsplit(env[i] + 5, ':');
		}
	}
	return (path);
}

static int	check_builtins(char **input, char **builtins, t_env *env)
{
	int k;

	k = -1;
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

int	check_exec(t_ast *tree, int rb, char **builtins, t_env *env)
{
	if ((rb && !tree) || (rb && !tree))
		return (1);
	env->path = get_path(env->env);
	// if (rb)
	// 	update_env(env->env, tree->parsed[ft_linecount(parsed->parsed) - 1], "_");
	if (rb == 0 || (parsed->parsed[0] && !ft_strcmp(parsed->parsed[0], "exit")))
	{
		ft_putstr("exit\n");
		return (EXIT_SUCCESS);
	}
	else if (check_builtins(parsed->parsed, builtins, env))
		;
	else if (check_command(parsed->parsed, env->path, env->env))
		;
	else
		error_print(parsed->parsed[0], NULL, E_NOTF);
	free_strarr(env->path);
	return (1);
}
