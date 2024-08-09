#include "../minishell.h"
#include <stdbool.h>


/*
 *	validity of identifier was done correctly
 *	and all case tested was identical to bash
 *	
 *	still need to implement function to add key val to export and env
 * */


/*
 *	not a valid identifier
 *	export =a
 *	export {number}*
 *	export *{special char execpt _}*
 *	export var=name=value
 *	export var_name =value
 *
 * */

 /*
  *	export var= --> export-> var="" | env->  var=
  *	export var --> export->var | env->
  *	
  * */

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

static char	*get_env(char *key, t_env *env)
{
	while(env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
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
	free(str1);
	free(str2);
	return (res);
}

void	add_to_export(char *key, char *value, t_env **env __attribute__ ((unused)))
{
	printf("key: %s\n", key);
	printf("value: %s\n", value);
	char	*tmp;
	char	*out_val;
	t_env	*node;

	tmp = NULL;
	if (check_var_exist(key, env))
		tmp = get_env(key, *env);
	if (value[0] == '+')
		out_val = get_value(tmp, value);
	else if (value[0] == '=')
		out_val = get_value(NULL, value);

	node = malloc(sizeof(t_env));
	node->key = ft_strdup(key);
	node->value = ft_strdup(out_val);
	ft_lstadd_back(env, node);
	free(out_val);
}

void	add_to_env(char *key, char *value, t_env *env __attribute__ ((unused)))
{
	(void )key;
	(void )value;
}

int	ft_export(char **cmd, t_prog *p __attribute__ ((unused)))
{
	int		i;
	char	*key;
	char	*value;
	i = 1;
	while (cmd[i])
	{
		split_val(cmd[i], &key, &value);
		if (is_valid_identifier(key))
		{
			add_to_export(key, value, &p->secret_env);
			add_to_env(key, value, p->env_list);
		}
		else
			printf("not a valid identifier\n");
		free(key);
		free(value);
		i++;
	}
	return (0);
}
