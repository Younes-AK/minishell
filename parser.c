/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:36:11 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/31 11:31:17 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_syntax(t_prog *p)
{
	t_node *iter;
	iter = p->list->head;
	if (p->list->tail->type == REDIR_HEREDOC || p->list->tail->type == REDIR_APPEND
		|| p->list->tail->type == REDIR_IN || p->list->tail->type == REDIR_OUT)
		return (false);
	while (iter)
    {
        if (iter->type == REDIR_HEREDOC || iter->type == REDIR_APPEND ||
            iter->type == REDIR_IN || iter->type == REDIR_OUT)
        {
            if (!iter->next || iter->next->type != WORD)
                return false;
        }
        if (iter->type == PIPE_LINE)
            if (iter->next->type == PIPE_LINE)
                return false;
        iter = iter->next;
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
bool parser(t_prog *p, char **env)
{
	store_env(env, p);
	if (!check_syntax(p))
	{
		write(2, "Syntax Error\n", 14);
		return (false);
	}
	else
	{
		return (true);
	}
}