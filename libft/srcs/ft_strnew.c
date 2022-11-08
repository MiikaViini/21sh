/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:42:33 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/08 11:40:53 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/libft.h"

char	*ft_strnew(size_t size)
{
	char	*fresh;
	int		i;

	i = 0;
	fresh = (char *)ft_memalloc(sizeof(char) * size + 1);
	while (size--)
	{
		fresh[i] = '\0';
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
