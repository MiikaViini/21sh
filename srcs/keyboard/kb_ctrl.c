/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:25:25 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/21 21:33:20 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_ctrl(t_term *t)
{
	if (t->ch == CTRL_W)
		ft_cut(t);
	else if (t->ch == CTRL_U)
		ft_copy(t);
	else if (t->ch == CTRL_Y)
		ft_paste(t);
	else if (t->ch == CTRL_L)
	{
		t->start_row = 0;
		run_capability("vi");
		run_capability("cl");
		ft_print_input(t, 0, 0);
		run_capability("ve");
	}
}
