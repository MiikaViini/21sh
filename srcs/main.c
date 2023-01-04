/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/04 17:15:54 by spuustin         ###   ########.fr       */
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

void	free_all(t_pars *pars, t_ast **tree, char *buf)
{
	if (tree)
		free(tree);
	free_parsed_input(pars->parsed);
	ft_strdel(&pars->trimmed);
	free(pars->parsed);
	ft_memset(buf, '\0', 4096);
}

void	check_read_bytes(int rb, t_env *env)
{
	if (rb == -1)
		exit(1);
	(void)env;
}

static int	ft_21sh(t_env *env, char **builtins, char *input)
{
	int		rb;
	t_ast	**tree;
	t_pars	parsed;

	rb = ft_strlen(input);
	tree = NULL;
	write(1, "\n", 1);
	check_read_bytes(rb, env);
	set_pars_struct(&parsed, input);
	if (check_quotes(input))
		error_print(NULL, NULL, E_QUOT);
	else
	{
		if (*parsed.trimmed)
			tree = parse_input(&parsed);
		else
		{
			free_all(&parsed, tree, input);
			return (rb);
		}
		execute_all(env, builtins, tree);
		free_all(&parsed, tree, input);
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

	init_tcaps(&t);
	builtins = initialize_and_set_builtins();
	get_env(&env, environ, argc, argv);
	ft_putstr("\033[2J\033[H");
	prompt(&t, &env, builtins);
	free_strarr(env.env);
	free_strarr(env.path);
	return (0);
}
