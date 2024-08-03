


#include "../minishell.h"

// int    ft_status(int status, bool flag)
// {
//     static int    exit_status;

//     if (flag)
//         exit_status = status;
//     return (exit_status);
// }

// void    exit_status(pid_t id)
// {
//     int        status;
//     pid_t    w_pid;

//     w_pid = wait(&status);
//     if (id == w_pid)
//     {
//         if (WIFSIGNALED(status))
//             ft_status(WTERMSIG(status) + 128, true);
//         else if (WIFEXITED(status))
//             ft_status(WEXITSTATUS(status), true);
//     }
//     else
//         return ;
// }

// int get_last_exit_status(int *exit_status)
// {
//     exit_status = ft_exit_status(&exit_status);
//     return (exit_status);
// }