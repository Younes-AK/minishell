/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:27:37 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/14 18:18:56 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_quote(t_lexer_state *state)
{
	if (state->in_quotes && *state->cmd_line == state->current_quote)
	{
		state->in_quotes = false;
		state->current_quote = '\0';
	}
	else if (!state->in_quotes)
	{
		state->in_quotes = true;
		state->current_quote = *state->cmd_line;
	}
	state->len++;
}

static void	process_space(t_lexer_state *state, t_prog *p)
{
	if (state->len > 0)
	{
		append_node(p, state->start, state->len, WORD);
		state->len = 0;
	}
	state->start = state->cmd_line + 1;
}

static void	process_operator(t_lexer_state *state, t_prog *p)
{
	if (*state->cmd_line == '>' && *(state->cmd_line + 1) == '>')
	{
		append_node(p, ">>", 2, REDIR_APPEND);
		state->cmd_line++;
	}
	else if (*state->cmd_line == '<' && *(state->cmd_line + 1) == '<')
	{
		append_node(p, "<<", 2, REDIR_HEREDOC);
		state->cmd_line++;
	}
	else if (*state->cmd_line == '>')
		append_node(p, ">", 1, REDIR_OUT);
	else if (*state->cmd_line == '<')
		append_node(p, "<", 1, REDIR_IN);
	else if (*state->cmd_line == '|')
	{
		append_node(p, "|", 1, PIPE_LINE);
		p->nbr_pipe++;
	}
	state->len = 0;
	state->start = state->cmd_line + 1;
}

static void	process_token(t_lexer_state *state, t_prog *p)
{
	if (is_quote(*state->cmd_line))
		process_quote(state);
	else if (state->in_quotes || (!is_whait_spaces(*state->cmd_line)
			&& !is_operator(*state->cmd_line)))
		state->len++;
	else if (is_whait_spaces(*state->cmd_line))
		process_space(state, p);
	else if (is_operator(*state->cmd_line))
		process_operator(state, p);
	state->cmd_line++;
	if (state->len == 0)
		state->start = state->cmd_line;
}

void	lexer(t_prog *p)
{
	t_lexer_state	state;

	init_lexer_state(&state, p);
	while (*state.cmd_line)
	{
		process_token(&state, p);
	}
	if (state.len > 0)
		append_node(p, state.start, state.len, WORD);
	free(p->cmd_line);
}
