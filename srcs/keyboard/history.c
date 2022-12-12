/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:45:45 by spuustin          #+#    #+#             */
/*   Updated: 2022/11/21 23:15:47 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// reads history from a file, and stores it into t->history array
// our history supports up to 100 lines of command-line calls
void	get_history(t_term *t)
{
	char	*source = "/";
	int		fd;

	t->history = (char **)malloc(sizeof(char *) * 101);
	ft_bzero(t->history, 101);
	fd = open(source, O_RDONLY | O_CREAT, 420);
	if (fd)
	{
		; //probably have to gnl here :(
	}
}
