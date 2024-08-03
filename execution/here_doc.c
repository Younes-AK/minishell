#include "../minishell.h"

#define TMP_FILE	"/tmp/minihell_temporary_file"

static void get_and_write_input(int tmp_fd, char *eof, t_prog *p)
{
    char *input;
	char *delemitre;
	bool to_expand = true;

    while (true)
    {
        sig_here_doc(p);
        input = readline("> ");
        if (!input)
        {
            close(tmp_fd);
            break;
        }
		delemitre = remove_qoutes(eof);
		if (is_quote(*input))
			to_expand = false;
        if (strcmp(input, delemitre) == 0)
        {
            close(tmp_fd);
            free(input);
            break;
        }
		if (to_expand && is_env_var(input))
            input = replace(input, p->env_list);
        ft_putendl_fd(input, tmp_fd);
        free(input);
    }
}

// static void clear_tmp_file_input(void)
// {
//     int tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
//     if (tmp_fd != -1)
//         close(tmp_fd);
// }

// static void make_tmp_file_input(void)
// {
//     int tmp_fd = open(TMP_FILE, O_RDONLY);
//     if (tmp_fd != -1)
//     {
//         unlink(TMP_FILE);
//         dup2(tmp_fd, STDIN_FILENO);
//         close(tmp_fd);
//     }
// }
static int create_temporary_file(char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        error_msg1("Error creating temporary file\n");
    return fd;
}
char *generate_name(int i)
{
    char *ret;
    ret = ft_strjoin(TMP_FILE, ft_itoa(i));
    return (ret);
}
void here_doc_input(t_exec_node *node, t_prog *p, int j)
{
    int i;
    int fd;

    i = 0;
    char *filename; 

    filename = generate_name(j);
    while(node->redir[i])
    {
        if (!ft_strcmp(node->redir[i], "<<"))
        {
            fd = create_temporary_file(filename);
            get_and_write_input(fd, node->redir[i + 1], p);
            node->redir[i + 1] = ft_strdup(filename);
            close(fd);
        }
        i+=2;
    }
    free(filename);
}

void ft_heredoc(t_prog *p)
{
    t_exec_node *node;
    int i;

    i = 0;
    p->original_stdin = dup(STDIN_FILENO);
    node = p->exec_list->head;
    while (node)
    {
        if (node->redir)
            here_doc_input(node, p, i);
        node = node->next;
        i++;
    }
    if (p->to_restart_stdin == 1)
    {
        dup2(p->original_stdin, 0);
        p->to_restart_stdin = 0;
    }
}