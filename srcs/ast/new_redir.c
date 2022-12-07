/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:49:48 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/07 14:52:09 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_tlist	*new_redir(char *content, char *file, int from, int redir_type)
{
	t_tlist	*fresh;

	fresh = (t_tlist *)ft_memalloc(sizeof(t_tlist));
	if (content == NULL)
	{
		fresh->str = NULL;
		fresh->type = 0;
		fresh->next = NULL;
		return (fresh);
	}
	fresh->str = ft_strdup(content);
	fresh->redir_type = redir_type;
	fresh->file = file;
	fresh->from_fd = from;
	fresh->next = NULL;
	return (fresh);
}