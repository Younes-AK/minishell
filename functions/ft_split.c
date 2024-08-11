/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:31:23 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/29 10:49:26 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_numofword(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	free_strings(int i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

static char	**ft_word(char const *s, char c, char **array, int words_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(array + i) = ft_substr(s, j, word_len(&*(s + j), c));
		if (!*(array + i))
		{
			free_strings(i, array);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c, t_prog *p)
{
	char	**strings;
	int		words;

	if (!s)
		return (NULL);
	words = ft_numofword(s, c);
	strings = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strings)
	{
		ft_putstr_fd("malloc fialled alocate memory\n", 2);
		ft_free_lists(p, "exit");
	}
	strings = ft_word(s, c, strings, words);
	return (strings);
}
