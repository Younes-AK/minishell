/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/21 10:54:17 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void f()
{
	system("leaks minishell");
}


int main(int ac, char **av, char **envp)
{
	// atexit(f);
	t_prog vars;
	ft_init(ac, av);
	store_env(envp, &vars);
    store_secret_env(envp, &vars);
	bool flg;
	while (true)
	{
		flg = false;
		vars.nbr_pipe = 0;
		vars.list_tok = init_list();
		vars.exec_list = init_exec_list();
		vars.r_line = readline("\033[34m[minishell]~> \033[0m");

		// if (!vars.r_line)
		// 	error_msg("Error\n");
		if (ft_strlen(vars.r_line) > 0)
			add_history(vars.r_line);
		if (vars.r_line[0] != '\0')
		{
			if(parssing(&vars))
			{
				flg = true;
				lexer(&vars, vars.list_tok);
				if (parser(&vars, envp, vars.exec_list))
				{
					;
					//execution(&vars, vars.exec_list);
				}
			}
		}

		char **strs  = ft_split(vars.r_line, ' ');
		if (*strs && !ft_strcmp(*strs, "cd"))
			cd(strs, vars.env_list);
		if (*strs && !ft_strcmp(*strs, "echo"))
			echo(strs);
		else if (*strs && !ft_strcmp(*strs, "pwd"))
			pwd();
		else if (*strs && !ft_strcmp(*strs, "env"))
			env(vars.env_list);
		else if (*strs && !ft_strcmp(*strs, "exit"))
			exit(0);
		else if (*strs && !ft_strcmp(*strs, "export"))
			ft_export(strs + 1, &vars);
		else if (*strs && !ft_strcmp(*strs, "unset"))
			ft_unset(strs + 1, vars.env_list);


		
		// t_tok_node *node;
		// node = vars.list_tok->head;
		// while (node)
		// {
		// 	printf("content = %s | type = %u | count = %d\n", node->content, node->type, node->len);
		// 	node = node->next;
		// }
		 	
		// t_env *pp;
		// pp = vars.secret_env;
		// while (pp)
		// {
		// 	printf("key = %s | value = %s\n", pp->key, pp->value);
		// 	pp = pp->next;
		// } 
		
		// if (vars.r_line[0] != 0)
		// {
		// 	if (flg)
		// 	{
		// 		t_exec_node *tmp = vars.exec_list->head;
		// 		char **cmd = NULL;
		// 		char **redir = NULL;
		// 		int i;
		// 		if (tmp == NULL)
		// 		{
		// 			printf("Error: exec_list is empty.\n");
		// 		}
		// 			i = 0;
		// 		while (tmp)    
		// 		{
		// 			printf("======={new node : %d}========\n", i);
		// 			if (!tmp)
		// 				break;
		// 			cmd = tmp->cmd;
		// 			while (*cmd)
		// 			{
		// 				printf("cmd : |%s|\n", *cmd);
		// 				cmd++;
		// 			}
		// 			redir = tmp->redir;
		// 			while (*redir)
		// 			{
		// 				printf("red : |%s|\n", *redir);
		// 				redir++;
		// 			}
		// 			i++;
		// 			tmp = tmp->next ;
		// 		}
			
		// 		free(vars.r_line);
		// 		free_tok_list(vars.list_tok);
		// 		free_exec_list(vars.exec_list);	
		// 	}
		// }
		// else
		// {
		// 	free(vars.list_tok);
		// 	free(vars.exec_list);
		// }
  	 }
		// free_env_list(vars.env_list);
		// free_env_list(vars.secret_env);

} // echo "hello $HOME $USER $HOMEBREW_TEMP"

// ls -l >>fil | wc -l > file | echo "dd hfhfh"