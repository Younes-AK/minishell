/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:35:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/22 15:37:57 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_whait_spaces(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_str_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_whait_spaces(line[i]))
			return (false);
		i++;
	}
	return (true);
}

char	*add_qoutes_if_not_exist(char *str)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = malloc(ft_strlen(str) + 3);
	i = 0;
	j = 0;
	tmp[j++] = '"';
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j++] = '"';
	tmp[j] = '\0';
	return (tmp);
}
