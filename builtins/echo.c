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
extern int exit_status;

static bool parse_echo_options(char **args, int *i)
{
    bool option_n = false;

    while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
    {
        char *p = args[*i] + 1;
        while (*p == 'n') p++;
        if (*p == '\0')
        {
            option_n = true;
            (*i)++;
        }
        else
            break;
    }
    return (option_n);
}

static void print_echo_args(char **args, int i, bool option_n)
{
    bool first;
    
    first = true;
    while (args[i])
    {
        if (!first)
            ft_putchar_fd(' ', STDOUT_FILENO);
        ft_putstr_fd(args[i], STDOUT_FILENO);
        first = false;
        i++;
    }

    if (!option_n)
        ft_putchar_fd('\n', STDOUT_FILENO);
}

int echo(char **args)
{
    int i = 1;
    bool option_n = parse_echo_options(args, &i);
    print_echo_args(args, i, option_n);
    exit_status = 0;
    return 0;
}
