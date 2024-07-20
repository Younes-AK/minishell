

#include "../minishell.h"

// void append_exec_list(t_prog *p, int index, t_exec_list *exec_list)
// {
//     t_tok_node *iter;
//     t_exec_node *node;
//     t_tok_node *prev;
//     int i = 0;
//     int j;

//     iter = p->list_tok->head;
//     prev = iter;
//     node = safe_allocation(sizeof(t_exec_node), 1);
//     node->cmd = safe_allocation(sizeof(char *) * (p->nbr_cmd + 1), 1);
//     node->redir = safe_allocation(sizeof(char *) * (p->nbr_redir + 1), 1);
//     while (i < index)
//     {
//         while (iter && iter->type != PIPE_LINE)
//             iter = iter->next;
//         if (iter && iter->type == PIPE_LINE)
//             iter = iter->next;
//         i++;
//     }
//     i = 0;
//     j = 0;
//     while (iter && iter->type != PIPE_LINE)
//     {
//        if (iter->type == WORD && (prev->type != REDIR_OUT && prev->type != REDIR_IN
//             && prev->type != REDIR_APPEND && prev->type != REDIR_HEREDOC))
//             node->cmd[i++] = ft_strdup(iter->content);
//         else
//             node->redir[j++] = ft_strdup(iter->content);
//         prev = iter;
//         iter = iter->next;
//     }
//     node->cmd[i] = NULL;
//     node->redir[j] = NULL;
//     node->next = NULL;
//     append_exec(exec_list, node);
// }



#include "../minishell.h"

static void init_exec_node(t_exec_node *node, t_prog *p)
{
    node->cmd = safe_allocation(sizeof(char *) * (p->nbr_cmd + 1), 1);
    node->redir = safe_allocation(sizeof(char *) * (p->nbr_redir + 1), 1);
}

static t_tok_node *move_to_index(t_tok_node *iter, int index)
{
    int i = 0;

    while (i < index)
    {
        while (iter && iter->type != PIPE_LINE)
            iter = iter->next;
        if (iter && iter->type == PIPE_LINE)
            iter = iter->next;
        i++;
    }
    return (iter);
}

static void fill_exec_node(t_exec_node *node, t_tok_node *iter)
{
    t_tok_node *prev;
    int i = 0;
    int j = 0;

    prev = iter;
    while (iter && iter->type != PIPE_LINE)
    {
        if (iter->type == WORD && (prev->type != REDIR_OUT && prev->type != REDIR_IN
            && prev->type != REDIR_APPEND && prev->type != REDIR_HEREDOC))
            node->cmd[i++] = ft_strdup(iter->content);
        else
            node->redir[j++] = ft_strdup(iter->content);
        prev = iter;
        iter = iter->next;
    }
    node->cmd[i] = NULL;
    node->redir[j] = NULL;
    node->next = NULL;
}
void append_exec_list(t_prog *p, int index, t_exec_list *exec_list)

{
    t_tok_node *iter;
    t_exec_node *node;

    iter = p->list_tok->head;
    node = safe_allocation(sizeof(t_exec_node), 1);
    init_exec_node(node, p);
    iter = move_to_index(iter, index);
    fill_exec_node(node, iter);
    append_exec(exec_list, node);
}