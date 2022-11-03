/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/03 12:52:46 by mviinika         ###   ########.fr       */
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

static void	rem_quote(t_quotes *quots, char *input, int *tot, int *i)
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

int	is_redirect(char *input, int i, t_quotes *quots)
{
	return ((input[i] == '>' && !quots->d_quote)
		|| (input[i] == '>' && !quots->s_quote));
}

static char	*word(t_pars *pars, int i, int *total, char **env)
{
	char		*word;
	t_quotes	quots;
	t_word		ints;

	initialise_structs(&quots, &ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		rem_quote(&quots, pars->trimmed, total, &i);
		if (is_operator(pars->trimmed[i], &quots))
		{
			word[0] = pars->trimmed[i];
			(*total)++;
			break ;
		}
		if (is_redirect(pars->trimmed, i, &quots))
			pars->redir = 1;
		if (is_expansion(pars->trimmed, i))
			ints.expan = 1;
		if (is_end_of_word(pars->trimmed[i], &quots) && (*total)++)
			break ;
		if (can_be_added(pars->trimmed[i], &quots))
			add_letter(word, pars->trimmed[i++], total, &ints.k);
	}
	if ((ints.expan && !quots.s_quote)
		|| (word[0] == '~' && word[1] != '$' && !quots.s_quote))
		word = handle_expansions(word, env, total, &i);
	ft_printf("%s\n", word);
	return (word);
}

char	**parse_input(t_env *env, t_pars *pars)
{
	int			i;
	int			k;
	static int	total;

	i = 0;
	k = 0;
	total = 0;
	while (i < pars->len)
	{
		pars->parsed[k++] = word(pars, i, &total, env->env);
		if (!pars->parsed[k - 1])
		{
			ft_strdel(&pars->trimmed);
			free_parsed_input(pars->parsed);
			free(pars->parsed);
			return (NULL);
		}
		i = total;
	}
	pars->parsed[k] = NULL;
	if (pars->redir)
	{
		redirect(pars, env);
		//ft_strdel(&pars->trimmed);
		//return (NULL);
	}
	ft_strdel(&pars->trimmed);
	return (pars->parsed);
}
