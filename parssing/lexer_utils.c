/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:20:59 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/14 18:21:02 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize_word(int *len, char *line, t_prog *p, char *type)
{
	if (!ft_strcmp(type, "WORD"))
	{
		append_node(p, line, *len, WORD);
	}
	*len = 0;
}

void	init_lexer_state(t_lexer_state *state, t_prog *p)
{
	state->cmd_line = p->cmd_line;
	state->start = p->cmd_line;
	state->len = 0;
	state->in_quotes = false;
	state->current_quote = '\0';
}
