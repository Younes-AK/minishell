/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:35:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/24 00:46:09 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_special_char(char c) 
{
    return (c == ' ' || c == '|' || c == '<' || c == '>');
}

bool is_quote(char c) 
{
    return (c == '\'' || c == '\"');
}

void tokenize_word(t_list *list, const char *start, int length, t_state state)
{
    append_element(list, start, length, WORD, state);
}

void tokenize_single_char(t_list *list, char c, t_token type, t_state state)
{
    append_element(list, &c, 1, type, state);
}

void tokenize_whitespace(t_list *list, const char *start, int length, t_state state)
{
    append_element(list, start, length, WHITE_SPACE, state);
}