/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:06:29 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/20 14:52:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_letter(char c, char *letters)
{
	int	index;

	index = 0;
	while (letters[index])
	{
		if (letters[index] == c)
			return (index);
		index++;
	}
	return (index);
}

char	*check_modifiers(char *format, t_modifiers *mods, va_list args)
{
	while (!ft_strrchr(CONV, *format))
	{
		format = width(args, format, mods);
		format = g_mods[find_letter(*format, MODS)](args, format, mods);
	}
	if (*format == 'x' || *format == 'U')
		mods->capital = 1;
	return (format);
}

int	conversion(va_list args, char *format)
{
	int			ch_count;
	t_modifiers	*modifiers;

	ch_count = 0;
	modifiers = ft_memalloc(sizeof(t_modifiers));
	if (!modifiers)
		return (-1);
	while (*format)
	{
		while (*format == '%')
		{
			format++;
			format = check_modifiers(format, modifiers, args);
			ch_count += g_specif[find_letter(*format++, CONV)](args, modifiers);
			modifiers = init_struct(modifiers);
		}
		if (!*format)
			break ;
		ft_putchar(*format);
		format++;
		ch_count++;
	}
	free(modifiers);
	return (ch_count);
}

int	ft_printf(char *format, ...)
{
	va_list	list;
	int		count;
	char	*temp;

	temp = ft_strdup(format);
	count = 0;
	if (!temp)
		return (-1);
	va_start(list, format);
	count += conversion(list, temp);
	va_end(list);
	ft_strdel(&temp);
	return (count);
}
