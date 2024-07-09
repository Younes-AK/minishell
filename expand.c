
#include "minishell.h"

char *replace(char *str, t_env *env_list) 
{
    // printf("--------->%s\n", str);
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
    
    // tmp = remove_qoutes(str);
    tmp = replace(str, env_list);
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

bool should_expand(const char* command) 
{
    bool in_single_quotes = false;
    bool in_double_quotes = false;
    size_t i = 0;

   while (i < ft_strlen(command)) 
    {
        char c = command[i];
        
        if (c == '\'') 
        {
            if (!in_double_quotes)
                in_single_quotes = !in_single_quotes;
        } 
        else if (c == '"') 
        {
            if (!in_single_quotes)
                in_double_quotes = !in_double_quotes;
        } 
        else if (c == '$' && !in_single_quotes)
            return true;
        i++;
    }
    return false;
}
bool to_expand(char *content, t_token type)
{
    if (type == WORD) 
    {
        if (should_expand(content) && is_env_var(content))
            return (true);
    }
    return (false);
}

void expand(t_tokenze *list, t_env *env_list) 
{   
   char *expanded_var;
    t_tok_node *iter;
    // char *tmp;
    iter = list->head;
    while (iter) 
    {
        if (to_expand(iter->content, iter->type)) 
        {
            expanded_var = get_env_val(iter->content, env_list);
            if (expanded_var) 
            {
                //tmp = remove_qoutes(expanded_var);
                // free(iter->content);
                iter->content = expanded_var;
            }
        }
        else
        {
            if (is_env_var(iter->content))
            {
                expanded_var = remove_qoutes(iter->content);
                free(iter->content);
                iter->content = expanded_var;
            }
        }
        iter = iter->next;
    }
}

