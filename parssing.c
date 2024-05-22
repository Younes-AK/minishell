/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:50:59 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/22 10:58:36 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool valid_patterns(char *str)
{
	if (!ft_strncmp(str, ">", ft_strlen(str)) || !ft_strncmp(str, "<", ft_strlen(str))
		|| !ft_strncmp(str, ">>", ft_strlen(str)) || !ft_strncmp(str, "<<", ft_strlen(str))
		|| !ft_strncmp(str, ">|", ft_strlen(str)) || !ft_strncmp(str, "|>", ft_strlen(str))
		|| !ft_strncmp(str, "|<", ft_strlen(str)) || !ft_strncmp(str, "|>|", ft_strlen(str))
		|| !ft_strncmp(str, "|<|", ft_strlen(str)) || !ft_strncmp(str, "|", ft_strlen(str))
		|| !ft_strncmp(str, "|>>", ft_strlen(str)) || !ft_strncmp(str, "|<<", ft_strlen(str)))
		return (true);
	return (false);
}
void check_valid_patterns(char **str)
{
	int i;
	
	i=0;
	while(str[i])
	{
		if(is_operator(str[i][0]))
		{
			if (valid_patterns(str[i]) == false)
			{
				write(2, "minishell : syntax error\n", 26);
				return;
			}
		}
		i++;
	}
}
bool check_quotes(t_prog *p)
{
	int d_qout_count;
	int s_qout_count;
	int	i;

	i = 0;
	d_qout_count = 0;
	s_qout_count = 0;
	while (p->line_rd[i])
	{
		if (p->line_rd[i] == QOUTE)
			s_qout_count++;
		if (p->line_rd[i] == DOUBLE_QUOTE)
			d_qout_count++;
		i++;
	}
	return (d_qout_count % 2 == 0 && s_qout_count % 2 == 0);
}
void ft_add_spaces(t_prog *p, int len) 
{    
    int i = 0;
    int j = 0;
    
    if (!check_quotes(p))
    {
		write(2, "minishell : syntax error\n", 26);
		return;
	}
    p->cmd_line = allocate(sizeof(p->cmd_line), len);
    while (p->line_rd[i] && j < len) 
	{
        if (is_operator(p->line_rd[i])) 
		{
            if (p->line_rd[i - 1] != WHITE_SPACE && !is_operator(p->line_rd[i - 1]))
                p->cmd_line[j++] = WHITE_SPACE;
            p->cmd_line[j++] = p->line_rd[i];
            if (p->line_rd[i + 1] != WHITE_SPACE  && !is_operator(p->line_rd[i + 1]))
                p->cmd_line[j++] = WHITE_SPACE;
        }
		else
            p->cmd_line[j++] = p->line_rd[i];
        i++;
    }
    p->cmd_line[j] = '\0';
}

void parssing(t_prog *p)
{
	int i;
	int len;

	i = 0;
	len = 0;
	// counting the line read to add spaces [injection spaces]
	while (p->line_rd[i] && is_whaitspace(p->line_rd[i]))
		i++;
	while (p->line_rd[i++])
	{
		if (is_operator(p->line_rd[i]))
		{
			if (p->line_rd[i] == PIPE_LINE)
				p->pipe_nbr++;
			if (p->line_rd[i - 1] != WHITE_SPACE && !is_operator(p->line_rd[i - 1]))
				len++;
			if (p->line_rd[i + 1] != WHITE_SPACE && !is_operator(p->line_rd[i + 1]))
				len++;
		}
		len++;
	}
	ft_add_spaces(p, len);
	p->patterns = ft_split(p->cmd_line, ' ');
	check_valid_patterns(p->patterns);
	free_allocation(p->patterns);
}
