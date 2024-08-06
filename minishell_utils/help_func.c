/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:48 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/05 10:15:10 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void *safe_allocation(size_t size, size_t lenght)
{
	void *ptr;
	ptr = malloc(size * lenght);
	if (!ptr)
		error_msg("Error : malloc fialed allocate memory\n");
	return (ptr);
}

t_tokenze *init_token_list()
{
	t_tokenze *list;

	list = safe_allocation(sizeof(t_tokenze), 1);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

void append_node(t_prog *p, char *content, int len, t_token type)
{
	t_tok_node *new_node;
	new_node = safe_allocation(sizeof(t_tok_node), 1);
	if (!new_node)
		ft_free_lists(p, "exit");
	new_node->content = ft_strndup(content, len);
	new_node->len = len;
	new_node->type = type;
	new_node->next = NULL;
	if (p->list_tok->tail)
		p->list_tok->tail->next = new_node;
	else
		p->list_tok->head = new_node;
	p->list_tok->tail = new_node;
	p->list_tok->size++;
}

t_exec_list *init_exec_list()
{
	t_exec_list *list;

	list = safe_allocation(sizeof(t_exec_list), 1);
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

void append_exec(t_exec_list *list, t_exec_node *new_node)
{	
	if (list->tail)
		list->tail->next = new_node;
	else
	{
		list->head = new_node;
	}
	list->tail = new_node;
}


