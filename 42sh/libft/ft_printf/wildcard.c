/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:46:14 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/04 12:53:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*star(va_list args, char *format, t_modifiers *mods)
{
	if (*format++ == '*' && !mods->dot)
		mods->width = va_arg(args, long long);
	if (mods->star || mods->dot)
		mods->precision = va_arg(args, long long);
	if (mods->width < 0)
	{
		mods->width = ft_abs(mods->width);
		mods->minus = 1;
	}
	return (format);
}
