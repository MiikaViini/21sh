/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:46:16 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	int	ft_iswhitespace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

static size_t	ft_returnindex(const char *s)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(*s) == 1)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strtrim(char const *s)
{
	char	*trimmed;
	size_t	i;
	size_t	k;
	size_t	j;

	i = ft_returnindex(s);
	k = ft_strlen((char *)s);
	j = 0;
	while (ft_iswhitespace(s[k - 1]) == 1 && k - i != 0)
		k--;
	trimmed = (char *)malloc(sizeof(char) * (k - i + 1));
	if (!trimmed)
		exit(1);
	while (i < k)
		trimmed[j++] = s[i++];
	trimmed[j] = '\0';
	return (trimmed);
}
