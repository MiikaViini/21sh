/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:29:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 15:28:57 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	init_tree(t_ast ***tree, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		(*tree)[i]->type = 0;
		(*tree)[i]->cmd = NULL;
		(*tree)[i]->file = NULL;
		(*tree)[i]->redir_type = -1;
		(*tree)[i]->to_fd = 0;
		(*tree)[i]->err_fd = 0;
		(*tree)[i]->fd_close = 0;
		i++;
	}
}
