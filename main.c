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
int G_VAR = 0;
void f()
{
	system("leaks minishell");
}
<<<<<<< HEAD
 
 void	sig_ign(int signum)
 {
	(void) signum;
	return ;
 }

void	function_handler(int signum)
{
	printf("\n");
	sigint_received = 0;

	rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
	(void)signum;
	return ;
}
void ft_exit(int signum)
{
	printf("signum: %d\n", signum);
	printf("eof: %d\n", EOF);
	exit(signum);
}
=======
>>>>>>> 5ed68ae43fffdc485e640ca79398217ede72ad5a

void loop(t_prog *prog, char **envp)
{
	prog->nbr_pipe = 0;
	prog->fd_in = -1;
	prog->fd_out = -1;
	prog->list_tok = init_token_list();
	prog->exec_list = init_exec_list();
	prog->r_line = readline("\033[34m[minishell]~> \033[0m");
	if (!prog->r_line)
		exit(0);
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
				free_tok_list(prog->list_tok);
				free_exec_list(prog->exec_list);
			}
		}
	}
	// free_env_list(prog->env_list);
	// free_env_list(prog->secret_env);
}
int main(int ac, char **av, char **envp)
{
<<<<<<< HEAD
	struct  sigaction handler;
	
	
	handler.sa_handler = &function_handler;

	handler.sa_flags = SA_RESTART;
	// signal(SIG)
	signal(SIGQUIT, sig_ign);
	sigaction(SIGINT, &handler, NULL);
=======
>>>>>>> 5ed68ae43fffdc485e640ca79398217ede72ad5a
	// atexit(f);
	rl_catch_signals = 0;
	 
	t_prog prog;
	ft_init(ac, av);
	store_env(envp, &prog);
    store_secret_env(envp, &prog);
	while (true)
	{
<<<<<<< HEAD
=======
		ft_sign();
>>>>>>> 5ed68ae43fffdc485e640ca79398217ede72ad5a
		loop(&prog, envp);
	}
} 