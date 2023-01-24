/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:52:08 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/16 19:50:13 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ctrl_d(t_term *t)
{
	if (!t->bytes)
		return (-1);
	if (t->index < t->bytes)
		delete_char(t);
	if (t->heredoc && !*t->nl_addr[t->c_row])
	{
		delim_fetch(t);
		ft_strcat(t->inp, t->delim);
		ft_putstr("21sh: warning: here-document at line ");
		ft_putnbr(t->c_row);
		ft_putstr(" delimited by end-of-file (wanted `EOF')");
		end_cycle(t);
		return (1);
	}
	return (0);
}

int	ctrl_d_exit(t_term *t)
{
	t = NULL;
	(void)t;
	write(1, "\n", 1);
	exit(0);
}
