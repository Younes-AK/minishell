/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:09 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/01 11:35:53 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env(t_env *env)
{
    while (env)
    {
        ft_putstr_fd(env->key, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(env->value, 1);
        ft_putstr_fd("\n", 1);
        env = env->next;
    }
    return (0);
}