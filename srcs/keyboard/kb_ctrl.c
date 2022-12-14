/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:25:25 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/14 19:25:45 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_ctrl(t_term *t)
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
