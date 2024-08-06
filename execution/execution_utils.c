
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
bool is_ambiguous(const char *filename) 
{
    int count = 0;
    const char *ptr;

    ptr = filename;
    while (*ptr) 
    {
        while (*ptr && (*ptr == ' ' || *ptr == '\t'))
            ptr++;
        if (*ptr)
            count++;
        while (*ptr && (*ptr != ' ' && *ptr != '\t'))
            ptr++;
    }
    return (count > 1);
}

static bool make_redirect(char *redirect, char *file, t_prog *p)
{
    if ((is_ambiguous(file) && p->is_env_cmd) || !ft_strcmp(file, "")) 
    {
        ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
        return (false);
    }
    if (!ft_strcmp(redirect, ">"))
        redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
    else if (!ft_strcmp(redirect, ">>"))
        redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
    else if (!ft_strcmp(redirect, "<") || !ft_strcmp(redirect, "<<"))
        redirect_input(file, O_RDONLY);
    return (true);
}

bool check_redirects(char **redirs, t_prog *p)
{
    int i = 0;
    while (redirs[i])
    {
        if (redirs[i + 1])
        {
            if (make_redirect(redirs[i], redirs[i + 1], p) == false)
                return (false);
        }
        i += 2;
    }
    return (true);
}

bool check_is_builtin(char *type)
{
    if (!type)
        return (false);
    if (!(ft_strcmp(type, "echo\0")) || !(ft_strcmp(type, "cd\0"))
        || !(ft_strcmp(type, "pwd")) || !(ft_strcmp(type, "export"))
        || !(ft_strcmp(type, "unset")) || !(ft_strcmp(type, "env"))
        || !(ft_strcmp(type, "exit")))
	        return (true);
    return (false);
}

void exec_builtins(char **cmd, t_prog *p)
{
    if (!(ft_strcmp(cmd[0], "echo\0")))
		echo(cmd);
    else if (!(ft_strcmp(cmd[0], "cd\0")))
		cd(cmd, p->env_list);
    else if (!(ft_strcmp(cmd[0], "pwd\0")))
		pwd();
    else if (!(ft_strcmp(cmd[0], "unset\0")))
		ft_unset(cmd, p->env_list);
    else if (!(ft_strcmp(cmd[0], "export\0")))
		ft_export(cmd , p);
    else if (!(ft_strcmp(cmd[0], "env\0")))
		env(p->env_list);
    else if (!(ft_strcmp(cmd[0], "exit\0")))
		ft_exit(cmd);
}