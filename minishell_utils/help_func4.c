/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:25:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/21 15:17:50 by yakazdao         ###   ########.fr       */
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
