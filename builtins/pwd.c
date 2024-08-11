/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:04:47 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/01 11:26:16 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int exit_status;
void pwd(void)
{
    char cwd[PATH_MAX];
    
    getcwd(cwd, PATH_MAX);
    ft_putstr_fd(cwd, 1);
    ft_putstr_fd("\n", 1);
    exit_status = 0;
}