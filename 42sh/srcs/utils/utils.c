/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:33:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/22 12:06:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

size_t	ft_linecount(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void	free_strarr(char **strarr)
{
	int	i;

	i = 0;
	if (!strarr && !strarr[i])
		return ;
	while (strarr[i] && strarr[i][0])
		ft_strdel(&strarr[i++]);
	free(strarr);
}

int	is_single_quote(char c)
{
	return (c == '\'');
}

int	is_double_quote(char c)
{
	return (c == '"');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
