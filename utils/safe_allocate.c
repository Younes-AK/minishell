/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:59:17 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/18 15:26:41 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void *allocate(char *type, size_t size)
{
	type = (char *)malloc (sizeof(char) * size + 1);
	if (!type)
	{
		ft_error("Error : malloc fialed to allocate memory\n");
	}
	return (type);
}