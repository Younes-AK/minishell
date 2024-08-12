#include "../minishell.h"

char *check_path(char **paths, char *cmd)
{
    char *full_path;
    char *cmd_path;
    int i;

    i = 0;
    if ((*cmd == '.' && *(cmd + 1) == '/') || *cmd == '/')
        return (cmd);
    cmd_path = ft_strjoin("/", cmd);
    while(paths && paths[i])
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
    free(cmd_path);
    return (NULL);
}

char * get_path(t_env *env_list, char *key)
{
    t_env *iter;

    iter = env_list;
    while (iter)
    {
        if (!strcmp(iter->key, key))
            return (iter->value);
        iter = iter->next;
    }
    return (NULL);
}

static void execute_cmd(char **cmd, t_prog *p)
{
    char **env_variables;
    
    if (!cmd || !*cmd) return;
    p->access_path = check_path(p->all_paths, cmd[0]);
    if (!p->access_path)
    {
        error_msg2(" : command not found", cmd[0]);
        exit(127);
    }
    env_variables = convert_env_list(p->env_list);
    execve(p->access_path, cmd, env_variables);
    error_msg2(" : command not found", cmd[0]);
    free(p->access_path);
    free_double_ptr(env_variables);
    exit(126);
}

void execute(char **cmd, t_prog *p)
{
    if (!cmd || !*cmd) return;
    p->path = get_path(p->env_list, "PATH");
    p->all_paths = ft_split(p->path, ':', p);
    execute_cmd(cmd, p);
    free_double_ptr(p->all_paths);
}
