/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:28:50 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/14 20:47:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void error_print(char *word, char *command, char *e_msg)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	if (command)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
	}
	if (word)
	{
		ft_putstr_fd(word, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(e_msg, 2);
}
