#include "../minishell.h"
extern int exit_status;
char	*ft_copy(char *src, size_t start, size_t end)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * (end - start + 1));
	while (start < end)
	{
		res[i] = src[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

bool	contain_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		++i;
	}
	return (false);
}

void	split_val(char *arg, char **key, char **value)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
		i++;
	end = i;
	*key = ft_copy(arg, start, end);
	*value = ft_copy(arg, end, ft_strlen(arg));	
}

bool	is_special_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (true);
		++i;
	}
	return (false);
}

bool	is_valid_identifier(char *key)
{
	if (contain_space(key) || key[0] == '\0' || ft_isdigit(key[0]) || is_special_char(key))
		return (false);
	return (true);
}

static t_env	*get_env(char *key, t_env *env)
{
	while(env)
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
	while (str2[i] == '+' || str2[i] == '=')
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
	else if (value[0] == '=' ||  value[0] == '+')
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

int	ft_export(char **cmd, t_prog *p __attribute__ ((unused)))
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
			exit_status = 0;
		}
		else
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			exit_status = 1;
		}
		free(key);
		free(value);
		i++;
	}
	return (0);
}