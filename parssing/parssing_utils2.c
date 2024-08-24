/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:37:15 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/23 21:17:09 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_quotes_and_operators(t_prog *p, char *quote)
{
	if ((p->tmp[p->i] == '\'' || p->tmp[p->i] == '"') && !*quote)
		*quote = p->tmp[p->i];
	else if (p->tmp[p->i] == *quote)
		*quote = 0;
	if (!*quote && is_operator(p->tmp[p->i]))
	{
		if (p->i != 0 && !is_whait_spaces(p->tmp[p->i - 1])
			&& !is_operator(p->tmp[p->i - 1]))
			p->cmd_line[p->j++] = ' ';
		p->cmd_line[p->j++] = p->tmp[p->i];
		if (!is_whait_spaces(p->tmp[p->i + 1])
			&& !is_operator(p->tmp[p->i + 1]) && p->tmp[p->i + 1])
			p->cmd_line[p->j++] = ' ';
	}
	else
	{
		if (!*quote && is_whait_spaces(p->tmp[p->i]))
			p->cmd_line[p->j] = ' ';
		else
			p->cmd_line[p->j] = p->tmp[p->i];
		p->j++;
	}
}

int	is_all_slashes(const char *cmd)
{
	while (*cmd)
	{
		if (*cmd != '/')
			return (0);
		cmd++;
	}
	return (1);
}
