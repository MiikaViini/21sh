/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:34:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;
	size_t	i;
	size_t	k;

	len = ft_strlen((char *)needle);
	i = 0;
	k = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		while (needle[k] == haystack[i + k])
		{
			if (k == len - 1)
				return ((char *)haystack + i);
			k++;
		}
		k = 0;
		i++;
	}
	return (NULL);
}
