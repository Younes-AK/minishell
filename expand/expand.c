/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-asri <oel-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:38:43 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/22 02:09:13 by oel-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

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
bool is_in_d_qoutes(char *str)
{
	if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		return (true);
	return (false);
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
		append_new_token_list(p, expanded_var, ft_strlen(expanded_var), iter->type);
	}
}

static bool	handle_ambiguous(t_tok_node *prev, char *expanded_var, t_prog *p)
{
	if ((prev->type == REDIR_OUT || prev->type == REDIR_APPEND)
		&& (is_ambiguous(expanded_var)
			|| !ft_strcmp(expanded_var, "")) && p->is_env_cmd)
	{
		error_msg2(" : ambiguous redirect", expanded_var);
		g_exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	process_token(t_tok_node *iter, t_tok_node *prev, \
	t_env *env_list, t_prog *p)
{
	if (is_env_var(iter->content))
		p->is_env_cmd = true;
	if (to_expand(iter->content, iter->type) && prev->type != REDIR_HEREDOC)
	{
		p->expanded_var = get_env_val(iter->content, env_list, p);
		if (!handle_ambiguous(prev, p->expanded_var, p))
			p->is_valid = false;
		if (p->expanded_var)
		{
			iter->content = p->expanded_var;
		}
		p->expanded_var = add_qoutes_if_not_exist(iter->content);
		expand_and_append(iter, iter->content, p);
	}
	else
	{
		p->expanded_var = add_qoutes_if_not_exist(iter->content);
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
	t_tok_node *node = p->new_tok_list->head;
	while (node)
	{
		char *tmp;
		// printf("bef ==> %s\n", node->content);
		node->content = add_qoutes_if_not_exist(node->content);
		// printf("after ==> %s\n", node->content);
		// node->content = "l's";
		// printf("=+=> %s\n", node->content);
		printf("after remove ==> %s\n", node->content); 
		tmp = remove_qoutes(node->content, p);
		// exit(0);
		free(node->content);
		node->content = tmp;
		node = node->next;
	}
	return (true);
}
