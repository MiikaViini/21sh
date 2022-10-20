/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:06:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 13:25:37 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	intlen(unsigned long long n)
{
	int	len;

	len = 1;
	while (n > 0 && len++)
		n = n / 10;
	return (len);
}

char	*ft_utoa(unsigned long long n)
{
	char				*res;
	size_t				len;

	len = intlen(n);
	res = ft_strnew(len);
	len--;
	while (n && len--)
	{
		res[len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
