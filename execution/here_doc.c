/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:13:45 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 11:31:46 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define TMP_FILE	"/tmp/minihell_temporary_file"

static bool	get_and_write_input(int tmp_fd, char *eof, t_prog *p)
{
	char	*input;
	char	*delemitre;
	bool	to_expand;

	to_expand = true;
	if (is_quote(*eof) || is_quote(eof[ft_strlen(eof) - 1]))
		to_expand = false;
	delemitre = remove_qoutes(eof, p);
	while (true)
	{
		sig_here_doc(p);
		input = readline("> ");
		if (!input)
			return (close(tmp_fd), true);
		if (ft_strcmp(input, delemitre) == 0)
		{
			return (free(delemitre), close(tmp_fd), free(input), true);
		}
		if (to_expand && is_env_var(input))
			input = replace(input, p->env_list);
		ft_putendl_fd(input, tmp_fd);
		free(input);
	}
	return (true);
}

static int	create_temporary_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_putstr_fd("Error creating temporary file\n", 2);
		return (-1);
	}
	return (fd);
}

char	*generate_name(int i, t_prog *p)
{
	char	*ret;
	char	*ka_pa;

	ka_pa = ft_itoa(i);
	ret = ft_strjoin(TMP_FILE, ka_pa);
	if (!ret)
		ft_free_lists(p, "exit");
	free(ka_pa);
	return (ret);
}

bool	here_doc_input(t_exec_node *node, t_prog *p, int j)
{
	int		i;
	int		fd;
	bool	ret;

	i = 0;
	p->filename = generate_name(j, p);
	ret = false;
	while (node->redir[i])
	{
		if (!ft_strcmp(node->redir[i], "<<"))
		{
			fd = create_temporary_file(p->filename);
			if (fd < 0)
				return (false);
			get_and_write_input(fd, node->redir[i + 1], p);
			free(node->redir[i + 1]);
			node->redir[i + 1] = ft_strdup(p->filename);
			close(fd);
			ret = true;
		}
		i += 2;
	}
	return (ret);
}

void	ft_heredoc(t_prog *p)
{
	t_exec_node		*node;
	t_temp_files	*tmp_file;

	p->i = 0;
	node = p->exec_list->head;
	p->temp_files = NULL;
	while (node)
	{
		if (node->redir)
		{
			if (here_doc_input(node, p, p->i))
			{
				tmp_file = add_temp_file(p->filename, p);
				append_temp_file(&p->temp_files, tmp_file);
			}
		}
		free(p->filename);
		node = node->next;
		p->i++;
	}
	if (p->to_restart_stdin == 1)
	{
		dup2(p->original_stdin, 0);
		p->to_restart_stdin = 0;
	}
}
