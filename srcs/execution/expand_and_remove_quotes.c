/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:17:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 12:56:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// static char	*remove_quotes(char *input)
// {
// 	int		i;
// 	int		k;
// 	char	quote;
// 	char	*fresh;

// 	i = 0;
// 	k = 0;
// 	quote = 0;
// 	fresh = ft_strnew(ft_strlen(input));
// 	while (input[i])
// 	{
// 		if ((input[i] == '\'' && quote == 0)
// 			|| (input[i] == '\"' && quote == 0))
// 			quote = input[i];
// 		else if (input[i] == quote)
// 			quote = 0;
// 		else if (input[i] != quote)
// 			fresh[k++] = input[i];
// 		i++;
// 	}
// 	ft_strdel(&input);
// 	return (fresh);
// }

// Expands variables from environment and removes quotes
int	expand_and_remove_quotes(t_ast **tree, t_env *env)
{
	int			i;
	int			k;
	t_quotes	quotes;

	k = 0;
	i = 0;
	initialise_structs(&quotes, NULL, NULL);
	while ((*tree)->type != NODE_PIPE && (*tree)->cmd[i])
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
