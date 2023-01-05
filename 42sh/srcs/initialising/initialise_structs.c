/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:20:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/20 12:20:26 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	initialise_structs(t_quotes *quotes, t_word *values, char *input)
{
	quotes->s_quote = 0;
	quotes->d_quote = 0;
	quotes->closed = 0;
	if (values)
	{
		values->k = 0;
		values->type = TOKEN_WORD;
		values->redir = -1;
		values->redir_way = 0;
		values->file = NULL;
		values->len = (int)ft_strlen(input);
	}
}
