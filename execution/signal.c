/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:26:50 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/02 12:03:06 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int G_VAR;
void    sig_int_here(int sig_num)
{
    (void)sig_num;
    // ft_status(1, true);
    G_VAR = 1;
    close(0);
    printf("\n");
}

void    ft_handl_quit(int sig_num)
{
    int        status;
    pid_t    pid;

    if (sig_num == SIGQUIT)
    {
        pid = wait(&status);
        if (pid > 0)
        {
            // ft_status(128 + WTERMSIG(status), true);
            write(1, "Quit: 3\n", 9);
        }
    }
}

void    sig_int(int sig_num)
{
    (void)sig_num;
    if (G_VAR == 0)
    {
        // ft_status(1, true);
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    ft_sign(void)
{
    signal(SIGINT, sig_int);
    signal(SIGQUIT, ft_handl_quit);
    rl_catch_signals = 0;
}

void    sig_here_doc(void)
{
    signal(SIGINT, sig_int_here);
    signal(SIGQUIT, SIG_IGN);
}