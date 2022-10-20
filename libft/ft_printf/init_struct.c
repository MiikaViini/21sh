/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:31:30 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/09 18:33:29 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_modifiers	*init_struct(t_modifiers *mods)
{
	mods->plus = 0;
	mods->minus = 0;
	mods->dot = 0;
	mods->hash = 0;
	mods->space = 0;
	mods->zero = 0;
	mods->star = 0;
	mods->width = 0;
	mods->l = 0;
	mods->h = 0;
	mods->ld = 0;
	mods->j = 0;
	mods->z = 0;
	mods->capital = 0;
	mods->precision = 0;
	mods->cap_u = 0;
	mods->o_zero = 0;
	mods->d_space = 0;
	mods->sign = 0;
	mods->p_spec = 0;
	mods->d_zerominus = 0;
	mods->f_prec = 0;
	mods->f_zero = 0;
	return (mods);
}
