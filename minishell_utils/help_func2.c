/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:35:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/01 15:09:46 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_operator(char c) 
{
    return (c == '|' || c == '<' || c == '>');
}

bool is_quote(char c) 
{
    return (c == '\'' || c == '\"');
}

bool is_whait_spaces(char c)
{
	return (c == ' ' || c == '\t');
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

// void	append(t_exec_list **lst, t_exec_list *new)
// {
// 	t_exec_list	*list;
	
// 	if (!lst || !new)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	list = *lst;
// 	while (list->next != NULL)
// 		list = list->next;
// 	list->next = new;
// }

 