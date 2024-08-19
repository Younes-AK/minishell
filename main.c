/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:07 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/19 21:43:49 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	loop(t_prog *prog)
{
	prog->r_line = readline("\033[34m[minishell]~> \033[0m");
	if (!prog->r_line)
	{
		close(prog->original_stdin);
		rl_clear_history();
		ft_free_lists(prog, "exit");
	}
	if (ft_strlen(prog->r_line) > 0)
		add_history(prog->r_line);
	if (prog->r_line[0] != '\0')
	{
		if (parssing(prog))
		{
			lexer(prog);
			if (parser(prog))
			{
				execution(prog, prog->exec_list);
				unlink_temp_files(prog->temp_files);
			}
		}
	}
}

struct termios	*term_input_output(void)
{
	static struct termios	tr;

	return (&tr);
}

void	set_default_env(t_env *env, t_prog *p)
{
	char	*args[3];

	args[2] = NULL;
	if (!check_var_exist("PATH", &env))
	{
		args[0] = "export";
		args[1] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin");
		ft_export(args, p);
		free(args[1]);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_prog			prog;

	rl_catch_signals = 0;
	(void)ac;
	(void)av;
	store_env(envp, &prog);
	store_secret_env(envp, &prog);
	set_default_env(prog.env_list, &prog);
	g_exit_status = 0;
	prog.original_stdin = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, term_input_output());
	while (true)
	{
		prog.expanded_var = NULL;
		prog.is_valid = true;
		prog.list_tok = init_token_list(&prog);
		prog.new_tok_list = init_token_list(&prog);
		prog.exec_list = init_exec_list(&prog);
		prog.nbr_pipe = 0;
		ft_sign();
		loop(&prog);
		ft_free_lists(&prog, "free");
		free(prog.r_line);
		tcsetattr(STDIN_FILENO, TCSANOW, term_input_output());
	}
}
