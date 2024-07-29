#include "../minishell.h"

#define TMP_FILE	"/tmp/minihell_temporary_file"

static int	create_temporary_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		error_msg1("error \n");
	return (fd);
}

static void get_and_write_input(int tmp_fd, char *eof)
{
    char *input;
    while (true)
    {
        input = readline("> ");
        if (!input)
        {
            perror("readline");
            // error_msg1("error2 \n");
            close(tmp_fd);
            exit(1);
        }
        if (strcmp(input, eof))
            ft_putendl_fd(input, tmp_fd);
        else
        {
            close(tmp_fd);
            free(input);
            break;
        }
        free(input);
    }
    exit(0);
}


static void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}

static void	make_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	dup2(tmp_fd, 0);
	close(tmp_fd);
}

void	here_doc_input(char *eof, int *save_fd)
{
	int		tmp_fd;
	int		save_fd_out;
	int		pid;
	int		status;

	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return ;
	save_fd_out = dup(1);
	dup2(save_fd[1], STDOUT_FILENO);
	// signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_and_write_input(tmp_fd, eof);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		clear_tmp_file_input();
		// g_minishell.error_status = 130;
	}
	make_tmp_file_input();
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
}