/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:19:15 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/09 20:48:51 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#include "ft_21sh.h"

static int	ft_inhibitor_catch(t_term *t, ssize_t index, int *bs, int *hd)
{
	*bs = 0;
	*hd = 0;
	if (t->inp[index] == '<')
		*hd = 1;
	else if (t->inp[index] == '\\')
		*bs = 1;
	else if ((t->inp[index] == D_QUO || t->inp[index] == S_QUO) \
	&& !ft_bslash_escape_check(t, index))
		return (1);
	return (0);
}

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
void	ft_deletion_shift(t_term *t, ssize_t index)
{
	int	blash;
	int	quote;
	int	heredoc;

	quote = ft_inhibitor_catch(t, index, &blash, &heredoc);
	t->inp[index] = '\0';
	while (&t->inp[index] < &t->inp[t->bytes])
	{
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index + 1] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		index++;
	}
	t->bytes--;
	if (blash)
		ft_quote_flag_check(t, t->index);
	else if (heredoc)
	{
		ft_heredoc_handling(t);
		if (!t->heredoc && t->delim)
			ft_strdel(&t->delim);
	}
	else if (quote)
		ft_quote_flag_reset(t);
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
	t->c_row++;
	t->total_row++;
	ft_strdel(&t->input_cpy);
	if (t->start_row + t->total_row >= t->ws_row)
	{
		run_capability("sf");
		t->start_row--;
	}
	set_cursor(0, t->start_row + t->c_row);
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
