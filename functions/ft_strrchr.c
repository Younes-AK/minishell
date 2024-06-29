/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:42:17 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/26 17:08:14 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int	lenght;

	lenght = ft_strlen(s);
	while (lenght > 0)
	{
		if (s[lenght] == (char)c)
		{
			return ((char *)&s[lenght]);
		}
		lenght--;
	}
	if (*s == (char)c)
		return ((char *)&s[lenght]);
	return (NULL);
}
