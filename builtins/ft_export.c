/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:37:01 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/15 15:22:18 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

static t_env	*get_env(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static char	*get_value(char *str1, char *str2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	if (str2[i] == '+')
		i++;
	if (str2[i] == '=')
		i++;
	len = ft_strlen(str1) + ft_strlen(str2) - i;
	res = malloc(sizeof(char) * (len + 1));
	j = 0;
	while (str1 && str1[j])
	{
		res[j] = str1[j];
		j++;
	}
	while (str2 && str2[i])
		res[j++] = str2[i++];
	res[j] = '\0';
	return (res);
}

void	add_to_export(char *key, char *value, t_env **env)
{
	t_env	*tmp;
	char	*out_val;
	t_env	*node;

	tmp = NULL;
	if (check_var_exist(key, env))
		tmp = get_env(key, *env);
	if (value[0] == '+' && tmp)
		out_val = get_value(tmp->value, value);
	else if (value[0] == '=' || value[0] == '+')
		out_val = get_value(NULL, value);
	else
		out_val = NULL;
	if (tmp)
	{
		if (out_val)
		{
			free(tmp->value);
			tmp->value = ft_strdup(out_val);
		}
	}
	else
	{
		node = malloc(sizeof(t_env));
		node->key = ft_strdup(key);
		node->value = ft_strdup(out_val);
		node->next = NULL;
		ft_lstadd_back(env, node);
	}
	free(out_val);
}

void	add_to_env(char *key, t_env **env_export, t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	tmp = NULL;
	node = NULL;
	if (check_var_exist(key, env_export))
		tmp = get_env(key, *env_export);
	node = get_env(key, *env);
	if (node)
	{
		if (tmp->value && tmp->value[0] != '\0')
		{
			free(node->value);
			node->value = ft_strdup(tmp->value);
		}
		else if (tmp->value && tmp->value[0] == '\0')
			node->value = NULL;
	}
	else if (tmp->value)
	{
		node = malloc(sizeof(t_env));
		node->key = ft_strdup(key);
		node->value = NULL;
		node->next = NULL;
		if (tmp->value[0] != '\0')
			node->value = ft_strdup(tmp->value);
		ft_lstadd_back(env, node);
	}
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

void	ft_export(char **cmd, t_prog *p)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (!ft_strcmp(cmd[0], "export") && !cmd[1])
		print_envi(p->secret_env);
	while (cmd[i])
	{
		split_val(cmd[i], &key, &value);
		if (is_valid_identifier(key))
		{
			add_to_export(key, value, &p->secret_env);
			add_to_env(key, &p->secret_env, &p->env_list);
			g_exit_status = 0;
		}
		else
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			g_exit_status = 1;
		}
		free(key);
		free(value);
		i++;
	}
}
