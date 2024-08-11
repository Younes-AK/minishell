

#include "../minishell.h"

bool execute_command(char **redirs, char **cmds, t_prog *p)
{
    if (!check_redirects(redirs, p))
    {
        return false;
    }
    execute(cmds, p);
    // free_double_ptr(cmds);
    return true;
}

void exec_builtin_parent(char **cmd, char **redirs, t_prog *p)
{
    check_redirects(redirs, p);
    exec_builtins(cmd, p);
}

void close_pipes(t_prog *p)
{
    if (!p->is_first)
        close(p->prev_pipe[0]);
    if (!p->is_last)
    {
        close(p->curr_pipe[1]);
        p->prev_pipe[0] = p->curr_pipe[0];
    }
}

bool check_is_builtin(char **type, int *index)
{
    if (!type)
        return (false);
    while (*type)
    {
      if (!(ft_strcmp(*type, "echo\0")) || !(ft_strcmp(*type, "cd\0"))
          || !(ft_strcmp(*type, "pwd")) || !(ft_strcmp(*type, "export"))
          || !(ft_strcmp(*type, "unset")) || !(ft_strcmp(*type, "env"))
          || !(ft_strcmp(*type, "exit")))
            return (true);
      type++;
      *index += 1;
    }
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
    {
        // p->is_env_cmd = true;
		    ft_export(cmd, p);
    }
    else if (!(ft_strcmp(cmd[0], "env\0")))
		env(p->env_list);
    else if (!(ft_strcmp(cmd[0], "exit\0")))
		ft_exit(cmd);
}