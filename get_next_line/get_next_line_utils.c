/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:58:10 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/11 10:58:53 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_found_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// size_t	ft_strlen(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(char *str)
// {
// 	char	*ptr;
// 	int		i;	

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	ptr = (char *)malloc(ft_strlen(str) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		*(ptr + i) = str[i];
// 		i++;
// 	}
// 	*(ptr + i) = '\0';
// 	return (ptr);
// }

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*allstr;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	allstr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!allstr)
		return (NULL);
	while (s1[i])
	{
		allstr[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
		allstr[i++] = s2[j++];
	allstr[i] = '\0';
	return (allstr);
}
