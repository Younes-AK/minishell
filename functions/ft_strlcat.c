/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:43:38 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/16 08:59:32 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dest && !len)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dest);
	if (len == 0 || dst_len >= len)
		return (src_len + len);
	i = 0;
	while (src[i] && (i < len - dst_len - 1))
	{
		dest[dst_len + i] = src[i];
		i++;
	}
	dest[dst_len + i] = '\0';
	return (dst_len + src_len);
}
