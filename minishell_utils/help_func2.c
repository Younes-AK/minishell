/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-asri <oel-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:35:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/22 06:35:47 by oel-asri         ###   ########.fr       */
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

bool	check_d_quotes_exist(char *str)
{
	if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		return (true);
	return (false);
}

char	*add_qoutes_if_not_exist(char *str)
{
	// char	*tmp;
	// int		i;
	// int		j;

	// i = 0;
	// j = 0;
	// printf("str: [%s]\n", str);
	// if (check_d_quotes_exist(str))
	// 	return (str);
	// tmp = safe_allocation(sizeof(char), ft_strlen(str) + 3);
	// tmp[i++] = '"';
	// while (str[j])
	// 	tmp[i++] = str[j++];
	// tmp[i++] = '"';
	// tmp[i] = '\0';
	// return (tmp);
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
