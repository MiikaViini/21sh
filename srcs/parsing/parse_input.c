/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/06 14:03:33 by mviinika         ###   ########.fr       */
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
	if ((c == '>' && quots->d_quote == 0)
		&& (c == '>' && quots->s_quote == 0))
		ret = 1;
	else if ((c == '<' && !quots->d_quote)
		&& (c == '<' && !quots->s_quote))
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

	(void)env;
	k = 0;
	initialise_structs(&quots, &ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		see_quote(&quots, pars->trimmed, i);
		if (is_end_of_word(pars->trimmed[i], &quots, k))
			break ;
		
		if (is_redirect(pars->trimmed[i], &quots) || (is_redirect(pars->trimmed[i], &quots) && pars->trimmed[i - 1] == '&'))
		{
			(*total)++;
			ints.type = TOKEN_REDIRECT;
			if (pars->trimmed[i + 1] == '&' && pars->trimmed[i] == '>')
			{
				word[k++] = pars->trimmed[i++];
				word[k] = pars->trimmed[i];
				(*total)++;
				ints.redir = REDIR_AGGR_OUT;
			}
			else if (pars->trimmed[i + 1] == '&' && pars->trimmed[i] == '<')
			{
				word[k++] = pars->trimmed[i++];
				word[k] = pars->trimmed[i];
				(*total)++;
				ints.redir = REDIR_AGGR_IN;
			}
			else if (pars->trimmed[i] == '>')		// Check for append redirection
			{
				ints.redir = REDIR_TRUNC;
				word[k++] = pars->trimmed[i];
				while (pars->trimmed[++i] == '>')
				{
					word[k] = pars->trimmed[i];
					ints.redir  = REDIR_APPEND;
				}
			}
			else if (pars->trimmed[i] == '<')		// Check for STD_IN redirect
			{
				word[k] = pars->trimmed[i++];
				ints.redir = REDIR_IN;
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
	token = newlst(word, &ints);
	ft_strdel(&word);
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
// Parsing and lexing input, *get_token()* will make token list as a linked list
// *make_ast()* will make abstract syntax tree from tokens
t_ast	**parse_input(t_env *env, t_pars *pars)
{
	int			i;
	static int	total;
	t_ast		**tree;
	t_tlist		*tokens;
	t_tlist	*temp;

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
	temp = tokens;
	while(tokens)
	{
		tree[i] = make_ast(&tokens);
		if (tree[i] == NULL)
		{
			tokens_del(&temp);
			delete_node(tree[i]);
			ft_strdel(&pars->trimmed);
			free(tree);
			return (NULL);
		}
		else if (tokens && tokens->type == TOKEN_SEMICOLON)
			tokens = tokens->next;
		i++;
	}
	tokens_del(&temp);
	ft_strdel(&pars->trimmed);
	return (tree);
}
