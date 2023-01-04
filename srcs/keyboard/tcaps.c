/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:35:34 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/19 20:18:47 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_getent(void)
{
	char	*termtype;
	char	term_buffer[2048];
	int		status;

	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		write(2, "could not get TERM env value\n", 30);
		exit(1);
	}
	status = tgetent(term_buffer, termtype);
	if (status < 0)
	{
		ft_printf("could not access the termcap database\n");
		exit(1);
	}
	else if (status == 0)
	{
		ft_printf("could not find the termtype\n");
		exit(1);
	}
	return (status);
}

int	ft_puts(int c)
{
	return ((int)write(1, &c, 1));
}

void	run_capability(char *cap)
{
	char	*p;

	p = tgetstr(cap, NULL);
	if (p == NULL)
	{
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(cap, 2);
		ft_putstr_fd(" : cannot ft_run_capability()\n", 2);
	}
	else
		tputs(p, 1, ft_putc);
}
