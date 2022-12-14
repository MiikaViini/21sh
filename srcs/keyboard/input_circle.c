/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:41:32 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/14 19:25:38 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_end_cycle(t_term *t)
{
	// if (t->bytes)
	// 	vec_push(&t->v_history, t->inp);
	//if (!ft_strncmp(t->inp, "history", 7))
		//ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}

static int	ctrl_d(t_term *t)
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
		ft_restart_cycle(t);
		return (1);
	}
	return (0);
}

static int	ft_isprint_or_enter(t_term *t)
{
	if (ft_isprint(t->ch) || t->ch == ENTER)
		insertion(t);
	if (t->ch == ENTER)
	{
		if ((!t->bslash && !(t->q_qty % 2) && !t->delim) \
			|| !ft_strcmp(t->nl_addr[t->c_row], t->delim))
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

t_term	*input_cycle(t_term *t)
{
	add_new_line(t, 0);
	while (t->ch != -1)
	{
		t->ch = get_input();
		if (ft_isprint_or_enter(t))
			return (t);
		if (t->ch == CTRL_D)
		{
			if (ctrl_d(t) == 1)
				continue ;
			if (ctrl_d(t) == -1)
				return (NULL);
		}
		ft_ctrl(t);
		ft_backspace_or_escape(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
	return (NULL);
}
