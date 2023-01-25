/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:00:06 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 10:27:21 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	is_operator(char c, t_quotes *quots)
{
	(void)quots;
	if ((quots->d_quote && !quots->closed)
		|| (quots->s_quote && !quots->closed))
		return (0);
	return ((c == '|' ) | (c == ';') | (c == '&'));
}
