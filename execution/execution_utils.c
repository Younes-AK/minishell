
#include "../minishell.h"

char **convert_env_list(t_env *env_list)
{
    size_t env_size = ft_lstsize(env_list);
    char **env_array = malloc((env_size + 1) * sizeof(char *));
    if (!env_array)
        return NULL;

    t_env *iter = env_list;
    size_t i = 0;
    while (iter && i < env_size)
    {
        size_t key_len = ft_strlen(iter->key);
        size_t value_len = ft_strlen(iter->value);
        
        env_array[i] = malloc(key_len + value_len + 2); 
        if (!env_array[i])
        {
            while (i > 0)
                free(env_array[--i]);
            free(env_array);
            return NULL;
        }
        
        ft_strcpy(env_array[i], iter->key);
        env_array[i][key_len] = '=';
        ft_strcpy(env_array[i] + key_len + 1, iter->value);
        
        i++;
        iter = iter->next;
    }
    env_array[env_size] = NULL;
    return env_array;
}

void	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0777);
	if (fd_file == -1)
		error_msg1("error111 \n");
	else
	{
		dup2(fd_file, 1);
		close(fd_file);
	}
}

void	redirect_input(char *file, int flags)
{
	int	fd_file;
    
	fd_file = open(file, flags);
	if (fd_file == -1)
		error_msg1("error222 \n");
	else
	{
		dup2(fd_file, 0);
		close(fd_file);
	}
}

static void make_redirect(char *redirect, char *file, int *save_fd, bool is_herdoc, t_prog *p)
{
    if (!strcmp(redirect, "<<"))
        here_doc_input(file, save_fd, p);
    else if (!strcmp(redirect, ">"))
        redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
    else if (!strcmp(redirect, "<") && !is_herdoc)
        redirect_input(file, O_RDONLY | O_CREAT);
    else if (!strcmp(redirect, ">>"))
        redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
}

bool check_heredoc(t_exec_list *list)
{
    t_exec_node *iter;
    int i;

    iter = list->head;
    while (iter)
    {
        i = 0;
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
void check_redirects(char **redirs, int *save_fd, t_prog *p)
{
    int i = 0;
    bool is_heredoc = check_heredoc(p->exec_list);
    while (redirs[i])
    {
        if (redirs[i + 1])
        {
            make_redirect(redirs[i], redirs[i + 1], save_fd, is_heredoc, p);
        }
        i += 2;
    }
}

bool check_is_builtin(char *type)
{
    if (!type)
        return (false);
    if (!(strcmp(type, "echo\0")) || !(strcmp(type, "cd\0"))
        || !(strcmp(type, "pwd")) || !(strcmp(type, "export"))
        || !(strcmp(type, "unset")) || !(strcmp(type, "env"))
        || !(strcmp(type, "exit")))
	        return (true);
    return (false);
}

void exec_builtins(char **cmd, t_prog *p)
{
    if (!(strcmp(cmd[0], "echo\0")))
		echo(cmd);
    else if (!(strcmp(cmd[0], "cd\0")))
		cd(cmd, p->env_list);
    else if (!(strcmp(cmd[0], "pwd\0")))
		pwd();
    else if (!(strcmp(cmd[0], "unset\0")))
		ft_unset(cmd, p->env_list);
    else if (!(strcmp(cmd[0], "export\0")))
		ft_export(cmd + 1, p);
    else if (!(strcmp(cmd[0], "env\0")))
		env(p->env_list);
    // else if (!(strcmp(cmd[0], "exit\0")))
	// 	exit(p->env_list);
}