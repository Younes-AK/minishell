/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/20 16:35:09 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_prog	prog;
	
 	(void)argc;
    (void)argv;
    (void)env;
	
	prog.line_rd = readline("minishell: ");
	parssing(&prog);
	
	// ===> still tockenization
	char **tokens = ft_tokenize(prog.line_rd);
	int i = 0;
	while (tokens[i])
	{
		printf("%s \n",tokens[i]);
		i++;
	}
	
}