/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:43:38 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/28 07:55:37 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strcat(char *restrict s1, const char *restrict s2) 
{
    char *dest = s1;
    while (*dest)
        dest++;
    while (*s2) 
	{
        *dest = *s2;
        dest++;
        s2++;
    }
    *dest = '\0';
    return (s1);
}

