/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:25:27 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/04 19:36:13 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_cons_redirs(t_tlist *tokens)
{
	while (tokens->next)
	{
		if (tokens->type == TOKEN_REDIRECT
			&& tokens->next->type != TOKEN_WORD)
		{
			error_print(NULL, tokens->next->str, E_SYNERR);
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
	if (check_cons_redirs(temp))
	{
		return (1);
	}
	i = ft_strlen(pars->last_token_str) - 1;
	if (pars->last_token_str[i] == '&'
		|| pars->last_token_str[i] == '|'
		|| pars->last_token_str[i] == ';'
		|| pars->last_token_str[i] == '>')
		err = 1;
	if (err)
		error_print("newline", NULL, E_SYNERR);
	return (err);
}
//|| pars->last_token_str[i] == '<'
