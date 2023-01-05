/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:56:41 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 11:59:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	check_equalsign(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (ft_strchr(&input[i], '='))
			return (0);
	}
	return (1);
}

int	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '=');
}

void	add_letter(char *word, char c, t_word *ints)
{
	word[ints->k] = c;
	ints->total += 1;
	ints->k += 1;
}

int	can_be_added(char c, t_quotes *quots)
{
	return ((c && quots->closed == 0) || (!ft_isspace(c) && quots->closed));
}

int	is_end_of_word(char c, t_quotes *quots, int index)
{
	return ((ft_isspace(c) && quots->s_quote + quots->d_quote == 0)
		|| (ft_isspace(c) && quots->closed)
		|| (is_operator(c, quots) && index != 0));
}
