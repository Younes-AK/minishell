
#include "minishell.h"

char *remove_qoutes(char *content) 
{
    int i = 0;
    int j = 0;
    bool in_double_quotes = false;
    bool in_single_quotes = false;
    int len = strlen(content);
    char *str = safe_allocation(sizeof(char), len + 1);

    while (content[i]) 
    {
        if (content[i] == '"' && !in_single_quotes) 
            in_double_quotes = !in_double_quotes;
        else if (content[i] == '\'' && !in_double_quotes)
            in_single_quotes = !in_single_quotes;
        else if (!(content[i] == '$' && in_single_quotes))
            str[j++] = content[i];
        i++;
    }
    str[j] = '\0';
    return str;
}

char *get_env_value(char *var_name, t_env *env_list) 
{
    t_env *iter = env_list;
    bool    flg;
    flg = false;
    while (*var_name && (ft_isdigit(*var_name) || *var_name == '@'))
    {
        flg = true;
        var_name++;
    }
    if (flg)
        return (var_name);
    while (iter) 
    {
        if (ft_strcmp(iter->key, var_name) == 0)
            return iter->value;
        iter = iter->next;
    }
    return "";
}

char *replace(char *str, t_env *env_list) 
{
    char *result;
    const char *start;
    const char *end;
    size_t var_len;
    char *var_name;
    const char *var_value;
    
    result = safe_allocation(sizeof(char), ft_strlen(str) + 1);
    result[0] = '\0';
    start = str;
    while (*start) 
    {
        if (*start == '$') 
        {
            end = start + 1;
            while (*end && (ft_isalnum(*end) || *end == '_' || *end == '@')) 
                end++;
            var_len = end - start - 1;
            var_name = safe_allocation(sizeof(char), var_len + 1);
            strncpy(var_name, start + 1, var_len);
            var_name[var_len] = '\0';
            var_value = get_env_value(var_name, env_list);
            result = ft_realloc(result, ft_strlen(result) + ft_strlen(var_value) + 1);
            ft_strcat(result, var_value);
            free(var_name);
            start = end;
        } 
        else 
        {
            size_t len = ft_strlen(result);
            result[len] = *start;
            result[len + 1] = '\0';
            start++;
        }
    }
    return (free(str) ,result);
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
    while (content[i]) {
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
    t_tok_node *iter;
    char *expanded_var;
    
    iter = list->head;
    while (iter) 
    {
        if (to_expand(iter->content, iter->type)) {
            expanded_var = get_env_val(iter->content, env_list);
            if (expanded_var) 
            {
                free(iter->content);
                iter->content = expanded_var;
            }
        }
        else
        {
            expanded_var = remove_qoutes(iter->content);
            iter->content = expanded_var;
        }
        iter = iter->next;
    }
}


