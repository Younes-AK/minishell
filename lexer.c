/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:27:37 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/27 15:07:37 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void tokenize_word(int *len, char *line, t_list *list, char *type)
{
	if (!ft_strcmp(type, "WORD") && *line == '$')
	{
		append_node(list, line, *len, ENV);
	}
	else if (!ft_strcmp(type, "WORD"))
	{
		append_node(list, line, *len, WORD);
	}
	else if (!ft_strcmp(type, "WHITE_SPACE"))
		append_node(list, " ", 1, WHITE_SPACE);
	*len = 0;
}

void tokenize_operator(t_list *list, char c)
{
	if (c == '>')
		append_node(list, ">", 1, REDIR_OUT);
	else if (c == '<')
		append_node(list, "<", 1, REDIR_IN);
	else if (c == '|')
		append_node(list, "|", 1, PIPE_LINE);
}
bool lexer(t_prog *p, t_list *list)
{
	int len;
	char *start;
	char *original_cmd_line;
	
	original_cmd_line = p->cmd_line;	
	len = 0;
	start = p->cmd_line;
	while (*p->cmd_line)
	{
		if (!is_whait_spaces(*p->cmd_line) && !is_operator(*p->cmd_line) && !is_quote(*p->cmd_line))
			len++;
		if (is_whait_spaces(*p->cmd_line))
		{
			if (len > 0)
				tokenize_word(&len, start, list, "WORD");
			tokenize_word(&len, start, list, "WHITE_SPACE");
		}
		else if(is_operator(*p->cmd_line))
			tokenize_operator(list, *p->cmd_line);
		p->cmd_line++;
		if (len == 0)
			start = p->cmd_line;
	}
	if (len > 0)
		tokenize_word(&len, start, list, "WORD");
	free(original_cmd_line);
	return (true);
}
