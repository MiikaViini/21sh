/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:12:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	res;

	dest_len = ft_strlen((char *)dest);
	src_len = ft_strlen((char *)src);
	res = dest_len + src_len;
	if (size <= dest_len && size <= res)
		res = src_len + size;
	while (*src && (dest_len + 1) < size)
		dest[dest_len++] = *src++;
	dest[dest_len] = '\0';
	return (res);
}
