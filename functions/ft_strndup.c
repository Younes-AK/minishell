/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:25:02 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/25 08:26:20 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *str, int len)
{
	char	*ptr;
	int		i;	

	ptr = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (str[i] && i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}