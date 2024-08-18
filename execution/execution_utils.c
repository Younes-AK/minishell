/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:59:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/18 22:57:57 by yakazdao         ###   ########.fr       */
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

void	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0777);
	if (fd_file == -1)
	{
		error_msg2(" : Is a directory", file);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd_file, 1);
		close(fd_file);
	}
}

void	redirect_input(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags);
	if (fd_file == -1)
	{
		error_msg2(" No such file or directory", file);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd_file, 0);
		close(fd_file);
	}
}

static void	make_redirect(char *redirect, char *file)
{
	if (!ft_strcmp(redirect, ">"))
		redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!ft_strcmp(redirect, ">>"))
		redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!ft_strcmp(redirect, "<") || !ft_strcmp(redirect, "<<"))
		redirect_input(file, O_RDONLY);
}

void	check_redirects(char **redirs)
{
	int	i;

	i = 0;
	while (redirs[i])
	{
		if (redirs[i + 1])
		{
			make_redirect(redirs[i], redirs[i + 1]);
		}
		i += 2;
	}
}
