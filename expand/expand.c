
#include "../minishell.h"


void append_expanded_tokens(t_tok_node *iter, char **tokens, t_prog *p)
{
    char **token_start = tokens;
    while (*tokens)
    {
        append_node11(p, *tokens, ft_strlen(*tokens), iter->type);
        tokens++;
    }
    free(token_start);
}

static void expand_and_append(t_tok_node *iter, char *expanded_var, t_prog *p)
{
    char *tmp = remove_qoutes(expanded_var, p);
    char **tt = ft_split(tmp, ' ', p);
    append_expanded_tokens(iter, tt, p);
    free(expanded_var);
    iter->content = tmp;
}

static bool handle_ambiguous_redirect(t_tok_node *prev, char *expanded_var, t_prog *p)
{
    if (prev->type == REDIR_OUT && (is_ambiguous(expanded_var)
        || !ft_strcmp(expanded_var, "")) && p->is_env_cmd)
    {
        ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
        return false;
    }
    return true;
}

static bool process_token(t_tok_node *iter, t_tok_node *prev, t_env *env_list, t_prog *p)
{
    if (is_env_var(iter->content))
        p->is_env_cmd = true;
    if (to_expand(iter->content, iter->type) && iter->type != REDIR_HEREDOC)
    {
        p->expanded_var = get_env_val(iter->content, env_list);
        if (!handle_ambiguous_redirect(prev, p->expanded_var, p))
            p->is_valid = false;
        else if (p->is_env_cmd)
        {
            p->expanded_var = ft_trim(p->expanded_var);
            if (p->expanded_var)
                expand_and_append(iter, p->expanded_var, p);
        }
    }
    else if (prev->type != REDIR_HEREDOC)
    {
        p->expanded_var = remove_qoutes(iter->content, p);
        free(iter->content);
        iter->content = p->expanded_var;
        append_node11(p, iter->content, ft_strlen(iter->content), iter->type);
    }
    else
        append_node11(p, iter->content, ft_strlen(iter->content), iter->type);
    return (p->is_valid);
}
bool expand(t_tokenze *list, t_env *env_list, t_prog *p)
{
    t_tok_node *iter;
    t_tok_node *prev;

    iter = list->head;
    prev = iter;
    while (iter)
    {
        if (!process_token(iter, prev, env_list, p))
            return (false);
        prev = iter;
        iter = iter->next;
    }
    return (true);
}

