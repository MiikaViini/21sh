/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:38:38 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 15:28:59 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	is_redirect(char c, t_quotes *quots)
{
	int	ret;

	ret = 0;
	if ((c == '>' && quots->d_quote == 0)
		&& (c == '>' && quots->s_quote == 0))
		ret = 1;
	else if ((c == '<' && !quots->d_quote)
		&& (c == '<' && !quots->s_quote))
		ret = 1;
	return (ret);
}
