
#include "../minishell.h"
extern int exit_status;
void free_env_var(char *var, t_env *env)
{
    t_env *iter;
    t_env *prev;

    iter = env;
    prev = iter;
    while(iter)
    {
        if (!strcmp(iter->key, var))
        {
            prev->next = iter->next;
            free(iter->key);
            free(iter->value);
            free(iter);
            return ;
        }
        prev = iter;
        iter = iter->next;
    }
}

int ft_unset(char **args, t_env *env, t_env *s_env)
{
    int nbr_args;
    int i;

    i = 0;
    nbr_args = get_args_nbr(args);
    while (i < nbr_args)
    {
        if (check_var_exist(args[i], &env))
            free_env_var(args[i], env);
        i++;
    }
    i = 0;
    while (i < nbr_args)
    {
        if (check_var_exist(args[i], &s_env))
            free_env_var(args[i], s_env);
        i++;
    }
    exit_status = 0;
    return (0);
}