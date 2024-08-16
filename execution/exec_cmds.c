/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:45:03 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/15 20:48:18 by yakazdao         ###   ########.fr       */
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

bool	check_dir(const char *content, t_prog *p)
{
	p->has_non_dot_or_slash = false;
	1 && (p->i = 0, p->dot_count = 0);
	if (strlen(content) == 0)
		return (false);
	while (p->i < (int)strlen(content))
	{
		if (content[p->i] == '.')
		{
			if (p->dot_count < 2)
				p->dot_count++;
		}
		else if (content[p->i] != '/' && (p->has_non_dot_or_slash = true))
			break ;
		else if (p->dot_count > 0)
			break ;
		p->i++;
	}
	if (p->has_non_dot_or_slash)
		return (false);
	if (p->dot_count == 0 || p->dot_count <= 2)
		return (true);
	return (false);
}

static void	execute_cmd(char **cmd, t_prog *p)
{
	char	**env_variables;

	if (!cmd || !*cmd)
		return ;
	if (!ft_strcmp(*cmd, "."))
	{
		error_msg2(" : filename argument required", cmd[0]);
		exit(2);
	}
	p->access_path = check_path(p->all_paths, cmd[0]);
	if (!p->access_path || !ft_strcmp(*cmd, ".."))
	{
		error_msg2(" : command not found", cmd[0]);
		exit(127);
	}
	if (check_dir(*cmd, p) && ft_strcmp(*cmd, "./minishell"))
	{
		error_msg2(" : Is a directory", cmd[0]);
		exit(126);
	}
	env_variables = convert_env_list(p->env_list);
	execve(p->access_path, cmd, env_variables);
	error_msg2(" : command not found", cmd[0]);
	free(p->access_path);
	free_double_ptr(env_variables);
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
