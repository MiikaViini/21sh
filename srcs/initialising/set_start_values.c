/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:46:48 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/04 15:55:28 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	set_start_values(t_ast ***tree, char *buf, int *rb)
{
	*rb = 1;
	(*tree) = NULL;
	*rb = read(0, buf, MAX_LINE);
}
