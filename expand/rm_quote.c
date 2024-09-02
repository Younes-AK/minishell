/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:26:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/27 23:19:30 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	exist(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*expand_herdoc(char *str, t_env *env_list, t_prog *p)
{
	1 && (p->size = ft_strlen(str) + 1, p->start = str, p->quote_type = 0);
	1 && (p->res = safe_allocation(sizeof(char), p->size), p->res[0] = '\0');
	while (*p->start)
	{
		if (*p->start == '"')
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

char	*remove_qoutes(char *content, t_prog *p)
{
	char		*str;
	char		count;
	int			i;
	size_t		j;

	str = malloc(ft_strlen(content) + 1);
	if (!str)
		(free(content), ft_free_lists(p, "exit"));
	i = 0;
	j = 0;
	count = 0;
	while (content[i])
	{
		if ((content[i] == '"' || content[i] == '\'') && count == 0
			&& exist(content + i + 1, content[i]))
			count = content[i];
		else if (content[i] == count)
			count = 0;
		else
			str[j++] = content[i];
		i++;
	}
	str[j] = '\0';
	return (ft_realloc(str, ft_strlen(content), j + 1));
}
