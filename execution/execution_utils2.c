/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:59:52 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/16 10:23:36 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	execute_command(char **redirs, char **cmds, t_prog *p)
{
	check_redirects(redirs);
	execute(cmds, p);
	return (true);
}

void	exec_builtin_parent(char **cmd, char **redirs, t_prog *p)
{
	check_redirects(redirs);
	exec_builtins(cmd, p);
}

void	close_pipes(t_prog *p)
{
	if (!p->is_first)
		close(p->prev_pipe[0]);
	if (!p->is_last)
	{
		close(p->curr_pipe[1]);
		p->prev_pipe[0] = p->curr_pipe[0];
	}
}

bool	check_is_builtin(char **type, int *index)
{
	if (!type)
		return (false);
	while (*type)
	{
		if (!(ft_strcmp(*type, "echo")) || !(ft_strcmp(*type, "cd"))
			|| !(ft_strcmp(*type, "pwd")) || !(ft_strcmp(*type, "export"))
			|| !(ft_strcmp(*type, "unset")) || !(ft_strcmp(*type, "env"))
			|| !(ft_strcmp(*type, "exit")))
			return (true);
		if (!ft_strcmp(*type, ""))
			type++;
		else
			return (false);
		*index += 1;
	}
	return (false);
}

void	exec_builtins(char **cmd, t_prog *p)
{
	if (!(ft_strcmp(cmd[0], "echo")))
		echo(cmd);
	else if (!(ft_strcmp(cmd[0], "cd")))
		cd(cmd, p->env_list);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		pwd();
	else if (!(ft_strcmp(cmd[0], "unset")))
		ft_unset(cmd, &p->env_list, &p->secret_env);
	else if (!(ft_strcmp(cmd[0], "export")))
		ft_export(cmd, p);
	else if (!(ft_strcmp(cmd[0], "env")))
		env(p->env_list);
	else if (!(ft_strcmp(cmd[0], "exit")))
		ft_exit(cmd);
}
