/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:43:38 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/07 09:18:52 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *ft_strcat(char *s1, const char *s2) 
// {
//     char *dest = s1;
//     if (!s1)
//         return (NULL);
//     while (*dest)
//         dest++;
//     while (*s2) 
// 	{
//         *dest = *s2;
//         dest++;
//         s2++;
//     }
//     *dest = '\0';
//     return (s1);
// }


char *ft_strcat(char *dest, const char *src) 
{
    char *dest_ptr = dest + ft_strlen(dest);
    while (*src) 
    {
        *dest_ptr++ = *src++;
    }
    *dest_ptr = '\0';
    return dest;
}

