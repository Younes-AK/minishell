#include "../minishell.h"
extern int exit_status;
static void save_restore_fds(int *save_fd, bool save)
{
    static const int fds[] = {STDIN_FILENO, STDOUT_FILENO};
    for (int i = 0; i < 2; i++)
    {
        if (save)
            save_fd[i] = dup(fds[i]);
        else
        {
            dup2(save_fd[i], fds[i]);
            close(save_fd[i]);
        }
    }
}

static void setup_pipes(int *prev_pipe, int *curr_pipe, bool is_first, bool is_last)
{
    if (!is_first)
    {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
    }
    if (!is_last)
    {
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[1]);
        close(curr_pipe[0]);
    }
}

static void execute_command(char **redirs, char **cmds, t_prog *p)
{
    int save_fd[2];
    save_restore_fds(save_fd, true);
    check_redirects(redirs, p);
    execute(cmds, p);
    free_double_ptr(cmds);
    save_restore_fds(save_fd, false);
}

static void exec_builtin_parent(char **cmd, char **redirs, t_prog *p)
{
    int save_fd[2];
    save_restore_fds(save_fd, true);
    check_redirects(redirs, p);
    exec_builtins(cmd, p);
    save_restore_fds(save_fd, false);
}

void execution(t_prog *p, t_exec_list *list)
{
    if (!list || !list->head)
        return;

    int prev_pipe[2], curr_pipe[2];
    t_exec_node *node = list->head;
    bool is_first = true;
    (void)p;
 
    while (node)
    {
        bool is_last = (node->next == NULL);

        if (!is_last)
            pipe(curr_pipe);
        if (check_is_builtin(node->cmd[0]) && is_first && is_last)
            exec_builtin_parent(node->cmd, node->redir, p);
        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                setup_pipes(prev_pipe, curr_pipe, is_first, is_last);
                execute_command(node->redir, node->cmd, p);
                // exit(p->error_status);
            }
            else if (pid < 0)
            {
                perror("fork");
                break;
            }
        }

        if (!is_first)
            close(prev_pipe[0]);
        if (!is_last)
        {
            prev_pipe[0] = curr_pipe[0];
            close(curr_pipe[1]);
        }
        is_first = false;
        node = node->next;
    }
    int status;
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
    }
}