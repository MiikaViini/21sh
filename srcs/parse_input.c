/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/11 13:57:02 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_tlist	*newlst(char *content, char type)
{
	t_tlist	*fresh;

	fresh = (t_tlist *)ft_memalloc(sizeof(t_tlist));
	if (content == NULL)
	{
		fresh->str = NULL;
		fresh->type = 0;
		fresh->next = NULL;
		return (fresh);
	}
	fresh->str = ft_strnew(ft_strlen(content));
	ft_memcpy(fresh->str, content, ft_strlen(content));
	fresh->type = type;
	fresh->next = NULL;
	return (fresh);
}

static void	initialise_structs(t_quotes *quotes, t_word *ints, char *input)
{
	quotes->s_quote = 0;
	quotes->d_quote = 0;
	quotes->closed = 0;
	ints->expan = 0;
	ints->k = 0;
	ints->len = (int)ft_strlen(input);
}

static void	see_quote(t_quotes *quots, char *input, int i)
{
	if (is_quote(input[i]))
	{
		while (is_double_quote(input[i]) && quots->s_quote == 0)
		{
			quots->d_quote += 1;
			i += 1;
		}
		while (is_single_quote(input[i]) && !quots->d_quote)
		{
			quots->s_quote += 1;
			i += 1;
		}
		if (quots->s_quote >= 2 || quots->d_quote >= 2)
			quots->closed = 1;
	}
}

char *remove_quotes(char *input)
{
	int 	i;
	int 	k;
	char	quote;
	char	*fresh;

	i = 0;
	k = 0;
	quote = 0;
	fresh = ft_strnew(ft_strlen(input));
	while (input[i])
	{
		
		if ((input[i] == '\'' && quote == 0)|| (input[i] == '\"' && quote == 0))
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		else if (input[i] != quote)
			fresh[k++] = input[i];
		i++;
	}
	ft_strdel(&input);
	return (fresh);
}

int	is_redirect(char *input, int i, t_quotes *quots)
{
	return ((input[i] == '>' && !quots->d_quote)
		|| (input[i] == '>' && !quots->s_quote));
}

static t_tlist	*get_token(t_pars *pars, t_env *env, int i, int *total)
{
	char		*word;
	t_quotes	quots;
	t_word		ints;
	t_tlist		*token;
	char		type;

	type = TOKEN_WORD;
	initialise_structs(&quots, &ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		see_quote(&quots, pars->trimmed, i);
		if (is_operator(pars->trimmed[i], &quots))
		{
			if (pars->trimmed[i] == '|')
				type = TOKEN_PIPE;
			else if (pars->trimmed[i] == ';')
				type = TOKEN_SEMICOLON;
			else if (pars->trimmed[i] == '<')
				type = TOKEN_GT;
			else if (pars->trimmed[i] == '>')
				type = TOKEN_LT;
			else if (pars->trimmed[i] == '&')
				type = TOKEN_AGGR;
			else
				type = TOKEN_ELSE;
			word[0] = pars->trimmed[i];
			(*total)++;
			break ;
		}
		if (is_expansion(pars->trimmed, i))
			type = TOKEN_DOLLAR;
		if (is_end_of_word(pars->trimmed[i], &quots) && (*total)++)
		{
			break ;
		}
		if (can_be_added(pars->trimmed[i], &quots))
			add_letter(word, pars->trimmed[i++], total, &ints.k);
	}
	if ((type == TOKEN_DOLLAR && !quots.s_quote)
		|| (word[0] == '~' && word[1] != '$' && !quots.s_quote))
	{
		word = handle_expansions(word, env->env, total, &i);
		type = TOKEN_WORD;
	}
	word = remove_quotes(word);
	token = newlst(word, type);
	return (token);
}



static void	lstaddlast(t_tlist **alst, t_tlist *new)
{
	t_tlist	*temp;

	temp = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			temp->next = new;
			break ;
		}
		temp = temp->next;
	}
}


// Parsing and lexing input, *get_token()* will make token list as a linked list
// *make_ast()* will make abstract syntax tree from tokens
t_ast	*parse_input(t_env *env, t_pars *pars)
{
	int			i;
	static int	total;
	t_ast		*tree;
	t_tlist		*tokens;

	i = 0;
	total = 0;
	tokens = NULL;
	tree = NULL;
	while (i < pars->len)
	{
		lstaddlast(&tokens, get_token(pars,env ,i, &total));
		i = total;
	}
	tree = make_ast(tokens);
	// ast_travers(tree);
	// exit(2);
	ft_strdel(&pars->trimmed);
	return (tree);
}
