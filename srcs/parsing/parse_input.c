/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 15:29:26 by mviinika         ###   ########.fr       */
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

static int	is_redirect(char c, t_quotes *quots)
{
	int	ret;

	ret = 0;
	if ((c == '>' && quots->d_quote == 0)
		&& (c == '>' && quots->s_quote == 0))
		ret = 1;
	else if ((c == '<' && !quots->d_quote)
		&& (c == '<' && !quots->s_quote))
		ret = 1;
	return (ret);
}

static int	is_aggr_err_out(t_quotes *quots, char redir, char operator)
{
	return (is_redirect(redir, quots) && operator == '&');
}

void set_values_aggr_io(t_word *ints, char **word, int *total)
{
	ints->type = TOKEN_REDIRECT;
	ints->redir = REDIR_AGGR_STERR_STOUT;
	ft_strdel(word);
	*word = ft_strdup("&>");
	(*total)++;
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

static t_tlist	*get_token(t_pars *pars, t_word *ints, int i, int *total)
{
	char		*word;
	t_quotes	quots;
	// t_word		ints;

	initialise_structs(&quots, ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints->len)
	{
		see_quote(&quots, pars->trimmed, i);
		if ((is_redirect(pars->trimmed[i], &quots) && ft_only_digits(word)))
		{
			i = redir_token(&pars->trimmed[i], &word[ints->k], &ints, total);
			break ;
		}
		else if (is_aggr_err_out(&quots, pars->trimmed[i], word[0]))
		{
			set_values_aggr_io(&ints, &word, total);
			break ;
		}
		if (is_end_of_word(pars->trimmed[i], &quots, ints->k) || is_redirect(pars->trimmed[i], &quots))
			break ;
		if (can_be_added(pars->trimmed[i], &quots))
			add_letter(word, pars->trimmed[i++], total, ints->k);
		if (is_operator(word[0], &quots) && !is_redirect(pars->trimmed[i], &quots))
		{
			set_operator_sign(&ints, &word);
			break;
		}
	}
	return (create_token(&word, pars, ints));
}

void init_tree(t_ast ***tree, size_t size)
{
	size_t i;
	
	i = 0;
	while (i < size)
	{
		(*tree)[i]->type = 0;
		(*tree)[i]->cmd = NULL;
		(*tree)[i]->file = NULL;
		(*tree)[i]->redir_type = -1;
		(*tree)[i]->to_fd = 0;
		(*tree)[i]->err_fd = 0;
		(*tree)[i]->fd_close = 0;
		i++;
	}
}

void build_all_asts(t_ast **tree, t_tlist *tokens)
{
	int	i;

	i = 0;
	while(tokens)
	{
		tree[i] = build_ast(&tokens);
		if (tokens && tokens->type == TOKEN_SEMICOLON)
			tokens = tokens->next;
		i++;
	}
}

void init_word_ints(char *input, t_word *ints)
{
	ints->i = 0;
	ints->total = 0;
	ints->expan = 0;
	ints->k = 0;
	ints->type = TOKEN_WORD;
	ints->redir = -1;
	ints->redir_way = 0;
	ints->file = NULL;
	ints->len = (int)ft_strlen(input);
}
// Parsing and lexing input, *get_token()* will make token list as a linked list
// *make_ast()* will make abstract syntax tree from tokens
t_ast	**parse_input(t_pars *pars)
{
	// int			i;
	// static int	total;
	t_ast		**tree;
	t_tlist		*tokens;
	t_tlist		*temp;
	t_word		ints;

	// i = 0;
	// total = 0;
	init_word_ints(pars->trimmed, &ints);
	tokens = NULL;
	tree = (t_ast **)ft_memalloc(sizeof(t_ast *) * 100);
	while (ints.i < pars->len)
	{
		token_to_last(&tokens, get_token(pars, &ints.i, &ints.total));
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

