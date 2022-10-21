/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/21 13:49:07 by mviinika         ###   ########.fr       */
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

static int	minishell(t_env *env, char **builtins)
{
	int		rb;
	char	buf[MAX_LINE + 1];
	char	**parsed_input;

	rb = 1;
	ft_memset(buf, '\0', MAX_LINE + 1);
	parsed_input = NULL;
	if (rb != 0)
	{
		rb = read(0, &buf, MAX_LINE);
		if (ft_strcmp(buf, ""))
		if (rb == -1)
			exit(1);
		if (check_quotes(buf))
			error_print(NULL, NULL, E_QUOT);
		else
		{
			if (rb != 0)
				parsed_input = parse_input(buf, env);
			rb = check_exec(parsed_input, rb, builtins, env);
		}
		ft_memset(buf, '\0', 4096);
		free_parsed_input(parsed_input);
		free(parsed_input);
	}
	return (rb);
}

static char	**initialize_and_set_builtins(void)
{
	static char	*builtins[6] = {"echo", "cd", "setenv", "unsetenv", "env"};

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
		rb = minishell(&env, builtins);
	}
	free_strarr(env.env);
	free_strarr(env.path);
	return (0);
}
