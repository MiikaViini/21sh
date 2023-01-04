/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:20:37 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/04 10:39:57 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	var_name_len(char *word, int len, int *i)
{
	(*i)++;
	if (word[*i] == '{' || word[*i] == '}')
		(*i)++;
	while (ft_isalnum(word[len + *i])
		|| (!ft_isalnum(word[len + *i]) && word[len + *i] == '_'))
		len++;
	return (len);
}

static char	*expand_and_concat(char *expanded, char **env, int k, int len)
{
	char	*temp;

	temp = ft_strjoin(expanded, env[k] + len + 1);
	expanded = ft_strcpy(expanded, temp);
	ft_strdel(&temp);
	return (expanded);
}

static int	add_letter_exp(char *word, char *expanded, int *i, int *j)
{
	if (word[*i] == '}')
	{
		*i += 1;
		return (0);
	}
	else if (!is_expansion(word, *i)
		|| (word[*i] == '~' && is_expansion(word, *i + 1)))
	{
		expanded[*j] = word[*i];
		*i += 1;
		*j += 1;
		return (0);
	}
	return (1);
}

char	*dollar_expansion(char *expanded, char *word, char **env, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (!add_letter_exp(word, expanded, &i, &j))
			;
		else
		{
			k = -1;
			len = var_name_len(word, len, &i);
			while (env[++k])
				if (ft_strncmp(env[k], &word[i], len) == 0
					&& env[k][len] == '=')
					expanded = expand_and_concat(expanded, env, k, len);
			i += len;
			j = ft_strlen(expanded);
			len = 0;
		}
	}
	return (expanded);
}
