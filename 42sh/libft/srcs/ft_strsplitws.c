/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitws.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:09:29 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:42 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	size_t	ft_wordcount(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((!ft_isspace(s[i]) && ft_isspace(s[i + 1]))
			|| (!ft_isspace(s[i]) && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static	char	*ft_word(char *s)
{
	char	*start;

	start = s;
	while (*s && !ft_isspace(*s))
		s++;
	*s = '\0';
	return (ft_strdup(start));
}

static void	*ft_freewords(char **words, size_t i)
{
	while (i--)
		ft_strdel(&words[i]);
	free(words);
	return (NULL);
}

static char	**ft_words(char *s, size_t count)
{
	char	**words;
	char	*word;
	size_t	i;

	i = 0;
	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (words)
	{
		while (i < count)
		{
			while (ft_isspace(*s))
				s++;
			if (*s)
			{
				word = ft_word(s);
				if (!word)
					return (ft_freewords(words, i));
				words[i] = word;
				i++;
				s = s + (ft_strlen(word) + 1);
			}
		}
		words[i] = NULL;
	}
	return (words);
}

char	**ft_strsplitws(char const *s)
{
	char	*string;
	char	**word_array;

	string = ft_strdup((char *)s);
	if (!s || !string)
		return (NULL);
	word_array = ft_words(string, ft_wordcount(string));
	free(string);
	return (word_array);
}
