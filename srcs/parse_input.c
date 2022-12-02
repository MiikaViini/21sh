/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/02 16:18:13 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_tlist	*newlst(char *content, t_word *word_attrs)
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
	fresh->type = word_attrs->type;
	fresh->redir_type = word_attrs->redir;
	fresh->file = word_attrs->file;
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
		ints->type = TOKEN_WORD;
		ints->redir = -1;
		ints->redir_way = 0;
		ints->file = NULL;
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
	int			k;
	int			j;

	(void)env;
	k = 0;
	j = 0;
	initialise_structs(&quots, &ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		see_quote(&quots, pars->trimmed, i);
		if (is_end_of_word(pars->trimmed[i], &quots) && word[k - 1])
		{
			break ;
		}
			
		if (is_redirect(pars->trimmed[i], &quots) || (is_redirect(pars->trimmed[i], &quots) && pars->trimmed[i - 1] == '&'))
		{
			ints.type = TOKEN_REDIRECT;
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
				if (pars->trimmed[i + 1] == '&' && pars->trimmed[i] == '>')
				{
					word[j] = pars->trimmed[i];
					ints.redir = REDIR_AGGR_IN;
				//	ints.type = TOKEN_REDIRECT;
				}
				else if (pars->trimmed[i + 1] == '&' && pars->trimmed[i] == '<')
				{
					word[j] = pars->trimmed[i];
					ints.redir = REDIR_AGGR_OUT;
					//ints.type = TOKEN_AGGR;
				}
				else if (pars->trimmed[i] == '>')		// Check for append redirection
				{
					ints.redir = REDIR_TRUNC;
					word[j++] = pars->trimmed[i++];
					if (pars->trimmed[i] == '>')
					{
						word[j] = pars->trimmed[i];
						(*total)++;
						ints.redir  = REDIR_APPEND;
					}
				}
				else if (pars->trimmed[i] == '<')		// Check for STD_IN redirect
				{
					word[j] = pars->trimmed[i++];
					ints.redir = REDIR_IN;
				}
				break;
			}
			else if (pars->trimmed[i - 1] == '&') 				// Check for aggregation/duplication
			{
				ints.redir = REDIR_AGGR_IO;
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
				ints.redir = REDIR_TRUNC;
				word[j++] = pars->trimmed[i++];
				if (pars->trimmed[i] == '>')
				{
					word[j] = pars->trimmed[i];
					ints.redir  = REDIR_APPEND;
				}
				(*total)++;
			}
			else if (pars->trimmed[i] == '<')		// Check for STD_IN redirect
			{
				word[j] = pars->trimmed[i];
				(*total)++;
				ints.redir = REDIR_IN;
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
				ints.type = TOKEN_PIPE;
			else if (word[0] == ';')
				ints.type = TOKEN_SEMICOLON;
			else
				ints.type = TOKEN_ELSE;
			break;
			i++;
		}
	}
	//ft_printf("word [%s] [%d]\n", word, type);
	token = newlst(word, &ints);
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
		if (tree[i] == NULL)
		{
			
			free(tree);
			return (NULL);
		}
		else if (tokens && tokens->type == TOKEN_SEMICOLON)
			tokens = tokens->next;
			
		i++;
	}
	// ast_travers(tree[i],env);
	ft_strdel(&pars->trimmed);
	return (tree);
}
