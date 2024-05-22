/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:21:43 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/22 11:57:42 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
 

t_tokens	*ft_lstnew(void *cmdline ,char *type, int i, int j, int lenght)
{
	t_tokens	*new;
	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	if (!ft_strncmp(type, "commands", ft_strlen(type)))
	{
		new->commands = (char **) malloc(sizeof (char *) * lenght + 1);
		new->commands[i] = cmdline;
	}
	if (!ft_strncmp(type, "redirections", ft_strlen(type)))
	{
		new->redirections = (char **) malloc(sizeof (char *) * lenght + 1);
		new->redirections[j] =  cmdline;
	}
	new->next = NULL;
	return (new);
}