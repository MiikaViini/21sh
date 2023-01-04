/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:09:28 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/14 19:10:02 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
