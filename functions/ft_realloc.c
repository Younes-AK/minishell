/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 07:32:10 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/28 07:46:58 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void *ft_realloc(void *ptr, size_t size) 
{
    void    *new_ptr;
    size_t  old_size;
    size_t  copy_size;
    
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL)
        return malloc(size);
    new_ptr = malloc(size);
    if (new_ptr == NULL)
        return NULL;
    old_size = 100; 
    copy_size = old_size < size ? old_size : size;
    ft_memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    return new_ptr;
}