/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/09 13:40:59 by mviinika         ###   ########.fr       */
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
	pars->std_out = dup(STDOUT_FILENO);
}

static int	minishell(t_env *env, char **builtins)
{
	int		rb;
	char	buf[MAX_LINE + 1];
	t_ast	*tree;
	t_pars	parsed;

	rb = 1;
	ft_memset(buf, '\0', MAX_LINE + 1);
	// parsed.fd = open("test", O_CREAT| O_RDWR | O_APPEND, 0777);
	// dup2(parsed.fd, STDOUT_FILENO);
	//parsed_input = NULL;
	tree = NULL;
	if (rb != 0)
	{
		// dup2(STDOUT_FILENO, parsed.std_out);
		rb = read(0, &buf, MAX_LINE);
		set_pars_struct(&parsed, buf);
		if (rb == -1)
			exit(1);
		if (check_quotes(buf))
			error_print(NULL, NULL, E_QUOT);
		else
		{
			if (rb != 0)
				tree = parse_input(env, &parsed);
			rb = check_exec(tree, rb, builtins, env);
		}
		// ft_putendl_fd(parsed.parsed[0], 1);
		ft_memset(buf, '\0', 4096);
		free_parsed_input(parsed.parsed);
		free(parsed.parsed);
		close(parsed.fd);
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
