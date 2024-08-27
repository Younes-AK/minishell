/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:25:23 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/27 23:18:47 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace(char *str, t_env *env_list, t_prog *p)
{
	1 && (p->size = ft_strlen(str) + 1, p->start = str, p->quote_type = 0);
	1 && (p->res = safe_allocation(sizeof(char), p->size), p->res[0] = '\0');
	while (*p->start)
	{
		if (*p->start == '\'' || *p->start == '"')
		{
			if (p->quote_type == 0)
				p->quote_type = *p->start;
			else if (*p->start == p->quote_type)
				p->quote_type = 0;
		}
		if (*p->start == '$' && *(p->start + 1)
			&& !is_whait_spaces(*(p->start + 1))
			&& *(p->start + 1) != '"' && *(p->start + 1) != '\''
			&& p->quote_type != '\'')
		{
			p->var_name = extract_var_name(&p->start);
			p->var_value = get_env_value(p->var_name, env_list);
			p->res = append_value(p->res, p->var_value, &p->size);
			(free(p->var_name), free((char *) p->var_value));
		}
		else
			p->res = append_char(p->res, *p->start++, &p->size);
	}
	return (p->res);
}

char	*get_env_val(char *str, t_env *env_list, t_prog *p)
{
	char	*tmp;

	if (str[0] == '$' && !str[1])
		return (str);
	tmp = replace(str, env_list, p);
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
