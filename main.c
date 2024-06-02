/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/01 18:49:35 by yakazdao         ###   ########.fr       */
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
		vars.nbr_pipe = 0;
		vars.list_tok = init_list();
		vars.r_line = readline("\033[34m[minishell]~> \033[0m");
		if (!vars.r_line)
			error_msg("Error\n");
		// if (ft_strcmp(vars.r_line, "") || is_str_spaces(vars.r_line))
		// 	return (1);
		if (ft_strlen(vars.r_line) > 0)
			add_history(vars.r_line);
		if(parssing(&vars))
		{
			lexer(&vars, vars.list_tok);
			if (!parser(&vars, env))
				;
		}
		// t_exec_list *iter;
		// iter = vars.exec_list;
		// while (iter)
		// {
		// 	printf("cmd : |%s|  red : |%s|\n", iter->cmd[0], iter->redir[0]);
		// 	iter =iter->next;
		// }
		// while (iter)
		// {
		// 	printf("content : |%s|  type : |%d| len : |%d|\n", iter->content, iter->type, iter->len);
		// 	iter =iter->next;
		// }
		free(vars.r_line);
		free_list(vars.list_tok);
    }
}

// ls -l >>fil | wc -l > file | echo "dd hfhfh"