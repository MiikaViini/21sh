/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:47:46 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/04 12:54:02 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*width(va_list args, char *format, t_modifiers *mods)
{
	char	res[100];
	int		i;

	(void)args;
	i = 0;
	if (!ft_isdigit(*format))
		return (format);
	else if (*format == '0')
	{
		mods->zero = 1;
		format++;
	}
	while (ft_isdigit(*format))
		res[i++] = *format++;
	res[i] = '\0';
	mods->width = ft_atoi(res);
	return (format);
}
