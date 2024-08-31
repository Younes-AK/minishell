/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_syntx_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:39:15 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/30 06:49:07 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

extern int	g_exit_status;

void read_in(char *delemitre)
{
	char	*input;

	while (true)
	{
		input = readline("> ");
		if (!input)
				return ;
		if (ft_strcmp (input, delemitre) == 0)
		{
			g_exit_status = 0;
			free(input);
			break;
		}
		free(input);
	}	
}
void read_herdoc(char **redirs)
{
	int		i;

	i = 0;
	while (redirs[i])
	{
		if (!ft_strcmp(redirs[i], "<<") && redirs[i + 1])
		{
			read_in(redirs[i + 1]);
		}
		i += 1;
	}
}
void heredoc_error(t_prog *p)
{
	t_exec_node	*iter;

	iter = p->exec_list->head;
	while (iter)
	{
		read_herdoc(iter->redir);
		iter = iter->next;
	}
}
char	*get_delm(t_prog *p)
{
	t_tok_node	*iter;

	iter = p->list_tok->head;
	while(iter)
	{
		if (iter->next && iter->type == REDIR_HEREDOC)
			if (iter->next->type == WORD)
				return (iter->next->content);
		iter = iter->next;
	}
	return (NULL);
}