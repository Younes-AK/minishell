#include "../minishell.h"

#define TMP_FILE	"/tmp/minihell_temporary_file"

static int create_temporary_file(void)
{
    int fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        error_msg1("Error creating temporary file\n");
    return fd;
}

static void get_and_write_input(int tmp_fd, char *eof, t_prog *p)
{
    char *input;
	char *delemitre;
	bool to_expand = true;
    while (true)
    {
        input = readline("> ");
		delemitre = remove_qoutes(eof);
		if (is_quote(*input))
			to_expand = false;
        if (!input)
        {
            close(tmp_fd);
            exit(130);
        }
        if (strcmp(input, delemitre) == 0)
        {
            close(tmp_fd);
            free(input);
            exit(0);
        }
		if (to_expand && is_env_var(input))
            input = replace(input, p->env_list);
        ft_putendl_fd(input, tmp_fd);
        free(input);
    }
}

static void clear_tmp_file_input(void)
{
    int tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
    if (tmp_fd != -1)
        close(tmp_fd);
}

static void make_tmp_file_input(void)
{
    int tmp_fd = open(TMP_FILE, O_RDONLY);
    if (tmp_fd != -1)
    {
        unlink(TMP_FILE);
        dup2(tmp_fd, STDIN_FILENO);
        close(tmp_fd);
    }
}

void here_doc_input(char *eof, int *save_fd, t_prog *p)
{
    int tmp_fd = create_temporary_file();
    if (tmp_fd == -1)
        return;

    int save_fd_out = dup(STDOUT_FILENO);
    dup2(save_fd[1], STDOUT_FILENO);
    pid_t pid = fork();
    if (pid == 0)
        get_and_write_input(tmp_fd, eof, p);
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) == 130)
                clear_tmp_file_input();
            else
                make_tmp_file_input();
        }
    }
    else
        error_msg1("Fork failed in here_doc_input\n");
    dup2(save_fd_out, STDOUT_FILENO);
    close(save_fd_out);
    close(tmp_fd);
}