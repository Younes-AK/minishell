#include "../minishell.h"

void ft_free(t_prog *p_struct)
{
    int i;

    i = 0;
    while(p_struct->all_paths[i])
    {
        free(p_struct->all_paths[i]);
        i++;
    }
    free(p_struct->all_paths);
}

char *check_path(char **paths, char *cmd)
{
    char *full_path;
    char *cmd_path;
    int i;

    i = 0;
    cmd_path = ft_strjoin("/", cmd);
    while(paths[i])
    {
        full_path = ft_strjoin(paths[i], cmd_path);
        if(access(full_path, X_OK) == 0)
        {
            free(cmd_path);
            return(full_path);
        }
        free(full_path);
        i++;
    }
    return (NULL);
}
char * get_path(t_env *env_list, char *key)
{
	t_env	*iter;

	iter = env_list;
	while (iter)
	{
		if (!strcmp(iter->key, key))
			return (iter->value);
		iter = iter->next;
	}
	return (NULL);
}
void execute_cmds(char **cmds, char **env, t_prog *p)
{
    p->access_path = check_path(p->all_paths, cmds[0]);
	if(!p->access_path)
    {
        ft_free(p);
        error_msg1(cmds[0]);
		error_msg1(": command not found\n");
		return;
    }
    execve(p->access_path, cmds, env);
    error_msg1("Error : Execve () failed\n");
}

bool exec_one_cmd(char **cmds, char **env, t_prog *p)
{
	int pid;

	pid = fork();
	if (pid == -1)
		return (error_msg1("pipe () failled"), false);
	if (pid == 0)
		execute_cmds(cmds, env, p);
	else
		waitpid(pid, NULL, 0);
	return (true);
}
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

    while (wait(NULL) > 0)
	;

    return true;
}

 

bool exec_cmds(t_prog *p, t_exec_list *exec_list, t_env *env_list)
{
	char **env;
	env = convert_env_list(env_list);
    p->path = get_path(env_list, "PATH");
	if (!p->path)
		error_msg1("Error : path not found\n");
    p->all_paths = ft_split(p->path, ':');
	if (!p->all_paths)
		return (error_msg1("Error : split func failed\n"), false);
	create_childs(exec_list, env, p);
	free_double_ptr(p->all_paths);
	free_double_ptr(env);


	// if (p->original_stdin >= 0)
    // {
    //     dup2(p->original_stdin, STDIN_FILENO);
    //     close(p->original_stdin);
    //     p->original_stdin = -1;
    // }

	return (true);
}

