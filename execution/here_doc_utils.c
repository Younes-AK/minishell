/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:22:22 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/22 21:31:24 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_status(const char *cmd)
{
	struct stat	st;

	if (is_all_slashes(cmd))
		return (1);
	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (1);
		else if (st.st_mode & S_IXUSR)
			return (0);
		else
			return (2);
	}
	else if (errno == ENOENT)
		return (3);
	else
		return (4);
}

void	unlink_temp_files(t_temp_files *temp_files_list)
{
	t_temp_files	*current;
	t_temp_files	*next;

	current = temp_files_list;
	if (!temp_files_list)
		return ;
	while (current)
	{
		if (check_status(current->filename) == 2 \
		&& unlink(current->filename) == -1)
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

char	*create_env_entry(t_env *iter)
{
	size_t	key_len;
	size_t	value_len;
	char	*entry;

	key_len = ft_strlen(iter->key);
	value_len = ft_strlen(iter->value);
	entry = malloc(key_len + value_len + 2);
	if (!entry)
		return (NULL);
	ft_strcpy(entry, iter->key);
	entry[key_len] = '=';
	ft_strcpy(entry + key_len + 1, iter->value);
	return (entry);
}

int	is_all_slashes(const char *cmd)
{
	while (*cmd)
	{
		if (*cmd != '/')
			return (0);
		cmd++;
	}
	return (1);
}
