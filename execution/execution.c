#include "../minishell.h"
extern int exit_status;

static bool execute_command(char **redirs, char **cmds, t_prog *p)
{
    if (!check_redirects(redirs, p))
    {
        return false;
    }
    execute(cmds, p);
    free_double_ptr(cmds);
    return true;
}

static void exec_builtin_parent(char **cmd, char **redirs, t_prog *p)
{
    check_redirects(redirs, p);
    exec_builtins(cmd, p);
}

static void close_pipes(t_prog *p)
{
    if (!p->is_first)
        close(p->prev_pipe[0]);
    if (!p->is_last)
    {
        close(p->curr_pipe[1]);
        p->prev_pipe[0] = p->curr_pipe[0];
    }
}

static void setup_child_pipes(t_prog *p)
{
    if (!p->is_first)
    {
        dup2(p->prev_pipe[0], STDIN_FILENO);
        close(p->prev_pipe[0]);
    }
    if (!p->is_last)
    {
        dup2(p->curr_pipe[1], STDOUT_FILENO);
        close(p->curr_pipe[1]);
        close(p->curr_pipe[0]);
    }
}

static void handle_child_process(t_exec_node *node, t_prog *p)
{
    setup_child_pipes(p);
    if (check_is_builtin(node->cmd[0]))
    {
        exec_builtins(node->cmd, p);
        exit(exit_status);
    }
    while (*node->cmd && !ft_strcmp(*node->cmd, ""))
        node->cmd++;
    if (!execute_command(node->redir, node->cmd, p))
    {
        if (!p->is_last)
        {
            close(p->curr_pipe[1]);
            dup2(p->curr_pipe[0], STDIN_FILENO);
        }
        exit(1);
    }
    exit(0);
}

static void wait_for_children(void)
{
    int status;
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
    }
}

static void fork_and_execute(t_exec_node *node, t_prog *p)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        handle_child_process(node, p);
    }
    else if (pid < 0)
    {
        ft_putstr_fd("fork function fialled\n", 2);
    }
}

void execution(t_prog *p, t_exec_list *list)
{
    t_exec_node *node;
    if (!list || !list->head)
        return;
    p->original_stdout = dup(1);
    p->is_first = true;
    node = list->head;
    while (node)
    {
        p->is_last = (node->next == NULL);
        if (!p->is_last)
            pipe(p->curr_pipe);
        if (check_is_builtin(node->cmd[0]) && p->is_first && p->is_last)
            exec_builtin_parent(node->cmd, node->redir, p);
        else
            fork_and_execute(node, p);
        close_pipes(p);
        p->is_first = false;
        node = node->next;
    }
    wait_for_children();
    dup2(p->original_stdout, STDOUT_FILENO);
    close(p->original_stdout);
}
