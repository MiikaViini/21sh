/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:41:18 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/17 20:22:58 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_prompt(ssize_t row)
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

void	set_cursor(ssize_t col, ssize_t row)
{
	char	*cm;

	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, (int)col, (int)row), 1, ft_putc);
}

int	ft_putc(int c)
{
	return ((int)write(1, &c, 1));
}
