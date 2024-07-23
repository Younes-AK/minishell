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
        error_msg1("path (1) is not accessible\n");
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
bool exec_multi_pipe(char **cmd, char **env, t_prog *p)
{
	if ((p->pid = fork()) == -1)
		return (error_msg1("fork () failled"), false);
	if (p->pid == 0)
	{
		close(p->end[0]);
		dup2(p->end[1], 1);
		execute_cmds(cmd, env, p);
	}
	else
	{
		close(p->end[1]);
		dup2(p->end[0], 0);
		waitpid(p->pid, NULL, 0);
	}
	return (true);
}

bool create_childs(t_exec_list *list, char **env, t_prog *p)
{
    t_exec_node *node;
	int i = 0;
	node = list->head;
	
    while (node)
    {
		if (*node->cmd)
		{
			if (p->nbr_pipe == 0)
				exec_one_cmd(node->cmd, env, p);
			else
			{
				if (i < p->nbr_pipe)
				{
					if (pipe(p->end) == -1)
						return(error_msg1("Error: pipe() fialled\n"), false);
				}
				exec_multi_pipe(node->cmd, env, p);
				i++;
			}
		}
		node = node->next;
    }
	// execute_cmds(node->cmd, env, p);
	return (true);
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

	return (true);
}

