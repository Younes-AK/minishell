/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:50:37 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/14 21:34:35 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (contain_space(key) || key[0] == '\0'
		|| ft_isdigit(key[0]) || is_special_char(key))
		return (false);
	return (true);
}
