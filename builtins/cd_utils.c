/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:05:34 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/23 20:09:19 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_add(char *oldpwd, t_env *env, t_prog *p, char *type)
{
	while (env)
	{
		if (!strcmp(env->key, type))
		{
			free(env->value);
			env_add(oldpwd, env, p);
			break ;
		}
		env = env->next;
	}
}

void	update_oldpwd(t_env *env, t_prog *p)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return ;
	if (is_in_env(env, "OLDPWD") == 0)
		free_and_add(oldpwd, env, p, "OLDPWD");
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
