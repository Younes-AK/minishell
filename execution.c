

#include "minishell.h"

void heredoc_handle(char *delimitre, t_prog *p)
{
    bool    expand;

    expand = true;
    if (pipe(p->end) == -1)
        error_msg("Error : pipe () failed\n");
    if ((p->pid = fork()) < 0)
        error_msg("Error : fork () failed\n");
    if (is_quote(*delimitre))
        expand = false;
    delimitre = remove_qoutes(delimitre);
    if (p->pid == 0)
    {
        close(p->end[0]);
        while (true)
        {
            p->line = get_next_line(0);
            if (!ft_strncmp(p->line, delimitre, ft_strlen(delimitre)))
                break;
            if (expand && is_env_var(p->line))
                p->line = replace(p->line, p->env_list);
            write(p->end[1], p->line, ft_strlen(p->line));
            free(p->line);
            p->line = get_next_line(0);
        }
        close(p->end[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(p->end[1]);
        dup2(p->end[0], 0);
        close(p->end[0]);
        wait(NULL);
    }
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

bool    red_in_handle(char *red_name, t_prog *p)
{
    int fd;

    if (pipe(p->end) == -1)
        error_msg("Error : pipe () failed\n");
    if ((p->pid = fork()) < 0)
        error_msg("Error : fork () failed\n");
    if (p->pid == 0)
    {
        fd = open(red_name, O_RDONLY, 0777);
        if (fd != 0)
            return (error_msg("open failed \n"), false);
        dup2(fd, 0);
        close (fd);
        close(p->end[1]);
        exit(0);
    }
    else
    {
        close(p->end[0]);
        dup2(p->end[1], 1);
        close(p->end[1]);
        wait(NULL);
    }
    return (true);
}

void redirs_handle(char **redirs, t_prog *p)
{
    int i;

    i = 0;
    (void)p;
    while (redirs[i])
    {
        if (!ft_strcmp(redirs[i], "<<"))
            heredoc_handle(redirs[i + 1], p);
        else if (!ft_strcmp(redirs[i], "<"))
            red_in_handle(redirs[i + 1], p);
        else if (!ft_strcmp(redirs[i], ">>") || !ft_strcmp(redirs[i], ">"))
            red_out_handle(redirs[i], redirs[i + 1], p);
        i += 1;
    }
}

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
    return (true);
}