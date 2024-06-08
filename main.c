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
	//atexit(f);
	t_prog vars;
	_init(ac, av, env);
	while (true)
	{
		vars.nbr_pipe = 0;
		vars.list_tok = init_list();
		vars.exec_list = init_exec_list();
		vars.r_line = readline("\033[34m[minishell]~> \033[0m");
		if (!vars.r_line)
			error_msg("Error\n");
		if (ft_strlen(vars.r_line) > 0)
			add_history(vars.r_line);
		if(parssing(&vars))
		{
			lexer(&vars, vars.list_tok);
			parser(&vars, env, vars.exec_list);
		}


		// t_tok_node *node;
		// node = vars.list_tok->head;
		// while(node)
		// {
		// 	printf("cont : %s | type : %d\n", node->content, node->type);
		// 	node = node->next;
		// }
		 
		t_exec_node *tmp = vars.exec_list->head;
        char **cmd; 
		char **redir;
		if (tmp == NULL)
		{
			printf("Error: exec_list is empty.\n");
		}
        while (tmp)
        {
			cmd = tmp->cmd;
			
            while (*cmd)
            {
                printf("cmd : |%s|\n", *cmd);
                cmd++;
            }
            redir = tmp->redir;
            while (*redir)
            {
                printf("red : |%s|\n", *redir);
                redir++;
            }
            printf("======={new node}========\n");
            if((tmp = tmp->next) == NULL)
				break;
        }
		
		free(vars.r_line);
		free_list(vars.list_tok);
		free_env_list(vars.env_list);
		//free_exec_list(vars.exec_list);
    }   
} // echo "hello $HOME $USER $HOMEBREW_TEMP"

// ls -l >>fil | wc -l > file | echo "dd hfhfh"