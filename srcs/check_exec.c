/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/05 13:43:17 by mviinika         ###   ########.fr       */
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
static int	check_builtins(char **input, char **builtins, t_env *env, int fd)
{
	int k;

	k = -1;
	fd = 1;
	while (builtins[++k])
	{
		if (ft_strequ(builtins[k], input[0]))
		{
			g_builtins[k](input, env, fd);
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
	while((*tree)->type != NODE_PIPE  && (*tree)->cmd[i])
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
int redirection(t_tlist *redirs)
{
	int fd;
	
	fd = 0;
	if (!redirs)
		return 0;
	if (redirs->redir_type == REDIR_TRUNC)
	{
		close(1);
		open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	}
	else if (redirs->redir_type == REDIR_APPEND)
	{
		close(1);
		redirs->file_fd = open(redirs->file, O_CREAT | O_WRONLY | O_APPEND, 0664);

	}
	else if (redirs->redir_type == REDIR_IN)
	{
		close(0);
		redirs->file_fd = open(redirs->file, O_RDONLY);
		if(fd == -1)
		{
			error_print(redirs->file, NULL, E_NOEX);
			return -1;
		}
	}
	else if (redirs->redir_type == REDIR_AGGR_IN || redirs->redir_type == REDIR_AGGR_OUT)
	{
		ft_printf("%d %d\n", redirs->from_fd, redirs->fd_close);
		if (redirs->fd_close)
			close(redirs->from_fd);
		else
			dup2(redirs->to_fd, redirs->from_fd);
	}
	redirection(redirs->next);
	return 0;
}


// Executes single command, so no pipe sequence was deteced. Also expand
// variables if found.
// For built-ins there is a duplicate from STD_OUT, since it cant open 
// it again so we open it end of the cycle.
int exec_single_command(t_ast *tree, int rb, char **builtins, t_env *env)
{
	int fd = 1;
	// int std_out;
	// int std_in;
	// int std_err;
	
	// std_err = dup(2);
	// std_out = dup(1);
	// std_in = dup(0);
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
		printf("jeee\n");
		if (redirection(tree->redirs) == -1)
			return 1;
	}
	if (check_builtins(tree->cmd, builtins, env, fd))
		;
	else
		check_command(tree->cmd, env->path, env->env, 0);
	free_strarr(env->path);
	// dup2(std_out, STDOUT_FILENO);
	// dup2(std_err, STDERR_FILENO);
	// dup2(std_in, STDIN_FILENO);
	// if (fd < 1)
	// 	close(fd);
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
	int fd;

	fd = 1;
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
		if (check_builtins(tree->cmd, builtins, env, fd))
			;
		else
		{	
			check_command(tree->cmd, env->path, env->env, 1);
		}
	}
	else if (tree->type == NODE_REDIR)
	{
		redirection(tree->redirs);
		if (check_builtins(tree->cmd, builtins, env, fd))
			;
		else
			check_command(tree->cmd, env->path, env->env, 0);
		//close(tree->out_fd);
	}
	else if (tree->type == NODE_PIPE)
		pipe_executor(tree, rb, builtins, env);
	free_strarr(env->path);
	exit(1);
}


// void duplicate_fildes(t_ast *tree)
// {
// 	int fd;
// 	fd = -1;
// 	if (tree->redir_type == REDIR_AGGR_IO)
// 	{
// 		fd = open(tree->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
// 	}
		
// 	else 
// 		fd = ft_atoi(tree->file);
// 	if (fd < 0)
// 		error_print(tree->file, NULL, E_NOEX);
// 	// close(tree->redir_fd);
// 	// close(fd);
// 	// dup(tree->redir_fd);
// 	// dup(fd);
// 	// dup(fd);
// 	//dup2(fd, tree->redir_fd);
// 	dup2(fd, STDERR_FILENO);
// 	dup2(fd, STDOUT_FILENO);
// 	//close(fd);
// 	close(tree->redir_fd);
// 	wait(0);
// }
