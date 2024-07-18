#include "minishell.h"

void heredoc_handle(char *delimiter, t_prog *p) {
    bool expand = true;
    if (pipe(p->end) == -1)
        error_msg("Error: pipe() failed\n");
    if ((p->pid = fork()) < 0)
        error_msg("Error: fork() failed\n");
    if (is_quote(*delimiter))
        expand = false;
    delimiter = remove_quotes(delimiter);
    if (p->pid == 0) {
        close(p->end[0]);
        while (true) {
            p->line = get_next_line(0);
            if (!ft_strncmp(p->line, delimiter, ft_strlen(delimiter)))
                break;
            if (expand && is_env_var(p->line))
                p->line = replace(p->line, p->env_list);
            write(p->end[1], p->line, ft_strlen(p->line));
            free(p->line);
        }
        close(p->end[1]);
        exit(EXIT_SUCCESS);
    } else {
        close(p->end[1]);
        dup2(p->end[0], 0);
        close(p->end[0]);
        wait(NULL);
    }
}

bool red_out_handle(char *redir, char *red_name, t_prog *p) {
    int fd;
    if (!strcmp(redir, ">>"))
        fd = open(red_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(red_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return error_msg("Error: open() failed\n"), false;
    dup2(fd, 1);
    close(fd);
    return true;
}

bool red_in_handle(char *red_name, t_prog *p) {
    int fd = open(red_name, O_RDONLY, 0644);
    if (fd == -1)
        return error_msg("Error: open() failed\n"), false;
    dup2(fd, 0);
    close(fd);
    return true;
}

void redirs_handle(char **redirs, t_prog *p) {
    int i = 0;
    while (redirs[i]) {
        if (!ft_strcmp(redirs[i], "<<"))
            heredoc_handle(redirs[i + 1], p);
        else if (!ft_strcmp(redirs[i], "<"))
            red_in_handle(redirs[i + 1], p);
        else if (!ft_strcmp(redirs[i], ">>") || !ft_strcmp(redirs[i], ">"))
            red_out_handle(redirs[i], redirs[i + 1], p);
        i += 2;  // Skip to next redirection pair
    }
}

void execute_command(t_exec_node *node, t_prog *p) {
    if (node->redir)
        redirs_handle(node->redir, p);
    if (execvp(node->cmd[0], node->cmd) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

bool execution(t_prog *p, t_exec_list *list) {
    t_exec_node *node = list->head;
    int input_fd = STDIN_FILENO;
    int fd[2];

    while (node) {
        if (node->next) {
            if (pipe(fd) == -1)
                return error_msg("Error: pipe() failed\n"), false;
        }

        p->pid = fork();
        if (p->pid == -1)
            return error_msg("Error: fork() failed\n"), false;
        if (p->pid == 0) {
            if (input_fd != STDIN_FILENO) {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            if (node->next) {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            execute_command(node, p);
        } else {
            wait(NULL);
            if (input_fd != STDIN_FILENO)
                close(input_fd);
            if (node->next) {
                close(fd[1]);
                input_fd = fd[0];
            }
        }
        node = node->next;
    }
    return true;
}

int main(int argc, char *argv[], char *envp[]) {
    t_prog p;
    t_exec_list list;
    // Initialize t_prog and t_exec_list
    // Parse the command line into t_exec_list
    // Call execution
    return 0;
}
