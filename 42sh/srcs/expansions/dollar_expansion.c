/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:20:37 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/10 15:30:04 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	var_name_len(char *word, int len, int i)
{
	while (ft_isalnum(word[len + i])
		|| (!ft_isalnum(word[len + i]) && word[len + i] == '_'))
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
	if (!is_expansion(word, *i)
		|| (word[*i] == '~' && is_expansion(word, *i + 1))
		|| word[*i + 1] == '}')
	{
		expanded[*j] = word[*i];
		*i += 1;
		*j += 1;
		return (0);
	}
	return (1);
}

int	check_exp_syntax(char *word)
{
	int	i;
	int open;

	i = 1;
	open = 0;
	while (word[i])
	{
		if (word[i] == '{' && open == 0)
			open = 1;
		else if (word[i] == '}' && open == 1)
			open = 0;
		i++;
	}
	if (open)
		return (1);
	return (0);
}

int	is_formatting(char *word)
{
	int	i;

	i = 0;
	if (word[i++] == ':')
	{
		if (word[i] == '-' || (word[i] == '=')
			|| word[i] == '+' || word[i] == '?')
			return (1);
	}
	return (0);
}

char	*dollar_expansion(char *expanded, char *word, char **env, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	if (check_exp_syntax(word))
	{
		error_print(NULL, NULL, E_BADS);
		return NULL;
	}
	while (word[i])
	{
		if (is_formatting(&word[i]))
		{
			format_parameters()
		}
		if (!add_letter_exp(word, expanded, &i, &j))
			;
		else
		{
			k = -1;
			len = var_name_len(word, len, ++i);
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
