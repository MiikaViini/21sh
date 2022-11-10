/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/10 11:46:10 by mviinika         ###   ########.fr       */
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

static void	rem_quote(t_quotes *quots, char *input, int *tot, int *i)
{
	if (is_quote(input[*i]))
	{
		while (is_double_quote(input[*i]) && quots->s_quote == 0)
		{
			quots->d_quote += 1;
			*i += 1;
			*tot += 1;
		}
		while (is_single_quote(input[*i]) && !quots->d_quote)
		{
			quots->s_quote += 1;
			*i += 1;
			*tot += 1;
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

static t_tlist	*get_token(t_pars *pars, int i, int *total)
{
	char		*word;
	t_quotes	quots;
	t_word		ints;
	t_tlist		*token;
	char		type;

	type = TOKEN_WORD;
	//token = newlst(NULL, 0);
	initialise_structs(&quots, &ints, pars->trimmed);
	word = ft_strnew(ft_strlen(pars->trimmed));
	while (ft_isspace(pars->trimmed[i]) && (*total)++)
		i++;
	while (i < ints.len)
	{
		rem_quote(&quots, pars->trimmed, total, &i);
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
	// if ((ints.expan && !quots.s_quote)
	// 	|| (word[0] == '~' && word[1] != '$' && !quots.s_quote))
	// 	word = handle_expansions(word, env, total, &i);
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

// static void	lstadd(t_tlist **alst, t_tlist *new)
// {
// 	new->next = *alst;
// 	*alst = new;
// }

t_ast	*parse_input(t_env *env, t_pars *pars)
{
	int			i;
	static int	total;
	t_ast		*tree;
	t_tlist		*tokens;

	i = 0;
	total = 0;
	tokens = NULL;
	(void)env;
	tree = NULL;
	while (i < pars->len)
	{
		//pars->parsed[k++] = get_token(pars, i, &total, env->env);
		//get_token(pars, i, &total, env->env);
		// if (!pars->parsed[k - 1])
		// {
		// 	ft_strdel(&pars->trimmed);
		// 	free_parsed_input(pars->parsed);
		// 	free(pars->parsed);
		// 	return (NULL);
		// }
		
		lstaddlast(&tokens, get_token(pars, i, &total));
		
		//tokens = tokens->next;
		i = total;
		
	}
	//pars->parsed[k] = NULL;
	// tokens = start;
	// while(tokens)
	// {
	// 	ft_printf("type ; %c", tokens->type);
	// 	ft_printf(" str ; %s\n", tokens->str);
	// 	tokens = tokens->next;
	// }
	// tree = create_ast_node(NULL, TOKEN_PIPE, 0);
	tree = make_ast(tokens);
	// ft_printf("%d", tree->type);
	// ft_printf("%s %d", tree->left->cmd, tree->left->type);
	// ft_printf("%s %d", tree->right->cmd,tree->right->type);
	//ft_printf("%s ", tree->cmd);
	// ast_travers(tree);
	// exit(2);
	// if (pars->redir)
	// {
	// 	redirect(pars, env);
	// 	//ft_strdel(&pars->trimmed);
	// 	//return (NULL);
	// }
	ft_strdel(&pars->trimmed);
	return (tree);
}
