
#include "minishell.h"

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