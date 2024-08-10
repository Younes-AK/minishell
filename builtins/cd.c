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

static void print_error(char **args) 
{
    ft_putstr_fd("cd: ", 2);
    if (args[2])
        ft_putstr_fd("string not in pwd: ", 2);
    else {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(args[1], 2);
}

static char *get_env_path(t_env *env, const char *key) 
{
    while (env) 
    {
        if (strcmp(env->key, key) == 0)
            return strdup(env->value);
        env = env->next;
    }
    return NULL;
}

static int update_oldpwd(t_env *env) 
{
    char cwd[PATH_MAX];
    char *oldpwd;

    if (getcwd(cwd, PATH_MAX) == NULL)
        return ERROR;
    if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
        return ERROR;
    if (is_in_env(env, "OLDPWD") == 0)
        env_add(oldpwd, env);
    else 
    {
        while (env) 
        {
            if (strcmp(env->key, "OLDPWD") == 0) 
            {
                free(env->value);
                env->value = strdup(cwd);
                break;
            }
            env = env->next;
        }
    }
    free(oldpwd);
    return SUCCESS;
}

static int go_to_path(int option, t_env *env) 
{
    int ret;
    char *env_path = NULL;

    if (option == 0) {
        update_oldpwd(env);
        env_path = get_env_path(env, "HOME");
        if (!env_path) {
            ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
            return ERROR;
        }
    } else if (option == 1) {
        env_path = get_env_path(env, "OLDPWD");
        if (!env_path) {
            ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
            return ERROR;
        }
        update_oldpwd(env);
    }
    ret = chdir(env_path);
    free(env_path);
    return ret;
}

int cd(char **args, t_env *env) 
{
    int cd_ret;

    if (!args[1])
        return go_to_path(0, env);
    if (strcmp(args[1], "-") == 0)
        cd_ret = go_to_path(1, env);
    else 
    {
        update_oldpwd(env);
        cd_ret = chdir(args[1]);
        if (cd_ret < 0) 
        {
            print_error(args);
            return cd_ret;
        }
    }
    return (0);
}
