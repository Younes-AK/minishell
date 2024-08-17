/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:35:44 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 11:21:20 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

bool	check_quotes(char *p)
{
	bool	in_d_quote;
	bool	in_s_quote;
	int		i;

	i = 0;
	in_d_quote = false;
	in_s_quote = false;
	while (p[i])
	{
		if (p[i] == '"' && !in_s_quote)
			in_d_quote = !in_d_quote;
		else if (p[i] == '\'' && !in_d_quote)
			in_s_quote = !in_s_quote;
		i++;
	}
	return (!in_s_quote && !in_d_quote);
}

int	count_new_str(char *line, t_prog *p)
{
	int		len;
	char	quote;

	1 && (p->i = 0, len = 0, quote = 0);
	while (line[p->i] && is_whait_spaces(line[p->i]))
		p->i++;
	while (line[p->i])
	{
		if ((line[p->i] == '\'' || line[p->i] == '\"') && !quote)
			quote = line[p->i];
		else if (line[p->i] == quote)
			quote = 0;
		if (!quote && is_operator(line[p->i]))
		{
			if (p->i > 0 && !is_whait_spaces(line[p->i - 1])
				&& !is_operator(line[p->i - 1]))
				len++;
			if (!is_whait_spaces(line[p->i + 1])
				&& !is_operator(line[p->i + 1]) && line[p->i + 1])
				len++;
		}
		len++;
		p->i++;
	}
	return (len);
}

bool	add_spaces(t_prog *p, int len)
{
	char	quote;

	p->i = 0;
	p->j = 0;
	quote = 0;
	p->cmd_line = safe_allocation(sizeof(char), len + 1);
	if (!p->cmd_line)
		return (false);
	process_characters(p, len, &quote);
	return (true);
}

char	*inject_spaces(char *input)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (is_whait_spaces(input[i]))
		i++;
	j = count_orignal_space(input, &i);
	ret = process_spaces(input, &i, j);
	return (ret);
}

bool	parssing(t_prog *p)
{
	int	len;

	len = 0;
	if (check_quotes(p->r_line))
	{
		p->tmp = inject_spaces(p->r_line);
		if (!p->tmp)
			ft_free_lists(p, "exit");
		len = count_new_str(p->tmp, p);
		if (!add_spaces(p, len))
			return (free(p->tmp), ft_free_lists(p, "exit"), false);
		free(p->tmp);
		return (true);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected quote \n", 48);
		g_exit_status = 258;
		return (false);
	}
}
