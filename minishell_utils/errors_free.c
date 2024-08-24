/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:32 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/23 13:12:13 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	error_msg1(char *msg, char *arg, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_status);
}

void	error_msg2(char *msg, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void	free_exec_list(t_exec_list *exec_list)
{
	t_exec_node	*curr;
	t_exec_node	*next;

	if (!exec_list)
		return ;
	curr = exec_list->head;
	while (curr)
	{
		next = curr->next;
		if (curr->cmd)
			free_double_ptr(curr->cmd);
		if (curr->redir)
			free_double_ptr(curr->redir);
		free(curr);
		curr = next;
	}
	free(exec_list);
}
