/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrndup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:34:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	**ft_strarrndup(char **dest, char **strarr, size_t size)
{
	int	i;

	i = -1;
	if (!strarr)
		return (NULL);
	size += ft_linecount(strarr) + 1;
	dest = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	while (strarr[++i])
		dest[i] = ft_strdup(strarr[i]);
	dest[i] = NULL;
	return (dest);
}
