/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/22 13:01:09 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void f()
{
	system("leaks minishell");
}
int main(int argc, char **argv, char **env)
{
	//atexit(f);
	t_prog	prog;
	t_tokens tokens;
	prog.pipe_nbr = 0;
 	(void)argc;
    (void)argv;
    (void)env;
	while(1)
	{
		prog.line_rd = readline("minishell: ");
		//parssing data input
		parssing(&prog);
		//start tockenization
		tokenization(&prog, &tokens);
		prog.pipe_nbr = 0;
	}
	
	
}