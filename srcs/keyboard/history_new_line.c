/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_new_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:08:59 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/21 22:20:18 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
	this could be replaced with memmove to add effeciency.
	that said this is rarely called.
*/

static void	add_to_capped_history(t_term *t, char *command)
{
	char	**temp;
	int		i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (MAX_HISTORY + 1));
	if (!temp)
		exit(1);
	while (t->history[i + 1])
	{
		temp[i] = ft_strdup(t->history[i + 1]);
		i++;
	}
	temp[i] = ft_strdup(command);
	i++;
	temp[i] = NULL;
	ft_free_array(t->history);
	t->history = temp;
}

void	add_command_to_history(t_term *t, char *command)
{
	if (t->history_size <= MAX_HISTORY)
	{
		// for now we assume t->history is always size 1024
		t->history[t->history_size] = ft_strdup(command);
		t->history_size++;
		t->history[t->history_size] = NULL;
	}
	else
		add_to_capped_history(t, command);
}
