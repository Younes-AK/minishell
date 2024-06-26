/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:35:44 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/26 09:18:34 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_quotes(char  *p)
{
	int d_qout_count;
	int s_qout_count;
	int	i;

	i = 0;
	d_qout_count = 0;
	s_qout_count = 0;
	while (p[i])
	{
		if (p[i] == '\'')
			s_qout_count++;
		if (p[i] == '"')
			d_qout_count++;
		i++;
	}
	return (d_qout_count % 2 == 0 && s_qout_count % 2 == 0);
}
int count(char *line)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (line[i] && is_whait_spaces(line[i]))
		i++;
	while (line[i])
	{
		if (is_operator(line[i]))
		{
			if (i > 0)
				if (!is_whait_spaces(line[i - 1]) && !is_operator(line[i - 1]))
					len++;
			if (!is_whait_spaces(line[i + 1]) && !is_operator(line[i + 1]))
				len++;
		}
		len++;
		i++;
	}
	return (len);
}
int count_over_space(char *input, int *index)
{
	int	k;
	int	j;
    bool in_quotes;
	
	j = 0;
	k = *index;
	in_quotes = false;
    while (k < (int)ft_strlen(input))
    {
        if (input[k] == '"' || input[k] == '\'') 
            in_quotes = !in_quotes;
        if (!(is_whait_spaces(input[k]) && is_whait_spaces(input[k + 1]) && !in_quotes))
            j++;
        k++;
    }
	return (j);
}
char *inject_spaces(char *input)
{
    int	i;
	int	j;
    bool in_quotes;
    char *p;
	
	i = 0;
	j = 0;
	in_quotes = false;
    while (is_whait_spaces(input[i]))
        i++;
	j = count_over_space(input, &i);
	p = safe_allocation(sizeof(char), j + 1);
    j = 0;
    while (input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
            in_quotes = !in_quotes;
        while (is_whait_spaces(input[i]) && is_whait_spaces(input[i + 1]) && !in_quotes)
            i++;
        p[j++] = input[i++];
    }
    while (j > 0 && p[j - 1] == ' ')
        j--;
    p[j] = '\0';
    return (p);
}
bool add_spaces(t_prog *p, int len) 
{    
    int i = 0;
    int j = 0;
	// if (*p->d == '|' || p->d[ft_strlen(p->d) - 1] == '|')
	// {
	// 	write(2, "minishell: syntax error near unexpected token `|' \n", 52);
	// 	return (false);
	// }
    p->cmd_line = safe_allocation(sizeof(p->cmd_line), len + 1);
    while (p->d[i] && j < len)
	{
        if (is_operator(p->d[i]))
		{
            if (i != 0 && p->d[i - 1] != ' ' && !is_operator(p->d[i - 1]))
                p->cmd_line[j++] = ' ';
            p->cmd_line[j++] = p->d[i];
            if (p->d[i + 1] != ' '  && !is_operator(p->d[i + 1]) && p->d[i + 1])
                p->cmd_line[j++] = ' ';
        }
		else
            p->cmd_line[j++] = p->d[i];
        i++;
    }
    p->cmd_line[j] = '\0';
	return (true);
}

bool parssing(t_prog *p)
{

	int len;

	len = 0;
	if (check_quotes(p->r_line))
	{
		p->d = inject_spaces(p->r_line);
		len = count(p->d);
		if (!add_spaces(p, len))
			return (false);
		free(p->d);
		return (true);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected quote \n", 48);
		return (false);
	}
}