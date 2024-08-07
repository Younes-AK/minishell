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

#include "../minishell.h"
extern int exit_status;

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

int count_new_str(char *line)
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

void add_spaces(t_prog *p, int len) 
{    
	p->i = 0;
	p->j = 0;
    p->cmd_line = safe_allocation(sizeof(p->cmd_line), len + 1);
	if (!p->cmd_line)
		ft_free_lists(p, "exit");
    while (p->tmp[p->i] && p->j < len)
	{
        if (is_operator(p->tmp[p->i]))
		{
            if (p->i != 0 && !is_whait_spaces(p->tmp[p->i - 1]) && !is_operator(p->tmp[p->i - 1]))
                p->cmd_line[p->j++] = ' ';
            p->cmd_line[p->j++] = p->tmp[p->i];
            if (!is_whait_spaces(p->tmp[p->i + 1]) && !is_operator(p->tmp[p->i + 1]) && p->tmp[p->i + 1])
                p->cmd_line[p->j++] = ' ';
        }
		else
		{
			if (is_whait_spaces(p->tmp[p->i]))
				p->cmd_line[p->j++] = ' ';
			else
            	p->cmd_line[p->j++] = p->tmp[p->i];
		}
        p->i++;
    }
    p->cmd_line[p->j] = '\0';
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

bool parssing(t_prog *p)
{
	int len;

	len = 0;
	if (check_quotes(p->r_line))
	{
		p->tmp = inject_spaces(p->r_line);
		if (!p->tmp)
			ft_free_lists(p, "exit");
		len = count_new_str(p->tmp);
		add_spaces(p, len);
		free(p->tmp);
		return (true);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected quote \n", 48);
		exit_status = 2;
		return (false);
	}
}
