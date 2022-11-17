/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/17 14:20:37 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_tlist	*newlst(char *content, char type, int redir)
{
	t_tlist	*fresh;

	fresh = (t_tlist *)ft_memalloc(sizeof(t_tlist));
	if (content == NULL)
	{
		fresh->str = NULL;
		fresh->type = 0;
		//fresh->type = 0;
		fresh->next = NULL;
		return (fresh);
	}
	fresh->str = ft_strnew(ft_strlen(content));
	ft_memcpy(fresh->str, content, ft_strlen(content));
	fresh->type = type;
	fresh->redir_type = redir;
	fresh->next = NULL;
	return (fresh);
}

void	initialise_structs(t_quotes *quotes, t_word *ints, char *input)
{
	quotes->s_quote = 0;
	quotes->d_quote = 0;
	quotes->closed = 0;
	if (ints)
	{
		ints->expan = 0;
		ints->k = 0;
		ints->len = (int)ft_strlen(input);
	}
}

void	see_quote(t_quotes *quots, char *input, int i)
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
	int			redir;
	int			k;

	type = TOKEN_WORD;
	redir = -1;
	(void)env;
	k = 0;
	initialise_structs(&quots, &ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		see_quote(&quots, pars->trimmed, i);
		
			
		// 	ft_strdel(&word);
		// 	word = ft_strndup(&pars->trimmed[i], 1);
		// 	(*total)++;
		// 	i += 1;
		// 	break ;
		// }
		if (is_end_of_word(pars->trimmed[i], &quots) && word[k - 1])
		{
			if (!is_operator(pars->trimmed[i],&quots))
				(*total)++;
			break ;
		}
		else if (can_be_added(pars->trimmed[i], &quots))
		{
			add_letter(word, pars->trimmed[i++], total, &ints.k);
			k++;
		}
		if (is_operator(word[0],&quots))
		{
			if (pars->trimmed[i] == '|')
				type = TOKEN_PIPE;
			else if (pars->trimmed[i] == ';')
				type = TOKEN_SEMICOLON;
			else if (pars->trimmed[i] == '<')
			{
				type = TOKEN_REDIRECT;
				redir = 0;
			}
				
			else if (pars->trimmed[i] == '>')
			{
				type = TOKEN_REDIRECT;
				if (pars->trimmed[i + 1] == '>')
				{
					redir = 1;
				}
				else
					redir = 2;
			}
			else if (pars->trimmed[i] == '&')
				type = TOKEN_AGGR;
			else
				type = TOKEN_ELSE;
			break ;
		}
	}
	ft_printf("%s\n", word);
	token = newlst(word, type, redir);
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
t_ast	**parse_input(t_env *env, t_pars *pars)
{
	int			i;
	static int	total;
	t_ast		**tree;
	t_tlist		*tokens;

	i = 0;
	total = 0;
	tokens = NULL;
		
	tree = (t_ast **)ft_memalloc(sizeof(t_ast *) * 100);
	while (i < pars->len)
	{
		lstaddlast(&tokens, get_token(pars,env ,i, &total));
		i = total;
	}
	i = 0;
	while(tokens)
	{
		tree[i] = make_ast(&tokens);
		if (tokens && tokens->type == TOKEN_SEMICOLON)
			tokens = tokens->next;
		i++;
	}
	// ast_travers(tree[i],env);
	// exit(1);
	ft_strdel(&pars->trimmed);
	return (tree);
}
