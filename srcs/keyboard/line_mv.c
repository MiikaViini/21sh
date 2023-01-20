/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_mv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:48:34 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/20 12:51:15 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static ssize_t	delim_row(t_term *t)
{
	ssize_t	delim_row;

	delim_row = 0;
	while (delim_row < t->total_row && (!delim_row
			|| !is_prompt_line(t, delim_row)))
		delim_row++;
	return (delim_row);
}

void	line_mv(t_term *t)
{
	t->ch = get_input();
	if (t->ch == ';')
	{
		t->ch = get_input();
		if (t->ch == '3')
		{
			t->ch = get_input();
			{
				if (t->ch == ARROW_UP && t->c_row && (!t->heredoc \
				|| t->c_row > delim_row(t)))
					line_up(t);
			}
			if (t->ch == ARROW_DOWN && t->c_row < t->total_row)
				line_down(t);
			t->ch = 0;
		}
	}
}
