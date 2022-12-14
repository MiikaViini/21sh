/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:40:13 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/14 19:36:26 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_delim_fetch(t_term *t)
{
	char	*ptr;
	char	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = ft_strchr(t->inp, '<') + 2;
		while (*ptr && ft_sspace(ptr))
			ptr++;
		if (*ptr)
		{
			end_q = ptr;
			while (*end_q && !ft_sspace(end_q))
				end_q++;
			t->delim = ft_strsub(ptr, 0, end_q - ptr);
		}
	}
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

static void	ft_insertion_enter(t_term *t)
{
	if (!t->nl_addr[t->c_row + 1])
	{
		if (t->bslash || t->q_qty % 2 || (t->heredoc \
			&& ft_strcmp(t->nl_addr[t->c_row], t->delim)))
		{
			t->inp[t->bytes++] = (char)t->ch;
			ft_create_prompt_line(t); //edited this and commented unwanted ones out
			t->index = t->bytes;
		}
	}
	ft_delim_fetch(t);
}

void	ft_heredoc_handling(t_term *t)
{
	if (t->index > 2 && t->ch == '<' && !(t->q_qty % 2))
	{
		if (t->inp[t->index - 1] == '<' && t->inp[t->index - 2] != '<')
			t->heredoc = 1;
		else
			t->heredoc = 0;
	}
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
	ft_heredoc_handling(t);
	ft_bslash_handling(t);
	if ((t->ch == D_QUO || t->ch == S_QUO) && !t->heredoc)
	{
		if (!t->bslash)
			ft_quote_handling(t, (char)t->ch);
		else
			t->bslash = 0;
	}
	t->c_col++;
	ft_shift_nl_addre(t, 1);
	if (t->inp[t->index])
		ft_shift_insert(t);
	t->inp[t->index++] = (char)t->ch;
	t->bytes++;
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
	run_capability("vi");
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
