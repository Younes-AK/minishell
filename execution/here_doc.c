/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:13:45 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/27 23:20:00 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define TMP_FILE	"/tmp/minihell_temporary_file"

extern int	g_exit_status;

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
			return (g_exit_status = 1, free(delemitre), close(tmp_fd), false);
		if (ft_strcmp (input, delemitre) == 0)
		{
			g_exit_status = 0;
			return (free(delemitre), close(tmp_fd), free(input), true);
		}
		if (to_expand && is_env_var(input))
			input = expand_herdoc(input, p->env_list, p);
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

	i = 0;
	p->filename = generate_name(j, p);
	while (node->redir[i])
	{
		if (!ft_strcmp(node->redir[i], "<<"))
		{
			fd = create_temporary_file(p->filename);
			if (fd < 0)
				return (false);
			if (!get_and_write_input(fd, node->redir[i + 1], p))
				return (close(fd), false);
			free(node->redir[i + 1]);
			node->redir[i + 1] = ft_strdup(p->filename);
			close(fd);
		}
		i += 2;
	}
	return (true);
}

bool	ft_heredoc(t_prog *p)
{
	t_var_hold	hold;

	1 && (hold.ret = true, hold.node = p->exec_list->head);
	1 && (p->temp_files = NULL, p->i = 0);
	while (hold.node)
	{
		if (hold.node->redir)
		{
			if (here_doc_input(hold.node, p, p->i))
			{
				hold.tmp_file = add_temp_file(p->filename, p);
				append_temp_file(&p->temp_files, hold.tmp_file);
			}
			else
			{
				hold.ret = false;
				break ;
			}
		}
		1 && (free(p->filename), hold.node = hold.node->next, p->i++);
	}
	if (p->to_restart_stdin == 1)
		1 && (dup2(p->original_stdin, 0), p->to_restart_stdin = 0);
	tcgetattr(STDIN_FILENO, term_input_output());
	return (hold.ret);
}
