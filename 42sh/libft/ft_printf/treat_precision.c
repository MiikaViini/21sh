/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:29:50 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/08 13:08:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*treat_sign(char *str, char *res, t_modifiers *mods, long long num)
{
	char	*temp;

	temp = NULL;
	if ((mods->plus && num >= 0 && !mods->zero)
		|| (mods->plus && num <= 0 && !mods->zero && *str == '0'))
	{
		temp = ft_strjoin("+", res);
		ft_strdel(&res);
		res = ft_strdup(temp);
		ft_strdel(&temp);
		mods->plus--;
	}
	else if (mods->sign && *str != '-' && !mods->f_zero)
	{
		temp = ft_strjoin("-", res);
		ft_strdel(&res);
		res = ft_strdup(temp);
		ft_strdel(&temp);
	}
	return (res);
}

char	*treat_precis(char *str, t_modifiers *mods, int len, long long num)
{
	char	*res;
	int		i;
	int		count;
	char	*temp;

	i = 0;
	count = mods->precision;
	temp = ft_strdup(str);
	if (!mods->precision && !mods->plus)
		return (temp);
	res = ft_strnew(mods->precision + 1);
	while (len + mods->sign < count-- + mods->sign)
		res[i++] = '0';
	res = treat_sign(str, res, mods, num);
	str = ft_strjoin(res, temp);
	ft_strdel(&res);
	res = ft_strdup(str);
	ft_strdel(&temp);
	ft_strdel(&str);
	return (res);
}
