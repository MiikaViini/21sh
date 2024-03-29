/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:25:27 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 11:07:45 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_operator(t_tlist *tokens)
{
	return ((tokens->type == TOKEN_REDIRECT
			&& tokens->next->type != TOKEN_WORD)
		|| (tokens->type == TOKEN_SEMICOLON
			&& tokens->next->type == TOKEN_SEMICOLON)
		|| (tokens->type == TOKEN_SEMICOLON
			&& tokens->next->type == TOKEN_PIPE)
		|| (tokens->type == TOKEN_PIPE
			&& tokens->next->type == TOKEN_PIPE)
		|| (tokens->type == TOKEN_AMPERSAND));
}

static int	check_cons_operators(t_tlist *tokens)
{
	if (tokens->type == TOKEN_PIPE
		|| tokens->type == TOKEN_SEMICOLON)
	{
		error_print(NULL, tokens->str, E_SYNERR);
		return (1);
	}
	while (tokens->next)
	{
		if (check_operator(tokens))
		{
			error_print(NULL, tokens->str, E_SYNERR);
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	check_syntax(t_pars *pars, t_tlist *tokens)
{
	t_tlist	*temp;
	int		i;
	int		err;

	temp = tokens;
	err = 0;
	if (check_cons_operators(temp))
		return (1);
	i = ft_strlen(pars->last_token_str) - 1;
	if (pars->last_token_str[i] == '|'
		|| pars->last_token_str[i] == '&'
		|| pars->last_token_str[i] == ';'
		|| pars->last_token_str[i] == '>'
		|| pars->last_token_str[i] == '<')
		err = 1;
	if (err)
		error_print("newline", NULL, E_SYNERR);
	return (err);
}
