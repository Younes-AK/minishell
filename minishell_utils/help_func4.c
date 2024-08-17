/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:25:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 11:27:19 by yakazdao         ###   ########.fr       */
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
