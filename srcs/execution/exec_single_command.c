/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:03:33 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/14 21:06:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int check_redirs(t_ast *tree, t_env *env)
{
	int ret;
	
	ret = 0;
	if (tree->type == NODE_REDIR)
	{
		if (redirection(tree->redirs, &ret) == -1)
		{
			free_strarr(env->path);
			return 1;
		}	
	}
	return 0;
}

int exec_single_command(t_ast *tree, int rb, char **builtins, t_env *env)
{
	if ((rb && !tree) || (!rb && !tree))
		return 1;
	env->path = get_path(env->env);
	expand_and_remove_quotes(&tree, env);
	if (rb && tree->type == NODE_CMD)
		update_env(env->env, tree->cmd[ft_linecount(tree->cmd) - 1], "_");
	if (rb == 0)
	{
		ft_putstr("exit\n");
		return 0;
	}
	if (check_redirs(tree, env) == 1)
		return 1;
	if (check_builtins(tree->cmd, builtins, env, 1))
		;
	else
		check_command(tree->cmd, env->path, env->env, 0);
	free_strarr(env->path);
	return 1;
}
