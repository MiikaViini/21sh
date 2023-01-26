/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:36:13 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/26 09:31:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	is_aggr_err_out(char *redir, t_quotes *quots)
{
	return ((ft_strncmp(redir, "&>", 2) == 0
			&& quots->d_quote == 0 && quots->s_quote == 0));
}

int	set_redirections(t_pars *pars, t_word *ints, char *word, t_quotes *quots)
{
	if ((is_aggr_err_out(&pars->trimmed[ints->i], quots) && word[0] == 0)
		|| (is_aggr_err_out(&pars->trimmed[ints->i], quots) && word[0] == 0))
	{
		set_values_aggr_io(ints, &word);
		return (1);
	}
	else if ((is_redirect(pars->trimmed[ints->i], quots)
			&& ft_only_digits(word)))
	{
		ints->i = redir_token(&pars->trimmed[ints->i], &word[ints->k], ints);
		return (1);
	}
	return (0);
}
