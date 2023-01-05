/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:00:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static long	ft_bitsign(long res)
{
	return (res >> 63);
}

static char	ft_decimalsign(long res)
{
	return ((char)(ft_bitsign(res) | 0x1));
}

static void	ft_sign(const char **str, char *sign)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	while (**str == '0')
		(*str)++;
}

int	ft_atoi(const char *str)
{
	long	res;
	char	sign;

	res = 0;
	sign = 1;
	ft_sign(&str, &sign);
	if (ft_isdigit(*str))
		res = sign * (*str++ - '0');
	while (ft_isdigit(*str))
	{
		res = 10 * res + sign * (*str++ - '0');
		if (ft_decimalsign(res) != sign)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return ((int)res);
}
