

#include "../minishell.h"

void process_heredoc(t_exec_node *node, t_prog *p, const char *temp_file) 
{
    int fd;
    char *delimiter;
    bool expand;
    int i = 0;

    while (node->redir[i]) 
    {
        if (strcmp(node->redir[i], "<<") == 0) {
            delimiter = node->redir[i + 1];
            expand = true;
            if (is_quote(*delimiter))
                expand = false;
            delimiter = remove_qoutes(delimiter);
            fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                return;
            }
            while ((p->line = get_next_line(0)) != NULL) 
            {
                if (!ft_strncmp(p->line, delimiter, ft_strlen(delimiter))) 
                {
                    free(p->line);
                    break;
                }
                if (expand && is_env_var(p->line))
                    p->line = replace(p->line, p->env_list);
                write(fd, p->line, ft_strlen(p->line));
                free(p->line);
            }
            close(fd);
        }
        i += 2;
    }
}

void heredoc_handle(t_exec_list *list, t_prog *p) 
{
    const char *temp_file;
    int fd;
    t_exec_node *node;
    
    temp_file = "/tmp/heredoc_temp";
    node = list->head;
    while (node) 
    {
        process_heredoc(node, p, temp_file);
        node = node->next;
    }
    p->original_heredoc = dup(STDIN_FILENO);
    fd = open(temp_file, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    unlink(temp_file);
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

void redirs_handle(char **redirs, t_prog *p)
{
    int i;

    i = 0;
    while (redirs[i])
    {
        if (!ft_strcmp(redirs[i], "<"))
            red_in_handle(redirs[i + 1], p);
        else if (!ft_strcmp(redirs[i], ">>") || !ft_strcmp(redirs[i], ">"))
            red_out_handle(redirs[i], redirs[i + 1], p);
        i+=2;
    }
}
bool is_here_doc(t_exec_list *list)
{
    t_exec_node *iter;
    int i;

    i = 0;
    iter = list->head;
    while(iter)
    {
        while (iter->redir[i])
        {
            if (!ft_strcmp(iter->redir[i], "<<"))
                return (true);
            i++;
        }
        iter = iter->next;
    }
    return (false);
}

bool execution(t_prog *p, t_exec_list *list)
{
    t_exec_node *node;
    node = list->head;
    if (is_here_doc(list))
        heredoc_handle(list, p);
    while (node)
    {
        if (*node->redir)
            redirs_handle(node->redir, p);
        node = node->next;
    }
    if (!exec_cmds(p, list, p->env_list))
        return (false);
    if (p->original_heredoc >= 0 && is_here_doc(list))
    {
        dup2(p->original_heredoc, STDIN_FILENO);
        close(p->original_heredoc);
        p->original_heredoc = -1;
    }
    return (true);
}