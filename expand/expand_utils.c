/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 07:55:32 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/09 13:25:41 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int exit_status;

char *append_value(char *res, const char *value, size_t *res_size) 
{
    size_t res_len;
    size_t new_res_size;
    size_t value_len;

    res_len = strlen(res);
    value_len = strlen(value);
    new_res_size = res_len + value_len + 1;
    if (new_res_size > *res_size) 
    {
        res = ft_realloc(res, *res_size, new_res_size);
        *res_size = new_res_size;
    }
    ft_strcat(res, value);
    return (res);
}

char *append_char(char *res, char c, size_t *res_size) 
{
    size_t len;
    
    len = ft_strlen(res);
    if (len + 2 > *res_size) 
    {
        res = ft_realloc(res, *res_size, len + 2);
        if (!res) 
        {
            error_msg("Error\nmalloc failled allocate memory");
            exit(1);
        }
        *res_size = len + 2;
    }
    res[len] = c;
    res[len + 1] = '\0';
    return (res);
}

char *remove_qoutes(char *content, t_prog *p)
{
    int i = 0;
    int j = 0;
    bool in_double_quotes = false;
    bool in_single_quotes = false;
    int len = ft_strlen(content);
    char *str = safe_allocation(sizeof(char), len + 2);
    if (!str)
    {
        free(content);
        ft_free_lists(p, "exit");
    }
    while (content[i])
    {
        if (content[i] == '"' && !in_single_quotes) 
            in_double_quotes = !in_double_quotes;
        else if (content[i] == '\'' && !in_double_quotes)
            in_single_quotes = !in_single_quotes;
        else if (!(content[i] == '$' && in_single_quotes))
            str[j++] = content[i];
        else if (content[i] == '$')
            str[j++] = content[i];
        i++;
    }
    str[j] = '\0';
    return (str);
}

char *get_env_value(const char *var_name, t_env *env_list)
{
    t_env *iter;
    char *pid_str;
    char *result;
    if (ft_strcmp(var_name, "$$") == 0)
    {
        pid_str = ft_strdup(var_name + 1);
        return (pid_str);
    }
    if (ft_strcmp(var_name, "$?") == 0) 
    {
        result = safe_allocation(sizeof(char), 1);
        result = ft_itoa(exit_status);
        return (result);
    }
    iter = env_list;
    while (iter) 
    {
        if (ft_strcmp(iter->key, var_name) == 0) 
            return iter->value;
        iter = iter->next;
    }
    return ("");
}

char *replace(char *str, t_env *env_list)
{
    size_t result_size;
    char    *result;
    const char  *start;
    char    *var_name;
    const char  *var_value;
    result_size = ft_strlen(str) + 1;
    result = safe_allocation(sizeof(char), result_size);
    result[0] = '\0';
    start = str;
   while (*start)
    {
        if (*start == '$' && *(start + 1) && !is_whait_spaces(*(start + 1)) && *(start + 1) != '"' && *(start + 1) != '\'')
        {
            var_name = extract_var_name(&start);
            var_value = get_env_value(var_name, env_list);
            result = append_value(result, var_value, &result_size);
            free(var_name);
        }
        else
        {
            result = append_char(result, *start, &result_size);
            start++;
        }
    }
    return (free(str), result);
}
