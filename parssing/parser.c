/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:36:11 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/21 19:50:55 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

bool	increment_cmd(t_tok_node *iter, t_tok_node *prev)
{
	if (iter->type == WORD && (prev->type != REDIR_OUT && prev->type != REDIR_IN
			&& prev->type != REDIR_APPEND && prev->type != REDIR_HEREDOC))
		return (true);
	return (false);
}

void	_init_exec_list(t_prog *p, t_exec_list *exec_list)
{
	t_tok_node	*iter;
	t_tok_node	*prev;

	1 && (p->i = 0, iter = p->new_tok_list->head, prev = iter);
	if (iter)
	{
		while (p->i < p->nbr_pipe + 1)
		{
			p->nbr_cmd = 0;
			p->nbr_redir = 0;
			while (iter && iter->type != PIPE_LINE)
			{
				if (increment_cmd(iter, prev))
					p->nbr_cmd++;
				else
					p->nbr_redir++;
				prev = iter;
				iter = iter->next;
			}
			append_exec_list(p, p->i, exec_list);
			if (iter)
				iter = iter->next;
			p->i++;
		}
	}
}

bool	check_red_syntax(t_prog *p)
{
	if (p->list_tok->tail->type == REDIR_HEREDOC || \
		p->list_tok->tail->type == REDIR_APPEND
		|| p->list_tok->tail->type == REDIR_IN || \
		p->list_tok->tail->type == REDIR_OUT
		|| p->list_tok->head->type == PIPE_LINE || \
		p->list_tok->tail->type == PIPE_LINE)
		return (false);
	return (true);
}

bool	check_syntax(t_prog *p)
{
	t_tok_node	*iter;

	iter = p->list_tok->head;
	if (iter)
	{
		if (!check_red_syntax(p))
			return (false);
		while (iter)
		{
			if (iter->type == REDIR_HEREDOC || iter->type == REDIR_APPEND
				|| iter->type == REDIR_IN || iter->type == REDIR_OUT)
			{
				if (!iter->next || iter->next->type != WORD)
					return (false);
			}
			if (iter->type == PIPE_LINE && iter->next)
				if (iter->next->type == PIPE_LINE)
					return (false);
			iter = iter->next;
		}
	}
	return (true);
}

bool	parser(t_prog *p)
{
	if (!check_syntax(p))
	{
		write(2, "minishell: syntax error near unexpected token\n", 47);
		g_exit_status = 258;
		return (false);
	}
	else
	{
		if (!expand(p->list_tok, p->env_list, p))
			return (false);
		_init_exec_list(p, p->exec_list);
		ft_heredoc(p);
		return (true);
	}
}
