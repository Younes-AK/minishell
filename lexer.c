/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:27:37 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/05 10:45:49 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void tokenize_word(int *len, char *line, t_tokenze *list, char *type)
{
	if (!ft_strcmp(type, "WORD"))
	{
		append_node(list, line, *len, WORD);
	}
	*len = 0;
}


void tokenize_operator(t_tokenze *list, char **cmd_line, t_prog *p, int *len)
{
    if (**cmd_line == '>' && *(*cmd_line + 1) == '>')
    {
        append_node(list, ">>", 2, REDIR_APPEND);
        (*cmd_line)++;
    }
    else if (**cmd_line == '<' && *(*cmd_line + 1) == '<')
    {
        append_node(list, "<<", 2, REDIR_HEREDOC);
        (*cmd_line)++;
    }
    else if (**cmd_line == '>')
        append_node(list, ">", 1, REDIR_OUT);
    else if (**cmd_line == '<')
        append_node(list, "<", 1, REDIR_IN);
    else if (**cmd_line == '|')
    {
        append_node(list, "|", 1, PIPE_LINE);
        p->nbr_pipe++;
    }
    *len = 0;
}


void process_quotes(char **cmd_line, bool *in_quotes, char *current_quote, int *len)
{
    if (*in_quotes && **cmd_line == *current_quote)
    {
        *in_quotes = false;
        *current_quote = '\0';
    }
    else if (!*in_quotes)
    {
        *in_quotes = true;
        *current_quote = **cmd_line;
    }
    (*len)++;
}

void  lexer(t_prog *p, t_tokenze *list)
{
    int     len;
    char    *start;
    bool    in_quotes;
    char    current_quote;
    char    *cmd_line;

    len = 0;
    start = p->cmd_line;
    in_quotes = false;
    current_quote = '\0';
    cmd_line = p->cmd_line;
    while (*cmd_line)
    {
        if (is_quote(*cmd_line))
            process_quotes(&cmd_line, &in_quotes, &current_quote, &len);
        else if (in_quotes || (!is_whait_spaces(*cmd_line) && !is_operator(*cmd_line)))
            len++;
        else if (is_whait_spaces(*cmd_line))
        {
            if (len > 0)
                tokenize_word(&len, start, list, "WORD");
            start = cmd_line + 1;
        }
        else if (is_operator(*cmd_line))
        {
            // if (len > 0)
            //     tokenize_word(&len, start, list, "WORD");
            tokenize_operator(list, &cmd_line, p, &len);
            start = cmd_line + 1;
        }
        cmd_line++;
        if (len == 0)
            start = cmd_line;
    }
    if (len > 0)
        tokenize_word(&len, start, list, "WORD");
    free(p->cmd_line);
}

