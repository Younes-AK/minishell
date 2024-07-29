#include "../minishell.h"

static void set_first_input_fd(int *old_pipe_in)
{
    *old_pipe_in = -1;
}

static void save_std_fds(int *save_fd)
{
    save_fd[0] = dup(STDIN_FILENO);
    save_fd[1] = dup(STDOUT_FILENO);
}

static void create_pipe(int *old_pipe_in, bool is_last)
{
    int new_pipe[2];

    if (*old_pipe_in != -1)
    {
        dup2(*old_pipe_in, STDIN_FILENO);
        close(*old_pipe_in);
    }
    if (!is_last)
    {
        pipe(new_pipe);
        dup2(new_pipe[1], STDOUT_FILENO);
        close(new_pipe[1]);
        *old_pipe_in = new_pipe[0];
    }
    else
    {
        *old_pipe_in = -1;
    }
}


static void restore_std_fds(int *save_fd)
{
    dup2(save_fd[0], STDIN_FILENO);
    close(save_fd[0]);
    dup2(save_fd[1], STDOUT_FILENO);
    close(save_fd[1]);
}

void command_parser(char **redirs, char **cmds, int *old_pipe_in, t_prog *p, bool is_last)
{
    int save_fd[2];

    save_std_fds(save_fd);
    create_pipe(old_pipe_in, is_last);
    check_redirects(redirs, save_fd);
    execute(cmds, p);
    free_double_ptr(cmds);
    restore_std_fds(save_fd);
}


void execution(t_prog *p, t_exec_list *list)
{
    int old_pipe_in;
    
    if (!list || !list->head)
        return;
    
    set_first_input_fd(&old_pipe_in);
    
    t_exec_node *node = list->head;
    while (node)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            command_parser(node->redir, node->cmd, &old_pipe_in, p, node->next == NULL);
            exit(0);
        }
        else
        {
            if (old_pipe_in != -1)
            {
                close(old_pipe_in);
            }
            node = node->next;
        }
    }
    int status;
    while (wait(&status) > 0);
}


