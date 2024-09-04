/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:13:45 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/27 23:20:00 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_directory(char *cmd)
{
	if (is_all_slashes(cmd))
		return (1);
	return (0);
}

int	check_file_permissions(struct stat *st, t_prog *p)
{
	if (S_ISDIR(st->st_mode))
		return (1);
	if (p->access_path)
		return (0);
	if (st->st_mode & S_IXUSR)
		return (5);
	return (2);
}
