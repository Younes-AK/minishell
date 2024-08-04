
#include "../minishell.h"

char *get_env_val(char *str, t_env *env_list) 
{
    char *tmp;
    // tmp = remove_qoutes(str);
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

void expand(t_tokenze *list, t_env *env_list, t_prog *p)
{   
    char *expanded_var;
    t_tok_node *iter;
    t_tok_node *prev;
    char *tmp;
    (void)p;
    iter = list->head;
    prev = iter;
    while (iter)
    {
        if (is_env_var(iter->content))
            p->is_env_cmd = true;
        if (to_expand(iter->content, iter->type) && prev->type != REDIR_HEREDOC) 
        {
            expanded_var = get_env_val(iter->content, env_list);
            if (expanded_var) 
            {
                tmp = remove_qoutes(expanded_var);
                //free(iter->content);
                iter->content = tmp;
            }
        }
        else
        {
            if (prev->type != REDIR_HEREDOC)
            {
                expanded_var = remove_qoutes(iter->content);
                free(iter->content);
                iter->content = expanded_var;
            }
        }
        prev = iter;
        iter = iter->next;
    }
}


