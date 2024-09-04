/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 07:55:32 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/23 10:17:00 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_value(char *res, const char *value, size_t *res_size, t_prog *p)
{
	size_t	res_len;
	size_t	new_res_size;
	size_t	value_len;

	res_len = ft_strlen(res);
	value_len = ft_strlen(value);
	new_res_size = res_len + value_len + 1;
	if (new_res_size > *res_size)
	{
		res = ft_realloc(res, *res_size, new_res_size, p);
		*res_size = new_res_size;
	}
	ft_strcat(res, value);
	return (res);
}

char	*append_char(char *res, char c, size_t *res_size, t_prog *p)
{
	size_t	len;

	len = ft_strlen(res);
	if (len + 2 > *res_size)
	{
		res = ft_realloc(res, *res_size, len + 2, p);
		if (!res)
			error_msg("Error\nmalloc failled allocate memory");
		*res_size = len + 2;
	}
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
}

char	*get_env_value(const char *var_name, t_env *env_list)
{
	t_env	*iter;
	char	*pid_str;
	char	*result;

	if (ft_strcmp(var_name, "$$") == 0)
	{
		pid_str = ft_strdup(var_name + 1);
		return (pid_str);
	}
	if (ft_strcmp(var_name, "$?") == 0)
	{
		result = ft_itoa(EXIT_STATUS);
		return (result);
	}
	iter = env_list;
	while (iter)
	{
		if (ft_strcmp(iter->key, var_name) == 0)
			return (ft_strdup(iter->value));
		iter = iter->next;
	}
	return (ft_strdup(""));
}

char	*extract_var_name(const char **start)
{
	const char	*end;
	char		*var_name;
	size_t		var_size;

	end = *start + 1;
	if (*end == '$' || *end == '@' || *end == '*' || *end == '#'
		|| *end == '?' || *end == '-' || *end == '!' || ft_isdigit(*end))
	{
		var_name = safe_allocation(sizeof(char), 3);
		var_name[0] = '$';
		var_name[1] = *end;
		var_name[2] = '\0';
		*start = end + 1;
		return (var_name);
	}
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	var_size = end - *start - 1;
	var_name = safe_allocation(sizeof(char), var_size + 1);
	ft_strncpy(var_name, *start + 1, var_size);
	var_name[var_size] = '\0';
	*start = end;
	return (var_name);
}

void	free_pids(int *pids)
{
	if (pids != NULL)
	{
		free(pids);
	}
}
