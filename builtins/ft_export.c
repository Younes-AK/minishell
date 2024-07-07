/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:36:16 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/07 14:34:02 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_export(char **args, t_env *env)
{
    (void)env;
    int nbr_args;
    int i;
    char *var;
   // int end;
    
    i = 0;
    
    // printf("--> %s\n", var);
    nbr_args = get_args_nbr(args);
    while (i < nbr_args)
    {
        var = ft_strchr(args[i], '=');
        i++;
    }
    return (0);
}