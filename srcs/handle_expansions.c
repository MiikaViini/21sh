/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:15:09 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/15 15:11:51 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static size_t longest_var(char **env)
{
	size_t longest;
	size_t len;
	size_t i;

	i = 0;
	longest = 0;
	len = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		if (len > longest)
			longest = len;
		i++;
	}
	return (longest);
}

static int mall_c(char *input, char **env)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (input[++i])
	{
		if (input[i] == '$')
			count++;
	}
	return (longest_var(env) * (count + 1));
}

static char *replace_expansion(char *word, char **env, char *input)
{
	char *expanded;
	int len;

	len = 0;
	expanded = ft_strnew(mall_c(input, env) + ft_strlen(input));
	if (word[0] == '~' && word[1] != '$')
		expanded = tilde_expansion(word, env, expanded);
	else
		expanded = dollar_expansion(expanded, word, env, len);
	return (expanded);
}

char *handle_expansions(char *input, char **env)
{
	char	*expanded;

	expanded = replace_expansion(input, env, input);
	if (!expanded)
		return (input);
	ft_strdel(&input);
	return (expanded);
}
