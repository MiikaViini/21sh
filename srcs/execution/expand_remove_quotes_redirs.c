/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remove_quotes_redirs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:47:37 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/19 16:08:28 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	expand_remove_quotes_redirs(t_tlist **redirs, t_env *env)
{
	int			k;
	t_tlist		*temp;
	t_quotes	quotes;

	k = 0;
	initialise_structs(&quotes, NULL, NULL);
	temp = (*redirs);
	while ((*redirs) && (*redirs)->file)
	{
		see_quote(&quotes, (*redirs)->file, k);
		while ((*redirs)->file[k])
		{	
			if (is_expansion((*redirs)->file, k) && !quotes.s_quote)
				(*redirs)->file = handle_expansions((*redirs)->file, env->env);
			k++;
		}
		(*redirs)->file = remove_quotes((*redirs)->file);
		k = 0;
		(*redirs) = (*redirs)->next;
	}
	(*redirs) = temp;
	return (0);
}
