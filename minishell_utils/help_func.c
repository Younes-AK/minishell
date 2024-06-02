/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:48 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/31 14:33:10 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void _init(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
}

void *safe_allocation(size_t size, size_t lenght)
{
	void *ptr;

	ptr = malloc(size * lenght);
	if (!ptr)
		error_msg("Error : malloc fialed allocate memory\n");
	return (ptr);
}

t_tokenze *init_list()
{
	t_tokenze *list;

	list = safe_allocation(sizeof(t_tokenze), 1);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

void append_node(t_tokenze *list, char *content, int len, t_token type)
{
	t_node *new_node;
	new_node = safe_allocation(sizeof(t_node), 1);
	new_node->content = ft_strndup(content, len);
	new_node->len = len;
	new_node->type = type;
	new_node->next = NULL;
	if (list->tail)
		list->tail->next = new_node;
	else
		list->head = new_node;
	list->tail = new_node;
	list->size++;
}
void free_list(t_tokenze *list) 
{
    t_node *curr;
    t_node *next;
	
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
