/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:09:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/20 10:09:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	pipe_executor(t_ast *tree, char **builtins, t_env *env)
{
	int	fd[2];

	if (pipe(fd) < 0)
		error_print(NULL, NULL, E_PIPEFAIL);
	if (fork() == 0)
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		exec_tree(tree->left, builtins, env);
	}
	if (fork() == 0)
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		exec_tree(tree->right, builtins, env);
	}
	close(fd[0]);
	close(fd[1]);
	wait(0);
	wait(0);
}

static void	exec_cmd(t_ast *tree, char **builtins, t_env *env)
{
	env->path = get_path(env->env);
	if (check_builtins(tree->cmd, builtins, env))
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
void	exec_tree(t_ast *tree, char **builtins, t_env *env)
{
	if (tree == NULL)
		return ;
	expand_and_remove_quotes(&tree, env);
	if (tree->type == NODE_CMD)
		update_env(env->env, tree->cmd[ft_linecount(tree->cmd) - 1], "_");
	if (tree->type == NODE_REDIR || tree->type == NODE_CMD)
	{
		if (tree->type == NODE_REDIR && check_redirs(tree, env) == 1)
			return ;
		exec_cmd(tree, builtins, env);
	}
	else if (tree->type == NODE_PIPE)
		pipe_executor(tree, builtins, env);
	exit(1);
}
