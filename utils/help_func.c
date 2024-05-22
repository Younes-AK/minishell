/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:50:49 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/22 15:23:23 by yakazdao         ###   ########.fr       */
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

void* allocate(size_t element_size, size_t length)
{
    void* ptr = malloc(element_size * length);
    if (ptr == NULL) 
        ft_error("Error : malloc failed to allocate memory\n");
    return ptr;
}

int get_nbr_words(const char *line, int *pos) 
{
    int len = 0;

    while (line[*pos] && line[*pos] != '|') 
    {
        while (line[*pos] == ' ') 
            (*pos)++;
        if (line[*pos] == '"' || line[*pos] == '\'') 
        {
            char quote_char = line[*pos];
            (*pos)++;
            while (line[*pos] && line[*pos] != quote_char) 
                (*pos)++;
            if (line[*pos] == quote_char) 
                (*pos)++;
            len++;
        } 
        else if (line[*pos] && line[*pos] != ' ' && line[*pos] != '|') 
        {
            while (line[*pos] && line[*pos] != ' ' && line[*pos] != '|') 
                (*pos)++;
            len++;
        }
        while (line[*pos] == ' ')
            (*pos)++;
        if (line[*pos] == '|') 
        {
            (*pos)++;
            break;
        }
    }
    return len;
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