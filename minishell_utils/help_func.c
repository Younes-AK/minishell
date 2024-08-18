/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:48 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 11:27:04 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*safe_allocation(size_t size, size_t lenght)
{
	void	*ptr;

	ptr = malloc(size * lenght);
	if (!ptr)
		error_msg("Error : malloc fialed allocate memory\n");
	return (ptr);
}

t_tokenze	*init_token_list(t_prog *p)
{
	t_tokenze	*list;

	list = safe_allocation(sizeof(t_tokenze), 1);
	if (!list)
	{
		free_envirement(p);
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_exec_list	*init_exec_list(t_prog *p)
{
	t_exec_list	*list;

	list = safe_allocation(sizeof(t_exec_list), 1);
	if (!list)
	{
		free_envirement(p);
		free_tok_list(p->list_tok);
		free_tok_list(p->new_tok_list);
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

void	append_node(t_prog *p, char *content, int len, t_token type)
{
	t_tok_node	*new_node;

	new_node = safe_allocation(sizeof(t_tok_node), 1);
	if (!new_node)
		ft_free_lists(p, "exit");
	new_node->content = ft_strndup(content, len);
	if (!new_node)
	{
		free(new_node);
		ft_free_lists(p, "exit");
	}
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

void	append_new_token_list(t_prog *p, char *content, int len, t_token type)
{
	t_tok_node	*new_node;

	new_node = safe_allocation(sizeof(t_tok_node), 1);
	if (!new_node)
		ft_free_lists(p, "exit");
	new_node->content = ft_strndup(content, len);
	if (!new_node)
	{
		free(new_node);
		ft_free_lists(p, "exit");
	}
	new_node->len = len;
	new_node->type = type;
	new_node->next = NULL;
	if (p->new_tok_list->tail)
		p->new_tok_list->tail->next = new_node;
	else
		p->new_tok_list->head = new_node;
	p->new_tok_list->tail = new_node;
	p->new_tok_list->size++;
}
