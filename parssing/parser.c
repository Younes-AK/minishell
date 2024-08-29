/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:36:11 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/29 09:05:16 by yakazdao         ###   ########.fr       */
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

char	*get_delemitre(t_prog *p)
{
	t_tok_node	*iter;

	iter = p->list_tok->head;
	while(iter)
	{
		if (iter->next && iter->type == REDIR_HEREDOC)
			if (iter->next->type == WORD)
				return (iter->next->content);
		iter = iter->next;
	}
	return (NULL);
}
int	check_red_syntax(t_prog *p)
{
	bool	check_heredoc;
	t_tok_node	*iter;
	
	check_heredoc = false;
	iter = p->list_tok->head;
	while (iter)
	{
		if (iter->type == REDIR_HEREDOC)
			check_heredoc = true;
		iter = iter->next;
	}
	if (p->list_tok->tail->type == PIPE_LINE  && check_heredoc == true && get_delemitre(p))
		return (2);
	if (p->list_tok->tail->type == REDIR_HEREDOC || \
		p->list_tok->tail->type == REDIR_APPEND
		|| p->list_tok->tail->type == REDIR_IN || \
		p->list_tok->tail->type == REDIR_OUT
		|| p->list_tok->head->type == PIPE_LINE || \
		p->list_tok->tail->type == PIPE_LINE)
		return (1);
	return (0);
}
void read_in(char *delemitre)
{
	char	*input;

	while (true)
	{
		input = readline("> ");
		if (!input)
				return ;
		if (ft_strcmp (input, delemitre) == 0)
		{
			g_exit_status = 0;
			break;
		}
		free(input);
	}	
}
void read_herdoc(char **redirs)
{
	int		i;

	i = 0;
	while (redirs[i])
	{
		if (!ft_strcmp(redirs[i], "<<"))
		{
			read_in(redirs[i + 1]);
		}
		i += 2;
	}
}
void heredoc_error(t_prog *p)
{
	t_exec_node	*iter;

	iter = p->exec_list->head;
	while (iter)
	{
		read_herdoc(iter->redir);
		iter = iter->next;
	}
}
bool	check_syntax(t_prog *p)
{
	t_tok_node	*iter;

	iter = p->list_tok->head;
	if (iter)
	{
		if (check_red_syntax(p) == 1)
			return (false);
		else if(check_red_syntax(p) == 2)
			return (p->heredoc_err = true, true);
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
	p->heredoc_err = false;
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
		if (p->heredoc_err)
		{
			heredoc_error(p);
			write(2, "minishell: syntax error near unexpected token\n", 47);
			g_exit_status = 258;
			return (false);
		}
		if (!ft_heredoc(p))
			return (false);
		return (true);
	}
}
