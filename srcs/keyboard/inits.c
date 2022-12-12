/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:41:19 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/12 20:07:47 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_term	*g_t;

void	init_term(t_term *t)
{
	init_signals();
	t->ch = 0;
	ft_memset(t->inp, '\0', BUFFSIZE);
	t->start_row = get_linenbr();
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->c_row = 0;
	t->total_row = 0;
	t->ws_col = 0;
	t->ws_row = 0;
	t->index = 0;
	t->heredoc = 0;
	t->total_row_cpy = 0;
	t->his = 0;
	//get_history(t);
	g_t = t;
	t->nl_addr = NULL;
	t->delim = NULL;
	get_window_size(t); //why is it done here again?
	t->prompt_len = (ssize_t)ft_strlen(SHELL_PROMPT); // can be removed imo
	t->m_prompt_len = (ssize_t)ft_strlen(OPEN_QUOTE); //changed //same
	t->c_col = t->prompt_len;
	t->input_cpy = NULL;
	t->total_row_cpy = 0;
}


static struct termios init_termios()
{
	struct termios ret;
	struct termios raw;
	
	if (tcgetattr(STDIN_FILENO, &ret) == -1)
		exit(1);
	raw = ret;
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	// run_capability("ti"); 
	run_capability("cl");
	return (ret);
}

void	init_tcaps(t_term *t)
{
	t->orig_termios = init_termios();
	init_term(t);
}
