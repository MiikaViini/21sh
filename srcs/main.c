/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 10:14:46 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	free_parsed_input(char **p_input)
{
	int	i;

	i = -1;
	if (!p_input || !p_input[0])
		return ;
	while (p_input[++i])
		ft_strdel(&p_input[i]);
}

void	set_pars_struct(t_pars *pars, char *input)
{
	pars->parsed = (char **)ft_memalloc(sizeof(char *) \
	* (ft_wordcount_ws(input) + 1));
	pars->trimmed = ft_strtrim(input);
	pars->len = (int)ft_strlen(pars->trimmed);
	pars->last_token_str = NULL;
}

int is_pipe_sequence(t_ast *tree)
{
	if (tree->right)
		return (1);
	return (0);
}

void reset_fds_to_default(char *terminal)
{
	close(STDIN_FILENO);
	open(terminal, O_RDWR);
	close(STDOUT_FILENO);
	open(terminal, O_RDWR);
	close(STDERR_FILENO);
	open(terminal, O_RDWR);
}

void execute_all(t_env *env, char **builtins, t_ast **tree, int *rb)
{
	int	i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree[i])
	{
		if (is_pipe_sequence(tree[i]))
		{
			if (fork() == 0)
				exec_tree(tree[i], *rb, builtins, env);
			wait(0);
		}
		else
			exec_single_command(tree[i]->left, *rb, builtins, env);
		delete_node(tree[i]);
		reset_fds_to_default(env->terminal);
		i++;
	}
}

void free_all(t_pars *pars, t_ast **tree, char *buf)
{
	if (tree)
		free(tree);
	free_parsed_input(pars->parsed);
	ft_strdel(&pars->trimmed);
	free(pars->parsed);
	ft_memset(buf, '\0', 4096);
}

static int	ft_21sh(t_env *env, char **builtins)
{
	int		rb;
	char	buf[MAX_LINE + 1];
	t_ast	**tree;
	t_pars	parsed;
	
	rb = 1;
	ft_memset(buf, '\0', MAX_LINE + 1);
	tree = NULL;
	rb = read(0, &buf, MAX_LINE);
	if (rb == -1)
		exit(1);
	set_pars_struct(&parsed, buf);
	if (check_quotes(buf))
		error_print(NULL, NULL, E_QUOT);
	else
	{
		if (*parsed.trimmed)
			tree = parse_input(&parsed);
		else
		{
			free_all(&parsed, tree, buf);
			// free_parsed_input(parsed.parsed);
			// ft_strdel(&parsed.trimmed);
			// free(parsed.parsed);
			return 1;
		}
		execute_all(env, builtins, tree, &rb);
		// while(tree[i])
		// {
		// 	if (is_pipe_sequence(tree[i]))
		// 	{
		// 		if (fork() == 0)
		// 			exec_tree(tree[i], rb, builtins, env);
		// 		wait(0);
		// 	}
		// 	else
		// 		exec_single_command(tree[i]->left, rb, builtins, env);
		// 	delete_node(tree[i]);
		// 	reset_fds_to_default();
		// 	i++;
		// }
		ft_memset(buf, '\0', 4096);
		free(tree);
		free_parsed_input(parsed.parsed);
		free(parsed.parsed);
	}
	return (rb);
}

static char	**initialize_and_set_builtins(void)
{
	static char	*builtins[7] = {"echo", "cd", "setenv", "unsetenv", "env", "exit"};

	return (builtins);
}

int	main(int argc, char **argv, char **environ)
{
	t_env	env;
	char	**builtins;
	int		rb;

	rb = 1;
	builtins = initialize_and_set_builtins();
	get_env(&env, environ, argc, argv);
	ft_putstr("\033[2J\033[H");
	while (rb != 0)
	{
		ft_putstr("21sh$ ");
		rb = ft_21sh(&env, builtins);
	}
	free_strarr(env.env);
	free_strarr(env.path);
	return (0);
}
