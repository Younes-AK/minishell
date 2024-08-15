/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:26:50 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/15 09:35:27 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

void	sig_int_here(int sig_num)
{
	(void)sig_num;
	g_exit_status = 1;
	close(0);
}

void	ft_handl_quit(int sig_num)
{
	int		status;
	pid_t	pid;

	g_exit_status = 0;
	if (sig_num == SIGQUIT)
	{
		pid = wait(&status);
		if (pid > 0)
		{
			write(1, "Quit: 3\n", 9);
		}
	}
}

void	sig_int(int sig_num)
{
	(void)sig_num;
	g_exit_status = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sign(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, ft_handl_quit);
	rl_catch_signals = 0;
}

void	sig_here_doc(t_prog *p)
{
	signal(SIGINT, sig_int_here);
	signal(SIGQUIT, SIG_IGN);
	p->to_restart_stdin = 1;
}
