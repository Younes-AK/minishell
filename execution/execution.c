

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
            while ((p->line = readline("> ")))
            {
                if (!ft_strncmp(p->line, delimiter, ft_strlen(delimiter))) 
                {
                    free(p->line);
                    break;
                }
                if (expand && is_env_var(p->line))
                    p->line = replace(p->line, p->env_list);
                write(fd, p->line, ft_strlen(p->line));
                write(fd, "\n", 1);
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
    (void)p;
    p->fd_out = dup(1);
    if (!strcmp(redir, ">>"))
        fd = open(red_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(red_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (error_msg("Error: open() failed\n"), false);
    dup2(fd, 1);
    return true;
}

bool red_in_handle(char *red_name, t_prog *p, bool *here_doc)
{
    if (*here_doc)
        return (true);
    int fd;
    fd = open(red_name, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return false;
    }

    p->fd_in = dup(STDIN_FILENO);
    if (p->fd_in < 0)
    {
        perror("dup1");
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

bool is_here_doc(t_exec_list *list, bool *is_heredoc)
{
    t_exec_node *iter;
    int i;

    iter = list->head;
    while(iter)
    {
        i = 0;
        while (iter->redir[i])
        {
            if (!ft_strcmp(iter->redir[i], "<<"))
            {
                *is_heredoc = true;
                return (true);
            }
            i++;
        }
        iter = iter->next;
    }
    return (false);
}
void redirs_handle(char **redirs, t_prog *p, bool is_heredoc)
{
    int i;
    (void)is_heredoc;
    i = 0;
    while (redirs[i])
    {
        // if(!ft_strcmp(redirs[i], "<") && is_heredoc)
        // {
        //     i+=2;
        //     continue;
        // }
        // if (!ft_strcmp(redirs[i], "<"))
        //     red_in_handle(redirs[i + 1], p);
        if (!ft_strcmp(redirs[i], ">>") || !ft_strcmp(redirs[i], ">"))
            red_out_handle(redirs[i], redirs[i + 1], p);
        i+=2;
    }
}
char *get_last_redin(t_exec_list *list)
{
    t_exec_node *iter;
    char *last_redin = NULL;
    int i;

    iter = list->head;
    while (iter)
    {
        i = 0;
        while (iter->redir && iter->redir[i] && iter->redir[i + 1])
        {
            if (strcmp(iter->redir[i], "<") == 0)
            {
                last_redin = iter->redir[i + 1];
            }
            i += 2;
        }
        iter = iter->next;
    }
    return last_redin;
}
bool execution(t_prog *p, t_exec_list *list)
{
    t_exec_node *node;
    node = list->head;
    bool is_heredoc;
    if (is_here_doc(list, &is_heredoc))
        heredoc_handle(list, p);
    char *filein = get_last_redin(list);
    if (filein)
        red_in_handle(filein, p, &is_heredoc);
    while (node)
    {
        if (*node->redir)
            redirs_handle(node->redir, p, is_heredoc);
        node = node->next;
    }
    if (!exec_cmds(p, list, p->env_list))
        return (false);
    if (p->fd_in >= 0)
    {
        dup2(p->fd_in, STDIN_FILENO);
        close(p->fd_in);
        p->fd_in = -1;
    }
     if (p->fd_out >= 0)
    {
        dup2(p->fd_out, STDOUT_FILENO);
        close(p->fd_out);
        p->fd_out = -1;
    }
    if (p->original_heredoc >= 0 && is_here_doc(list, &is_heredoc))
    {
        dup2(p->original_heredoc, STDIN_FILENO);
        close(p->original_heredoc);
        p->original_heredoc = -1;
    }
    return (true);
}