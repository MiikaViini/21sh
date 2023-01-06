/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:33:54 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/06 12:47:19 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_vars	*new_variable(char *content)
{
	t_vars *new;
	
	new = (t_vars *)ft_memalloc(sizeof(t_vars));
	new->next = NULL;
	if (content == NULL)
	{
		new->var = NULL;
		return (new);
	}
	new->var = ft_strdup(content);
	return (new);
}