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

void set_env_value(const char *key, const char *value, t_env **env)
{
    t_env *current;
    char *new_value;
    t_env *new_node;

    current = *env;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    new_value = ft_strjoin(key, "=");
    new_value = ft_strjoin(new_value, value);
    new_node = ft_lstnew(ft_strdup(key), new_value);
    if (new_node)
        ft_lstadd_back(env, new_node);
}
static int update_oldpwd(t_env *env)
{
    char cwd[PATH_MAX];
    char *oldpwd;

    if (getcwd(cwd, PATH_MAX) == NULL)
        return (1);
    oldpwd = ft_strjoin("OLDPWD=", cwd);
    if (!oldpwd)
        return (1);
    set_env_value("OLDPWD", cwd, &env);
    free(oldpwd);
    return (00);
}

int cd(char **args, t_env *env)
{
    int args_nbr;
    char curr_path[PATH_MAX];
    static char prev_path[PATH_MAX];
    
    args_nbr = get_args_nbr(args);
    if (getcwd(curr_path, PATH_MAX) == NULL)
        return (ft_putstr_fd("Error: Unable to get current directory\n", 2), 1);
    if (args_nbr == 1 || (args_nbr == 2 && !ft_strcmp(args[1], "~")))
    {
        char *home = get_env_value("HOME", env);
        if (!home)
            return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
        if (chdir(home) != 0)
            return (ft_putstr_fd("Error: chdir() failed\n", 2), 1);
    }
    else if (args_nbr == 2 && !ft_strcmp(args[1], "-"))
    {
        if (prev_path[0] == '\0')
            return (ft_putstr_fd("minishell: OLDPWD not set\n", 2), 1);
        if (chdir(prev_path) != 0)
            return (ft_putstr_fd("Error: chdir() failed to find path\n", 2), 1);
        ft_putendl_fd(prev_path, 1);
    }
    else if (args_nbr == 2)
    {
        if (!ft_strcmp(args[1], "''") || !ft_strcmp(args[1], "\"\""))
            return (0);
        if (chdir(args[1]) != 0)
            return (ft_putstr_fd("minishell: cd: No such file or directory\n", 2), 1);
    }
    else if (args_nbr > 2)
        return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
    update_oldpwd(env);
    ft_strcpy(prev_path, curr_path);
    return (0);
}