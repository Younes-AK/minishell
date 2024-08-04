/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:55:32 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/30 15:59:54 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*allstr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	allstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!allstr)
		return (NULL);
	while (s1[i])
	{
		allstr[i] = s1[i];
		i++;
	}
	allstr[i++] = ' ';
	while (s2[j])
	{
		allstr[i] = s2[j];
		j++;
		i++;
	}
	allstr[i] = '\0';
	return (allstr);
}
