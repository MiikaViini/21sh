/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:10:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/09 19:00:04 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*treat_minus(char *str, char *pad, t_modifiers *mods)
{
	char	*res;

	if (mods->minus == 1)
		res = ft_strjoin(str, pad);
	else
		res = ft_strjoin(pad, str);
	return (res);
}

char	*treat_width(char *str, t_modifiers *mods, int len)
{
	char	*temp;
	char	*res;
	int		i;
	int		count;
	char	c;

	c = ' ';
	count = mods->width - len + (mods->dot * mods->sign);
	i = 0;
	res = ft_strdup(str);
	if (mods->width == 0 || count < 0)
		return (res);
	ft_strdel(&res);
	temp = ft_strnew(count);
	if ((mods->zero == 1 && mods->minus == 0 && !mods->dot)
		|| (mods->zero == 1 && mods->minus == 0 && mods->f_zero))
		c = '0';
	while (count-- > 0 && i < mods->width - (int)ft_strlen(str)
		- (mods->zero * mods->plus - mods->sign))
		temp[i++] = c;
	res = treat_minus(str, temp, mods);
	ft_strdel(&temp);
	return (res);
}
