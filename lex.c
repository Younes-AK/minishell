/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:27:37 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/01 11:59:56 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void tokenize_word(int *len, char *line, t_tokenze *list, char *type)
{
	if (!ft_strcmp(type, "WORD") && *line == '$')
	{
		append_node(list, line, *len, ENV);
	}
	else if (!ft_strcmp(type, "WORD"))
	{
		append_node(list, line, *len, WORD);
	}
	// else if (!ft_strcmp(type, "WHITE_SPACE"))
	// 	append_node(list, " ", 1, WHITE_SPACE);
	*len = 0;
}

void tokenize_operator(t_tokenze *list, char **c, t_prog *p)
{
    if (**c == '>' && *(*c + 1) == '>')
    {
        append_node(list, ">>", 2, REDIR_APPEND);
        (*c)++;
    }
    else if (**c == '<' && *(*c + 1) == '<')
    {
        append_node(list, "<<", 2, REDIR_HEREDOC);
        (*c)++;
    }
    else if (**c == '>')
        append_node(list, ">", 1, REDIR_OUT);
    else if (**c == '<')
        append_node(list, "<", 1, REDIR_IN);
    else if (**c == '|')
	{
        append_node(list, "|", 1, PIPE_LINE);
		p->nbr_pipe++;
	}
}


void lexer(t_prog *p, t_tokenze *list) 
{
    int len = 0;
    char *start;
    char *original_cmd_line = p->cmd_line;
    bool in_quotes = false;
    char current_quote = '\0';
    start = p->cmd_line;
    while (*p->cmd_line)
	{
        if (is_quote(*p->cmd_line))
		{
            if (in_quotes && *p->cmd_line == current_quote)
			{
                in_quotes = false;
                current_quote = '\0';
            } 
			else if (!in_quotes) 
			{
                in_quotes = true;
                current_quote = *p->cmd_line;
            }
            len++;
        }
		else if (in_quotes)
            len++;
        else if (!is_whait_spaces(*p->cmd_line) && !is_operator(*p->cmd_line))
            len++;
        else if (is_whait_spaces(*p->cmd_line))
		{
            if (len > 0)
                tokenize_word(&len, start, list, "WORD");
        } 
		else if (is_operator(*p->cmd_line)) 
		{
            if (len > 0)
                tokenize_word(&len, start, list, "WORD");
            tokenize_operator(list, &p->cmd_line, p);
        }
        p->cmd_line++;
        if (len == 0)
            start = p->cmd_line;
    }
    if (len > 0)
        tokenize_word(&len, start, list, "WORD");
    free(original_cmd_line);
}
