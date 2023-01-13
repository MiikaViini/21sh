/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:41:32 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/13 19:58:00 by spuustin         ###   ########.fr       */
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
		add_command_to_history(t, t->history_buff);
		ft_strclr(t->history_buff);
	}
	if (ft_strequ(t->inp, "history"))
		history_command(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
	t->sigint = 0;
}

static int	ft_isprint_or_enter(t_term *t)
{
	if ((ft_isprint(t->ch) || t->ch == ENTER) && t->bytes < (BUFFSIZE - 1))
		insertion(t);
	if (t->ch == ENTER)
	{
		if ((!t->bslash && !(t->q_qty % 2) && !t->delim) \
			|| (t->delim && !ft_strcmp(t->nl_addr[t->c_row], t->delim)))
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

int	input_cycle(t_term *t)
{
	int		ctrl_d_ret;

	ft_add_nl_last_row(t, t->inp, 0);
	t->c_col = write(1, SHELL_PROMPT, (size_t)t->prompt_len);
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
