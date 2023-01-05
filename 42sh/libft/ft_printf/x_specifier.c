/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:33:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/08 13:10:21 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	x_prep_mods(t_modifiers *mods)
{
	mods->plus = 0;
	if (mods->minus || (mods->dot && mods->hash))
		mods->zero = 0;
	if (mods->width && mods->zero)
		mods->width = mods->width - (mods->hash * 2);
}

char	*treat_zerox(char *string, t_modifiers *mods, long long num)
{
	char	*res;
	char	*temp;

	temp = ft_strdup(string);
	res = NULL;
	if ((mods->hash == 1 && mods->capital == 1 && num)
		|| (mods->minus && mods->hash == 1 && num && mods->capital == 1))
	{
		res = ft_strjoin("0x", temp);
		mods->hash = 0;
	}
	else if ((mods->hash == 1 && num)
		|| (mods->minus && mods->hash == 1 && num))
	{
		res = ft_strjoin("0X", temp);
		mods->hash = 0;
	}
	else
		res = ft_strdup(temp);
	ft_strdel(&temp);
	return (res);
}

int	x_specifier(va_list args, t_modifiers *mods)
{
	unsigned long long		num;
	char					*string;
	char					*output;
	int						count;

	x_prep_mods(mods);
	num = va_arg(args, unsigned long long );
	string = type_cast(num, mods, 16);
	output = treat_precis(string, mods, ft_strlen(string), num);
	ft_strdel(&string);
	if (mods->precision || (mods->precision == 0 && mods->width && !mods->zero))
		string = treat_zerox(output, mods, num);
	else
		string = ft_strdup(output);
	ft_strdel(&output);
	output = treat_width(string, mods, ft_strlen(string));
	ft_strdel(&string);
	string = check_edges(mods, output, num);
	ft_strdel(&output);
	output = treat_zerox(string, mods, num);
	count = ft_putstrlen(output);
	ft_strdel(&string);
	ft_strdel(&output);
	return (count);
}
