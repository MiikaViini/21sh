/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:48 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 12:05:45 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	is_expansion(char *str, int i)
{
	//ft_printf("str [%s] [%d]\n", str, str[i - 1]);
	if ((str[i] == '$' && ft_isalnum(str[i + 1]))
		|| (str[i] == '$' && str[i + 1] == '_')
		|| (str[0] == '~' && str[1] != '$'))
		return (1);
	return (0);
}
