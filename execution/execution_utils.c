
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
    return (env_array);
}

void	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0777);
	if (fd_file == -1)
    {
		error_msg2(" : Is a directory", file);
        exit(EXIT_FAILURE);
    }
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
    {
		error_msg2(" No such file or directory", file);
        exit(EXIT_FAILURE);
    }
	else
	{
		dup2(fd_file, 0);
		close(fd_file);
	}
}


static bool make_redirect(char *redirect, char *file)
{
    if (!ft_strcmp(redirect, ">"))
        redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
    else if (!ft_strcmp(redirect, ">>"))
        redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
    else if (!ft_strcmp(redirect, "<") || !ft_strcmp(redirect, "<<"))
        redirect_input(file, O_RDONLY);
    return (true);
}

bool check_redirects(char **redirs)
{
    int i = 0;
    while (redirs[i])
    {
        if (redirs[i + 1])
        {
            if (make_redirect(redirs[i], redirs[i + 1]) == false)
                return (false);
        }
        i += 2;
    }
    return (true);
}
