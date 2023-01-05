/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/02 12:50:20 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern int	g_signal;

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

static int check_read_bytes(int rb)
{
	if (rb == -1)
		exit(1);
	else if (rb == 0)
		return 0;
	return (rb);
}

static int	ft_21sh(t_env *env, char **builtins)
{
	int		rb;
	char	buf[MAX_LINE + 1];
	t_ast	**tree;
	t_pars	parsed;

	set_start_values(&tree, buf, &rb);
	if (!check_read_bytes(rb))
		return 0;
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

static void set_intern_vars(t_env *env)
{
	int i;

	i = 0;
	env->intr = (t_intr *)ft_memalloc(sizeof(t_intr));
	env->intr->env = (char **)ft_memalloc(sizeof(char *));
	env->intr->env[i++] = ft_strdup("SHELL_VERSION=0.0");
	env->intr->env[i] = NULL;
}

int	main(int argc, char **argv, char **environ)
{
	t_env	env;
	char	**builtins;
	int		rb;

	rb = 1;
	builtins = initialize_and_set_builtins();
	get_env(&env, environ, argc, argv);
	set_intern_vars(&env);
	ft_putstr("\033[2J\033[H");
	set_signal_handling();
	while (rb != 0)
	{
		//ft_printf("signal %d\n", g_signal);
		ft_putstr("42sh$ ");
		rb = ft_21sh(&env, builtins);
		g_signal = 0;
	}
	free_strarr(env.env);
	free_strarr(env.intr->env);
	free(env.intr);
	return (0);
}
