/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:52:56 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/07 14:53:13 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_tlist	*new_token(char *content, t_word *word_attrs)
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
	fresh->type = word_attrs->type;
	fresh->redir_type = word_attrs->redir;
	fresh->file = word_attrs->file;
	fresh->next = NULL;
	return (fresh);
}