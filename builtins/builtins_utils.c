/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:11:59 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/20 23:35:49 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_env(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	env_add(char *new_var, t_env *env)
{
	char	*delimiter;
	size_t	key_len;
	t_env	*new_node;
	char	*tmp;

	tmp = new_var;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	delimiter = ft_strchr(new_var, '=');
	key_len = delimiter - new_var;
	new_node->key = strndup(new_var, key_len);
	new_node->value = strdup(delimiter + 1);
	new_node->next = NULL;
	// free(tmp);
	while (env->next)
		env = env->next;
	env->next = new_node;
}

long int	modulo(long int nbr)
{
	long int	result;

	result = nbr % 256;
	if (result < 0)
		result += 256;
	return (result);
}

void	print_envi(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

void	__ft_add(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	ft_lstadd_back(env, node);
}
