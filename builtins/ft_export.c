/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:36:16 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/21 21:15:22 by yakazdao         ###   ########.fr       */
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

char *add_quotes(char *s)
{
    char *ret;
    int i = 0;
    ret = safe_allocation(sizeof(char), ft_strlen(s) + 3);

    ret[i++] = '"';
    while (*s)
        ret[i++] = *s++;
    ret[i++] = '"';
    ret[i] = '\0';
    return (ret);
}
void    update_var_value(char *key, char *value, t_env **env, t_prog *p)
{
    t_env *iter;

    iter = *env;
    if (is_env_var(value))
        value = replace(ft_strdup(value), *env);
    while (iter)
    {
        if (!ft_strcmp(iter->key, key))
        {
            if (p->concatanate)
            {
                char *s = ft_strcat(remove_qoutes(iter->value), value);
                iter->value = add_quotes(s);
                free(s);
            }
            else
            {
                free(iter->value);
                iter->value = add_quotes(value);
            }
            return;
        }
        iter = iter->next;
    }
}

void print_env(t_env *env)
{
    t_env *iter;

    iter = env;
    while (iter)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(iter->key, 1);
        if (iter->value)
        {
            ft_putstr_fd("=",1);
            ft_putstr_fd(iter->value, 1);
        }
        ft_putstr_fd("\n",1);
        iter = iter->next;
    }
}
void add_to_env(char *str, t_env **env, t_prog *p)
{
    t_env *new_node;
    char **var;
    
    p->concatanate = false;
    new_node = malloc(sizeof(t_env));
    var = ft_split(str, '=');
    if (var[0][ft_strlen(var[0]) - 1] == '+')
    {
        var[0][ft_strlen(var[0]) - 1] = '\0';
        p->concatanate = true;
    }
    new_node->key = ft_strdup(var[0]);
    new_node->next = NULL;
    if (str[ft_strlen(str) - 1] == '=')
        new_node->value = ft_strdup("\"\"");
    else if (!check_var_exist(var[0], env) && !search(str, '='))
        new_node->value = ft_strdup("");
    else if (!check_var_exist(var[0], env) && search(str, '='))
        new_node->value = add_quotes(ft_strchr(str, '=') + 1);
    if (check_var_exist(var[0], env) && search(str, '='))
    {
        if (p->concatanate)
            update_var_value(var[0], ft_strchr(str, '=') + 1, env, p);
        else
            update_var_value(var[0], ft_strchr(str, '=') + 1, env, p);
        return ;
    }
    ft_lstadd_back(env, new_node);
}
 
bool check_valid_identifier(char *identifier)
{
    if (!identifier || *identifier == '=')
        return (false);
    while (*identifier && *identifier != '=' && *identifier != ' ')
    {
        if (!ft_isalnum(*identifier) && *identifier != '_' && *identifier != '+')
            return (false);
        identifier++;
    }
    return (true);
}

bool ft_toprint(char **args, int *i)
{
    bool to_print;

    to_print = false;
    while (*args)
    {
        if (!ft_strcmp(*args, ""))
        {
            *i += 1;
            to_print = true;
        }
        else
            to_print = false;
        args++;
    }
    return (to_print);
}
int ft_export(char **args, t_prog *p)
{
    int nbr_args;
    int i;
    
    i = 0;
    nbr_args = get_args_nbr(args);
    if (nbr_args == 0 || ft_toprint(args, &i))
        return (print_env(p->env_list), 0);
    while (i < nbr_args)
    {
        if (check_valid_identifier(args[i]))
            add_to_env(args[i], &p->env_list, p);
        else
            ft_putstr_fd("export: not a valid identifier\n", 1);
        i++;
    }
    return (0);
}

 