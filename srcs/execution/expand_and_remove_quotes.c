/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:17:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 15:23:35 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// Expands variables from environment and removes quotes
int	expand_and_remove_quotes(t_ast **tree, t_env *env)
{
	int			i;
	int			k;
	t_quotes	quotes;

	k = 0;
	i = 0;
	initialise_structs(&quotes, NULL, NULL);
	while ((*tree)->cmd[i] && (*tree)->type != NODE_PIPE)
	{
		see_quote(&quotes, (*tree)->cmd[i], k);
		while ((*tree)->cmd[i][k])
		{	
			if (is_expansion((*tree)->cmd[i], k) && !quotes.s_quote)
				(*tree)->cmd[i] = handle_expansions((*tree)->cmd[i], env->env);
			k++;
		}
		(*tree)->cmd[i] = remove_quotes((*tree)->cmd[i]);
		k = 0;
		i++;
	}
	return (0);
}
