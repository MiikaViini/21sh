/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:42:02 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/09 21:28:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	u_specifier(va_list args, t_modifiers *mods)
{
	unsigned long long	num;
	char				*string;
	char				*output;
	int					count;

	if (mods->capital)
		mods->cap_u = 1;
	mods->hash = 0;
	num = va_arg(args, unsigned long long );
	mods->plus = 0;
	string = type_cast(num, mods, 10);
	output = treat_mods(string, mods, ft_strlen(string), num);
	ft_strdel(&string);
	string = check_edges(mods, output, num);
	count = ft_putstrlen(string);
	ft_strdel(&string);
	ft_strdel(&output);
	return (count);
}
