/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 07:55:32 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/09 12:17:17 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_var_name(const char **start) 
{
    const char *end = *start + 1;
    char *var_name;
    size_t var_size;
    if (*end == '$' || *end == '@' || *end == '*' || *end == '#'
        || *end == '?' || *end == '-' || *end == '!' || ft_isdigit(*end))
    {
        var_name = safe_allocation(sizeof(char), 3);
        var_name[0] = '$';
        var_name[1] = *end;
        var_name[2] = '\0';
        *start = end + 1;
        return (var_name);
    }
    while (*end && (ft_isalnum(*end) || *end == '_' || *end == '@' || *end == '$'))
        end++;
    var_size = end - *start - 1;
    var_name = safe_allocation(sizeof(char), var_size + 1);
    ft_strncpy(var_name, *start + 1, var_size);
    var_name[var_size] = '\0';
    *start = end;
    return (var_name);
}
// char *extract_var_name(const char **start) 
// {
//     const char *end = *start + 1;
//     if (*end == '$' || *end == '@' || *end == '*' || *end == '#' ||
//         *end == '?' || *end == '-' || *end == '!' || *end == '0') {
//         end++;
//     } else {
//         while (*end && (ft_isalnum(*end) || *end == '_')) {
//             end++;
//         }
//     }
//     size_t var_size = end - *start - 1;
//     char *var_name = safe_allocation(sizeof(char), var_size + 1);
//     ft_strncpy(var_name, *start + 1, var_size);
//     var_name[var_size] = '\0';
//     *start = end;
//     return var_name;
// }



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
    return res;
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

char *remove_qoutes(char *content) 
{
    int i = 0;
    int j = 0;
    bool in_double_quotes = false;
    bool in_single_quotes = false;
    int len = ft_strlen(content);
    char *str = safe_allocation(sizeof(char), len + 2);
    while (content[i])
    {
        if (content[i] == '"' && !in_single_quotes) 
            in_double_quotes = !in_double_quotes;
        else if (content[i] == '\'' && !in_double_quotes)
            in_single_quotes = !in_single_quotes;
        else if (!(content[i] == '$' && in_single_quotes))
            str[j++] = content[i];
        if (content[i] == '$')
            str[j++] = content[i];
        i++;
    }
    str[j] = '\0';
    // char *s = "...........$sdfghjkl;$HOME";
    return str;
}

char *get_env_value(const char *var_name, t_env *env_list) 
{
    t_env *iter;
    char *pid_str;
    printf("--> %s\n", var_name);
    
    if (ft_strcmp(var_name, "$$") == 0) 
    {
        pid_str = safe_allocation(sizeof(char), 20);
        sprintf(pid_str, "%d", getpid());
        return (pid_str);
    }
    // if (strcmp(var_name, "$?") == 0) {
    //     // return last exit status
    // }
    iter = env_list;
    while (iter) 
    {
        if (ft_strcmp(iter->key, var_name) == 0) 
            return iter->value;
        iter = iter->next;
    }
    return ("");
}

