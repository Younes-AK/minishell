/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:44:05 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/14 21:46:02 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_trim(char *str)
{
	char	*end;

	while (is_whait_spaces((unsigned char)*str))
		str++;
	if (*str == 0)
		return (ft_strdup(""));
	end = (char *)str + ft_strlen(str) - 1;
	while (end > str && is_whait_spaces((unsigned char)*end))
		end--;
	end[1] = '\0';
	return (ft_strdup(str));
}
