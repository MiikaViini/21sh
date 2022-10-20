/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:49:11 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	intlen(unsigned long long n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n > 0 && len++)
		n = n / 10;
	return (len);
}

unsigned long long	treat_minus(long long n)
{
	unsigned long	temp;

	temp = 0;
	n = ~n;
	temp += (unsigned long)n + 1;
	return (temp);
}

char	*ft_ltoa(long long n)
{
	char			*res;
	size_t			len;
	unsigned long	temp;

	if (n < 0)
		temp = treat_minus(n);
	else
		temp = (unsigned long)n;
	len = intlen(temp);
	res = ft_strnew(len + 1);
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	if (n < 0)
		res[0] = '-';
	else
		len--;
	while (temp && len--)
	{
		res[len] = (temp % 10) + '0';
		temp /= 10;
	}
	return (res);
}
