/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:17:48 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/21 11:45:13 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_lstclear(t_tokens **lst, void (*del)(void*))
// {
// 	if (!lst || !del || !(*lst))
// 		return ;
// 	ft_lstclear(&(*lst)->next, del);
// 	(del)((*lst)->content);
// 	free(*lst);
// 	*lst = NULL;
// }
