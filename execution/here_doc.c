#include "../minishell.h"

#define TMP_FILE	"/tmp/minihell_temporary_file"

static void get_and_write_input(int tmp_fd, char *eof, t_prog *p)
{
    char *input;
	char *delemitre;
	bool to_expand = true;

    if (is_quote(*eof))
        to_expand = false;
    while (true)
    {
        sig_here_doc(p);
        input = readline("> ");
        if (!input)
        {
            close(tmp_fd);
            break;
        }
		delemitre = remove_qoutes(eof, p);
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
    char *ka_pa;

    ka_pa = ft_itoa(i);
    ret = ft_strjoin(TMP_FILE, ka_pa);
    free(ka_pa);
    return (ret);
}
void here_doc_input(t_exec_node *node, t_prog *p, int j)
{
    int i;
    int fd;

    i = 0;
    char *filename; 

    while(node->redir[i])
    {
        filename = generate_name(j);
        if (!ft_strcmp(node->redir[i], "<<"))
        {
            fd = create_temporary_file(filename);
            get_and_write_input(fd, node->redir[i + 1], p);
            node->redir[i + 1] = filename;
            close(fd);
        }
        i+=2;
    }
}

void ft_heredoc(t_prog *p)
{
    t_exec_node *node;
    int i;

    i = 0;
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