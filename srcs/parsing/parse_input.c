/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 21:39:22 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	initialise_structs(t_quotes *quotes, t_word *ints, char *input)
{
	quotes->s_quote = 0;
	quotes->d_quote = 0;
	quotes->closed = 0;
	if (ints)
	{
		ints->expan = 0;
		ints->k = 0;
		ints->type = TOKEN_WORD;
		ints->redir = -1;
		ints->redir_way = 0;
		ints->file = NULL;
		ints->len = (int)ft_strlen(input);
	}
}

void set_operator_sign(t_word *ints, char **word)
{
	if (*word[0] == '|')
		ints->type = TOKEN_PIPE;
	else if (*word[0] == ';')
		ints->type = TOKEN_SEMICOLON;
	else
		ints->type = TOKEN_ELSE;
}

t_tlist *create_token(char **word, t_pars *pars, t_word *ints)
{
	t_tlist *token;

	token = new_token(*word, ints);
	ft_strdel(&pars->last_token_str);
	pars->last_token_str = ft_strdup(token->str);
	ft_strdel(word);
	return (token);
}

static t_tlist	*get_token(t_pars *pars, t_word *ints)
{
	char		*word;
	t_quotes	quots;

	initialise_structs(&quots, ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[ints->i]) && ints->total++)
		ints->i++;
	while (ints->i < ints->len)
	{
		see_quote(&quots, pars->trimmed, ints->i);
		if (set_redirections(pars, ints, word, &quots))
			break ;
		if (is_end_of_word(pars->trimmed[ints->i], &quots, ints->k) 
			|| is_redirect(pars->trimmed[ints->i], &quots))
			break ;
		if (can_be_added(pars->trimmed[ints->i], &quots))
			add_letter(word, pars->trimmed[ints->i++], ints);
		if (is_operator(word[0], &quots) 
			&& !is_redirect(pars->trimmed[ints->i], &quots))
		{
			set_operator_sign(ints, &word);
			break;
		}
	}
	return (create_token(&word, pars, ints));
}

// Parsing and lexing input, *get_token()* will make token list as a linked list
// *make_ast()* will make abstract syntax tree from tokens
t_ast	**parse_input(t_pars *pars)
{
	t_ast		**tree;
	t_tlist		*tokens;
	t_tlist		*temp;
	t_word		ints;

	ints.i = 0;
	ints.total = 0;
	tokens = NULL;
	tree = (t_ast **)ft_memalloc(sizeof(t_ast *) * ft_wordcount_ws(pars->trimmed));
	while (ints.i < pars->len)
	{
		token_to_last(&tokens, get_token(pars, &ints));
		ints.i = ints.total;
	}
	temp = tokens;
	if (!check_syntax(pars, tokens))
		build_all_asts(tree, tokens);
	tokens_del(&temp);
	ft_strdel(&pars->trimmed);
	ft_strdel(&pars->last_token_str);
	return (tree);
}

