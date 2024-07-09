/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:35:26 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/08 08:11:30 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(char **args)
{
    int     args_nbr;
    bool    option;
    
    option = false;
    args_nbr = get_args_nbr(args);
    if (args_nbr > 0)
    {
        while (*args && (ft_strcmp(*args, "echo")))
            args++;
        if (*args && !ft_strcmp(*args, "echo"))
            args++;
        while (*args && ft_strcmp(*args, "-n") == 0)
        {
            option = true;
            args++;
        }
        while (*args)
        {
            ft_putstr_fd(*args, 1);
            if (*(args + 1))
                ft_putstr_fd(" ", 1);
            args++;
        }
        if (!option)
            ft_putstr_fd("\n", 1);
    }
    return (0);
}
