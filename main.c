/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/31 11:29:20 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void f()
{
	system("leaks minishell");
}


int main(int ac, char **av, char **env)
{
	t_prog vars;
	_init(ac, av, env);
	while (true)
	{
		vars.list = init_list();
		vars.r_line = readline("\033[34m[minishell]~> \033[0m");
		if (!vars.r_line)
			error_msg("Error\n");
		// if (ft_strcmp(vars.r_line, "") || is_str_spaces(vars.r_line))
		// 	return (1);
		if (ft_strlen(vars.r_line) > 0)
			add_history(vars.r_line);
		if(parssing(&vars))
		{
			lexer(&vars, vars.list);
			if (!parser(&vars, env))
				;
		}
		// t_node *iter;
		// iter = vars.list->head;
	
		// while (iter)
		// {
		// 	printf("content : |%s|  type : |%d| len : |%d|\n", iter->content, iter->type, iter->len);
		// 	iter =iter->next;
		// }
		free(vars.r_line);
		free_list(vars.list);
    }
}

// ls -l >>fil | wc -l > file | echo "dd hfhfh"