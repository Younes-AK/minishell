/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:35:44 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/24 00:49:10 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_special_char(t_list *list, const char **input, const char **start, int *token_len, t_state *state) 
{
    if (**input == ' ') 
	{
        if (*token_len > 0) 
		{
            tokenize_word(list, *start, *token_len, *state);
            *token_len = 0;
        }
        tokenize_whitespace(list, *input, 1, *state);
    } 
	else 
	{
        if (**input == '|') 
		{
            if (*token_len > 0) 
			{
                tokenize_word(list, *start, *token_len, *state);
                *token_len = 0;
            }
            tokenize_single_char(list, **input, PIPE_LINE, *state);
        } 
		else if (**input == '<') 
		{
            if (*token_len > 0) 
			{
                tokenize_word(list, *start, *token_len, *state);
                *token_len = 0;
            }
            tokenize_single_char(list, **input, REDIR_IN, *state);
        } 
		else if (**input == '>')
		{
            if (*token_len > 0) 
			{
                tokenize_word(list, *start, *token_len, *state);
                *token_len = 0;
            }
            tokenize_single_char(list, **input, REDIR_OUT, *state);
        }
    }
    (*input)++;
}

void handle_quote(t_list *list, const char **input, t_state *state) 
{
    if (**input == '\'') 
	{
        if (*state == DEFAULT)
            *state = IN_SQUOTE;
        else if (*state == IN_SQUOTE)
            *state = DEFAULT;
        tokenize_single_char(list, **input, QUOTE, *state);
    } 
	else if (**input == '\"') 
	{
        if (*state == DEFAULT)
            *state = IN_DQUOTE;
        else if (*state == IN_DQUOTE)
            *state = DEFAULT;
        tokenize_single_char(list, **input, DOUBLE_QUOTE, *state);
    }
    (*input)++;
}




void lexing(t_list *list, const char *input)
{
    t_state state = DEFAULT;
    const char *start = input;
    int token_len = 0;

    while (*input) 
	{
        if (is_special_char(*input))
            handle_special_char(list, &input, &start, &token_len, &state);
        else if (is_quote(*input))
            handle_quote(list, &input, &state);
        else 
		{
            if (token_len == 0)
                start = input;
            token_len++;
            input++;
        }
    }
    if (token_len > 0)
        tokenize_word(list, start, token_len, state);
}