/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:36:16 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/11 09:02:24 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


bool search(const char *str, char c)
{
    if (*str == '\0')
        return false;
    if (*str == c)
        return true;
    return search(str + 1, c);
}

char *get_var_name(char *str)
{
    char **strs;
    strs = ft_split(str, '=');
    if (!strs)
        return (NULL);
    
    return ("");
}
int ft_export(char **args, t_env *env)
{
    (void)env;
    int nbr_args;
    int i;
    char *var;
    
    i = 0;
    nbr_args = get_args_nbr(args);
    while (i < nbr_args)
    {
        if (search(args[i] , '='))
        {
            printf("--> %s\n", args[i]);
        }
        else
        {
           
        }
        var = get_var_name(args[i]);
     
        i++;
    }
    return (0);
}