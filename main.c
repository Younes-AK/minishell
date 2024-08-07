/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/02 12:10:32 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int exit_status;
void f()
{
	system("leaks minishell");
}


void loop(t_prog *prog, char **envp)
{
	prog->r_line = readline("\033[34m[minishell]~> \033[0m");
	if (!prog->r_line)
	{
		free_env_list(prog->env_list);
		ft_free_lists(prog, "exit");
		close(prog->original_stdin);
		exit(1);
	}
	if (ft_strlen(prog->r_line) > 0)
		add_history(prog->r_line);
	if (prog->r_line[0] != '\0')
	{
		if(parssing(prog))
		{
			lexer(prog, prog->list_tok);
			if (parser(prog, envp))
			{
				execution(prog, prog->exec_list);
			}
		}
	}
}
int main(int ac, char **av, char **envp)
{
	// atexit(f);
	rl_catch_signals = 0;
	t_prog prog;
	ft_init(ac, av);
	store_env(envp, &prog);
    prog.original_stdin = dup(STDIN_FILENO);
	while (true)
	{
		prog.list_tok = init_token_list();
		prog.exec_list = init_exec_list();
		prog.is_env_cmd = false;
		prog.nbr_pipe = 0;
		ft_sign();
		loop(&prog, envp);
		ft_free_lists(&prog, "free");
		free(prog.r_line);
		// free(prog.cmd_line);
	}

} 
 