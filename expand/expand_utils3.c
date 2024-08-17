
#include "../minishell.h"

char *handle_variable(const char **start, t_env *env_list,
                             char *result, size_t *result_size)
{
    char        *var_name;
    const char  *var_value;

    var_name = extract_var_name(start);
    var_value = get_env_value(var_name, env_list);
    result = append_value(result, var_value, result_size);
    free(var_name);
    free((char *) var_value);
    return (result);
}

char *process_string(const char *start, t_env *env_list,
                            char *result, size_t *result_size)
{
    char quote_type;

    quote_type = 0;
    while (*start)
    {
        if (*start == '\'' || *start == '"')
        {
            if (quote_type == 0)
                quote_type = *start;
            else if (*start == quote_type)
                quote_type = 0;
        }
        if (*start == '$' && *(start + 1) && !is_whait_spaces(*(start + 1))
            && *(start + 1) != '"' && *(start + 1) != '\'' && quote_type != '\'')
            result = handle_variable(&start, env_list, result, result_size);
        else
        {
            result = append_char(result, *start, result_size);
            start++;
        }
    }
    return (result);
}