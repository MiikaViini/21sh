/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:45:22 by mviinika          #+#    #+#             */
/*   Updated: 2022/03/23 22:51:20 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*dot(va_list args, char *format, t_modifiers *mods)
{
	char	*num;
	int		i;

	i = 0;
	num = ft_strnew(25);
	(void)args;
	format++;
	while (*format >= '0' && *format <= '9')
		num[i++] = *format++;
	mods->precision = ft_atoi(num);
	mods->dot = 1;
	ft_strdel(&num);
	return (format);
}
