/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:38:43 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/30 07:42:50 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_expanded_tokens(t_tok_node *iter, char **tokens, t_prog *p)
{
	char	**token_start;

	token_start = tokens;
	while (*tokens)
	{
		append_new_token_list(p, *tokens, ft_strlen(*tokens), iter->type);
		tokens++;
	}
	free_double_ptr(token_start);
}

static void	expand_and_append(t_tok_node *iter, char *expanded_var, t_prog *p)
{
	char	**all_str;

	if (!is_in_d_qoutes(expanded_var))
	{
		all_str = ft_split(expanded_var, ' ', p);
		append_expanded_tokens(iter, all_str, p);
	}
	else
	{
		append_new_token_list(p, expanded_var, \
		ft_strlen(expanded_var), iter->type);
	}
}

static bool	handle_ambiguous(t_tok_node *prev, char *expanded_var)
{
	if ((prev->type == REDIR_OUT || prev->type == REDIR_APPEND)
		&& (is_ambiguous(expanded_var)
			|| !ft_strcmp(expanded_var, "")))
	{
		error_msg2(" : ambiguous redirect", expanded_var);
		EXIT_STATUS = 1;
		return (false);
	}
	return (true);
}

static bool	process_token(t_tok_node *iter, t_tok_node *prev, \
	t_env *env_list, t_prog *p)
{
	char	*temp;

	if (iter->content && iter->content[0] == '$' && iter->content[1] == '"')
	{
		temp = ft_strdup(iter->content + 1);
		free(iter->content);
		iter->content = temp;
	}
	if (to_expand(iter->content, iter->type) && prev->type != REDIR_HEREDOC)
	{
		p->expanded_var = get_env_val(iter->content, env_list, p);
		if (!handle_ambiguous(prev, p->expanded_var))
			p->is_valid = false;
		iter->content = p->expanded_var;
		expand_and_append(iter, p->expanded_var, p);
	}
	else
	{
		append_new_token_list(p, iter->content, \
				ft_strlen(iter->content), iter->type);
	}
	return (p->is_valid);
}

bool	expand(t_tokenze *list, t_env *env_list, t_prog *p)
{
	t_tok_node	*iter;
	t_tok_node	*prev;

	iter = list->head;
	prev = iter;
	while (iter)
	{
		if (!process_token(iter, prev, env_list, p))
			return (false);
		prev = iter;
		iter = iter->next;
	}
	ft_remove_q(p);
	return (true);
}
