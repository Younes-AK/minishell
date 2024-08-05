#include "../minishell.h"
#define BUFF_SIZE 1024

void print_env(t_env *env)
{
    t_env *iter = env;

    while (iter)
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(iter->key, STDOUT_FILENO);
        if (iter->value)
        {
            ft_putstr_fd("=\"", STDOUT_FILENO);
            ft_putstr_fd(iter->value, STDOUT_FILENO);
            ft_putstr_fd("\"", STDOUT_FILENO);
        }
        ft_putstr_fd("\n", STDOUT_FILENO);
        iter = iter->next;
    }
}

static int print_error(int error, const char *arg)
{
    if (error == -1)
        ft_putstr_fd("export: not valid in this context: ", STDERR_FILENO);
    else if (error == 0 || error == -3)
        ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);

    int i = 0;
    while (arg[i] && (arg[i] != '=' || error == -3))
    {
        write(STDERR_FILENO, &arg[i], 1);
        i++;
    }
    write(STDERR_FILENO, "\n", 1);
    return (1);
}

char *get_env_name(char *dest, const char *src)
{
    int i = 0;
    while (src[i] && src[i] != '=' && i < BUFF_SIZE - 1)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int is_valid_env(const char *arg)
{
    char name[BUFF_SIZE];
    get_env_name(name, arg);

    if (!*name)
        return -3;
    if (!isalpha(*name) && *name != '_')
        return 0;

    for (int i = 1; name[i]; i++)
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return 0;
    }

    return strchr(arg, '=') ? 2 : 1;
}

int update_env(t_env **env, const char *arg)
{
    char name[BUFF_SIZE];
    get_env_name(name, arg);

    t_env *current = *env;
    while (current)
    {
        if (strcmp(current->key, name) == 0)
        {
            free(current->value);
            current->value = strchr(arg, '=') ? ft_strdup(strchr(arg, '=') + 1) : ft_strdup("");
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void add_to_env(t_env **env, const char *arg)
{
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node)
        return;

    char name[BUFF_SIZE];
    get_env_name(name, arg);

    new_node->key = ft_strdup(name);
    new_node->value = strchr(arg, '=') ? ft_strdup(strchr(arg, '=') + 1) : ft_strdup("");
    new_node->next = NULL;

    if (!*env)
    {
        *env = new_node;
    }
    else
    {
        t_env *current = *env;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
}

int ft_export(char **args, t_prog *p)
{
    int exit_status = 0;
    if (!args[1])
    {
        print_env(p->env_list);
        return 0;
    }

    for (int i = 1; args[i]; i++)
    {
        int error_ret = is_valid_env(args[i]);
        if (error_ret <= 0)
        {
            exit_status = print_error(error_ret, args[i]);
            continue;
        }
        if (!update_env(&p->env_list, args[i]))
            add_to_env(&p->env_list, args[i]);
        if (!update_env(&p->secret_env, args[i]))
            add_to_env(&p->secret_env, args[i]);
    }

    return exit_status;
}