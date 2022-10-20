/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount_ws.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:15:19 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_wordcount_ws(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((!ft_isspace(s[i]) && ft_isspace(s[i + 1]))
			|| (!ft_isspace(s[i]) && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}
