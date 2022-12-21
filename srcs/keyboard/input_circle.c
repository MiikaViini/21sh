/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:41:32 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/21 21:25:31 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_end_cycle(t_term *t)
{
	t->start_row = get_linenbr();
	if (t->bytes)
	{
		ft_memcpy(t->history_buff, t->inp, t->bytes);
		ft_nl_removal(t);
		//vec_push(&t->v_history, t->history_buff); //copy from buff to history-array
		ft_strclr(t->history_buff);
	}
	// if (!ft_strncmp(t->inp, "history", 7))
	// 	ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}

// static int	ctrl_d(t_term *t)
// {
// 	if (!t->bytes)
// 		return (-1);
// 	if (t->index < t->bytes)
// 		ft_delete(t);
// 	if (t->heredoc && !*t->nl_addr[t->c_row])
// 	{
// 		ft_putstr("21sh: warning: here-document at line ");
// 		ft_putnbr(t->c_row);
// 		ft_putstr(" delimited by end-of-file (wanted `EOF')");
// 		ft_end_cycle(t);
// 		ft_restart_cycle(t);
// 		return (1);
// 	}
// 	return (0);
// }

static int	ft_isprint_or_enter(t_term *t)
{
	if ((ft_isprint(t->ch) || t->ch == ENTER) && t->bytes < BUFFSIZE)
		insertion(t);
	if (t->ch == ENTER && t->c_row == t->total_row)
	{
		if ((!t->bslash && !(t->q_qty % 2) && !t->delim) \
			|| (t->delim && ft_strequ(t->nl_addr[t->c_row], t->delim)))
		{
			ft_end_cycle(t);
			return (1);
		}
		t->bslash = 0;
	}
	return (0);
}

static void	ft_backspace_or_escape(t_term *t)
{
	if (t->ch == BACKSPACE && t->index)
		ft_backspace(t);
	if (t->ch == ESCAPE)
		ft_esc_parse(t);
}

int	ctrl_d(t_term *t)
{
	if (!t->bytes)
		return (-1);
	if (t->index < t->bytes)
		ft_delete(t);
	if (t->heredoc && !*t->nl_addr[t->c_row])
	{
		ft_putstr("21sh: warning: here-document at line ");
		ft_putnbr(t->c_row);
		ft_putstr(" delimited by end-of-file (wanted `EOF')");
		ft_end_cycle(t);
		return (1);
	}
	return (0);
}

static int	ctrl_d_exit(t_term *t)
{
	t = NULL;
	write(1, "\n", 1);
	//history_write_to_file(t);
	return (1);
}
//return values differ from ref
int	input_cycle(t_term *t)
{
	int		ctrl_d_ret;

	t->c_col = write(1, SHELL_PROMPT, (size_t)t->prompt_len);
	ft_add_nl_last_row(t, t->inp, 0);
	while (t->ch != -1)
	{
		t->ch = get_input();
		if (ft_isprint_or_enter(t))
			return (0);
		if (t->ch == CTRL_D)
		{
			ctrl_d_ret = ctrl_d(t);
			if (ctrl_d_ret == 1)
				break ;
			if (ctrl_d_ret == -1)
				return (ctrl_d_exit(t));
		}
		ft_ctrl(t);
		ft_backspace_or_escape(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
	return (0);
}
