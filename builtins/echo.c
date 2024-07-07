/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:35:26 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/07 14:36:46 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(char **args)
{
    int args_nbr;
    bool    option;
    int i;
    i = 0;
    option = false;
    args_nbr = get_args_nbr(args);
    
    if (args_nbr > 0)
    {
        while (*args && (ft_strcmp(*args, "echo" )))
            args++;
        if (*args && !ft_strcmp(*args, "echo"))
            args++;
        while (args[i] && args[i] && ft_strcmp(args[i], "-n") == 0)
        {
            option = true;
            i++;
        }
        while (args[i])
        {
            ft_putstr_fd(args[i], 1);
            if (args[i] && args[i + 1])
                ft_putstr_fd(" ", 1);
            i++;
        }
        if (!option)
            ft_putstr_fd("\n", 1);
    }
    return (0);
}
