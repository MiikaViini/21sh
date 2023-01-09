/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/09 19:41:52 by spuustin         ###   ########.fr       */
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

int	is_pipe_sequence(t_ast *tree)
{
	if (tree->right)
		return (1);
	return (0);
}

void	reset_fds_to_default(char *terminal)
{
	close(STDIN_FILENO);
	open(terminal, O_RDWR);
	close(STDOUT_FILENO);
	open(terminal, O_RDWR);
	close(STDERR_FILENO);
	open(terminal, O_RDWR);
}



static int	ft_21sh(t_env *env, char **builtins, char *input)
{
	int		rb;
	t_ast	**tree;
	t_pars	parsed;
	int		i;
	char 	*terminal = ttyname(1);

	// ft_printf("input: |%s|\n", input);
	rb = ft_strlen(input);
	i = 0;
	tree = NULL;
	write(1, "\n", 1);
	set_pars_struct(&parsed, input);
	if (check_quotes(input))
		error_print(NULL, NULL, E_QUOT);
	else
	{
		if (*parsed.trimmed)
			tree = parse_input(env, &parsed);
		else
		{
			free_parsed_input(parsed.parsed);
			ft_strdel(&parsed.trimmed);
			free(parsed.parsed);
			return 1;
		}
		while(tree && tree[i])
		{
			if (is_pipe_sequence(tree[i]))
			{
				if (fork() == 0)
					exec_tree(tree[i], rb, builtins, env);
				wait(0);
			}
			else
				exec_single_command(tree[i]->left, rb, builtins, env);
			delete_node(tree[i]);
			reset_fds_to_default(terminal);
			i++;
		}
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

static void	prompt(t_term *t, t_env *env, char **builtins)
{
	int		rb;

	rb = 1;
	while (!input_cycle(t))
	{
		write_history_to_file(t);
		rb = ft_21sh(env, builtins, t->inp);
		ft_restart_cycle(t);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_env	env;
	t_term	t;
	char	**builtins;
	int		rb;

	init_tcaps(&t);
	rb = 1;
	builtins = initialize_and_set_builtins();
	get_env(&env, environ, argc, argv);
	ft_putstr("\033[2J\033[H");
	prompt(&t, &env, builtins);
	free_strarr(env.env);
	free_strarr(env.path);
	return (0);
}
