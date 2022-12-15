/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:51:44 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 21:06:48 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	add_aggr_out(char **trimmed, char **word, t_word *ints, int *total)
{
	**word = **trimmed;
	(*word)++;
	(*trimmed)++;
	**word = **trimmed;
	(*total)++;
	(*total)++;
	ints->redir = REDIR_AGGR_OUT;
	return (2);
}

int	add_aggr_in(char *trimmed, char *word, t_word *ints, int *total)
{
	*word = *trimmed;
	word++;
	trimmed++;
	*word = *trimmed;
	(*total)++;
	(*total)++;
	ints->redir = REDIR_AGGR_IN;
	return (2);
}

int	add_redir_out(char *trimmed, char *word, t_word *ints, int *total)
{
	(*total)++;
	ints->redir = REDIR_TRUNC;
	*word = *trimmed;
	word++;
	trimmed++;
	if (*trimmed == '>')
	{
		(*total)++;
		*word = *trimmed;
		ints->redir  = REDIR_APPEND;
		return (2);
	}
	return (1);
}

int	add_redir_in(char *trimmed, char *word, t_word *ints, int *total)
{
	(*total)++;
	*word = *trimmed;
	(trimmed)++;
	ints->redir = REDIR_IN;
	return (1);
}

int add_shortcut(char *trimmed, char *word, t_word *ints, int *total)
{
	*word = *trimmed;
	word++;
	trimmed++;
	*word = *trimmed;
	(*total)++;
	(*total)++;
	ints->redir = REDIR_AGGR_STERR_STOUT;
	return (2);
}

int redir_token(char *trimmed, char *word, t_word *ints) // Maybe jumptable here
{
	int i;

	i = 0;
	ints->type = TOKEN_REDIRECT;
	if ((trimmed[1])  == '&' && trimmed[0] == '>')
		i = add_aggr_out(&trimmed, &word, ints, &ints->total);
	else if ((trimmed[0])  == '&' && trimmed[1] == '>')
		i = add_shortcut(trimmed, word, ints, &ints->total);
	else if ((trimmed[1]) == '&' && trimmed[0] == '<')
		i = add_aggr_in(trimmed, word, ints, &ints->total);
	else if (*trimmed == '>')
		i = add_redir_out(trimmed, word, ints, &ints->total);
	else if (*trimmed == '<')
		i = add_redir_in(trimmed, word, ints, &ints->total);
	return (i);
}
