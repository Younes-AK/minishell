/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 10:55:04 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/11 07:56:45 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int cd(char **args, t_env *env)
{
    int args_nbr;
    char curr_path[PATH_MAX];
    static char prev_path[PATH_MAX];
    char *new_path;
    
    args_nbr = get_args_nbr(args);
    getcwd(curr_path, PATH_MAX);
    if (args_nbr == 1 || (args_nbr == 2 && !ft_strcmp(args[1], "~")))
    {
        if (chdir(get_env_value("HOME", env)) != 0)
            return (ft_putstr_fd("Error chdir() failled to found path\n", 2), 1);
    }
    else if (args_nbr == 2 && !ft_strcmp(args[1], "-"))
    {
        if (prev_path[0] == '\0')
            return (ft_putstr_fd("minishell : OLDPWD not set\n", 2), 1);
        if (chdir(prev_path) != 0)
            return (ft_putstr_fd("Error chdir() failled to found path\n", 2), 1);
        ft_putstr_fd(prev_path, 1);
        ft_putstr_fd("\n", 1);
    }
    else if (args_nbr > 1)
    {
        if (!ft_strcmp(args[1], "''") || !ft_strcmp(args[1], "\"\""))
            return (0);
        args[1] = ft_strjoin("/", args[1]);
        new_path = ft_strjoin(curr_path, args[1]);
        if (chdir(new_path) != 0)
            return (ft_putstr_fd("Error11 chdir() failled to found path\n", 2), 1);
    }
    ft_strcpy(prev_path, curr_path);
    return (0);
}
