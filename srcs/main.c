/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/14 15:39:06 by mviinika         ###   ########.fr       */
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
	pars->redir = 0;
	// pars->std_out = dup(STDOUT_FILENO);
}

int is_pipe_sequence(t_ast *tree)
{
	if (tree->right)
		return (1);
	return (0);
}

static int	ft_21sh(t_env *env, char **builtins)
{
	int		rb;
	char	buf[MAX_LINE + 1];
	t_ast	**tree;
	t_pars	parsed;
	int		i;

	rb = 1;
	i = 0;
	ft_memset(buf, '\0', MAX_LINE + 1);
	tree = NULL;
	if (rb != 0)
	{
		rb = read(0, &buf, MAX_LINE);
		if (rb == -1)
			exit(1);
		set_pars_struct(&parsed, buf);
		if (check_quotes(buf))
			error_print(NULL, NULL, E_QUOT);
		else
		{
			if (*parsed.trimmed)
				tree = parse_input(env, &parsed);
			else
				return 1;
			while(tree[i])
			{
				if (is_pipe_sequence(tree[i]))
				{
					if (fork() == 0)
						rb = exec_tree(tree[i], rb, builtins, env);
					wait(0);
				}
				else
					rb = exec_single_command(tree[i]->left, rb, builtins, env);
				i++;
			}
		}
		ft_memset(buf, '\0', 4096);
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
