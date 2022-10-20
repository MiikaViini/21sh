/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:23:53 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;

	fresh = (t_list *)malloc(sizeof(t_list));
	if (!fresh)
	{
		return (NULL);
	}
	if (content == NULL)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
		fresh->next = NULL;
		return (fresh);
	}
	fresh->content = malloc(content_size);
	if (!fresh->content)
	{
		free(fresh);
		return (NULL);
	}
	ft_memcpy(fresh->content, content, content_size);
	fresh->content_size = content_size;
	fresh->next = NULL;
	return (fresh);
}
