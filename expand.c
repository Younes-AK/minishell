
#include "minishell.h"

char *remove_qoutes(char *content)
{
    int i;
    int j;
    int len;
    char *str;

    i = 0;
    j = 0;
    len = 0;
    while (content[i++])
        if (content[i] == '"' || content[i] == '$')
            len++;
    i = 0;
    str = safe_allocation(sizeof(char), ft_strlen(content) - len + 1);
    while (content[i] && (content[i] == '"' || content[i] == '$'))
        i++;
    while (content[i] && content[i] != '"')
    {
        if (content[i] == '$')
            i++;
        else
            str[j++] = content[i++];
    }
    str[j] = '\0';
    return (str);
}
char *get_env_val(char *content, t_env **env_list)
{
    t_env *iter;
    char *str;
    int i = 0;
    char *ret;
    ret = ft_strdup("");
    str = remove_qoutes(content);
    char **s = ft_split(str, ' ');
    while (s[i])
    {
        iter = *env_list;
        while (iter)
        {
            if (!ft_strcmp(s[i], iter->key))
                s[i] = iter->value;
            iter = iter->next;
        }
        ret = ft_strjoin(ret, s[i]);
        i++;
    }
    free(str);
    free_double_ptr(s);
    return (ret);
}
bool is_env_var(char *content)
{
    int i;

    i = 0;
    while (content[i])
    {
        if (content[i] == '$')
            return (true);
        i++;
    }
    return (false);
}
bool to_expand(char *content, t_token type)
{
    if (content[0] == '"' && type == WORD)
    {
        if (is_env_var(content))
        {
            return (true);
        }
    }
    return (false);
}
void expand(t_tokenze *list, t_env *env_list)
{
    t_tok_node *iter;
    char *expanded_var;
    iter = list->head;
    while (iter)
    {
        if (to_expand(iter->content, iter->type))
        {
            expanded_var = get_env_val(iter->content, &env_list);
            if (expanded_var)
            {
               free(iter->content);
               iter->content = expanded_var;
            }
        }
        iter = iter->next;
    }
}