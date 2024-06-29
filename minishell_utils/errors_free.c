/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:57:32 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/25 14:55:43 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void free_exec_list(t_exec_list *exec_list)
{
    if (!exec_list)
        return;
    t_exec_node *curr = exec_list->head;
    t_exec_node *next;
    int i;
	
    while (curr)
    {
        next = curr->next;
        i = 0;
        if (curr->cmd)
        {
            while (curr->cmd[i])
                free(curr->cmd[i++]);
            free(curr->cmd);
        }
        i = 0;
        if (curr->redir)
        {
            while (curr->redir[i])
                free(curr->redir[i++]);
            free(curr->redir);
        }
        free(curr);
        curr = next;
    }
    exec_list->head = exec_list->tail = NULL;
}

void free_env_list(t_env *env_list) 
{
    t_env *current = env_list;
    t_env *next;
    while (current) 
	{
        next = current->next; 
        free(current->key); 
        free(current->value); 
        free(current); 
        current = next;
    }
}

void free_tok_list(t_tokenze *list) 
{
    t_tok_node *curr;
    t_tok_node *next;
	
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