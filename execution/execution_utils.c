/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:59:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/23 13:25:51 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

char	**convert_env_list(t_env *env_list, t_prog *p)
{
	int		env_size;
	t_env	*iter;
	char	**env_array;

	env_size = ft_lstsize(env_list);
	env_array = malloc((env_size + 1) * sizeof(char *));
	iter = env_list;
	p->i = 0;
	if (!env_array)
		return (NULL);
	while (iter && p->i < env_size)
	{
		env_array[p->i] = create_env_entry(iter);
		if (!env_array[p->i])
		{
			while (p->i > 0)
				free(env_array[--p->i]);
			free(env_array);
			return (NULL);
		}
		p->i++;
		iter = iter->next;
	}
	env_array[env_size] = NULL;
	return (env_array);
}

bool	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0777);
	if (fd_file == -1)
	{
		error_msg2(" : No such file or directory", file);
		g_exit_status = 1;
		return (false);
	}
	else
	{
		dup2(fd_file, 1);
		close(fd_file);
		return (true);
	}
}

bool	redirect_input(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags);
	if (fd_file == -1)
	{
		g_exit_status = 1;
		error_msg2(" : No such file or directory", file);
		return (false);
	}
	else
	{
		dup2(fd_file, 0);
		close(fd_file);
		return (true);
	}
}

static bool	make_redirect(char *redirect, char *file)
{
	bool	ret;

	ret = true;
	if (!ft_strcmp(redirect, ">"))
		ret = redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!ft_strcmp(redirect, ">>"))
		ret = redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!ft_strcmp(redirect, "<") || !ft_strcmp(redirect, "<<"))
		ret = redirect_input(file, O_RDONLY);
	return (ret);
}

bool	check_redirects(char **redirs)
{
	int	i;

	i = 0;
	while (redirs[i])
	{
		if (redirs[i + 1])
		{
			if (!make_redirect(redirs[i], redirs[i + 1]))
				return (false);
		}
		i += 2;
	}
	return (true);
}
