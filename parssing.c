/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:35:44 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/06 09:01:52 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_quotes(char *p)
{
    int i;
    bool in_d_quote;
    bool in_s_quote;
	
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
int count_extra_spaces(char *input, int *index)
{
	int	k;
	int	j;
    bool in_squotes;
    bool in_dquotes;
	
	j = 0;
	k = *index;
	in_squotes = false;
	in_dquotes = false;
    while (k < (int)ft_strlen(input))
    {
        if (input[k] == '\'') 
            in_squotes = !in_squotes;
		else if (input[k] == '"') 
            in_dquotes = !in_dquotes;
        if (!(is_whait_spaces(input[k]) && is_whait_spaces(input[k + 1]) && !in_squotes && !in_dquotes))
            j++;
        k++;
    }
	return (j);
}
char *inject_spaces(char *input)
{
    int	i;
	int	j;
    bool in_squotes;
    bool in_dquotes;
    char *p;
	
	i = 0;
	j = 0;
	in_squotes = false;
	in_dquotes = false;
    while (is_whait_spaces(input[i])){
        i++;
	}
	j = count_extra_spaces(input, &i);
	p = safe_allocation(sizeof(char), j + 1);
	if (!p)
		exit(1);
    j = 0;
    while (input[i])
    {
        if (input[i] == '"')
            in_dquotes = !in_dquotes;
		else if (input[i] == '"')
            in_squotes = !in_squotes;
        while (is_whait_spaces(input[i]) && is_whait_spaces(input[i + 1]) && !in_squotes && !in_dquotes)
            i++;
        p[j++] = input[i++];
    }
    while (j > 0 && p[j - 1] == ' ')
        j--;
    p[j] = '\0';
    return (p);
}
void add_spaces(t_prog *p, int len) 
{    
    int i;
    int j;

	i = 0;
	j = 0;
    p->cmd_line = safe_allocation(sizeof(p->cmd_line), len + 1);
    while (p->d[i] && j < len)
	{
        if (is_operator(p->d[i]))
		{
            if (i != 0 && !is_whait_spaces(p->d[i - 1]) && !is_operator(p->d[i - 1]))
                p->cmd_line[j++] = ' ';
            p->cmd_line[j++] = p->d[i];
            if (!is_whait_spaces(p->d[i + 1]) && !is_operator(p->d[i + 1]) && p->d[i + 1])
                p->cmd_line[j++] = ' ';
        }
		else
		{
			if (is_whait_spaces(p->d[i]))
				p->cmd_line[j++] = ' ';
			else
            	p->cmd_line[j++] = p->d[i];
		}
        i++;
    }
    p->cmd_line[j] = '\0';
}

bool parssing(t_prog *p)
{
	int len;

	len = 0;
	if (check_quotes(p->r_line))
	{
		p->d = inject_spaces(p->r_line);
		len = count(p->d);
		add_spaces(p, len);
		free(p->d);
		return (true);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected quote \n", 48);
		return (false);
	}
}
