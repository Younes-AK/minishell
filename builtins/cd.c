/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 10:55:04 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/01 10:28:00 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_args_nbr1(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

char *get_env_var(char *path, t_env *env)
{
    while (env)
    {
        if (!ft_strcmp(path, env->key))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

int cd(char **args, t_env *env)
{
    int args_nbr;
    char curr_path[PATH_MAX];
    static char prev_path[PATH_MAX];
    char *new_path;
    
    args_nbr = get_args_nbr1(args);
    getcwd(curr_path, PATH_MAX);
    if (args_nbr == 1 && !ft_strcmp(args[0], "cd"))
    {
        if (chdir(get_env_var("HOME", env)) != 0)
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
        args[1] = ft_strjoin("/", args[1]);
        new_path = ft_strjoin(curr_path, args[1]);
        if (chdir(new_path) != 0)
            return (ft_putstr_fd("Error chdir() failled to found path\n", 2), 1);
    }
    strcpy(prev_path, curr_path);
    return (0);
}
