/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/19 09:58:27 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int g_signal;

static void	set_signal_int(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		ft_putchar('\n');
		ft_putstr("21sh$ ");
	}
	else if (signal == SIGWINCH)
	{
		;
	}
	
}

void	set_signal_handling(void)
{
	signal(SIGINT, set_signal_int);
	signal(SIGWINCH, set_signal_int);
}

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

static int	ft_21sh(t_env *env, char **builtins)
{
	int		rb;
	char	buf[MAX_LINE + 1];
	t_ast	**tree;
	t_pars	parsed;

	set_signal_handling();
	set_start_values(&tree, buf, &rb);
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
			return (rb);
		}
		execute_all(env, builtins, tree);
		free_all(&parsed, tree, buf);
	}
	return (rb);
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
		if (g_signal != 1)
			ft_putstr("21sh$ ");
		g_signal = 0;
		rb = ft_21sh(&env, builtins);
	}
	free_strarr(env.env);
	free_strarr(env.path);
	return (0);
}
