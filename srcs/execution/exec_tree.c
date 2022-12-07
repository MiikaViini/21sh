/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:09:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/07 12:42:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	pipe_executor(t_ast *tree, int rb, char **builtins, t_env *env)
{
	int fd[2];
	if (pipe(fd) < 0)
			error_print(NULL, NULL, E_PIPEFAIL);
	if ((fork1()) == 0)
	{
		
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		exec_tree(tree->left, rb, builtins, env);
	}
	if ((fork1()) == 0)
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		exec_tree(tree->right, rb, builtins, env);
	}
	close(fd[0]);
	close(fd[1]);
	wait(0);
	wait(0);
}

static void exec_cmd(t_ast *tree, char **builtins, t_env *env)
{
	env->path = get_path(env->env);
	if (check_builtins(tree->cmd, builtins, env, 1))
		;
	else
		check_command(tree->cmd, env->path, env->env, 1);
	free_strarr(env->path);
}
// Executes syntax tree node by node from left to right
// trees root is always PIPE. Depending of TOKEN, it executes necessary
// actions with that node. When PIPE is found, recursively executes tree.
// Does proper piping in child processes and waits them to finish. in the
// end closes pipes and exits child process.

int	exec_tree(t_ast *tree, int rb, char **builtins, t_env *env)
{
	if ((!tree) || (!rb && !tree))
		return 1;
	expand_and_remove_quotes(&tree, env);
	if (rb && tree->type == NODE_CMD)
		update_env(env->env, tree->cmd[ft_linecount(tree->cmd) - 1], "_");
	if (rb == 0)
	{
		free_strarr(env->path);
		ft_putstr("exit\n");
		return 0;
	}
	if (tree->type == NODE_CMD)
		exec_cmd(tree, builtins, env);
	else if (tree->type == NODE_REDIR)
	{
		if (redirection(tree->redirs) == -1)
		{
			free_strarr(env->path);
			return 1;
		}
		exec_cmd(tree, builtins, env);
	}
	else if (tree->type == NODE_PIPE)
		pipe_executor(tree, rb, builtins, env);
	exit (1);
}