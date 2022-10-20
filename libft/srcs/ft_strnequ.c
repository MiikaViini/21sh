/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:39:19 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if ((!*s1 && !*s2) || n <= 0)
		return (1);
	while (n--)
	{
		if (*s1 != *s2)
			return (0);
		if (n <= 0)
			return (1);
		s1++;
		s2++;
	}
	return (1);
}
