/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-asri <oel-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:45:03 by yakazdao          #+#    #+#             */
/*   Updated: 2024/09/07 02:29:49 by oel-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*cmd_path;
	int		i;

	i = 0;
	if ((*cmd == '.' && *(cmd + 1) == '/') || *cmd == '/'
		|| ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!paths)
		return (NULL);
	cmd_path = ft_strjoin("/", cmd);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd_path);
		if (access(full_path, X_OK) == 0)
			return (free(cmd_path), full_path);
		free(full_path);
		i++;
	}
	return (free(cmd_path), NULL);
}

static int	check_command_status(char *cmd, t_prog *p)
{
	if (!ft_strcmp(cmd, ""))
		return (3);
	if (is_all_slashes(cmd) || !ft_strcmp(cmd, ".."))
		return (1);
	p->access_path = check_path(p->all_paths, cmd);
	if (!p->access_path && ft_strchr(cmd, '/'))
		p->access_path = ft_strdup(cmd);
	if (p->access_path)
		p->path_to_check = p->access_path;
	else
		p->path_to_check = cmd;
	if (stat(p->path_to_check, &p->st) == 0)
	{
		if (S_ISDIR(p->st.st_mode))
			return (1);
		if (access(p->path_to_check, X_OK) == 0)
			return (5);
		return (2);
	}
	if (p->access_path)
		return (0);
	if (errno == ENOENT)
		return (3);
	return (4);
}

static void	handle_command_errors(char **cmd, int cmd_status)
{
	if (cmd_status == 1)
		error_msg1("is a directory", cmd[0], 126);
	else if (cmd_status == 2)
		error_msg1("Permission denied", cmd[0], 126);
	else if (cmd_status == 3)
	{
		if (ft_strchr(cmd[0], '/'))
			error_msg1("No such file or directory", cmd[0], 127);
		else
			error_msg1("command not found", cmd[0], 127);
	}
	else if (cmd_status == 4)
		error_msg1(strerror(errno), cmd[0], 126);
	else
		return ;
}

static void	execute_cmd(char **cmd, t_prog *p)
{
	if (!cmd || !*cmd)
		return ;
	if (!ft_strcmp(*cmd, "minishell") || !ft_strcmp(*cmd, ".."))
		error_msg1("command not found", cmd[0], 127);
	p->cmd_status = check_command_status(cmd[0], p);
	handle_command_errors(cmd, p->cmd_status);
	if (p->cmd_status == 2 || p->cmd_status == 5)
	{
		if (!p->access_path)
			p->access_path = ft_strdup(cmd[0]);
	}
	p->env_variables = convert_env_list(p->env_list, p);
	if (p->access_path)
	{
		execve(p->access_path, cmd, p->env_variables);
		error_msg1(strerror(errno), cmd[0], 127);
	}
	error_msg2("execve fialed", cmd[0]);
	(free(p->access_path), free_double_ptr(p->env_variables), exit(127));
}

void	execute(char **cmd, t_prog *p)
{
	if (!cmd || !*cmd)
		return ;
	p->path = get_path(p->env_list, "PATH");
	p->all_paths = ft_split(p->path, ":", p);
	execute_cmd(cmd, p);
	free_double_ptr(p->all_paths);
}
// void	execute(char **cmd, t_prog *p)
// {
// 	if (!cmd || !*cmd)
// 		return ;
// 	p->path = get_path(p->env_list, "PATH");
// 	p->all_paths = p->path ? ft_split(p->path, ":", p) : NULL;
// 	execute_cmd(cmd, p);
// 	free_double_ptr(p->all_paths);
// }
