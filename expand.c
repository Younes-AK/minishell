
#include "minishell.h"

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
        if (*start == '$')
        {
            var_name = extract_var_name(&start);
            var_value = get_env_value(var_name, env_list);
            result = append_value(result, var_value, &result_size);
            free (var_name);
        }
        else
        {
            result = append_char(result, *start, &result_size);
            start++;
        }
    }
    return (free(str), result);
}

char *get_env_val(char *str, t_env *env_list) 
{
    char *tmp;
    
    tmp = remove_qoutes(str);
    tmp = replace(tmp, env_list);
    return (tmp);
}

bool is_env_var(char *content) 
{
    int i = 0;
    while (content[i]) 
    {
        if (content[i] == '$')
            return true;
        i++;
    }
    return false;
}

bool to_expand(char *content, t_token type) 
{
    if (content[0] != '\'' && type == WORD) 
    {
        if (is_env_var(content))
            return true;
    }
    return false;
}

void expand(t_tokenze *list, t_env *env_list) 
{
    t_tok_node *iter = list->head;
    while (iter) 
    {
        if (to_expand(iter->content, iter->type)) 
        {
            char *expanded_var = get_env_val(iter->content, env_list);
            if (expanded_var) 
            {
                free(iter->content);
                iter->content = expanded_var;
            }
        }
        iter = iter->next;
    }
}

