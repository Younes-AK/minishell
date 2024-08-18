/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:19:32 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 11:16:09 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_orignal_space(char *input, int *index)
{
	int		i;
	int		j;
	bool	in_squotes;
	bool	in_dquotes;

	j = 0;
	i = *index;
	in_squotes = false;
	in_dquotes = false;
	while (i < (int)ft_strlen(input))
	{
		if (input[i] == '\'')
			in_squotes = !in_squotes;
		else if (input[i] == '"')
			in_dquotes = !in_dquotes;
		if (! (is_whait_spaces(input[i]) && is_whait_spaces(input[i + 1])
				&& !in_squotes && !in_dquotes))
			j++;
		i++;
	}
	return (j);
}

char	*process_spaces(char *input, int *i, int j)
{
	bool	in_squotes;
	bool	in_dquotes;
	char	*ret;

	in_squotes = false;
	in_dquotes = false;
	ret = safe_allocation(sizeof(char), j + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (input[*i])
	{
		if (input[*i] == '"')
			in_dquotes = !in_dquotes;
		else if (input[*i] == '\'')
			in_squotes = !in_squotes;
		while (is_whait_spaces(input[*i]) && is_whait_spaces(input[*i + 1])
			&& !in_squotes && !in_dquotes)
			(*i)++;
		ret[j++] = input[(*i)++];
	}
	while (j > 0 && ret[j - 1] == ' ')
		j--;
	ret[j] = '\0';
	return (ret);
}

void	process_characters(t_prog *p, int len, char *quote)
{
	while (p->tmp[p->i] && p->j < len)
	{
		if ((p->tmp[p->i] == '\'' || p->tmp[p->i] == '\"') && !*quote)
			*quote = p->tmp[p->i];
		else if (p->tmp[p->i] == *quote)
			*quote = 0;
		if (!*quote && is_operator(p->tmp[p->i]))
		{
			if (p->i != 0 && !is_whait_spaces(p->tmp[p->i - 1])
				&& !is_operator(p->tmp[p->i - 1]))
				p->cmd_line[p->j++] = ' ';
			p->cmd_line[p->j++] = p->tmp[p->i];
			if (!is_whait_spaces(p->tmp[p->i + 1])
				&& !is_operator(p->tmp[p->i + 1]) && p->tmp[p->i + 1])
				p->cmd_line[p->j++] = ' ';
		}
		else
			p->cmd_line[p->j++] = (!*quote && is_whait_spaces(p->tmp[p->i]))
				? ' ' : p->tmp[p->i];
		p->i++;
	}
	p->cmd_line[p->j] = '\0';
}

void	free_envirement(t_prog	*p)
{
	free_env_list(p->env_list);
	free_env_list(p->secret_env);
}

void	ft_free_lists(t_prog *prog, char *state)
{
	if (!ft_strcmp(state, "exit"))
	{
		free_envirement(prog);
		free_tok_list(prog->list_tok);
		free_tok_list(prog->new_tok_list);
		free_exec_list(prog->exec_list);
		exit(EXIT_FAILURE);
	}
	free_tok_list(prog->list_tok);
	free_tok_list(prog->new_tok_list);
	free_exec_list(prog->exec_list);
}
