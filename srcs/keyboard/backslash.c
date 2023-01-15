/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:39:53 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 17:09:22 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	backslash_escape_check(t_term *t, ssize_t pos)
{
	ssize_t	start;
	ssize_t	count;

	if (!pos)
		return (0);
	start = pos - 1;
	while (start && t->inp[start] == '\\')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->inp[count] == '\\')
		count++;
	if ((count - start) % 2)
		return (1);
	return (0);
}
