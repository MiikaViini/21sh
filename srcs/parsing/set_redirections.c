/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:36:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 15:29:17 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	is_aggr_err_out(t_quotes *quots, char redir, char operator)
{
	return (is_redirect(redir, quots) && operator == '&');
}

int	set_redirections(t_pars *pars, t_word *ints, char *word, t_quotes *quots)
{
	if ((is_redirect(pars->trimmed[ints->i], quots) && ft_only_digits(word)))
	{
		ints->i = redir_token(&pars->trimmed[ints->i], &word[ints->k], ints);
		return (1);
	}
	else if (is_aggr_err_out(quots, pars->trimmed[ints->i], word[0]))
	{
		set_values_aggr_io(ints, &word, &ints->total);
		return (1);
	}
	return (0);
}
