/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:50:02 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/11 20:44:21 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

ssize_t	ft_row_lowest_line(t_term *t)
{
	ssize_t	row;

	row = t->c_row;
	while (t->nl_addr[row + 1] && !ft_is_prompt_line(t, row + 1))
		row++;
	return (row);
}

// ssize_t	ft_len_lowest_line(t_term *t, ssize_t row)
// {
// 	ssize_t	len;

// 	if (t->nl_addr[row + 1])
// 		len = t->nl_addr[row + 1] - t->nl_addr[row];
// 	else
// 		len = &t->inp[t->bytes] - t->nl_addr[row];
// 	if (ft_is_prompt_line(t, row))
// 	{
// 		if (!row)
// 			len += t->prompt_len;
// 		else
// 			len += t->m_prompt_len;
// 	}
// 	return (len);
// }

ssize_t	ft_len_lowest_line(t_term *t, ssize_t row)
{
	ssize_t	len;

	if (t->nl_addr[row + 1])
		len = t->nl_addr[row + 1] - t->nl_addr[row] - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	len += ft_get_prompt_len(t, row);
	return (len);
}
