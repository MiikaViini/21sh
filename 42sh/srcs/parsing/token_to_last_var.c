/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_last_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:27:13 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/09 10:31:16 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	token_to_last_var(t_vars **alst, t_vars *new)
{
	t_vars	*temp;

	temp = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			temp->next = new;
			break ;
		}
		temp = temp->next;
	}
}
