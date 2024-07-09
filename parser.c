/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:36:11 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/09 09:56:48 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void append_exec_list(t_prog *p, int index, t_exec_list *exec_list)
{
    t_tok_node *iter;
    t_exec_node *node;
    int i = 0;
    int j = 0;

    iter = p->list_tok->head;
    node = safe_allocation(sizeof(t_exec_node), 1);
    node->cmd = safe_allocation(sizeof(char *) * (p->nbr_cmd + 1), 1);
    node->redir = safe_allocation(sizeof(char *) * (p->nbr_redir + 1), 1);
    while (i < index)
    {
        while (iter && iter->type != PIPE_LINE)
            iter = iter->next;
        if (iter && iter->type == PIPE_LINE)
            iter = iter->next;
        i++;
    }
    i = 0;
    j = 0;
    while (iter && iter->type != PIPE_LINE)
    {
        if (iter->type == WORD)
            node->cmd[i++] = ft_strdup(iter->content);
        else
            node->redir[j++] = ft_strdup(iter->content);
        iter = iter->next;
    }
    node->cmd[i] = NULL;
    node->redir[j] = NULL;
    node->next = NULL;
    append_exec(exec_list, node);
}


void _init_exec_list(t_prog *p, t_exec_list *exec_list)
{
    t_tok_node *iter;
    int i = 0;
    // if (!p->list_tok->head)  
    //     return;
    iter = p->list_tok->head;
    if (iter)
    {
        while (i < p->nbr_pipe + 1)
        {
            p->nbr_cmd = 0;
            p->nbr_redir = 0;
            while (iter && iter->type != PIPE_LINE)
            {
                if (iter->type == WORD)
                    p->nbr_cmd++;
                else
                    p->nbr_redir++;
                iter = iter->next;
            }
            append_exec_list(p, i, exec_list);
            if (iter)
                iter = iter->next;
            i++;
        }
    }
}

bool check_syntax(t_prog *p)
{
	t_tok_node *iter;
    
	iter = p->list_tok->head;
    if (iter)
    {
        if (p->list_tok->tail->type == REDIR_HEREDOC || p->list_tok->tail->type == REDIR_APPEND
            || p->list_tok->tail->type == REDIR_IN || p->list_tok->tail->type == REDIR_OUT
            || p->list_tok->head->type == PIPE_LINE || p->list_tok->tail->type == PIPE_LINE)
            return (false);
        while (iter)
        {
            if (iter->type == REDIR_HEREDOC || iter->type == REDIR_APPEND ||
                iter->type == REDIR_IN || iter->type == REDIR_OUT)
            {
                if (!iter->next || iter->next->type != WORD)
                    return false;
            }
            if (iter->type == PIPE_LINE && iter->next)
                if (iter->next->type == PIPE_LINE)
                    return false;
            iter = iter->next;
        }
    }
	return (true);
}

void store_env(char **env, t_prog *p)
{
	p->env_list = NULL;
	char **tmp;
	t_env *node;
	int i;
	char *str;
	i = 0;
	while(env[i])
	{
		tmp = ft_split(env[i], '=');
		str = ft_strdup(tmp[0]); 
		node = ft_lstnew(str, strdup(strchr(env[i], '=') + 1));
		ft_lstadd_back(&p->env_list, node);
		free_double_ptr(tmp);
		i++;
	}
}
bool parser(t_prog *p, char **env, t_exec_list *exec_list)
{
	store_env(env, p);
    (void)exec_list;
	if (!check_syntax(p))
	{
		write(2, "minishell: syntax error near unexpected token\n", 47);
		return (false);
	}
	else
	{
		expand(p->list_tok, p->env_list);
		_init_exec_list(p, exec_list);
		return (true);
	}
}
