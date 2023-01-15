/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_new_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:08:59 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 16:22:30 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_history_reset_nl(t_term *t, char *inp)
{
	ssize_t	i;
	ssize_t	col;
	ssize_t	row;

	i = -1;
	col = 0;
	row = t->c_row;
	while (inp[++i])
	{
		col++;
		if (((col + ft_get_prompt_len(t, row))) == t->ws_col || inp[i] == '\n')
		{
			row++;
			col = 0;
			t->total_row++;
			ft_add_nl_last_row(t, inp, i + 1);
		}
	}
	t->bytes = &inp[i] - t->nl_addr[0];
	t->index = t->bytes;
}

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

/*
	memmove possible
*/

static void	increase_history_size(t_term *t)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (t->history_size + 2));
	if (!temp)
		exit(1);
	i = 0;
	while (t->history[i])
	{
		temp[i] = ft_strdup(t->history[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_array(t->history);
	t->history = temp;
}

void	add_command_to_history(t_term *t, char *command)
{
	if (t->history_size < MAX_HISTORY)
	{
		increase_history_size(t);
		t->history[t->history_size] = ft_strdup(command);
		t->history_size++;
		t->history[t->history_size] = NULL;
	}
	else
		add_to_capped_history(t, command);
}
