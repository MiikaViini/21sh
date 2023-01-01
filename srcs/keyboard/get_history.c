/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:29:47 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/01 16:58:50 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
 * It moves the cursor to the end of the line
 *
 * @param t the term structure
 */
// static void	ft_history_trigger_end(t_term *t, int display_row)
// {
// 	t->index = t->bytes;
// 	t->c_row = t->total_row;
// 	if (ft_is_prompt_line(t, t->c_row))
// 	{
// 		if (!t->c_row)
// 			t->c_col = t->prompt_len;
// 		else
// 			t->c_col = t->m_prompt_len;
// 	}
// 	t->c_col += &t->inp[t->bytes] - t->nl_addr[t->c_row];
// 	set_cursor(t->c_col, t->total_row + display_row);
// 	run_capability("ve");
// }

/*
 * It sets the cursor to the beginning of the line, clears the screen, and
 * prints the prompt
 *
 * @param t the term structure
 */
// static void	ft_history_trigger_start(t_term *t, int display_row)
// {
// 	run_capability("vi");
// 	t->quote = 0;
// 	t->q_qty = 0;
// 	t->c_col = 0;
// 	set_cursor(t->c_col, display_row);
// 	t->c_row = 0;
// 	t->index = 0;
// 	t->total_row = 0;
// 	run_capability("cd");
// 	write(1, SHELL_PROMPT, 7);
// }

/*
 * It takes a history number,
 * and if it exists, it copies it into the input buffer, otherwise it copies the
 * original input buffer
 *
 * @param t the term structure
 * @param his the history number to trigger
 */

//previously was this

// void	ft_history_trigger(t_term *t, ssize_t pos)
// {
// 	char	*history;
// 	int		display_row;

// 	display_row = t->start_row - t->c_row;
// 	ft_history_trigger_start(t, display_row);
// 	//history = (char *)vec_get(&t->v_history, t->v_history.len - (size_t)his);
// 	history = ft_strdup(t->history[t->history_size - pos]);
// 	if (history)
// 	{
// 		t->bytes = (ssize_t)ft_strlen(history);
// 		if (!t->input_cpy)
// 			t->input_cpy = ft_strdup(t->inp);
// 		ft_memset((void *)t->inp, '\0', BUFF_SIZE);
// 		ft_memcpy((void *)t->inp, (void *)history, (size_t)t->bytes);
// 	}
// 	else
// 	{
// 		t->bytes = (ssize_t)ft_strlen(t->input_cpy);
// 		ft_memset((void *)t->inp, '\0', BUFF_SIZE);
// 		ft_memcpy((void *)t->inp, (void *)t->input_cpy, (size_t)t->bytes);
// 		ft_strdel(&t->input_cpy);
// 	}
// 	ft_reset_nl_addr(t);
// 	ft_print_trail(t);
// 	ft_memdel((void *)&history);
// 	ft_history_trigger_end(t, display_row);
// }

static void	ft_history_reset_nl(t_term *t, char *inp)
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

static void	ft_history_inp_update(t_term *t, char *history)
{
	if (history)
	{
		ft_memset((void *)t->nl_addr[t->c_row], '\0', \
		ft_strlen(t->nl_addr[t->c_row]));
		ft_memcpy(t->nl_addr[t->c_row], history, ft_strlen(history));
	}
	else
	{
		ft_memset((void *)t->nl_addr[t->c_row], '\0', \
		ft_strlen(t->nl_addr[t->c_row]));
		if (t->input_cpy)
			ft_memcpy(t->nl_addr[t->c_row], t->input_cpy, \
			ft_strlen(t->input_cpy));
	}
}

static void	ft_history_clear_line(t_term *t, ssize_t row)
{
	set_cursor(0, (t->start_row + t->history_row));
	if (row > t->history_row)
	{
		while (row > t->history_row)
		{
			ft_remove_nl_addr(t, row);
			t->total_row--;
			row--;
		}
	}
	run_capability("cd");
}

static void	ft_history_push(t_term *t)
{
	if (t->history_row == -1)
	{
		t->input_cpy = ft_strsub(t->nl_addr[t->c_row], 0, \
		ft_strlen(t->nl_addr[t->c_row]));
		if (*t->history_buff)
		{
			ft_nl_removal(t);
			add_command_to_history(t, t->history_buff);
			ft_memset((void *)t->history_buff, '\0', \
			ft_strlen(t->history_buff));
		}
		t->history_row = t->c_row;
	}
	t->c_row = t->history_row;
}

void	ft_history_trigger(t_term *t, ssize_t pos)
{
	ssize_t	row;
	char	*history;

	if (t->c_row != t->total_row)
		return ;
	row = t->c_row;
	ft_history_push(t);
	run_capability("vi");
	if (t->history[t->history_size - pos])
		history = ft_strdup(t->history[t->history_size - (size_t)pos]);
	else
		history = ft_strdup("");
	ft_history_clear_line(t, row);
	ft_history_inp_update(t, history);
	ft_history_reset_nl(t, t->nl_addr[t->history_row]);
	ft_quote_flag_reset(t);
	if (t->start_row + t->total_row >= t->ws_row)
		t->start_row = t->ws_row - (t->total_row + 1);
	ft_print_input(t, t->c_row, 1);
	if (!history)
	{
		ft_strdel(&t->input_cpy);
		t->history_row = -1;
	}
	run_capability("ve");
}
