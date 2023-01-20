/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/20 11:48:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	check_read_bytes(int rb, t_env *env)
{
	if (rb == -1)
		exit(1);
	(void)env;
}

static int	ft_21sh(t_env *env, char **builtins, char *input, t_term *t)
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
		execute_all(env, builtins, tree, t);
		free_all(&parsed, tree, input);
	}
	return (rb);
}

char	*ft_lexer(t_term *t)
{
	char	*trimmed;

	trimmed = ft_strtrim(t->inp);
	if (!*trimmed)
		ft_strdel(&trimmed);
	trimmed = heredoc(t, trimmed);
	return (trimmed);
}

static void	prompt(t_term *t, t_env *env, char **builtins)
{
	char	*new;

	while (!input_cycle(t))
	{
		
		new = ft_lexer(t);
	
		write_history_to_file(t);
		if (new)
			ft_21sh(env, builtins, new, t);
		else
			write(1, "\n", 1);
		restart_cycle(t);
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
