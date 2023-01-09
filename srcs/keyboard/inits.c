/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:41:19 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/09 20:25:28 by spuustin         ###   ########.fr       */
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
	t->history_row = -1;
	t->his = 0;
	t->sigint = 0;
	t->total_row_cpy = 0;
}

void	init_term(t_term *t)
{
	g_t = t;
	init_signals();
	ft_memset(t->inp, '\0', BUFFSIZE);
	ft_memset(t->history_buff, '\0', BUFFSIZE);
	init_helper(t);
	history_to_array(t);
	t->start_row = 0; //maybe wrong
	t->nl_addr = NULL;
	t->delim = NULL;
	get_window_size(t);
	t->prompt_len = (ssize_t)ft_strlen(SHELL_PROMPT);
	t->m_prompt_len = (ssize_t)ft_strlen(OPEN_QUOTE);
	t->c_col = ft_strlen(SHELL_PROMPT);
	t->input_cpy = NULL;
	t->clipboard.buff = NULL;
}

static struct termios	init_termios(void)
{
	struct termios	ret;
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &ret) == -1)
		exit(1);
	raw = ret;
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	return (ret);
}

void	init_tcaps(t_term *t)
{
	ft_getent();
	t->orig_termios = init_termios();
	init_term(t);
}
