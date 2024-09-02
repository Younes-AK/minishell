/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:38:20 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/25 21:46:28 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_var(char *var, t_env **env)
{
	t_env	*iter;
	t_env	*prev;

	if (!env || !*env)
		return ;
	iter = *env;
	prev = NULL;
	while (iter)
	{
		if (!ft_strcmp(iter->key, var) && ft_strcmp(iter->key, "_"))
		{
			if (prev)
				prev->next = iter->next;
			else
				*env = iter->next;
			free(iter->key);
			free(iter->value);
			free(iter);
			return ;
		}
		prev = iter;
		iter = iter->next;
	}
}

void	unset_env(int nbr_args, t_env **env, char **args)
{
	int	i;

	i = 1;
	while (i < nbr_args)
	{
		if (is_valid_identifier(args[i]))
		{
			if (check_var_exist(args[i], env))
				free_env_var(args[i], env);
		}
		else
		{
			error_msg2(" : not a valid identifier", args[i]);
			EXIT_STATUS = 1;
		}
		i++;
	}
}

void	ft_unset(char **args, t_env **env, t_env **s_env)
{
	int	nbr_args;
	int	i;

	nbr_args = get_args_nbr(args);
	i = 1;
	unset_env(nbr_args, env, args);
	while (i < nbr_args)
	{
		if (check_var_exist(args[i], s_env))
			free_env_var(args[i], s_env);
		i++;
	}
	if (EXIT_STATUS != 1)
		EXIT_STATUS = 0;
}
