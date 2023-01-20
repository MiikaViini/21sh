/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:41:19 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/20 10:50:27 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_term	*g_t;

void	init_helper(t_term *t)
{
	t->ch = 0;
	t->quote = 0;
	t->q_qty = 0;
	t->bslash = 0;
	t->bytes = 0;
	t->c_row = 0;
	t->total_row = 0;
	t->ws_col = 0;
	t->ws_row = 0;
	t->index = 0;
	t->heredoc = 0;
	t->total_row_cpy = 0;
	t->clipboard.type = 0;
	t->his = 0;
	t->history_row = -1;
	t->sigint = 0;
}

void	init_term(t_term *t)
{
	g_t = t;
	ft_memset(t->inp, '\0', BUFFSIZE);
	ft_memset(t->history_buff, '\0', BUFFSIZE);
	init_helper(t);
	history_to_array(t);
	t->start_row = 0;
	t->nl_addr = NULL;
	t->delim = NULL;
	get_window_size(t);
	t->prompt_len = (ssize_t)ft_strlen(SHELL_PROMPT);
	t->m_prompt_len = (ssize_t)ft_strlen(OPEN_QUOTE);
	t->c_col = ft_strlen(SHELL_PROMPT);
	t->input_cpy = NULL;
	t->clipboard.buff = NULL;
}

static void	init_termios(t_term *t)
{
	if (tcgetattr(STDIN_FILENO, &t->orig_termios) == -1)
		exit(1);
	t->raw = t->orig_termios;
	t->raw.c_lflag &= ~(ICANON | ECHO | IEXTEN);
	t->raw.c_iflag &= ~(IXON | BRKINT);
	t->raw.c_cc[VMIN] = 1;
	t->raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->raw) == -1)
	{
		error_print(NULL, NULL, E_TCATTR);
		exit(1);
	}
}

void	init_tcaps(t_term *t)
{
	ft_getent();
	init_termios(t);
	init_term(t);
}
