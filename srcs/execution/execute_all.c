/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:42:03 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 12:13:12 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	delete_node(t_ast *node)
{
	if (node == NULL)
		return ;
	delete_node(node->left);
	if (node->cmd)
		free_strarr(node->cmd);
	if (node->file)
		ft_strdel(&node->file);
	if (node->redirs)
		tokens_del(&node->redirs);
	delete_node(node->right);
	free(node);
}

static void	reset_fds_to_default(char *terminal)
{
	close(STDIN_FILENO);
	open(terminal, O_RDWR);
	close(STDOUT_FILENO);
	open(terminal, O_RDWR);
	close(STDERR_FILENO);
	open(terminal, O_RDWR);
}

static int	is_pipe_sequence(t_ast *tree)
{
	if (tree->right)
		return (1);
	return (0);
}

void	execute_all(t_env *env, char **builtins, t_ast **tree)
{
	int	i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree[i])
	{
		if (is_pipe_sequence(tree[i]))
		{
			if (fork_wrapper() == 0)
				exec_tree(tree[i], builtins, env);
			wait(0);
		}
		else
			exec_single_command(tree[i]->left, builtins, env);
		delete_node(tree[i]);
		reset_fds_to_default(env->terminal);
		i++;
	}
}
