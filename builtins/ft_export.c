#include "../minishell.h"

void print_env(t_env *env)
{
    t_env *iter = env;

    while (iter)
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(iter->key, STDOUT_FILENO);
        if (iter->value && iter->value[0] != '\0')
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
    int i;
    
    i = 0;
    if (error == -1)
        ft_putstr_fd("export: not valid in this context: ", STDERR_FILENO);
    else if (error == 0 || error == -2)
        ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
    while (arg[i] && (arg[i] != '=' || error == -2))
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
    return (dest);
}

int check_valid_env(const char *arg)
{
    char name[BUFF_SIZE];
    int i;

    i = 0;
    get_env_name(name, arg);
    if (!*name)
        return (-2);
    if (!ft_isalpha(*name) && *name != '_')
        return (0);
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return ft_strchr(arg, '=') ? 2 : 1;
}

int update_env(t_env **env, const char *arg)
{
    char name[BUFF_SIZE];
    get_env_name(name, arg);

    t_env *current = *env;
    while (current)
    {
        if (ft_strcmp(current->key, name) == 0)
        {
            free(current->value);
            if (ft_strchr(arg, '='))
                current->value = ft_strdup(strchr(arg, '=') + 1);
            else
                current->value = ft_strdup("");
            return (1);
        }
        current = current->next;
    }
    return 0;
}

void add_to_env(t_env **env, const char *arg)
{
    t_env *new_node;
    new_node = malloc(sizeof(t_env));
    char name[BUFF_SIZE];
    if (!new_node)
        return;
    get_env_name(name, arg);
    new_node->key = ft_strdup(name);
    if (ft_strchr(arg, '='))
        new_node->value = ft_strdup(ft_strchr(arg, '=') + 1);
    else
        new_node->value = ft_strdup("");
    new_node->next = NULL;
    if (!*env)
        *env = new_node;
    else
        ft_lstadd_back(env, new_node);
}

int ft_export(char **args, t_prog *p)
{
    int exit_status = 0;
    int i;

    i = 1;
    if (!args[1])
        return (print_env(p->env_list), 0);
    while (args[i])
    {
        int error_ret = check_valid_env(args[i]);
        if (error_ret <= 0)
        {
            exit_status = print_error(error_ret, args[i]);
            i++;
            continue;
        }
        if (!update_env(&p->env_list, args[i]))
            add_to_env(&p->env_list, args[i]);
        i++;
    }
    return exit_status;
}