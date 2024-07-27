/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/21 20:22:44 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void f()
{
	system("leaks minishell");
}
 

void loop(t_prog *prog, char **envp)
{
	prog->nbr_pipe = 0;
	prog->fd_in = -1;
	prog->list_tok = init_token_list();
	prog->exec_list = init_exec_list();
	prog->r_line = readline("\033[34m[minishell]~> \033[0m");
	if (!prog->r_line)
		error_msg1("Error\n");
	if (ft_strlen(prog->r_line) > 0)
		add_history(prog->r_line);
	if (prog->r_line[0] != '\0')
	{
		if(parssing(prog))
		{
			lexer(prog, prog->list_tok);
			if (parser(prog, envp, prog->exec_list))
			{
				execution(prog, prog->exec_list);
				free_tok_list(prog->list_tok);
				free_exec_list(prog->exec_list);
			}
		}
	}
}
int main(int ac, char **av, char **envp)
{
	// atexit(f);
	t_prog prog;
	ft_init(ac, av);
	store_env(envp, &prog);
    store_secret_env(envp, &prog);
	while (true)
	{
		loop(&prog, envp);
	}
		// char **strs  = ft_split(vars.r_line, ' ');
		// if (*strs && !ft_strcmp(*strs, "cd"))
		// 	cd(strs, vars.env_list);
		// if (*strs && !ft_strcmp(*strs, "echo"))
		// 	echo(strs);
		// else if (*strs && !ft_strcmp(*strs, "pwd"))
		// 	pwd();
		// else if (*strs && !ft_strcmp(*strs, "env"))
		// 	env(vars.env_list);
		// else if (*strs && !ft_strcmp(*strs, "exit"))
		// 	exit(0);
		// else if (*strs && !ft_strcmp(*strs, "export"))
		// 	ft_export(strs + 1, &vars);
		// else if (*strs && !ft_strcmp(*strs, "unset"))
		// 	ft_unset(strs + 1, vars.env_list);
	free_env_list(prog.env_list);
	free_env_list(prog.secret_env);

} 
