/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:12:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/07 09:18:13 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void *ft_memcpy(void *dest, const void *src, size_t n) 
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (n--) 
    {
        *d++ = *s++;
    }
    return dest;
}
