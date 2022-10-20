/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:32:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	**ft_strarrcpy(char **dest, char **strarr)
{
	int	i;

	i = -1;
	if (!strarr)
		return (NULL);
	while (strarr[++i])
		dest[i] = strarr[i];
	return (dest);
}
