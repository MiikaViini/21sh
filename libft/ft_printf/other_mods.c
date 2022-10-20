/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_mods.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:49:48 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/04 12:55:30 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*j_flag(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format++ == 'j')
		mods->j = 1;
	return (format);
}

char	*z_flag(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format++ == 'z')
		mods->z = 1;
	return (format);
}

char	*do_nothing(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	(void)mods;
	if (!ft_strrchr(CONV, *format))
		format++;
	return (format);
}

int	do_nothing_conv(va_list args, t_modifiers *mods)
{
	(void)args;
	(void)mods;
	return (0);
}
