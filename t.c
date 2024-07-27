bool exec_multi_pipe(char **cmd, char **env, t_prog *p, int in_fd, int out_fd)
{
    p->pid = fork();
    if (p->pid == -1)
        return (error_msg1("fork() failed"), false);

    if (p->pid == 0)
    {
        if (in_fd != STDIN_FILENO)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        execute_cmds(cmd, env, p);
        exit(EXIT_FAILURE);  // In case execute_cmds fails
    }
    
    // Parent doesn't wait here, it continues to set up the next command
    if (in_fd != STDIN_FILENO)
        close(in_fd);
    if (out_fd != STDOUT_FILENO)
        close(out_fd);
    
    return true;
}

bool create_childs(t_exec_list *list, char **env, t_prog *p)
{
    t_exec_node *node;
    int in_fd = STDIN_FILENO;
    int fd[2];

    node = list->head;
    while (node)
    {
        if (*node->cmd)
        {
            if (node->next && pipe(fd) == -1)
                return (error_msg1("Error: pipe() failed\n"), false);

            if (p->nbr_pipe == 0)
                exec_one_cmd(node->cmd, env, p);
            else
                exec_multi_pipe(node->cmd, env, p, in_fd, node->next ? fd[1] : STDOUT_FILENO);

            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (node->next)
            {
                close(fd[1]);
                in_fd = fd[0];
            }
        }
        node = node->next;
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    return true;
}