/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:56:41 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/15 14:54:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int check_equalsign(char *input)
{
	int i;

	i = -1;
	while (input[++i])
	{
		if (ft_strchr(&input[i], '='))
			return (0);
	}
	return (1);
}

int is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '=');
}

void add_letter(char *word, char c, int *total, int *k)
{
	word[*k] = c;
	*total += 1;
	*k += 1;
	//*k += 1;
}

int can_be_added(char c, t_quotes *quots)
{
	return ((c && quots->closed == 0) || (!ft_isspace(c) && quots->closed));
}

int is_end_of_word(char c, t_quotes *quots, int index)
{
	return ((ft_isspace(c) && quots->s_quote + quots->d_quote == 0)
		|| (ft_isspace(c) && quots->closed) || (is_operator(c, quots) && index != 0));
}

int is_operator (char c, t_quotes *quots)
{
	(void)quots;
	if ((quots->d_quote && !quots->closed) || (quots->s_quote && !quots->closed))
		return 0;
	return ((c == '|' ) | (c == ';') | (c == '&'));
}

void tokens_del(t_tlist **tokens)
{
	t_tlist *temp;
	t_tlist	*list;

	list = *tokens;
	while(list != NULL)
	{
		temp = list->next;
		if (list->str)
			ft_strdel(&list->str);
		if (list->file)
			ft_strdel(&list->file);
		free(list);
		list = temp;
	}
	*tokens = NULL;
}

void delete_node(t_ast *node)
{
	//t_ast *temp;
	if (node == NULL)
		return ;
	delete_node(node->left);
	if (node->cmd)
	free_strarr(node->cmd);
	if (node->file)
		ft_strdel(&node->file);
	if(node->redirs)
		tokens_del(&node->redirs);
	delete_node(node->right);
	free(node);
	
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_print(NULL, NULL, E_NOFORK);
	return pid;
}
