/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:25:23 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 12:49:04 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char    *replace(char *str, t_env *env_list)
{
    size_t  result_size;
    char    *result;

    result_size = ft_strlen(str) + 1;
    result = safe_allocation(sizeof(char), result_size);
    if (!result)
        return (NULL);
    result[0] = '\0';
    return (process_string(str, env_list, result, &result_size));
}

char	*get_env_val(char *str, t_env *env_list)
{
	char	*tmp;

	if (str[0] == '$' && !str[1])
		return (str);
	tmp = replace(str, env_list);
	free(str);
	return (tmp);
}

bool	should_expand(const char *command)
{
	bool	in_s_quotes;
	bool	in_d_quotes;
	size_t	i;

	in_s_quotes = false;
	in_d_quotes = false;
	i = 0;
	while (i < ft_strlen(command))
	{
		if (command[i] == '\'')
		{
			if (!in_d_quotes)
				in_s_quotes = !in_s_quotes;
		}
		else if (command[i] == '"')
		{
			if (!in_s_quotes)
				in_d_quotes = !in_d_quotes;
		}
		else if (command[i] == '$' && !in_s_quotes)
			return (true);
		i++;
	}
	return (false);
}

bool	to_expand(char *content, t_token type)
{
	if (type == WORD)
	{
		if (should_expand(content) && is_env_var(content))
			return (true);
	}
	return (false);
}

bool	is_ambiguous(const char *filename)
{
	int			count;
	const char	*ptr;

	count = 0;
	ptr = filename;
	while (*ptr)
	{
		while (*ptr && (*ptr == ' ' || *ptr == '\t'))
			ptr++;
		if (*ptr)
			count++;
		while (*ptr && (*ptr != ' ' && *ptr != '\t'))
			ptr++;
	}
	return (count > 1);
}
