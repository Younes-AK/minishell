/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:50:49 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/19 17:30:29 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_whaitspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

// void new_lenght(t_prog *p, int *len)
// {
// 	int i;
	
// 	i = 0;
// 	while (p->line_rd[i] && is_whaitspace(p->line_rd[i]))
// 		i++;
// 	while (p->line_rd[i++])
// 	{
// 		if (is_operator(p->line_rd[i]))
// 		{
// 			if (p->line_rd[i - 1] != ' ' && (p->line_rd[i - 1] != '<' && p->line_rd[i - 1] != '>'))
// 				*len++;
// 			if (p->line_rd[i + 1] != ' ' && (p->line_rd[i + 1] != '<' && p->line_rd[i + 1] != '>'))
// 				*len++;
// 		}
// 		*len++;
// 	}
// }