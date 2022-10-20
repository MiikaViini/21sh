/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:30:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_over_sixteen(unsigned long long int num, int base, int flag)
{
	char	*res;
	int		remainder;
	int		i;

	remainder = 0;
	res = ft_strnew(20);
	i = 0;
	while (num)
	{
		remainder = num % base;
		if (remainder > 9)
			res[i++] = 'A' + (remainder - 10) + (CAPITAL * flag);
		else
			res[i++] = remainder + '0';
		num /= base;
	}
	return (ft_strrev(res));
}

char	*ft_itoabase(unsigned long long int num, int base, int flag)
{
	int						i;
	char					*res;

	res = ft_strnew(24);
	i = 0;
	res[0] = '0';
	if (num == 0)
		return (res);
	if (base > 15)
	{
		ft_strdel(&res);
		return (ft_over_sixteen(num, base, flag));
	}
	while (num)
	{
		res[i++] = (num % base) + '0';
		num /= base;
	}
	return (ft_strrev(res));
}
