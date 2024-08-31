/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:45:03 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/25 23:04:24 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*cmd_path;
	int		i;

	i = 0;
	if ((*cmd == '.' && *(cmd + 1) == '/') || *cmd == '/')
		return (cmd);
	cmd_path = ft_strjoin("/", cmd);
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd_path);
		if (access(full_path, X_OK) == 0)
		{
			free(cmd_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(cmd_path);
	return (NULL);
}

char	*get_path(t_env *env_list, char *key)
{
	t_env	*iter;

	iter = env_list;
	while (iter)
	{
		if (!ft_strcmp(iter->key, key))
			return (iter->value);
		iter = iter->next;
	}
	return (NULL);
}

static int check_command_status(char *cmd, t_prog *p)
{
    struct stat st;

    if (is_all_slashes(cmd))
        return 1;

    p->access_path = check_path(p->all_paths, cmd);
    if (stat(cmd, &st) == 0)
    {
        if (S_ISDIR(st.st_mode))
            return 1;
        if (p->access_path)
            return 0;
        else if (st.st_mode & S_IXUSR)
            return 5;
        else
            return 2;
    }
    else if (errno == ENOENT)
    {
        if (p->access_path)
            return 0;
        else
            return 3;
    }
    else
        return 4;
}

static void execute_cmd(char **cmd, t_prog *p)
{
    if (!cmd || !*cmd)
        return;
    p->cmd_status = check_command_status(cmd[0], p);
    if (!ft_strcmp(*cmd, "minishell"))
        error_msg1(": command not found", cmd[0], 127);
    else if (p->cmd_status == 1)
        error_msg1(": is a directory", cmd[0], 126);
    else if (p->cmd_status == 2)
        error_msg1(": Permission denied", cmd[0], 126);
    else if (p->cmd_status == 3)
    {
        if (ft_strchr(cmd[0], '/'))
            error_msg1(": No such file or directory", cmd[0], 127);
        else
            error_msg1(": command not found", cmd[0], 127);
    }
    else if (p->cmd_status == 4)
        error_msg1(": Error accessing file", cmd[0], 126);
    else if (p->cmd_status == 5)
        p->access_path = ft_strdup(cmd[0]);
    p->env_variables = convert_env_list(p->env_list, p);
    if (p->access_path)
        execve(p->access_path, cmd, p->env_variables);
    error_msg2(": command not found", cmd[0]);
    (free(p->access_path),  free_double_ptr(p->env_variables));
   exit(127);
}

void	execute(char **cmd, t_prog *p)
{
	if (!cmd || !*cmd)
		return ;
	p->path = get_path(p->env_list, "PATH");
	p->all_paths = ft_split(p->path, ':', p);
	execute_cmd(cmd, p);
	free_double_ptr(p->all_paths);
}
