/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-asri <oel-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:11:59 by yakazdao          #+#    #+#             */
/*   Updated: 2024/09/07 02:25:47 by oel-asri         ###   ########.fr       */
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

void	env_add(char *new_var, t_env *env, t_prog *p)
{
	char	*delimiter;
	size_t	key_len;
	t_env	*new_node;
	char	*tmp;

	tmp = new_var;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		error_msg("Error : malloc fialed allocate memory\n");
		ft_free_lists(p, "exit");
	}
	delimiter = ft_strchr(new_var, '=');
	key_len = delimiter - new_var;
	new_node->key = strndup(new_var, key_len);
	new_node->value = strdup(delimiter + 1);
	new_node->next = NULL;
	while (env && env->next)
		env = env->next;
	if (env)
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

void	__ft_add(t_env **env, char *key, char *value, t_prog *p)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		error_msg("Error : malloc fialed allocate memory\n");
		ft_free_lists(p, "exit");
	}
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	ft_lstadd_back(env, node);
}
