/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:40:13 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/02 19:45:13 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_insertion_enter(t_term *t)
{
	if (!t->nl_addr[t->c_row + 1])
	{
		ft_delim_fetch(t);
		t->bslash = ft_bslash_escape_check(t, t->bytes);
		if (t->q_qty % 2 \
			|| (t->heredoc \
			&& (t->delim && ft_strcmp(t->nl_addr[t->c_row], t->delim))) \
			|| t->bslash)
		{
			t->history_row = -1;
			ft_memcpy(t->history_buff, t->inp, t->bytes);
			t->inp[t->bytes++] = (char)t->ch;
			ft_create_prompt_line(t, t->bytes);
			t->index = t->bytes;
		}
	}
}

void	ft_heredoc_handling(t_term *t, int index)
{
	ssize_t	start;
	ssize_t	count;

	start = index;
	while (start && t->inp[start] == '<')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->inp[count] == '<')
		count++;
	if ((count - start) >= 2)
		t->heredoc = 1;
	else
		t->heredoc = 0;
}

/*
 * It shifts all the characters in the input buffer to the right of the
 * cursor one position to the right
 *
 * @param t the term structure
 */

void	ft_shift_insert(t_term *t)
{
	ssize_t	bytes_cpy;

	bytes_cpy = t->bytes;
	while (&t->inp[bytes_cpy] >= &t->inp[t->index])
	{
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy + 1] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		bytes_cpy--;
	}
}

static void	ft_insertion_char(t_term *t)
{
	ft_putc(t->ch);
	t->c_col++;
	ft_shift_nl_addr(t, 1);
	if (t->inp[t->index])
		ft_shift_insert(t);
	t->inp[t->index++] = (char)t->ch;
	t->bytes++;
	if ((t->inp[t->index - 1] == D_QUO || t->inp[t->index - 1] == S_QUO) \
		&& !t->heredoc)
	{
		if (!ft_bslash_escape_check(t, t->index - 1))
			ft_quote_flag_reset(t);
	}
	if (t->inp[t->index - 1] == '<')
	{
		ft_heredoc_handling(t, t->index - 1);
		if (!t->heredoc && t->delim)
			ft_strdel(&t->delim);
	}
	else if (t->inp[t->index - 1] == '\\')
		ft_quote_flag_check(t, t->index - 1);
}

void	insertion(t_term *t)
{
	if (t->ch == ENTER)
		ft_insertion_enter(t);
	else
		ft_insertion_char(t);
	trigger_nl(t);
	if (t->inp[t->index])
		ft_print_trail(t);
}
