/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/16 14:58:31 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// Get binary paths from environment
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

// Check if cmd is builtin
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

// Fork wrapper, with pid check.
int	fork1(void)
{
	int pid;

	pid = fork();
	if(pid == -1)
		error_print(NULL, NULL, E_NOFORK);
	return pid;
}

//Remove quotes from input
char *remove_quotes(char *input)
{
	int 	i;
	int 	k;
	char	quote;
	char	*fresh;

	i = 0;
	k = 0;
	quote = 0;
	fresh = ft_strnew(ft_strlen(input));
	while (input[i])
	{
		
		if ((input[i] == '\'' && quote == 0)|| (input[i] == '\"' && quote == 0))
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		else if (input[i] != quote)
			fresh[k++] = input[i];
		i++;
	}
	ft_strdel(&input);
	return (fresh);
}

// Expands variables from environment and removes quotes
void expand_and_remove_quotes(t_ast **tree, t_env *env)
{
	int i;
	int k;
	t_quotes quotes;

	k = 0;
	i = 0;
	initialise_structs(&quotes, NULL, NULL);
	while((*tree)->type != NODE_PIPE && (*tree)->type != NODE_REDIR && (*tree)->cmd[i])
	{
		see_quote(&quotes, (*tree)->cmd[i], k);
		while ((*tree)->cmd[i][k])
		{	
			if (is_expansion((*tree)->cmd[i], k) && !quotes.s_quote)
			{
				(*tree)->cmd[i] = handle_expansions((*tree)->cmd[i], env->env);
			}
			k++;
		}
		(*tree)->cmd[i] = remove_quotes((*tree)->cmd[i]);
		k = 0;
	 	i++;
	}
}
void redirection(t_ast *tree, int rb, char **builtins, t_env *env)
{
	int fd;
	int cf;

	cf = 1;
	if (tree->redir_type == '>')
	{
		if (tree->redir_type == '>')
			fd = open(tree->file, O_CREAT | O_WRONLY | O_APPEND, 0755);
		else
			fd = open(tree->file, O_CREAT | O_WRONLY, 0755);
	}
	else if (tree->redir_type == '<')
	{
		fd = open(tree->file, O_RDONLY);
		cf = 0;
	}
	dup2(fd, cf);
	close(fd);
	wait(0);
}
// Executes single command, so no pipe sequnce was deteced. Also expand
// variables if found
int exec_single_command(t_ast *tree, int rb, char **builtins, t_env *env)
{
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
		redirection(tree, rb, builtins, env);
	}
	if (check_builtins(tree->cmd, builtins, env))
		;
	else
		check_command(tree->cmd, env->path, env->env, 0);
	free_strarr(env->path);
	return 1;
}



// executing pipe sequences
void	pipe_executor(t_ast *tree, int rb, char **builtins, t_env *env)
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


// Executes syntax tree node by node from left to right
// trees root is always PIPE. Depending of TOKEN, it executes necessary
// actions with that node. When PIPE is found, recursively executes tree.
// Does proper piping in child processes and waits them to finish. in the
// end closes pipes and exits child process.
int	exec_tree(t_ast *tree, int rb, char **builtins, t_env *env)
{
	int i;
	
	i = 0;
	if ((!tree) || (!rb && !tree))
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
	if (tree->type == NODE_CMD)
	{
		if (check_builtins(tree->cmd, builtins, env))
			;
		else
			check_command(tree->cmd, env->path, env->env, 1);
	}
	else if (tree->type == NODE_REDIR)
	{

		redirection(tree, rb, builtins, env);
		exec_tree(tree->left, rb, builtins, env);
		
	}
	else if (tree->type == NODE_PIPE)
		pipe_executor(tree, rb, builtins, env);
	free_strarr(env->path);
	exit(1);
}
