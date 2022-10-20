/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_with_mods.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:04:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/08 13:22:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*apply_space(t_modifiers *mods, char *str)
{
	char	*output;

	if (mods->d_space > 0 && mods->zero)
	{
		if (*str != ' ')
			output = ft_strjoin(" ", str);
		else
			output = ft_strdup(str);
	}
	else
		output = ft_strdup(str);
	return (output);
}

char	*apply_sign(char *string, t_modifiers *mods, long long num)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup(string);
	if (num >= 0 && *string != ' ' && *string != '+' && mods->plus)
	{
		ft_strdel(&res);
		res = ft_strjoin("+", string);
	}
	else if ((mods->sign && *string == '0')
		|| (mods->width <= (int)ft_strlen(string) && mods->sign
			&& *string != '-' && *string != ' '))
	{
		ft_strdel(&res);
		res = ft_strjoin("-", string);
	}
	return (res);
}

char	*treat_mods(char *str, t_modifiers *mods, int count, long long num)
{
	char	*res;
	char	*temp;

	res = ft_strdup(str);
	temp = treat_precis(res, mods, ft_strlen(res), num);
	ft_strdel(&res);
	if (mods->d_space > 0 && !mods->zero)
	{
		res = ft_strjoin(" ", temp);
		ft_strdel(&temp);
		temp = ft_strdup(res);
		ft_strdel(&res);
	}
	if (count < mods->width + mods->sign)
	{
		res = treat_width(temp, mods, ft_strlen(temp));
		ft_strdel(&temp);
		temp = ft_strdup(res);
		ft_strdel(&res);
	}
	res = apply_space(mods, temp);
	ft_strdel(&temp);
	temp = apply_sign(res, mods, num);
	ft_strdel(&res);
	return (temp);
}
