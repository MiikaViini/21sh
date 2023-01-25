/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 10:28:03 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	set_operator_sign(t_word *values, char **word)
{
	if (*word[0] == '|')
		values->type = TOKEN_PIPE;
	else if (*word[0] == ';')
		values->type = TOKEN_SEMICOLON;
	else if (*word[0] == '&')
		values->type = TOKEN_AMPERSAND;
	else
		values->type = TOKEN_ELSE;
}

static t_tlist	*create_token(char **word, t_pars *pars, t_word *values)
{
	t_tlist	*token;

	token = new_token(*word, values);
	ft_strdel(&pars->last_token_str);
	pars->last_token_str = ft_strdup(token->str);
	ft_strdel(word);
	return (token);
}

static t_tlist	*get_token(t_pars *pars, t_word *values)
{
	char		*word;
	t_quotes	quots;

	initialise_structs(&quots, values, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[values->i]) && values->total++)
		values->i++;
	while (values->i < values->len)
	{
		see_quote(&quots, pars->trimmed, values->i);
		if (set_redirections(pars, values, word, &quots))
			break ;
		if (is_end_of_word(pars->trimmed[values->i], &quots, values->k)
			|| is_redirect(pars->trimmed[values->i], &quots))
			break ;
		if (can_be_added(pars->trimmed[values->i], &quots))
			add_letter(word, pars->trimmed[values->i++], values);
		if (is_operator(word[0], &quots)
			&& !is_redirect(pars->trimmed[values->i], &quots))
		{
			set_operator_sign(values, &word);
			break ;
		}
	}
	return (create_token(&word, pars, values));
}

static size_t	wc_delim(const char *s, char delim)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == delim)
			count++;
		i++;
	}
	return (count);
}

// Parsing and lexing input, *get_token()* will make token list as a linked list
// *make_ast()* will make abstract syntax tree from tokens
t_ast	**parse_input(t_pars *pars)
{
	t_ast		**tree;
	t_tlist		*tokens;
	t_tlist		*temp;
	t_word		values;

	values.i = 0;
	values.total = 0;
	tokens = NULL;
	tree = (t_ast **)ft_memalloc(sizeof(t_ast *) * \
								(wc_delim(pars->trimmed, ';') + 1));
	while (values.i < pars->len)
	{
		token_to_last(&tokens, get_token(pars, &values));
		values.i = values.total;
	}
	temp = tokens;
	if (!check_syntax(pars, tokens))
		build_all_asts(tree, tokens);
	tokens_del(&temp);
	ft_strdel(&pars->trimmed);
	ft_strdel(&pars->last_token_str);
	return (tree);
}
