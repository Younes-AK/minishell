/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/24 01:34:20 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	
	t_prog vars;
	while (true)
	{
		vars.r_line = readline("[minishell]~> ");
		if (!vars.r_line)
			error_msg("Error\n");
		// if (ft_strcmp(vars.r_line, "") || is_str_spaces(vars.r_line))
		// 	return (1);
		if (ft_strlen(vars.r_line) > 0)
			add_history(vars.r_line);
			
		t_list *lexer_results = init_list();
		lexing(lexer_results, vars.r_line);

 
    	t_node *current = lexer_results->head;
    	while (current) {
       		printf("Token: |%s| Type: |%d| State: |%d|\n", current->content, current->type, current->state);
        	current = current->next;
    	}

		free(vars.r_line);
	}
}


// ls -l > fil | wc -l > file | echo "dd hfhfh"