/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:09:29 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	size_t	ft_wordcount(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static	char	*ft_word(char *s, char c)
{
	char	*start;

	start = s;
	while (*s && *s != c)
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

static char	**ft_words(char *s, char c, size_t count)
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
			while (*s == c)
				s++;
			if (*s)
			{
				word = ft_word(s, c);
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

char	**ft_strsplit(char const *s, char c)
{
	char	*string;
	char	**word_array;

	string = ft_strdup((char *)s);
	if (!s || !string)
		return (NULL);
	word_array = ft_words(string, c, ft_wordcount(string, c));
	free(string);
	return (word_array);
}
