

#include "../minishell.h"

void heredoc_reader(char *delimiter, t_prog *p)
{
    bool expand = !is_quote(*delimiter);
    delimiter = remove_qoutes(delimiter);

    char *line = get_next_line(0);
    while (line)
    {
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
        {
            free(line);
            break;
        }
        if (expand && is_env_var(line))
            line = replace(line, p->env_list);
        write(p->end[1], line, ft_strlen(line));
        free(line);
        line = get_next_line(0);
    }
    free(delimiter);
}

void heredoc_handle(char **redirs, t_prog *p)
{
    int i = 0;

    if (pipe(p->end) == -1)
        error_msg("Error : pipe () failed\n");
    p->original_stdin = dup(STDIN_FILENO);
    p->pid = fork();
    if (p->pid < 0)
        error_msg("Error : fork () failed\n");
    if (p->pid == 0)
    {
        close(p->end[0]);
        while (redirs[i])
        {
            if (!ft_strcmp(redirs[i], "<<"))
                heredoc_reader(redirs[i + 1], p);
            i += 2;
        }
        close(p->end[1]);

    }
    else
    {
        close(p->end[1]);
        dup2(p->end[0], STDIN_FILENO);
        close(p->end[0]);
        waitpid(p->pid, NULL, 0);
    }
}

void redirs_handle(char **redirs, t_prog *p)
{
    int i = 0;
    bool has_heredoc = false;

    while (redirs[i])
    {
        if (!ft_strcmp(redirs[i], "<<"))
        {
            has_heredoc = true;
            break;
        }
        i += 2;
    }

    if (has_heredoc)
        heredoc_handle(redirs, p);

  
    // i = 0;
    // while (redirs[i])
    // {
    //     if (ft_strcmp(redirs[i], "<<") && ft_strcmp(redirs[i], "<") && ft_strcmp(redirs[i], ">") && ft_strcmp(redirs[i], ">>"))
    //     {
    //         // Handle input/output redirections
    //         // ...
    //     }
    //     i += 2;
    // }
}


bool red_out_handle(char *redir, char *red_name, t_prog *p)
{
    int fd;

    if (pipe(p->end) == -1)
        error_msg("Error: pipe() failed\n");
    if ((p->pid = fork()) < 0)
        error_msg("Error: fork() failed\n");
    if (p->pid == 0)
    {
        close(p->end[0]);
        if (!strcmp(redir, ">>"))
            fd = open(red_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(red_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (error_msg("Error: open() failed\n"), false);
        dup2(fd, 1);
        close(fd);
        close(p->end[1]);
        exit(0);
    }
    else
    {
        close(p->end[1]);
        dup2(p->end[0], 0);
        close(p->end[0]);
        wait(NULL);
    }
    return true;
}

bool red_in_handle(char *red_name, t_prog *p)
{
    int fd;

    fd = open(red_name, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return false;
    }

    p->original_stdin = dup(STDIN_FILENO);
    if (p->original_stdin < 0)
    {
        perror("dup");
        close(fd);
        return false;
    }

    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return false;
    }
    close(fd);

    return true;
}

// void redirs_handle(char **redirs, t_prog *p)
// {
//     int i;

//     i = 0;
//     while (redirs[i])
//     {
//         if (!ft_strcmp(redirs[i], "<<"))
//             heredoc_handle(redirs, p);
//         else if (!ft_strcmp(redirs[i], "<"))
//             red_in_handle(redirs[i + 1], p);
//         else if (!ft_strcmp(redirs[i], ">>") || !ft_strcmp(redirs[i], ">"))
//             red_out_handle(redirs[i], redirs[i + 1], p);
//         i+=2;
//     }
// }

bool execution(t_prog *p, t_exec_list *list)
{
    t_exec_node *node;
    node = list->head;
    while (node)
    {
        if (*node->redir)
            redirs_handle(node->redir, p);
        node = node->next;
    }
    if (!exec_cmds(p, list, p->env_list))
    {
        return (false);
    }
    if (p->original_stdin >= 0)
    {
        dup2(p->original_stdin, STDIN_FILENO);
        close(p->original_stdin);
        p->original_stdin = -1;
    }
    exit(0);
    return (true);
}