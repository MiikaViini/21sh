/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectobin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:48:10 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static unsigned long long	treat_minus(long long num, int *sign)
{
	unsigned long long	res;

	if (num == -9223372036854775807 - 1)
	{
		num++;
		res = (num * -1) + 1;
	}
	else
		res = num * -1;
	*sign = 1;
	return (res);
}

char	*ft_dectobin(long long num)
{
	char				*bin;
	size_t				i;
	unsigned long long	res;
	int					sign;

	i = 0;
	bin = ft_strnew(64);
	bin[0] = '0';
	sign = 0;
	if (num < 0)
		res = treat_minus(num, &sign);
	else
		res = num;
	while (res)
	{
		bin[i++] = (res % 2) + '0';
		res /= 2;
	}
	if (sign)
		bin[i] = '-';
	return (ft_strrev(bin));
}
