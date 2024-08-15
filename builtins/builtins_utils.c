/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:11:59 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/14 21:14:43 by yakazdao         ###   ########.fr       */
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
	free(tmp);
	while (env->next)
		env = env->next;
	env->next = new_node;
}
