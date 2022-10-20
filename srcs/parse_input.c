/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/20 14:59:15 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	initialise_structs(t_quotes *quotes, t_word *ints, char *input)
{
	quotes->s_quote = 0;
	quotes->d_quote = 0;
	quotes->closed = 0;
	ints->expan = 0;
	ints->k = 0;
	ints->len = (int)ft_strlen(input);
}

static void rem_quote(t_quotes *quots, char *input, int *tot, int *i)
{
	if (is_quote(input[*i]))
	{
		while (is_double_quote(input[*i]) && quots->s_quote == 0)
		{
			quots->d_quote += 1;
			*i += 1;
			*tot += 1;
		}
		while (is_single_quote(input[*i]) && !quots->d_quote)
		{
			quots->s_quote += 1;
			*i += 1;
			*tot += 1;
		}
		if (quots->s_quote >= 2 || quots->d_quote >= 2)
			quots->closed = 1;
	}
}

static char	*word(char *input, int i, int *total, char **env)
{
	char		*word;
	t_quotes	quots;
	t_word		ints;

	initialise_structs(&quots, &ints, input);
	word = ft_strnew(ft_strlen(input));
	while (ft_isspace(input[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		ft_printf("jee\n");
		rem_quote(&quots, input, total, &i);
		if (is_expansion(input, i))
			ints.expan = 1;
		if (is_end_of_word(input[i], &quots) && (*total)++)
			break ;
		if (can_be_added(input[i], &quots))
			add_letter(word, input[i++], total, &ints.k);
	}
	// if ((ints.expan && !quots.s_quote)
	// 	|| (word[0] == '~' && word[1] != '$' && !quots.s_quote))
		word = handle_expansions(word, env, total, &i);
	return (word);
}

void	set_pars_struct(t_pars *pars, char *input)
{
	pars->parsed = (char **)ft_memalloc(sizeof(char *) \
	* (ft_wordcount_ws(input) + 1));
	pars->trimmed = ft_strtrim(input);
	pars->len = (int)ft_strlen(pars->trimmed);
}

char	**parse_input(char *input, char **env)
{
	int			i;
	int			k;
	static int	total;
	t_pars		pars;

	i = 0;
	k = 0;
	total = 0;
	set_pars_struct(&pars, input);
	while (i < pars.len)
	{
		pars.parsed[k++] = word(pars.trimmed, i, &total, env);
		if (!pars.parsed[k - 1])
		{
			ft_strdel(&pars.trimmed);
			free_parsed_input(pars.parsed);
			free(pars.parsed);
			return (NULL);
		}
		i = total;
	}
	pars.parsed[k] = NULL;
	ft_strdel(&pars.trimmed);
	return (pars.parsed);
}
