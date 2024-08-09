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
	while (arg[i] && arg[i] != '=')
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

void	add_to_export(char *key, char *value)
{

}

void	add_to_env(char *key, char *value)
{

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
			add_to_export(key, value);
			add_to_env(key, value);
		}
		else
			printf("not a valid identifier\n");
		i++;
	}
	return (0);
}
