/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:21:34 by yakazdao          #+#    #+#             */
/*   Updated: 2024/07/07 14:37:02 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_args_nbr(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

void store_env(char **env, t_prog *p)
{
	p->env_list = NULL;
	char **tmp;
	t_env *node;
	int i;
	char *str;
	i = 0;
	while(env[i])
	{
		tmp = ft_split(env[i], '=');
		str = ft_strdup(tmp[0]); 
		node = ft_lstnew(str, strdup(strchr(env[i], '=') + 1));
		ft_lstadd_back(&p->env_list, node);
		free_double_ptr(tmp);
		i++;
	}
}


bool is_env_var(char *content)
{
    int i = 0;
    while (content[i]) 
    {
        if (content[i] == '$')
            return true;
        i++;
    }
    return false;
}

bool check_var_exist(char *str, t_env **env)
{
    t_env *iter;

    iter = *env;
    while (iter)
    {
        if (!ft_strcmp(iter->key, str))
            return (true);
        iter = iter->next;
    }
    return (false);
}

