/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:40:13 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/19 20:44:53 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_isseparator(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

static void	delim_fetch_error(t_term *t, char *ptr)
{
	if (*ptr && ft_isseparator(*ptr))
	{
		ft_putstr_fd("\n21sh: syntax error near unexpected token `", 2);
		write(2, ptr, 1);
		ft_putstr_fd("'", 2);
	}
	else
		ft_putstr_fd("\n21sh: syntax error near unexpected token `newline'", 2);
	ft_strclr(t->inp);
	t->heredoc = 0;
}

static char	*strdelim(t_term *t)
{
	char	*ptr;
	int		delim_qty;

	ptr = t->inp;
	delim_qty = 0;
	while (*ptr)
	{
		if (*ptr == '<')
			delim_qty++;
		if (delim_qty == 2)
			return (ptr + 1);
		ptr++;
	}
	return (ptr);
}

static int	ft_delim_fetch(t_term *t)
{
	char	*ptr;
	char	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = strdelim(t);
		while (*ptr && ft_sspace(ptr))
			ptr++;
		if (*ptr && !ft_isseparator(*ptr))
		{
			end_q = ptr;
			while (*end_q && !ft_sspace(end_q))
				end_q++;
			t->delim = ft_strsub(ptr, 0, end_q - ptr);
		}
		else
		{
			delim_fetch_error(t, ptr);
			return (1);
		}
	}
	return(0);
}

// static void	ft_add_nl_last_rowss(t_term *t, ssize_t pos)
// {
// 	int		index;
// 	char	**n_arr;

// 	index = -1;
// 	n_arr = NULL;
// 	if (!t->nl_addr)
// 	{
// 		t->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
// 		t->nl_addr[++index] = &t->inp[pos];
// 		t->nl_addr[++index] = NULL;
// 	}
// 	else
// 	{
// 		n_arr = (char **)ft_memalloc(sizeof(char *) \
// 			* (size_t)(t->total_row + 2));
// 		while (t->nl_addr[++index])
// 			n_arr[index] = t->nl_addr[index];
// 		n_arr[index++] = &t->inp[pos];
// 		n_arr[index] = NULL;
// 		ft_memdel((void **)&t->nl_addr);
// 		t->nl_addr = n_arr;
// 	}
// }

// void	ft_create_prompt_linee(t_term *t, ssize_t loc)
// {
// 	int		row;

// 	row = get_linenbr();
// 	t->c_row++;
// 	t->total_row++;
// 	if (t->start_row + t->total_row >= t->ws_row)
// 		run_capability("sf");
// 	else
// 		row++;
// 	t->c_col = t->m_prompt_len;
// 	set_cursor(0, row);
// 	write(1, OPEN_QUOTE, 2);
// 	ft_add_nl_last_rowss(t, loc);
// }

static int	ft_bslash_escape_check(t_term *t, ssize_t pos)
{
	ssize_t	start;
	ssize_t	count;

	if (!pos)
		return (0);
	start = pos - 1;
	while (start && t->inp[start] == '\\')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->inp[count] == '\\')
		count++;
	if ((count - start) % 2)
		return (1);
	return (0);
}

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

void	ft_bslash_handling(t_term *t)
{
	ssize_t	i;

	i = t->index - 1;
	if (t->ch == '\\' && t->index == t->bytes && !t->heredoc)
	{
		while (i && t->inp[i] == '\\')
			i--;
		if ((t->index - i) % 2)
			t->bslash = 1;
		else
			t->bslash = 0;
	}
	else
		if (t->ch != D_QUO && t->ch != S_QUO)
			t->bslash = 0;
}

void	ft_shift_nl_addre(t_term *t, int num)
{
	ssize_t	row;

	row = t->c_row + 1;
	while (t->nl_addr[row] && !ft_is_prompt_line(t, row))
		row++;
	while (t->nl_addr[row++])
		t->nl_addr[row - 1] = &t->nl_addr[row - 1][num];
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

void	ft_quote_flag_reset(t_term *t)
{
	ssize_t	i;

	i = -1;
	t->q_qty = 0;
	t->quote = 0;
	t->heredoc = 0;
	while (t->inp[++i])
	{
		if ((t->inp[i] == D_QUO || t->inp[i] == S_QUO) && !t->heredoc)
		{
			if (!ft_bslash_escape_check(t, i))
				ft_quote_handling(t, t->inp[i]);
		}
		if (t->inp[i] == '<')
		{
			ft_heredoc_handling(t, i);
			if (!t->heredoc && t->delim)
				ft_strdel(&t->delim);
		}
	}
}

void	ft_quote_flag_check(t_term *t, ssize_t index)
{
	ssize_t	i;

	i = index;
	while (t->inp[i] && t->inp[i] == '\\')
		i++;
	if (t->inp[i] == S_QUO || t->inp[i] == D_QUO)
		ft_quote_flag_reset(t);
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

static void	ft_print_line(t_term *t, ssize_t row)
{
	if (row == t->c_row)
	{
		if (t->nl_addr[row + 1])
			write(1, &t->inp[t->index], \
				(size_t)(t->nl_addr[row + 1] - &t->inp[t->index]));
		else
			write(1, &t->inp[t->index], \
				(size_t)((&t->inp[t->bytes] - &t->inp[t->index]) + 1));
	}
	else
	{
		if (ft_is_prompt_line(t, row))
			print_prompt(row);
		if (t->nl_addr[row + 1])
			write(1, t->nl_addr[row], \
				(size_t)(t->nl_addr[row + 1] - t->nl_addr[row]));
		else
			write(1, t->nl_addr[row], \
				(size_t)((&t->inp[t->bytes] - t->nl_addr[row]) + 1));
	}
}

static void	ft_print_line_traill(t_term *t)
{
	ssize_t	row;
	ssize_t	dis_row;

	row = t->c_row;
	dis_row = get_linenbr();
	while (row <= t->total_row)
	{
		run_capability("ce");
		ft_print_line(t, row++);
		set_cursor(0, ++dis_row);
	}
}

static void	ft_print_traill(t_term *t)
{
	run_capability("vi");
	run_capability("sc");
	ft_print_line_traill(t);
	run_capability("rc");
	run_capability("ve");
}

void	insertion(t_term *t)
{
	if (t->ch == ENTER)
		ft_insertion_enter(t);
	else
		ft_insertion_char(t);
	trigger_nl(t);
	if (t->inp[t->index])
		ft_print_traill(t);
}
