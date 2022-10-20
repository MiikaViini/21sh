/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:47:44 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*str = *(unsigned char *)src;
		if (*str == (unsigned char)c)
			return (str + 1);
		str++;
		src++;
	}
	return (NULL);
}
