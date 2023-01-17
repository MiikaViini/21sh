/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:47:03 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/17 23:12:16 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
//# include "ft_21sh.h"

int		check_syntax(t_pars *pars, t_tlist *tokens);
int		is_redirect(char c, t_quotes *quots);
t_tlist	*new_token(char *content, t_word *word_attrs);
t_ast	**parse_input(t_pars *pars);
int		redir_token(char *trimmed, char *word, t_word *values);
int		set_redirections(t_pars *pars, t_word *values, \
											char *word, t_quotes *quots);
void	set_values_aggr_io(t_word *values, char **word);
void	token_to_last(t_tlist **alst, t_tlist *new);
void	tokens_del(t_tlist **tokens);

#endif
