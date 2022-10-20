/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:48:27 by mviinika          #+#    #+#             */
/*   Updated: 2022/03/22 10:07:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*minus(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format++ == '-')
		mods->minus = 1;
	return (format);
}

char	*plus(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format++ == '+')
		mods->plus = 1;
	return (format);
}

char	*zero(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format++ == '0')
		mods->zero = 1;
	return (format);
}

char	*space(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format++ == ' ')
		mods->space = 1;
	return (format);
}

char	*hashtag(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format++ == '#')
		mods->hash = 1;
	return (format);
}
