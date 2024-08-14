

#include "../minishell.h"

int is_in_env(t_env *env, const char *key) 
{
    while (env) 
    {
        if (ft_strcmp(env->key, key) == 0)
            return 1;
        env = env->next;
    }
    return 0;
}

void env_add(const char *new_var, t_env *env) 
{
    char *delimiter;
    size_t key_len;
    t_env *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return;
    delimiter = ft_strchr(new_var, '=');
    key_len = delimiter - new_var;
    new_node->key = strndup(new_var, key_len);
    new_node->value = strdup(delimiter + 1);
    new_node->next = NULL;
    while (env->next)
        env = env->next;
    env->next = new_node;
}

void ft_memdel(void *ptr) 
{
    if (ptr) 
    {
        free(ptr);
        ptr = NULL;
    }
}