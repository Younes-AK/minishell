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

void    update_var_value(char *key, char *value, t_env **env)
{
    t_env *iter;

    iter = *env;
    if (is_env_var(value))
        value = replace(ft_strdup(value), *env);
    while (iter)
    {
        if (!ft_strcmp(iter->key, key))
        {
            free(iter->value);
            iter->value = ft_strdup(value);
            return;
        }
        iter = iter->next;
    }
}
void add_to_env(char *str, t_env **env)
{
    t_env *new_node;
    char **var;

    new_node = malloc(sizeof(t_env));
    var = ft_split(str, '=');
    if (!check_var_exist(var[0], env) && !search(str, '='))
    {
        new_node->key = ft_strdup(var[0]);
        new_node->value = NULL;
        new_node->next = NULL;
        ft_lstadd_back(env, new_node);
    }
    else if (!check_var_exist(var[0], env) && search(str, '='))
    {
        new_node->key = ft_strdup(var[0]);
        new_node->value = ft_strdup(ft_strchr(str, '=') + 1);
        new_node->next = NULL;
        ft_lstadd_back(env, new_node);
    }
    else if (check_var_exist(var[0], env) && search(str, '='))
        update_var_value(var[0], ft_strchr(str, '=') + 1, env);
}

void print_env(t_env *env)
{
    t_env *iter;

    iter = env;
    while (iter)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(iter->key, 1);
        ft_putstr_fd("=",1);
        ft_putstr_fd(iter->value, 1);
        ft_putstr_fd("\n",1);
        iter = iter->next;
    }
}
int ft_export(char **args, t_prog *p)
{
    int nbr_args;
    int i;
    
    i = 0;
    nbr_args = get_args_nbr(args);
    if (nbr_args == 0)
        return (print_env(p->env_list), 0);
    while (i < nbr_args)
    {
        add_to_env(args[i], &p->env_list);
        i++;
    }
    return (0);
}