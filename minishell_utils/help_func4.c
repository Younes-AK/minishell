/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:25:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/22 22:16:26 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tok_list(t_tokenze *list)
{
	t_tok_node	*curr;
	t_tok_node	*next;

	if (!list)
		return ;
	curr = list->head;
	while (curr)
	{
		next = curr->next;
		free(curr->content);
		free(curr);
		curr = next;
	}
	free(list);
}

void	append_exec(t_exec_list *list, t_exec_node *new_node)
{
	if (list->tail)
		list->tail->next = new_node;
	else
	{
		list->head = new_node;
	}
	list->tail = new_node;
}

void	free_env_list(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	if (!env_list)
		return ;
	while (current)
	{
		if (current->next)
			next = current->next;
		else
			next = NULL;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	ft_remove_q(t_prog *p)
{
	char		*tmp;
	t_tok_node	*iter;
	t_tok_node	*prev;

	iter = p->new_tok_list->head;
	prev = iter;
	while (iter)
	{
		if (!ft_strcmp(iter->content, "\"\"")
			|| !ft_strcmp(iter->content, "\'\'"))
			iter->content = ft_strdup("	");
		if (prev->type != REDIR_HEREDOC)
		{
			tmp = remove_qoutes(iter->content, p);
			free(iter->content);
		}
		else
			tmp = iter->content;
		iter->content = tmp;
		prev = iter;
		iter = iter->next;
	}
}

bool	is_in_d_qoutes(char *str)
{
	if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		return (true);
	return (false);
}
