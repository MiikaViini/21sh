/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:43:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/libft.h"

char	*ft_strndup(const char *s, size_t size)
{
	char	*str;
	int		i;
	size_t	str_len;

	i = 0;
	str_len = ft_strlen((char *)s);
	if (str_len > size)
		str = (char *)malloc(sizeof(char) * (size + 1));
	else
		str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		exit(1);
	while (s[i] && size--)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
