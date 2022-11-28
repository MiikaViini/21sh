/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/28 21:22:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_tlist	*newlst(char *content, char type, int redir, int redir_way)
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
	fresh->str = ft_strdup(content);
	fresh->type = type;
	fresh->redir_type = redir;
	fresh->redir_way = redir_way;
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

int	is_redirect(char c, t_quotes *quots)
{
	int	ret;

	ret = 0;
	if ((c == '>' && !quots->d_quote)
		|| (c == '>' && !quots->s_quote))
		ret = 1;
	else if ((c == '<' && !quots->d_quote)
		|| (c == '<' && !quots->s_quote))
		ret = 1;
	return (ret);
}

int is_aggregation(char *input, int *i, t_quotes *quots)
{
	(void)quots;
	if ((ft_isdigit(input[*i]) && input[*i + 1] == '>' )
		|| (ft_isdigit(input[*i]) && input[*i + 1] == '<'))
	{
		if (input[*i + 1] == '&' && ft_isdigit(input[*i + 2]))
		{
			return (1);
		}
		else
		{
			return (-1);
		}
	}
	return (0);
}

static t_tlist	*get_token(t_pars *pars, t_env *env, int i, int *total)
{
	char		*word;
	t_quotes	quots;
	t_word		ints;
	t_tlist		*token;
	char		type;
	int			redir;
	int			redir_way;
	int			k;
	int			j;

	type = TOKEN_WORD;
	redir = -1;
	redir_way = 0;
	(void)env;
	k = 0;
	j = 0;
	initialise_structs(&quots, &ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		//ft_printf("%s\n",&pars->trimmed[i]);
		//ft_printf("%c\n", pars->trimmed[i]);
		see_quote(&quots, pars->trimmed, i);
		if (is_end_of_word(pars->trimmed[i], &quots) && word[k - 1])
			break ;
		if (is_redirect(pars->trimmed[i], &quots) || (is_redirect(pars->trimmed[i], &quots) && pars->trimmed[i - 1] == '&'))
		{
			type = TOKEN_REDIRECT;
			if (ft_isdigit(word[j]))				// Checks if there is a digit before redirecting
			{
				i--;
				while (pars->trimmed[i])
				{
					(*total)++;
					if ((pars->trimmed[i] == '>' && pars->trimmed[i + 1] != '&')
						|| pars->trimmed[i] == '&' || !ft_isdigit(pars->trimmed[i]))
					{
						break;
					}
					word[j++] = pars->trimmed[i++];
					
				}
				//ft_printf("%c\n", pars->trimmed[i]);
				if (pars->trimmed[i + 1] == '&')
				{
					word[j] = pars->trimmed[i];
					redir = REDIR_AGGR;
				}
				else if (pars->trimmed[i] == '>')		// Check for append redirection
				{
					redir_way = REDIR_TRUNC;
					word[j++] = pars->trimmed[i++];
					if (pars->trimmed[i] == '>')
					{
						word[j] = pars->trimmed[i];
						(*total)++;
						redir_way  = REDIR_APPEND;
					}
				}
				else if (pars->trimmed[i] == '<')		// Check for STD_IN redirect
				{
					word[j] = pars->trimmed[i++];
					redir_way = REDIR_IN;
				}
				break;
			}
			else if (pars->trimmed[i - 1] == '&') 				// Check for aggregation/duplication
			{
				redir = REDIR_AGGR_IO;
				word[j++] = pars->trimmed[i++];
				if (pars->trimmed[i] == '>')
				{
					word[j] = pars->trimmed[i];
					(*total)++;
				}
				(*total)++;
			}
			else if (pars->trimmed[i] == '>')		// Check for append redirection
			{
				redir_way = REDIR_TRUNC;
				i++;
				if (pars->trimmed[i++] == '>')
				{
					(*total)++;
					redir_way  = REDIR_APPEND;
				}
				(*total)++;
			}
			else if (pars->trimmed[i] == '<')		// Check for STD_IN redirect
			{
				(*total)++;
				redir_way = REDIR_IN;
				i++;
			}
			break;
		}
		if (can_be_added(pars->trimmed[i], &quots))
		{
			add_letter(word, pars->trimmed[i++], total, &ints.k);
			k++;
		}
		if (is_operator(word[0], &quots) && !is_redirect(pars->trimmed[i], &quots))
		{
			if (word[0] == '|')
				type = TOKEN_PIPE;
			else if (word[0] == ';')
				type = TOKEN_SEMICOLON;
			else
				type = TOKEN_ELSE;
			break;
			// i++;
		}
	}
	//ft_printf("%s\n", word);
	token = newlst(word, type, redir, redir_way);
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
	ft_strdel(&pars->trimmed);
	return (tree);
}
