/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:25:25 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/15 17:18:03 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	clipboard(t_term *t)
{
	if (t->ch == CTRL_W)
		ctrl_cut(t);
	else if (t->ch == CTRL_U)
		ctrl_copy(t);
	else if (t->ch == CTRL_Y)
		ctrl_paste(t);
	else if (t->ch == CTRL_L)
	{
		t->start_row = 0;
		run_capability("vi");
		run_capability("cl");
		print_input(t, 0, 0);
		run_capability("ve");
	}
}
