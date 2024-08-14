

#include "../minishell.h"

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
    while (*end && (ft_isalpha(*end) || *end == '_'))
        end++;
    var_size = end - *start - 1;
    var_name = safe_allocation(sizeof(char), var_size + 1);
    ft_strncpy(var_name, *start + 1, var_size);
    var_name[var_size] = '\0';
    *start = end;
    return (var_name);
}

char *get_env_val(char *str, t_env *env_list)
{
    char *tmp;
    if (str[0] == '$' && !str[1])
        return (str);
    tmp = replace(str, env_list);
    return (tmp);
}

bool should_expand(const char* command) 
{
    bool    in_s_quotes;
    bool    in_d_quotes;
    char    c;
    size_t  i;

    in_s_quotes = false;
    in_d_quotes = false;
    i = 0;
    while (i < ft_strlen(command)) 
    {
        c = command[i];
        if (c == '\'') 
        {
            if (!in_d_quotes)
                in_s_quotes = !in_s_quotes;
        } 
        else if (c == '"') 
        {
            if (!in_s_quotes)
                in_d_quotes = !in_d_quotes;
        } 
        else if (c == '$' && !in_s_quotes)
            return (true);
        i++;
    }
    return (false);
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
bool is_ambiguous(const char *filename)
{
    int count = 0;
    const char *ptr;

    ptr = filename;
    while (*ptr) 
    {
        while (*ptr && (*ptr == ' ' || *ptr == '\t'))
            ptr++;
        if (*ptr)
            count++;
        while (*ptr && (*ptr != ' ' && *ptr != '\t'))
            ptr++;
    }
    return (count > 1);
}