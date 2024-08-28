/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:04:53 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/28 17:01:21 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

void	setup_child_pipes(t_prog *p)
{
	if (!p->is_first)
	{
		if (dup2(p->prev_pipe[0], STDIN_FILENO) == -1)
		{
			error_msg("dup2 failled");
			ft_free_lists(p, "exit");
		}
		close(p->prev_pipe[0]);
	}
	if (!p->is_last)
	{
		if (dup2(p->curr_pipe[1], STDOUT_FILENO) == -1)
		{
			error_msg("dup2 failled");
			ft_free_lists(p, "exit");
		}
		close(p->curr_pipe[1]);
		close(p->curr_pipe[0]);
	}
}

void	handle_child_process(t_exec_node *node, t_prog *p)
{
	int	index;

	index = 0;
	setup_child_pipes(p);
	if (check_is_builtin(node->cmd, &index))
	{
		if (!check_redirects(node->redir))
			return ;
		exec_builtins(node->cmd, p);
	}
	else
	{
		if (!execute_command(node->redir, node->cmd, p))
		{
			if (!p->is_last)
			{
				close(p->curr_pipe[1]);
				dup2(p->curr_pipe[0], STDIN_FILENO);
			}
			exit(1);
		}
	}
	exit(0);
}

void	wait_for_children(t_prog *p)
{
	int		status;
	void	(*orig_sigint_handler)(int);
	int		i;

	i = 0;
	orig_sigint_handler = signal(SIGINT, SIG_IGN);
	while (waitpid(p->pids[i], &status, WUNTRACED) > 0)
	{
		if (g_exit_status != 1)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_exit_status = WTERMSIG(status) + 128;
		}
		i++;
	}
	signal(SIGINT, orig_sigint_handler);
}

void	fork_and_execute(t_exec_node *node, t_prog *p, int *index)
{
	pid_t	pid;

	pid = fork();
	p->pids[*index] = pid;
	(*index)++;
	if (pid == 0)
		handle_child_process(node, p);
	else if (pid < 0)
	{
		ft_free_lists(p, "exit");
		ft_putstr_fd("fork function fialled\n", 2);
	}
}

void	execution(t_prog *p, t_exec_list *list)
{
	t_exec_node	*node;
	int			index;
	int			pid_index;

	if (!list || !list->head)
		return ;
	1 && (pid_index = 0, p->original_stdout = dup(1), index = 0);
	1 && (p->is_first = true, node = list->head);
	p->pids = safe_allocation(sizeof(int), p->nbr_pipe + 2);
	while (node)
	{
		p->is_last = (node->next == NULL);
		if (!p->is_last)
			pipe(p->curr_pipe);
		if (check_is_builtin(node->cmd, &index) && p->is_first && p->is_last)
			exec_builtin_parent(node->cmd + index, node->redir, p);
		else
			fork_and_execute(node, p, &pid_index);
		close_pipes(p);
		p->is_first = false;
		node = node->next;
	}
	wait_for_children(p);
	dup2(p->original_stdout, STDOUT_FILENO);
	close(p->original_stdout);
}
