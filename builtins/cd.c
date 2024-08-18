/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 10:55:04 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 15:00:39 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
	g_exit_status = 1;
}

static char	*get_env_path(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

static void	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return ;
	if (is_in_env(env, "OLDPWD") == 0)
		env_add(oldpwd, env);
	else
	{
		while (env)
		{
			if (ft_strcmp(env->key, "OLDPWD") == 0)
			{
				free(env->value);
				env->value = strdup(cwd);
				break ;
			}
			env = env->next;
		}
	}
	free(oldpwd);
}

static int	move_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME");
		if (!env_path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), ERROR);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD");
		if (!env_path)
		{
			g_exit_status = 1;
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), ERROR);
		}
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	free(env_path);
	return (ret);
}

void	cd(char **args, t_env *env)
{
	int	cd_ret;

	if (!args[1])
	{
		move_to_path(0, env);
		return ;
	}
	if (!ft_strcmp(args[1], "-"))
		cd_ret = move_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
		{
			print_error(args);
			return ;
		}
		g_exit_status = 0;
	}
}
