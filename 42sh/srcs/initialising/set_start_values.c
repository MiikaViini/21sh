/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:46:48 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/20 13:15:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	set_start_values(t_ast ***tree, char *buf, int *rb)
{
	*rb = 1;
	ft_memset(buf, '\0', MAX_LINE + 1);
	(*tree) = NULL;
	*rb = read(0, buf, MAX_LINE);
}
