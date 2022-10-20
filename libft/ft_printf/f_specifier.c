/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:29:41 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/08 13:11:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	f_neg_mods(t_modifiers *mods)
{
	mods->sign = 1;
	mods->plus = 0;
	mods->width--;
	if (mods->width && !mods->dot && !mods->zero)
		mods->width++;
	if ((mods->zero == 1 && mods->width && mods->f_prec)
		|| (mods->zero == 1 && mods->dot && !mods->f_prec))
		mods->width--;
	mods->d_space = 0;
	if ((mods->zero && mods->width > 0 && !mods->minus)
		|| (mods->dot && mods->f_prec > 0))
		mods->d_zerominus++;
	if (mods->width < 0)
		mods->width = 0;
}

static void	f_prep_mods(t_modifiers *mods, char *string, long double num)
{
	if (mods->minus)
		mods->zero = 0;
	if (*string == '-')
		f_neg_mods(mods);
	if (mods->zero)
		mods->f_zero++;
	if (mods->space && !mods->plus && 1 / num > 0)
	{
		mods->d_space = 1;
		if (mods->precision)
			mods->precision--;
		if ((int)ft_strlen(string) < mods->width && mods->zero)
			mods->width = mods->width - mods->space;
	}
}

static int	inf_nan(char *str, t_modifiers *mods, int count, long double num)
{
	char	*output;

	ft_strdel(&str);
	if (mods->hash && mods->f_prec && mods->sign)
		mods->width++;
	mods->dot = 0;
	mods->zero = 0;
	if (num == -1.0 / 0 && mods->width++)
		mods->sign++;
	str = check_infinity(num, mods);
	output = treat_width(str, mods, ft_strlen(str));
	count = ft_putstrlen(output);
	ft_strdel(&str);
	ft_strdel(&output);
	return (count);
}

static void	f_prec_prep(t_modifiers *mods)
{
	mods->f_prec = mods->precision;
	if (!mods->dot && mods->precision == 0)
		mods->precision = 6;
	if (mods->dot && !mods->hash && !mods->precision)
		mods->precision = -1;
}

int	f_specifier(va_list args, t_modifiers *mods)
{
	long double		num;
	char			*string;
	int				count;
	char			*output;

	if (mods->ld == 1)
		num = (long double)va_arg(args, long double );
	else
		num = (double)va_arg(args, double );
	count = 0;
	f_prec_prep(mods);
	string = ft_ftoa(num, mods->precision);
	f_prep_mods(mods, string, num);
	if (num == 1.0 / 0 || num == -1.0 / 0 || num != num)
		return (inf_nan(string, mods, count, (long double)num));
	if (mods->dot && mods->hash && !mods->f_prec)
		output = ft_strjoin(string + mods->d_zerominus, ".");
	else
		output = ft_strdup(string + mods->d_zerominus);
	ft_strdel(&string);
	string = treat_mods(output, mods, ft_strlen(output), num);
	count = ft_putstrlen(string);
	ft_strdel(&string);
	ft_strdel(&output);
	return (count);
}
