/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_aggr_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:34:26 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 21:34:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void set_values_aggr_io(t_word *ints, char **word, int *total)
{
	ints->type = TOKEN_REDIRECT;
	ints->redir = REDIR_AGGR_STERR_STOUT;
	ft_strdel(word);
	*word = ft_strdup("&>");
	(*total)++;
}