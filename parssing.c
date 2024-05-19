/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:50:59 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/19 10:13:26 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
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
		if (p->line_rd[i] == '\'')
			s_qout_count++;
		if (p->line_rd[i] == '\"')
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
        ft_error("Error \n");
    p->cmd_line = allocate(p->cmd_line, len);
    while (p->line_rd[i] && j < len) 
	{
        if (is_operator(p->line_rd[i])) 
		{
            if (p->line_rd[i - 1] != ' ' && p->line_rd[i - 1] != '<' && p->line_rd[i - 1] != '>') 
                p->cmd_line[j++] = ' ';
            p->cmd_line[j++] = p->line_rd[i];
            if (p->line_rd[i + 1] != ' '  && p->line_rd[i + 1] != '<' && p->line_rd[i + 1] != '>')
                p->cmd_line[j++] = ' ';
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
	while (p->line_rd[i] && is_whaitspace(p->line_rd[i]))
		i++;
	while (p->line_rd[i++])
	{
		if (is_operator(p->line_rd[i]))
		{
			if (p->line_rd[i - 1] != ' ' && (p->line_rd[i - 1] != '<' && p->line_rd[i - 1] != '>'))
				len++;
			if (p->line_rd[i + 1] != ' ' && (p->line_rd[i + 1] != '<' && p->line_rd[i + 1] != '>'))
				len++;
		}
		len++;
	}
	ft_add_spaces(p, len);
}
// "echo     "hello  $USER " > file | grep h |cat << eof | cat >> file | echo 'done'"