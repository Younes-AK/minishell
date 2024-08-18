/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:22:22 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 11:24:11 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unlink_temp_files(t_temp_files *temp_files_list)
{
	t_temp_files	*current;
	t_temp_files	*next;

	current = temp_files_list;
	if (!temp_files_list)
		return ;
	while (current)
	{
		if (unlink(current->filename) == -1)
		{
			ft_putstr_fd("Error unlinking temporary file: ", 2);
			ft_putstr_fd(current->filename, 2);
			ft_putstr_fd("\n", 2);
		}
		if (current->next)
			next = current->next;
		else
			next = NULL;
		free(current->filename);
		free(current);
		current = next;
	}
}

void	*add_temp_file(char *filename, t_prog *p)
{
	t_temp_files	*new;

	new = malloc(sizeof(t_temp_files));
	if (!new)
	{
		ft_free_lists(p, "exit");
	}
	new->filename = ft_strdup(filename);
	new->next = NULL;
	return (new);
}

void	append_temp_file(t_temp_files **lst, t_temp_files *new)
{
	t_temp_files	*list;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while (list->next != NULL)
		list = list->next;
	list->next = new;
}
