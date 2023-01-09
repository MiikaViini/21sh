/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:48:03 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/09 10:26:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	token_to_last(t_tlist **alst, t_tlist *new)
{
	t_tlist	*temp;

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
