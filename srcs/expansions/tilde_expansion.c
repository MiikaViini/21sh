/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:50:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 12:04:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*expand_and_cat_tld(char *expanded, char **env, char *word, int len)
{
	char	*temp;

	temp = ft_strdup(*env + len);
	ft_strdel(&expanded);
	expanded = ft_strjoin(temp, &word[1]);
	ft_strdel(&temp);
	return (expanded);
}

static char	*handle_home(char *word, char **env, char *expanded)
{
	int	k;

	k = -1;
	while (env[++k])
	{
		if (ft_strncmp(env[k], "HOME=", 5) == 0)
		{
			expanded = expand_and_cat_tld(expanded, env + k, word, 5);
			break ;
		}
		else
		{
			ft_strdel(&expanded);
			expanded = ft_strdup(word);
		}
	}
	return (expanded);
}

static char	*handle_oldpwd(char *word, char **env, char *expanded)
{
	int	k;

	k = -1;
	while (env[++k])
	{
		if (ft_strncmp(env[k], "OLDPWD=", 7) == 0)
		{
			expanded = expand_and_cat_tld(expanded, env + k, &word[1], 7);
			break ;
		}
		else
		{
			ft_strdel(&expanded);
			expanded = ft_strdup(word);
		}
	}
	return (expanded);
}

static char	*handle_pwd(char *word, char **env, char *expanded)
{
	int	k;

	k = -1;
	while (env[++k])
	{
		if (ft_strncmp(env[k], "PWD=", 4) == 0)
		{
			expanded = expand_and_cat_tld(expanded, env + k, &word[1], 4);
			break ;
		}
		else
		{
			ft_strdel(&expanded);
			expanded = ft_strdup(word);
		}
	}
	return (expanded);
}

char	*tilde_expansion(char *word, char **env, char *expanded)
{
	char	*temp;

	if (word[1] == '/' || word[1] == '\0')
		expanded = handle_home(word, env, expanded);
	else if (word[1] == '-' && !word[2])
		expanded = handle_oldpwd(word, env, expanded);
	else if (word[1] == '+' && !word[2])
		expanded = handle_pwd(word, env, expanded);
	else
	{
		ft_strdel(&expanded);
		temp = user_expansion(word);
		if (!temp)
			return (NULL);
		expanded = ft_strdup(temp);
		ft_strdel(&temp);
	}
	return (expanded);
}
