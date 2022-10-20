/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linecount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:41:32 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_linecount(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}
