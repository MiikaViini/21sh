/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:19:15 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/08 19:56:30 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
void	ft_deletion_shift(t_term *t, int mode)
{
	ssize_t	index_cpy;

	if (mode == BCK)
		t->index--;
	index_cpy = t->index;
	t->inp[index_cpy] = '\0';
	while (&t->inp[index_cpy] < &t->inp[t->bytes])
	{
		t->inp[index_cpy] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		t->inp[index_cpy + 1] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		t->inp[index_cpy] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		index_cpy++;
	}
	t->bytes--;
}

void	ft_delete(t_term *t)
{
	ssize_t	len;
	ssize_t	row;

	row = ft_row_lowest_line(t);
	if (t->nl_addr[row + 1] && (&t->inp[t->index + 1] \
		== t->nl_addr[t->c_row + 1] && ft_is_prompt_line(t, t->c_row + 1)))
		return ;
	if (t->nl_addr[row + 1])
		len = (t->nl_addr[row + 1] - t->nl_addr[row]) - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	update_nl_addr_del(t);
	ft_deletion_shift(t, t->index);
	run_capability("ce");
	if (!len)
	{
		ft_remove_nl_addr(t, row);
		t->total_row--;
	}
	if (t->inp[t->index])
		ft_print_trail(t);
}

void	ft_create_prompt_line(t_term *t, ssize_t loc)
{
	int		row;

	row = get_linenbr();
	t->c_row++;
	t->total_row++;
	if (row == (t->ws_row - 1))
		run_capability("sf");
	else
		row++;
	set_cursor(0, row);
	t->c_col = write(1, OPEN_QUOTE, ft_strlen(OPEN_QUOTE));
	ft_add_nl_last_row(t, t->inp, loc);
}

ssize_t	ft_get_prompt_len(t_term *t, ssize_t row)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (!row)
		prompt_len = ft_strlen(SHELL_PROMPT);
	if (t->nl_addr[row][-1] == '\n')
		prompt_len = ft_strlen(OPEN_QUOTE);
	return (prompt_len);
}
