/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_specifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:42:47 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/10 11:18:20 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	per_specifier(va_list args, t_modifiers *mods)
{
	int		count;
	char	*res;
	char	*temp;
	int		i;
	char	c;

	c = ' ';
	i = 0;
	count = 0;
	(void)args;
	res = ft_strdup("%");
	mods->precision = 0;
	mods->dot = 0;
	temp = treat_width(res, mods, ft_strlen(res));
	count = ft_putstrlen(temp);
	ft_strdel(&res);
	ft_strdel(&temp);
	return (count);
}
