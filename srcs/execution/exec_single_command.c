/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:03:33 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/09 09:32:29 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int exec_single_command(t_ast *tree, int rb, char **builtins, t_env *env)
{
	int fd = 1;

	if ((rb && !tree) || (!rb && !tree))
		return 1;
	env->path = get_path(env->env);
	expand_and_remove_quotes(&tree, env);
	if (rb && tree->type == NODE_CMD)
	{
		update_env(env->env, tree->cmd[ft_linecount(tree->cmd) - 1], "_");
	}
	if (rb == 0)
	{
		ft_putstr("exit\n");
		return 0;
	}
	if (tree->type == NODE_REDIR)
	{
		if (redirection(tree->redirs) == -1)
		{
			free_strarr(env->path);
			return 1;
		}	
	}
	if (check_builtins(tree->cmd, builtins, env, fd))
		;
	else
		check_command(tree->cmd, env->path, env->env, 0);
	free_strarr(env->path);
	return 1;
}
