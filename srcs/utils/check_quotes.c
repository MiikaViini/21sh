/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:16:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/09 09:33:21 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int check_quotes(char *input)
{
	int i;
	int s_quote;
	int d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !s_quote && !d_quote)
			s_quote = 1;
		else if (input[i] == '\'')
			s_quote = 0;
		else if (input[i] == '\"' && !d_quote && !s_quote)
			d_quote = 1;
		else if (input[i] == '\"')
			d_quote = 0;
		i++;
	}
	return (s_quote + d_quote);
}

