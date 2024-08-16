/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:21:29 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/16 10:05:04 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_exec_node(t_exec_node *node, t_prog *p)
{
	node->cmd = safe_allocation(sizeof(char *) * (p->nbr_cmd + 1), 1);
	if (!node->cmd)
	{
		free (node);
		ft_free_lists(p, "exit");
	}
	node->redir = safe_allocation(sizeof(char *) * (p->nbr_redir + 1), 1);
	if (!node->redir)
	{
		free (node);
		free_double_ptr(node->cmd);
		ft_free_lists(p, "exit");
	}
}

static t_tok_node	*move_to_index(t_tok_node *iter, int index)
{
	int	i;

	i = 0;
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

static void	fill_exec_node(t_exec_node *node, t_tok_node *iter)
{
	int			i;
	int			j;
	t_tok_node	*prev;

	j = 0;
	i = 0;
	prev = iter;
	while (iter && iter->type != PIPE_LINE)
	{
		if (iter->type == WORD && (prev->type != REDIR_OUT
				&& prev->type != REDIR_IN
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

void	append_exec_list(t_prog *p, int index, t_exec_list *exec_list)

{
	t_tok_node	*iter;
	t_exec_node	*node;

	iter = p->new_tok_list->head;
	node = safe_allocation(sizeof(t_exec_node), 1);
	if (!node)
		ft_free_lists(p, "exit");
	init_exec_node(node, p);
	iter = move_to_index(iter, index);
	fill_exec_node(node, iter);
	append_exec(exec_list, node);
}
