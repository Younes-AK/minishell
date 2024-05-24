/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:48 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/24 01:23:41 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_whait_spaces(char c)
{
	return (c >= 9 && c <= 13);
}
bool is_str_spaces(char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if (!is_whait_spaces(line[i]))
			return (false);
		i++;
	}
	return (true);
}

void *safe_allocation(size_t size, size_t lenght)
{
	void *ptr;

	ptr = malloc(size * lenght);
	if (!ptr)
		error_msg("Error : malloc fialed allocate memory\n");
	return (ptr);
}

t_list *init_list() 
{
    t_list *list = malloc(sizeof(t_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void append_element(t_list *list, const char *content, int len, t_token type, t_state state)
{
    t_node *new_elem = malloc(sizeof(t_node));
    new_elem->content = strndup(content, len);
    new_elem->len = len;
    new_elem->type = type;
    new_elem->state = state;
    new_elem->next = NULL;

    if (list->tail) {
        list->tail->next = new_elem;
    } else {
        list->head = new_elem;
    }

    list->tail = new_elem;
    list->size++;
}