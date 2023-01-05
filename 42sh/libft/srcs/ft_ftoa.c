/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:07:21 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

void	rounding(char *str, int index)
{
	if (str[index] == '.')
		rounding(str, index - 1);
	if (str[index] + 1 > '0' && str[index] + 1 <= '9')
		str[index] += 1;
	else if (str[index] == '9')
	{
		str[index] = '0';
		rounding(str, index - 1);
	}
}

static long double	fract_part(long double fract, int apoint, char *afterdot)
{
	int	remain;
	int	i;

	i = 1;
	remain = 0;
	while (apoint-- > 0)
	{
		fract = (long double)fract * 10.0;
		remain = (unsigned long long)fract;
		afterdot[i++] = remain + '0';
		fract = fract - (long double)remain;
	}
	return (fract);
}

static char	*rded_fracts(long double fract, int ap, char *afdot, char **integer)
{
	char	*num;
	int		int_i;
	char	*temp;

	int_i = 0;
	fract = fract_part(fract, ap, afdot);
	if (((*integer[int_i] == '9' && afdot[1] >= '5' ) && !ap)
		|| (*integer[int_i] == '9' && ap <= 1 && fract >= 0.5))
		temp = ft_strjoin("0", *integer);
	else
		temp = ft_strdup(*integer);
	num = ft_strjoin(temp, afdot);
	ft_strdel(&temp);
	if (1.0 - fract < 0 + fract || (1.0 - fract == 0 + fract
			&& (num[ft_strlen(num) - 1] + 1 - '0') % 2 == 0))
	{
		rounding(num, ft_strlen(num) - 1);
	}
	return (num);
}

static char	*toarr(long double fract, unsigned long long inte, int ap, int sign)
{
	char	*integer;
	char	*fractions;
	int		i;
	char	*output;

	i = 0;
	integer = ft_ltoa(inte);
	if (ap > 6)
		fractions = ft_strnew(ap + 2);
	else
		fractions = ft_strnew(6 + 2);
	if (ap > 0)
		fractions[i++] = '.';
	output = rded_fracts(fract, ap, fractions, &integer);
	ft_strdel(&integer);
	if (sign && fractions[0] != '-')
		integer = ft_strjoin("-", output);
	else
		integer = ft_strdup(output);
	ft_strdel(&output);
	ft_strdel(&fractions);
	return (integer);
}

char	*ft_ftoa(long double num, int afterpoint)
{
	unsigned long long	l_dot;
	long double			r_dot;
	char				*res;
	int					sign;

	sign = 0;
	if (num < 0 || 1 / num < 0)
	{
		num = num * -1;
		sign = 1;
	}
	l_dot = (unsigned long long)num;
	r_dot = num - (long double)l_dot;
	res = toarr(r_dot, l_dot, afterpoint, sign);
	return (res);
}
