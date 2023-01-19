/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:35:34 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/19 15:53:40 by mviinika         ###   ########.fr       */
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
		error_print(NULL, NULL, E_NOTERM);
		exit(1);
	}
	status = tgetent(term_buffer, termtype);
	if (status < 0)
	{
		error_print(NULL, NULL, E_TDB);
		exit(1);
	}
	else if (status == 0)
	{
		error_print(NULL, NULL, E_UKNTERM);
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
		error_print(NULL, cap, E_CAP);
	else
		tputs(p, 1, ft_putc);
}
