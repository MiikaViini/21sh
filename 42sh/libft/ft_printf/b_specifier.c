/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:00:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/29 09:05:37 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_mods(t_modifiers *mods)
{
	mods->zero = 0;
	mods->precision = 0;
	mods->hash = 0;
}

static long long	set_num(va_list args, t_modifiers *mods, long long num)
{
	if (mods->l == 2)
		num = va_arg(args, long long);
	else if (mods->l == 1)
		num = va_arg(args, long);
	else if (mods->h == 1)
		num = va_arg(args, int);
	else if (mods->h == 2)
		num = va_arg(args, int);
	else
		num = va_arg(args, int);
	return (num);
}

int	b_specifier(va_list args, t_modifiers *mods)
{
	char		*str;
	char		*temp;
	int			count;
	long long	num;

	set_mods(mods);
	count = 0;
	num = 0;
	num = set_num(args, mods, num);
	str = ft_dectobin(num);
	if (str[0] == '-')
		temp = ft_strjoin("-0b", str + 1);
	else
		temp = ft_strjoin("0b", str);
	ft_strdel(&str);
	str = treat_mods(temp, mods, ft_strlen(temp), num);
	count = ft_putstrlen(str);
	ft_strdel(&temp);
	ft_strdel(&str);
	return (count);
}
