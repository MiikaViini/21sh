/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:41:32 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/09 23:32:43 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


// is pos even needed, for now always set to 0
// check values this is called with

void	ft_remove_nl_addr(t_term *t, ssize_t row)
{
	ssize_t	i;
	ssize_t	j;
	char	**new_array;

	i = -1;
	j = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) \
		* (size_t)(t->total_row + 1));
	while (t->nl_addr[++i])
	{
		if (i != row)
			new_array[++j] = t->nl_addr[i];
	}
	new_array[++j] = NULL;
	ft_memdel((void **)&t->nl_addr); //free_array
	t->nl_addr = new_array;
}

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
void	ft_deletion_shift(t_term *t, int mode)
{
	ssize_t	index_cpy;

	if (mode == BCK)
		t->index--;
	index_cpy = t->index;
	t->inp[index_cpy] = '\0';
	while (&t->inp[index_cpy] < &t->inp[t->bytes])
	{
		t->inp[index_cpy] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		t->inp[index_cpy + 1] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		t->inp[index_cpy] = t->inp[index_cpy] ^ t->inp[index_cpy + 1];
		index_cpy++;
	}
	t->bytes--;
}

void	ft_quote_decrement(t_term *t, int num)
{
	if (!(t->q_qty % 2))
	{
		t->quote = t->inp[t->index - num];
		t->q_qty--;
	}
	else if ((t->q_qty % 2) && t->quote == t->inp[t->index - num])
	{
		t->quote = 0;
		t->q_qty--;
	}
}

int	get_linenbr(void)
{
	char	buf[16];
	int		len;
	int		i;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\033[6n", 4);
	len = 0;
	while (read(0, buf + len, 1) == 1)
	{
		if (buf[len++] == 'R')
			break ;
	}
	len = 0;
	i = 0;
	while (buf[i] && buf[i] != ';')
	{
		if (ft_isdigit(buf[i]))
			buf[len++] = buf[i];
		i++;
	}
	buf[len] = '\0';
	return (ft_atoi(buf) - 1);
}

void	ft_create_prompt_line(t_term *t)
{
	int		row;

	row = get_linenbr();
	t->c_row++;
	t->total_row++;
	if (t->start_row + t->total_row >= t->ws_row)
		run_capability("sf");
	else
		row++;
	t->c_col = t->m_prompt_len;
	set_cursor(0, row);
	write(1, OPEN_QUOTE, 2);
	add_new_line(t, t->bytes);
}

static void	ft_print_prompt(ssize_t row)
{
	if (!row)
		ft_putstr(SHELL_PROMPT);
	else
		ft_putstr(OPEN_QUOTE);
}

//this could be int that includes printing of prompt, no pointer return needed
char	*ft_is_prompt_line(t_term *t, int row)
{
	if (!row || t->nl_addr[row][-1] == '\n')
		return (t->nl_addr[row]);
	return (NULL);
}

void	ft_shift_nl_addr(t_term *t, int num)
{
	int	row;

	row = t->c_row + 1;
	while (t->nl_addr[row] && !ft_is_prompt_line(t, row))
		row++;
	while (t->nl_addr[row++])
		t->nl_addr[row - 1] = &t->nl_addr[row - 1][num];
}

int	ft_putc(int c)
{
	return ((int)write(1, &c, 1));
}

void	set_cursor(ssize_t col, ssize_t row)
{
	char	*cm;

	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, (int)col, (int)row), 1, ft_putc);
}

static void	ft_print_line_trail(t_term *t)
{
	ssize_t	row;
	ssize_t dis_row;

	dis_row = 0;
	row = t->c_row;
	dis_row = get_linenbr();
	while (row <= t->total_row)
	{
		run_capability("ce");
		if (row == t->c_row)
		{
			if (t->nl_addr[row + 1])
				write(1, &t->inp[t->index], (size_t)(t->nl_addr[row + 1] - &t->inp[t->index]));
			else
				write(1, &t->inp[t->index], (size_t)((&t->inp[t->bytes] - &t->inp[t->index]) + 1));	
		}
		else
		{
			if (ft_is_prompt_line(t, row))
				ft_print_prompt(row);
			if (t->nl_addr[row + 1])
				write(1, t->nl_addr[row], (size_t)(t->nl_addr[row + 1] - t->nl_addr[row]));
			else
				write(1, t->nl_addr[row], (size_t)((&t->inp[t->bytes] - t->nl_addr[row]) + 1));
		}
		set_cursor(0, ++dis_row);
		row++;
	}
}

void	ft_print_trail(t_term *t)
{
	ssize_t row;

	run_capability("vi");
	run_capability("sc");
	run_capability("sf");
	row = get_linenbr();
	run_capability("vi");
	ft_print_line_trail(t);
	run_capability("rc");
	run_capability("ve");
	set_cursor(t->c_col, row);
	run_capability("ve");
}

void	ft_quote_handling(t_term *t, char ch)
{
	if (!t->q_qty || (t->q_qty % 2 && !t->quote))
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (!(t->q_qty % 2) && !t->quote)
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (ch == t->quote)
	{
		t->quote = 0;
		t->q_qty++;
	}
}

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

static void	ft_ctrl(t_term *t)
{
	if (t->ch == CTRL_C)
		ft_restart_cycle(t);
	else if (t->ch == CTRL_W)
		ft_cut(t);
	else if (t->ch == CTRL_U)
		ft_copy(t);
	else if (t->ch == CTRL_Y)
		ft_paste(t);
	else if (t->ch == CTRL_L)
	{
		run_capability("cl");
		write(1, SHELL_PROMPT, 6);
	}
}

static void	update_nl_addr_del(t_term *t)
{
	ssize_t	row;

	row = t->c_row + 1;
	while (t->nl_addr[row])
	{
		if (ft_is_prompt_line(t, row))
			t->nl_addr[row] = &t->nl_addr[row][-1];
		row++;
	}
}

void	ft_delete(t_term *t)
{
	ssize_t	len;
	ssize_t	row;

	if (t->index && (t->inp[t->index] == D_QUO || \
	t->inp[t->index] == S_QUO))
		ft_quote_decrement(t, 0);
	row = ft_row_lowest_line(t);
	if (t->nl_addr[row + 1]
		&& (&t->inp[t->index + 1] == t->nl_addr[t->c_row + 1]
			&& ft_is_prompt_line(t, t->c_row + 1)))
		return ;
	if (t->nl_addr[row + 1])
		len = (t->nl_addr[row + 1] - t->nl_addr[row]) - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	update_nl_addr_del(t);
	ft_deletion_shift(t, DEL);
	run_capability("ce");
	if (!len)
	{
		ft_remove_nl_addr(t, row);
		t->total_row--;
	}
	if (t->inp[t->index])
		ft_print_trail(t);
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
