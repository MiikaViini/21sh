/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:16:25 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/10 11:37:45 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	neg_mods(t_modifiers *mods)
{
	mods->sign = 1;
	mods->plus = 0;
	if (mods->width && mods->dot && !mods->precision)
		mods->width--;
	mods->d_space = 0;
	if ((mods->zero && mods->width && !mods->minus && !mods->dot)
		|| mods->precision)
	{
		mods->d_zerominus++;
		mods->width--;
	}
}

static void	prep_mods(t_modifiers *mods)
{
	mods->d_space = mods->space - mods->plus;
	if (mods->precision < 0)
	{
		mods->precision = 0;
		mods->dot = 0;
	}
	if (mods->minus)
		mods->zero = 0;
	if (mods->d_space == 1 && mods->zero && !mods->precision && !mods->dot)
		mods->width--;
}

int	d_specifier(va_list args, t_modifiers *mods)
{
	long long		num;
	int				count;
	char			*string;
	char			*output;

	prep_mods(mods);
	num = va_arg(args, long long );
	string = type_cast_int(num, mods);
	if (string[0] == '-')
		neg_mods(mods);
	output = check_edges(mods, string, num);
	ft_strdel(&string);
	string = treat_mods(output + mods->d_zerominus,
			mods, ft_strlen(output) - mods->d_zerominus, num);
	ft_strdel(&output);
	count = ft_putstrlen(string);
	ft_strdel(&string);
	ft_strdel(&output);
	return (count);
}
