/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:18:27 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/09 21:25:17 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*l_length(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format == 'l')
	{
		mods->l += 1;
		format++;
	}
	return (format);
}

char	*h_length(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format == 'h')
	{
		mods->h += 1;
		format++;
	}
	return (format);
}

char	*ld_length(va_list args, char *format, t_modifiers *mods)
{
	(void)args;
	if (*format == 'L')
	{
		mods->ld = 1;
		format++;
	}
	return (format);
}

char	*type_cast(unsigned long long int num, t_modifiers *mods, int base)
{
	char	*string;

	string = NULL;
	if (mods->h == 1 && !mods->cap_u)
		string = ft_itoabase((unsigned short)num, base, mods->capital);
	else if (mods->h == 2)
		string = ft_itoabase((unsigned char)num, base, mods->capital);
	else if (mods->l == 1)
		string = ft_itoabase((unsigned long)num, base, mods->capital);
	else if (mods->l == 2 || mods->j || mods->cap_u || mods->z)
		string = ft_itoabase((unsigned long long)num, base, mods->capital);
	else
		string = ft_itoabase((unsigned int)num, base, mods->capital);
	return (string);
}

char	*type_cast_int(long long int num, t_modifiers *mods)
{
	char	*string;

	string = NULL;
	if (mods->h == 1 && !mods->z && !mods->j)
		string = ft_itoa((short)num);
	else if (mods->h == 2 && !mods->l && !mods->z && !mods->j)
		string = ft_itoa((char)num);
	else if (mods->l == 1 || mods->z)
		string = ft_ltoa((long)num);
	else if (mods->l == 2 || mods->j)
		string = ft_ltoa((long long)num);
	else
		string = ft_ltoa((int)num);
	return (string);
}
