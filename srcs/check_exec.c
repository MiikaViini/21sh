/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/14 15:54:16 by mviinika         ###   ########.fr       */
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
		//ft_printf("%d\n", input[0]);
		
		if (ft_strequ(builtins[k], input[0]))
		{
			g_builtins[k](input, env);
			return (1);
		}
	}
	
	return (0);
}
int	fork1(void)
{
	int pid;

	pid = fork();
	if(pid == -1)
		error_print(NULL, NULL, E_NODIGIT);
	return pid;
}

int exec_single_command(t_ast *tree, int rb, char **builtins, t_env *env)
{
	if ((rb && !tree) || (!rb && !tree))
		return 1;
		
	env->path = get_path(env->env);
	if (tree->type == TOKEN_DOLLAR || (tree->cmd[0][0] == '~' && tree->cmd[0][0] != '$'))
	{
		
		tree->cmd[0] = handle_expansions(tree->cmd[0], env->env);
		tree->type = TOKEN_WORD;
	}
	if (rb && tree->type == TOKEN_WORD)
	{
		
		update_env(env->env, tree->cmd[ft_linecount(tree->cmd) - 1], "_");
	}

	if (rb == 0)
	{
		ft_putstr("exit\n");
		return 0;
	}
	if (check_builtins(tree->cmd, builtins, env))
	{
		;
	}
	else if (check_command(tree->cmd, env->path, env->env))
	{
		;
	}
	else
		error_print(tree->cmd[0], NULL, E_NOTF);
	free_strarr(env->path);
	return 1;
}

int	exec_tree(t_ast *tree, int rb, char **builtins, t_env *env)
{
	int fd[2];
	int stdin;
	int stdout;
	int i;

	i = 0;
	stdin = dup(0);
	stdout = dup(1);
	if ((!tree) || (!rb && !tree))
		return 1;
	env->path = get_path(env->env);
	while(tree->cmd[i])
	{
		
		if (tree->type == TOKEN_DOLLAR || (tree->cmd[0][0] == '~' && tree->cmd[0][0] != '$'))
		{
			tree->cmd[i] = handle_expansions(tree->cmd[i], env->env);
			tree->type = TOKEN_WORD;
		}
	}
	//word = remove_quotes(word);
	if (rb && tree->type == TOKEN_WORD)
		update_env(env->env, tree->cmd[ft_linecount(tree->cmd) - 1], "_");
	if (rb == 0)
	{
		ft_putstr("exit\n");
		return 0;
	}
	if (tree->type == TOKEN_WORD && check_builtins(tree->cmd, builtins, env))
	{
		;
	}
	else if (tree->type == TOKEN_WORD && check_command_tree(tree->cmd, env->path, env->env))
	{
		;
	}
	else if (tree->type == TOKEN_PIPE)
	{
		if (pipe(fd) < 0)
			error_print(NULL, NULL, E_PIPEFAIL);
		if ( (fork1()) == 0)
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
		dup2(stdin, 0);
		dup2(stdout, 1);
		close(stdin);
		close(stdout);
		wait(0);
		wait(0);
	}
	exit(1);
}
