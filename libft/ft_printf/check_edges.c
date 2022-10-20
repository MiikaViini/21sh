/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edges.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:12:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/09 18:58:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_edges(t_modifiers *mods, char *format, long long num)
{
	char	*temp;
	int		i;

	i = -1;
	if ((!mods->o_zero && mods->dot && mods->precision == 0
			&& num == 0 && !mods->width)
		|| (!mods->o_zero && mods->dot && mods->precision == 0
			&& num < 0 && !mods->width && !mods->d_space && *format == '0'))
		temp = ft_strnew(1);
	else if ((mods->o_zero && !mods->precision && !num)
		|| (!mods->width && mods->dot && mods->precision == 0 && !num))
		temp = ft_strdup("0");
	else if (mods->dot && mods->precision == 0 && num == 0)
	{
		while (format[++i])
			if (ft_isdigit(format[i]))
				format[i] = ' ';
		if (mods->d_space && mods->width <= 1)
			temp = ft_strdup(format + mods->space);
		else
			temp = ft_strdup(format);
	}
	else
		temp = ft_strdup(format);
	return (temp);
}

char	*check_infinity(double num, t_modifiers *mods)
{
	double	posinf;
	double	neginf;
	char	*res;
	int		i;

	i = 0;
	res = ft_strnew(4);
	if (!res)
		return (NULL);
	posinf = 1.0 / 0;
	neginf = -1.0 / 0;
	if (num == posinf && !mods->plus && !mods->space)
		res = ft_strcpy(res, "inf");
	else if (num == posinf && mods->plus)
		res = ft_strcpy(res, "+inf");
	else if (num == posinf && mods->space)
		res = ft_strcpy(res, " inf");
	else if (num == neginf)
		res = ft_strcpy(res, "-inf");
	else if ((long double)num != (long double)num)
		res = ft_strcpy(res, "nan");
	return (res);
}
