/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 09:39:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/libft.h"

static size_t	ft_lenint(int n)
{
	unsigned char	len;

	len = 1;
	if (n < 0)
	{
		if (n == -2147483648)
			n = n + 1;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static	int	ft_isminus(int n)
{
	if (n >= 0)
		return (0);
	else
		return (1);
}

static	int	ft_remsign(int n)
{
	if (n <= 0)
		return (n * -1);
	return (n);
}

static	int	ft_ismin(int n)
{
	if (n == -2147483648)
		n = n + 1;
	return (n);
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	i;
	int		t;

	t = n;
	n = ft_ismin(n);
	n = ft_remsign(n);
	i = 0;
	num = ft_strnew(ft_lenint(t) + 1);
	if (!num)
		exit(1);
	if (n == 0)
		num[i++] = '0';
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n = n / 10;
	}
	if (t == -2147483648)
		*num = *num + 1;
	if (ft_isminus(t) == 1)
		num[i++] = '-';
	num[i] = '\0';
	return (ft_strrev(num));
}
