/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:58:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 11:58:22 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	tokens_del(t_tlist **tokens)
{
	t_tlist	*temp;
	t_tlist	*list;

	list = *tokens;
	while (list != NULL)
	{
		temp = list->next;
		if (list->str)
			ft_strdel(&list->str);
		if (list->file)
			ft_strdel(&list->file);
		free(list);
		list = temp;
	}
	*tokens = NULL;
}