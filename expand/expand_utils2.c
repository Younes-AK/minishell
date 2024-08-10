

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