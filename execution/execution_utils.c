
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

static void make_redirect(char *redirect, char *file, int *save_fd)
{
    if (!strcmp(redirect, ">"))
        redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
    else if (!strcmp(redirect, "<"))
        redirect_input(file, O_RDONLY | O_CREAT);
    else if (!strcmp(redirect, ">>"))
        redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
    else if (!strcmp(redirect, "<<"))
        here_doc_input(file, save_fd);
}

void check_redirects(char **redirs, int *save_fd)
{
    int i = 0;
    while (redirs[i])
    {
        if (redirs[i + 1])
        {
            make_redirect(redirs[i], redirs[i + 1], save_fd);
        }
        i += 2;
    }
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

