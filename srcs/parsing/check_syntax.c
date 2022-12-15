/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:25:27 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 14:27:19 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int check_cons_redirs(t_tlist *tokens)
{
	
	while(tokens->next)
	{
		if (tokens->type == TOKEN_REDIRECT && tokens->next->type == TOKEN_REDIRECT)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int check_syntax(t_pars *pars, t_tlist *tokens)
{
	t_tlist *temp;

	temp = tokens;
	int i;
	int err;
	
	err = check_cons_redirs(temp);
	i = ft_strlen(pars->last_token_str) - 1;
	if (pars->last_token_str[i] == '&' 
		|| pars->last_token_str[i] == '|' 
		|| pars->last_token_str[i] == ';'
		|| pars->last_token_str[i] == '>'
		|| pars->last_token_str[i] == '<')
		err = 1;
	if (err)
		error_print(NULL, NULL, E_SYNERR);
	return err;
}
