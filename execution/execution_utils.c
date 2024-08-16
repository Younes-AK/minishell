/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:59:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/16 10:21:49 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_env_list(t_env *env_list)
{
	size_t	env_size;
	char	**env_array;
	t_env	*iter;
	size_t	i;
	size_t	key_len;
	size_t	value_len;

	env_size = ft_lstsize(env_list);
	env_array = malloc((env_size + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	iter = env_list;
	i = 0;
	while (iter && i < env_size)
	{
		key_len = ft_strlen(iter->key);
		value_len = ft_strlen(iter->value);
		env_array[i] = malloc(key_len + value_len + 2);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (NULL);
		}
		ft_strcpy(env_array[i], iter->key);
		env_array[i][key_len] = '=';
		ft_strcpy(env_array[i] + key_len + 1, iter->value);
		i++;
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
