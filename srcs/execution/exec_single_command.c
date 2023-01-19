/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:03:33 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/19 14:04:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	exec_single_command(t_ast *tree, char **builtins, t_env *env)
{
	if (!tree)
		return (1);
	env->path = get_path(env->env);
	if (expand_and_remove_quotes(&tree, env))
	{
		free_strarr(env->path);
		return (1);
	}
	if (tree->type == NODE_CMD)
		update_env(env->env, tree->cmd[ft_linecount(tree->cmd) - 1], "_");
	if (check_redirs(tree, env) == 1)
		return (1);
	if (check_builtins(tree->cmd, builtins, env))
		;
	else
		check_command(tree->cmd, env->path, env->env, 0);
	free_strarr(env->path);
	return (1);
}
