/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:50:02 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 17:05:07 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

ssize_t	row_lowest_line(t_term *t)
{
	ssize_t	row;

	row = t->c_row;
	while (t->nl_addr[row + 1] && !is_prompt_line(t, row + 1))
		row++;
	return (row);
}

ssize_t	len_lowest_line(t_term *t, ssize_t row)
{
	ssize_t	len;

	if (t->nl_addr[row + 1])
		len = t->nl_addr[row + 1] - t->nl_addr[row] - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	len += get_prompt_len(t, row);
	return (len);
}
