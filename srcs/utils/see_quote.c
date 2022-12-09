/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:49:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/09 09:33:34 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	see_quote(t_quotes *quots, char *input, int i)
{
	if (is_quote(input[i]))
	{
		while (is_double_quote(input[i]) && quots->s_quote == 0)
		{
			quots->d_quote += 1;
			i += 1;
		}
		while (is_single_quote(input[i]) && !quots->d_quote)
		{
			quots->s_quote += 1;
			i += 1;
		}
		if (quots->s_quote >= 2 || quots->d_quote >= 2)
			quots->closed = 1;
	}
}
