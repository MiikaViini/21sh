/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:55:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 15:29:45 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*remove_quotes(char *input)
{
	int		i;
	int		k;
	char	quote;
	char	*fresh;

	i = 0;
	k = 0;
	quote = 0;
	fresh = ft_strnew(ft_strlen(input));
	while (input[i])
	{
		if ((input[i] == '\'' && quote == 0)
			|| (input[i] == '\"' && quote == 0))
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		else if (input[i] != quote)
			fresh[k++] = input[i];
		i++;
	}
	ft_strdel(&input);
	return (fresh);
}
